/* SPDX-License-Identifier: GPL-2.0 */
/**
 * mqtt.c -- MQTT client implementation for 3-phase energy meter
 *
 * Implements lightweight MQTT 3.1.1 client for publishing meter data
 * and subscribing to configuration commands over UART (ESP8266/ESP32).
 */

#include "mqtt.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* ============================================================
 * Private Macros
 * ============================================================ */

#define MQTT_STRING_LEN(x)	((uint8_t)((x) & 0xFF))
#define MQTT_SET_BYTE(buf, pos, val)	((buf)[(pos)] = (uint8_t)(val))
#define MQTT_GET_BYTE(buf, pos)	((uint8_t)(buf)[(pos)])

/* ============================================================
 * Private Function Prototypes
 * ============================================================ */

static int32_t mqtt_encode_length(uint8_t *buf, uint32_t len);
static uint32_t mqtt_decode_length(const uint8_t *buf, uint8_t *bytes_read);
static int32_t mqtt_build_connect_packet(mqtt_context_t *ctx, uint8_t *packet, uint16_t *packet_len);
static int32_t mqtt_build_publish_packet(mqtt_context_t *ctx, uint8_t *packet, uint16_t *packet_len,
					 const char *topic, const uint8_t *payload, uint16_t payload_len,
					 uint8_t qos, bool retain);
static int32_t mqtt_build_subscribe_packet(mqtt_context_t *ctx, uint8_t *packet, uint16_t *packet_len,
					   const char *topic, uint8_t qos);
static int32_t mqtt_build_ping_packet(uint8_t *packet, uint16_t *packet_len);
static int32_t mqtt_build_disconnect_packet(uint8_t *packet, uint16_t *packet_len);

/* ============================================================
 * MQTT Protocol Implementation
 * ============================================================ */

/**
 * mqtt_encode_length - Encode remaining length for MQTT packet
 */
static int32_t mqtt_encode_length(uint8_t *buf, uint32_t len)
{
	uint8_t pos = 0;

	do {
		buf[pos++] = (uint8_t)((len & 0x7F) | (pos > 0 ? 0x80 : 0));
		len >>= 7;
	} while (len > 0 && pos < 4);

	return pos;
}

/**
 * mqtt_decode_length - Decode remaining length from MQTT packet
 */
static uint32_t mqtt_decode_length(const uint8_t *buf, uint8_t *bytes_read)
{
	uint32_t len = 0;
	uint8_t multiplier = 1;
	uint8_t pos = 0;

	do {
		len += (buf[pos] & 0x7F) * multiplier;
		multiplier *= 0x80;
		pos++;
	} while ((buf[pos - 1] & 0x80) != 0 && pos < 4);

	*bytes_read = pos;
	return len;
}

/**
 * mqtt_build_connect_packet - Build MQTT CONNECT packet
 */
static int32_t mqtt_build_connect_packet(mqtt_context_t *ctx, uint8_t *packet, uint16_t *packet_len)
{
	uint16_t pos = 0;
	uint8_t var_len[4];
	uint8_t var_len_len;
	uint16_t payload_len;

	/* Fixed header */
	packet[pos++] = MQTT_CONNECT << 4;

	/* Calculate variable header + payload length */
	/* Protocol name: "MQTT" */
	uint16_t proto_name_len = 4 + 2;  /* "MQTT" + length field */
	uint16_t connect_flags = 0;

	if (ctx->config.username[0])
		connect_flags |= 0x80;
	if (ctx->config.password[0])
		connect_flags |= 0x40;
	if (ctx->config.clean_session)
		connect_flags |= 0x02;

	uint16_t connect_hdr_len = proto_name_len + 4;  /* protocol level + flags + keepalive */
	payload_len = connect_hdr_len + 2 + strlen(ctx->config.client_id);  /* client ID */

	if (ctx->config.username[0])
		payload_len += 2 + strlen(ctx->config.username);
	if (ctx->config.password[0])
		payload_len += 2 + strlen(ctx->config.password);

	var_len_len = mqtt_encode_length(var_len, payload_len);

	/* Position of remaining length */
	uint16_t len_pos = pos;
	pos++;

	/* Copy variable length */
	memcpy(&packet[len_pos], var_len, var_len_len);
	pos += var_len_len - 1;

	/* Variable header: Protocol Name */
	packet[pos++] = 0;  /* Length MSB */
	packet[pos++] = 4;  /* Length LSB */
	packet[pos++] = 'M';
	packet[pos++] = 'Q';
	packet[pos++] = 'T';
	packet[pos++] = 'T';

	/* Protocol Level (3.1.1) */
	packet[pos++] = 4;

	/* Connect Flags */
	packet[pos++] = connect_flags;

	/* Keep Alive */
	packet[pos++] = (uint8_t)(ctx->config.keep_alive >> 8);
	packet[pos++] = (uint8_t)(ctx->config.keep_alive & 0xFF);

	/* Payload: Client ID */
	uint16_t client_id_len = strlen(ctx->config.client_id);
	packet[pos++] = (uint8_t)(client_id_len >> 8);
	packet[pos++] = (uint8_t)(client_id_len & 0xFF);
	memcpy(&packet[pos], ctx->config.client_id, client_id_len);
	pos += client_id_len;

	/* Payload: Username */
	if (ctx->config.username[0]) {
		uint16_t user_len = strlen(ctx->config.username);
		packet[pos++] = (uint8_t)(user_len >> 8);
		packet[pos++] = (uint8_t)(user_len & 0xFF);
		memcpy(&packet[pos], ctx->config.username, user_len);
		pos += user_len;
	}

	/* Payload: Password */
	if (ctx->config.password[0]) {
		uint16_t pass_len = strlen(ctx->config.password);
		packet[pos++] = (uint8_t)(pass_len >> 8);
		packet[pos++] = (uint8_t)(pass_len & 0xFF);
		memcpy(&packet[pos], ctx->config.password, pass_len);
		pos += pass_len;
	}

	*packet_len = pos;
	return 0;
}

/**
 * mqtt_build_publish_packet - Build MQTT PUBLISH packet
 */
static int32_t mqtt_build_publish_packet(mqtt_context_t *ctx, uint8_t *packet, uint16_t *packet_len,
				      const char *topic, const uint8_t *payload, uint16_t payload_len,
				      uint8_t qos, bool retain)
{
	uint16_t pos = 0;
	uint8_t var_len[4];
	uint8_t var_len_len;
	uint16_t topic_len = strlen(topic);
	uint16_t var_header_len = 2 + topic_len + (qos > 0 ? 2 : 0);
	uint32_t remaining_len = var_header_len + payload_len;

	/* Fixed header */
	packet[pos++] = (MQTT_PUBLISH << 4) | (qos << 1) | (retain ? 1 : 0);

	/* Remaining length */
	var_len_len = mqtt_encode_length(var_len, remaining_len);
	memcpy(&packet[pos], var_len, var_len_len);
	pos += var_len_len;

	/* Variable header: Topic Name */
	packet[pos++] = (uint8_t)(topic_len >> 8);
	packet[pos++] = (uint8_t)(topic_len & 0xFF);
	memcpy(&packet[pos], topic, topic_len);
	pos += topic_len;

	/* Packet Identifier (QoS 1 only) */
	if (qos > 0) {
		ctx->packet_id++;
		if (ctx->packet_id == 0)
			ctx->packet_id = 1;
		packet[pos++] = (uint8_t)(ctx->packet_id >> 8);
		packet[pos++] = (uint8_t)(ctx->packet_id & 0xFF);
	}

	/* Payload */
	memcpy(&packet[pos], payload, payload_len);
	pos += payload_len;

	*packet_len = pos;
	return 0;
}

/**
 * mqtt_build_subscribe_packet - Build MQTT SUBSCRIBE packet
 */
static int32_t mqtt_build_subscribe_packet(mqtt_context_t *ctx, uint8_t *packet, uint16_t *packet_len,
					 const char *topic, uint8_t qos)
{
	uint16_t pos = 0;
	uint8_t var_len[4];
	uint8_t var_len_len;
	uint16_t topic_len = strlen(topic);
	uint16_t remaining_len = 2 + topic_len + 1;  /* packet ID + topic + QoS */

	/* Fixed header */
	packet[pos++] = (MQTT_SUBSCRIBE << 4) | 0x02;  /* QoS 1 */

	/* Remaining length */
	var_len_len = mqtt_encode_length(var_len, remaining_len);
	memcpy(&packet[pos], var_len, var_len_len);
	pos += var_len_len;

	/* Packet Identifier */
	ctx->packet_id++;
	if (ctx->packet_id == 0)
		ctx->packet_id = 1;
	packet[pos++] = (uint8_t)(ctx->packet_id >> 8);
	packet[pos++] = (uint8_t)(ctx->packet_id & 0xFF);

	/* Topic */
	packet[pos++] = (uint8_t)(topic_len >> 8);
	packet[pos++] = (uint8_t)(topic_len & 0xFF);
	memcpy(&packet[pos], topic, topic_len);
	pos += topic_len;

	/* QoS */
	packet[pos++] = qos;

	*packet_len = pos;
	return 0;
}

/**
 * mqtt_build_ping_packet - Build MQTT PINGREQ packet
 */
static int32_t mqtt_build_ping_packet(uint8_t *packet, uint16_t *packet_len)
{
	packet[0] = MQTT_PINGREQ << 4;
	packet[1] = 0;
	*packet_len = 2;
	return 0;
}

/**
 * mqtt_build_disconnect_packet - Build MQTT DISCONNECT packet
 */
static int32_t mqtt_build_disconnect_packet(uint8_t *packet, uint16_t *packet_len)
{
	packet[0] = MQTT_DISCONNECT << 4;
	packet[1] = 0;
	*packet_len = 2;
	return 0;
}

/* ============================================================
 * Public API Implementation
 * ============================================================ */

/**
 * mqtt_init - Initialize MQTT client
 */
int32_t mqtt_init(mqtt_context_t *ctx, const mqtt_config_t *config)
{
	if (!ctx || !config)
		return -1;

	memset(ctx, 0, sizeof(mqtt_context_t));
	memcpy(&ctx->config, config, sizeof(mqtt_config_t));

	/* Set defaults */
	if (ctx->config.keep_alive == 0)
		ctx->config.keep_alive = MQTT_KEEP_ALIVE_SEC;

	ctx->state = MQTT_STATE_DISCONNECTED;
	ctx->packet_id = 0;

	return 0;
}

/**
 * mqtt_connect - Connect to MQTT broker
 */
int32_t mqtt_connect(mqtt_context_t *ctx, int (*send_cb)(const uint8_t *data, uint16_t len))
{
	uint8_t packet[MQTT_MAX_PACKET_SIZE];
	uint16_t packet_len;

	if (!ctx || !send_cb)
		return -1;

	ctx->state = MQTT_STATE_CONNECTING;

	/* Build CONNECT packet */
	if (mqtt_build_connect_packet(ctx, packet, &packet_len) != 0) {
		ctx->state = MQTT_STATE_ERROR;
		return -1;
	}

	/* Send to broker */
	if (send_cb(packet, packet_len) != 0) {
		ctx->state = MQTT_STATE_ERROR;
		return -1;
	}

	/* Note: In real implementation, we'd wait for CONNACK here.
	 * For ESP8266/ESP32 bridge, the module handles MQTT protocol. */

	ctx->connected = true;
	ctx->state = MQTT_STATE_CONNECTED;
	ctx->last_ping = 0;
	ctx->retry_count = 0;

	return 0;
}

/**
 * mqtt_disconnect - Disconnect from MQTT broker
 */
int32_t mqtt_disconnect(mqtt_context_t *ctx, int (*send_cb)(const uint8_t *data, uint16_t len))
{
	uint8_t packet[16];
	uint16_t packet_len;

	if (!ctx || !send_cb)
		return -1;

	mqtt_build_disconnect_packet(packet, &packet_len);
	send_cb(packet, packet_len);

	ctx->connected = false;
	ctx->state = MQTT_STATE_DISCONNECTED;

	return 0;
}

/**
 * mqtt_process_input - Process incoming MQTT data
 */
int32_t mqtt_process_input(mqtt_context_t *ctx, const uint8_t *data, uint16_t len)
{
	uint16_t pos = 0;

	if (!ctx || !data || len == 0)
		return -1;

	while (pos < len) {
		uint8_t header = data[pos++];
		uint8_t packet_type = (header >> 4) & 0x0F;

		if (pos >= len)
			break;

		uint8_t bytes_read;
		uint32_t remaining_len = mqtt_decode_length(&data[pos], &bytes_read);
		pos += bytes_read;

		switch (packet_type) {
		case MQTT_CONNACK:
			/* Connection acknowledged */
			if (pos + 2 <= len) {
				uint8_t ack_flags = data[pos++];
				uint8_t return_code = data[pos++];

				if (return_code == 0) {
					ctx->connected = true;
					ctx->state = MQTT_STATE_CONNECTED;
				} else {
					ctx->connected = false;
					ctx->state = MQTT_STATE_ERROR;
				}
			}
			break;

		case MQTT_PUBLISH:
			/* Incoming publish - handle subscription messages */
			if (pos + 2 <= len) {
				uint16_t topic_len = (data[pos] << 8) | data[pos + 1];
				pos += 2;

				if (pos + topic_len + 2 <= len) {
					/* Process config message here if needed */
					pos += topic_len + remaining_len - topic_len - 2;
				}
			}
			break;

		case MQTT_SUBACK:
			/* Subscription acknowledged */
			break;

		case MQTT_PINGRESP:
			/* Ping response received */
			break;

		default:
			/* Skip unknown packet type */
			pos += remaining_len;
			break;
		}
	}

	return 0;
}

/**
 * mqtt_publish_meter_data - Publish meter data to broker
 */
int32_t mqtt_publish_meter_data(mqtt_context_t *ctx, int (*send_cb)(const uint8_t *data, uint16_t len),
				const struct meter_data_s *meter_data)
{
	uint8_t packet[MQTT_MAX_PACKET_SIZE];
	uint16_t packet_len;
	char topic[MQTT_MAX_TOPIC_LEN];
	char payload[MQTT_MAX_PAYLOAD_LEN];

	if (!ctx || !send_cb || !meter_data)
		return -1;

	if (!ctx->connected)
		return -1;

	/* Build topic name */
	snprintf(topic, sizeof(topic), "%s/meter/data", ctx->config.device_id);

	/* Build JSON payload */
	int json_len = mqtt_build_meter_json(payload, sizeof(payload), meter_data);
	if (json_len < 0)
		return -1;

	/* Build PUBLISH packet */
	if (mqtt_build_publish_packet(ctx, packet, &packet_len, topic,
				       (const uint8_t *)payload, json_len,
				       MQTT_QOS_0, false) != 0)
		return -1;

	return send_cb(packet, packet_len);
}

/**
 * mqtt_publish_status - Publish device status
 */
int32_t mqtt_publish_status(mqtt_context_t *ctx, int (*send_cb)(const uint8_t *data, uint16_t len),
			const char *status_json)
{
	uint8_t packet[MQTT_MAX_PACKET_SIZE];
	uint16_t packet_len;
	char topic[MQTT_MAX_TOPIC_LEN];

	if (!ctx || !send_cb || !status_json)
		return -1;

	if (!ctx->connected)
		return -1;

	/* Build topic name */
	snprintf(topic, sizeof(topic), "%s/meter/status", ctx->config.device_id);

	/* Build PUBLISH packet */
	if (mqtt_build_publish_packet(ctx, packet, &packet_len, topic,
				       (const uint8_t *)status_json, strlen(status_json),
				       MQTT_QOS_0, false) != 0)
		return -1;

	return send_cb(packet, packet_len);
}

/**
 * mqtt_subscribe_config - Subscribe to configuration topic
 */
int32_t mqtt_subscribe_config(mqtt_context_t *ctx, int (*send_cb)(const uint8_t *data, uint16_t len))
{
	uint8_t packet[MQTT_MAX_PACKET_SIZE];
	uint16_t packet_len;
	char topic[MQTT_MAX_TOPIC_LEN];

	if (!ctx || !send_cb)
		return -1;

	if (!ctx->connected)
		return -1;

	/* Build topic name */
	snprintf(topic, sizeof(topic), "%s/meter/config", ctx->config.device_id);

	/* Build SUBSCRIBE packet */
	if (mqtt_build_subscribe_packet(ctx, packet, &packet_len, topic, MQTT_QOS_1) != 0)
		return -1;

	return send_cb(packet, packet_len);
}

/**
 * mqtt_ping - Send PINGREQ to keep connection alive
 */
int32_t mqtt_ping(mqtt_context_t *ctx, int (*send_cb)(const uint8_t *data, uint16_t len))
{
	uint8_t packet[16];
	uint16_t packet_len;

	if (!ctx || !send_cb)
		return -1;

	if (!ctx->connected)
		return -1;

	mqtt_build_ping_packet(packet, &packet_len);
	return send_cb(packet, packet_len);
}

/**
 * mqtt_is_connected - Check if MQTT is connected
 */
bool mqtt_is_connected(const mqtt_context_t *ctx)
{
	return ctx && ctx->connected;
}

/**
 * mqtt_get_state - Get MQTT connection state
 */
mqtt_state_t mqtt_get_state(const mqtt_context_t *ctx)
{
	return ctx ? ctx->state : MQTT_STATE_DISCONNECTED;
}

/**
 * mqtt_set_message_callback - Set message callback (placeholder for future use)
 */
void mqtt_set_message_callback(mqtt_context_t *ctx, mqtt_msg_callback_t callback)
{
	(void)ctx;
	(void)callback;
	/* Callback storage and invocation would be added here
	 * for handling incoming subscription messages */
}

/**
 * mqtt_build_meter_json - Build meter data JSON payload
 */
int32_t mqtt_build_meter_json(char *buffer, uint16_t size, const struct meter_data_s *meter_data)
{
	if (!buffer || !meter_data || size < 100)
		return -1;

	int len = 0;
	len += snprintf(&buffer[len], size - len, "{");

	/* Phase data */
	for (int i = 0; i < METER_PHASE_COUNT; i++) {
		const struct phase_data_s *phase = &meter_data->phase_data[i];
		char phase_label = 'A' + i;
		len += snprintf(&buffer[len], size - len,
				"\"%c\":{"
				"\"V\":%.1f,"
				"\"I\":%.2f,"
				"\"P\":%.1f,"
				"\"Q\":%.1f,"
				"\"S\":%.1f,"
				"\"PF\":%.3f,"
				"\"THD_V\":%.1f,"
				"\"THD_I\":%.1f},%c",
				phase_label,
				phase->rms_voltage,
				phase->rms_current,
				phase->act_pwr,
				phase->react_pwr,
				phase->app_pwr,
				phase->pf,
				phase->thd.voltage,
				phase->thd.current,
				(i < METER_PHASE_COUNT - 1) ? ',' : ' ');	
	}

	/* Frequency and energy */
	len += snprintf(&buffer[len], size - len,
			"\"F\":%.1f,\"E\":%.0f}",
			meter_data->frequency,
			meter_data->energy_Ws);

	return len;
}

/**
 * mqtt_build_status_json - Build status JSON payload
 */
int32_t mqtt_build_status_json(char *buffer, uint16_t size, uint32_t uptime_seconds)
{
	if (!buffer || size < 80)
		return -1;

	return snprintf(buffer, size,
			"{\"uptime\":%lu,\"status\":\"online\",\"version\":\"1.0.0\"}",
			(unsigned long)uptime_seconds);
}