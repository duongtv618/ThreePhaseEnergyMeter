/* SPDX-License-Identifier: GPL-2.0 */
/**
 * mqtt.h -- MQTT client for 3-phase energy meter
 *
 * Provides lightweight MQTT 3.1.1 client functionality for publishing
 * meter readings and subscribing to configuration commands.
 *
 * Supported features:
 * - Connect to MQTT broker with keep-alive
 * - Publish meter data as JSON payload
 * - Subscribe to configuration topics
 * - QoS 0 and QoS 1 support
 *
 * Topic structure:
 *   - Publish:  <device_id>/meter/data     - meter readings JSON
 *   - Publish:  <device_id>/meter/status  - device status
 *   - Subscribe:<device_id>/meter/config   - configuration commands
 */

#ifndef MQTT_H
#define MQTT_H

#include <stdint.h>
#include <stdbool.h>
#include "share_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================
 * MQTT Configuration
 * ============================================================ */

#define MQTT_MAX_PACKET_SIZE    512
#define MQTT_MAX_TOPIC_LEN      64
#define MQTT_MAX_PAYLOAD_LEN   400
#define MQTT_KEEP_ALIVE_SEC     60
#define MQTT_RECONNECT_DELAY_MS 5000
#define MQTT_MAX_RETRY_COUNT    3

/* MQTT Control Packet Types */
#define MQTT_CONNECT      1
#define MQTT_CONNACK      2
#define MQTT_PUBLISH      3
#define MQTT_PUBACK       4
#define MQTT_SUBSCRIBE    8
#define MQTT_SUBACK       9
#define MQTT_UNSUBSCRIBE 10
#define MQTT_UNSUBACK    11
#define MQTT_PINGREQ      12
#define MQTT_PINGRESP     13
#define MQTT_DISCONNECT  14

/* MQTT QoS Levels */
#define MQTT_QOS_0       0
#define MQTT_QOS_1       1

/* MQTT Connection States */
typedef enum {
	MQTT_STATE_DISCONNECTED = 0,
	MQTT_STATE_CONNECTING,
	MQTT_STATE_CONNECTED,
	MQTT_STATE_ERROR
} mqtt_state_t;

/* ============================================================
 * Data Structures
 * ============================================================ */

/**
 * mqtt_config - MQTT configuration
 */
struct mqtt_config {
	char broker_host[64];
	uint16_t broker_port;
	char client_id[32];
	char username[32];
	char password[32];
	char device_id[16];
	uint16_t keep_alive;
	bool clean_session;
};

/**
 * mqtt_context - MQTT connection context
 */
struct mqtt_context {
	mqtt_state_t state;
	struct mqtt_config config;
	uint16_t packet_id;
	uint32_t last_ping;
	uint8_t retry_count;
	bool connected;
};

typedef struct mqtt_config mqtt_config_t;
typedef struct mqtt_context mqtt_context_t;

/**
 * mqtt_message - MQTT message
 */
struct mqtt_message {
	char topic[MQTT_MAX_TOPIC_LEN];
	uint8_t topic_len;
	uint8_t payload[MQTT_MAX_PAYLOAD_LEN];
	uint16_t payload_len;
	uint8_t qos;
	bool retain;
};

/**
 * mqtt_msg_callback_t - Message callback function type
 */
typedef void (*mqtt_msg_callback_t)(const struct mqtt_message *msg);

/* ============================================================
 * API Functions
 * ============================================================ */

int32_t mqtt_init(mqtt_context_t *ctx, const mqtt_config_t *config);
int32_t mqtt_connect(mqtt_context_t *ctx, int (*send_cb)(const uint8_t *data, uint16_t len));
int32_t mqtt_disconnect(mqtt_context_t *ctx, int (*send_cb)(const uint8_t *data, uint16_t len));
int32_t mqtt_process_input(mqtt_context_t *ctx, const uint8_t *data, uint16_t len);
int32_t mqtt_publish_meter_data(mqtt_context_t *ctx, int (*send_cb)(const uint8_t *data, uint16_t len),
				const struct meter_data_s *meter_data);
int32_t mqtt_publish_status(mqtt_context_t *ctx, int (*send_cb)(const uint8_t *data, uint16_t len),
			const char *status_json);
int32_t mqtt_subscribe_config(mqtt_context_t *ctx, int (*send_cb)(const uint8_t *data, uint16_t len));
int32_t mqtt_ping(mqtt_context_t *ctx, int (*send_cb)(const uint8_t *data, uint16_t len));
bool mqtt_is_connected(const mqtt_context_t *ctx);
mqtt_state_t mqtt_get_state(const mqtt_context_t *ctx);
void mqtt_set_message_callback(mqtt_context_t *ctx, mqtt_msg_callback_t callback);
int32_t mqtt_build_meter_json(char *buffer, uint16_t size, const struct meter_data_s *meter_data);
int32_t mqtt_build_status_json(char *buffer, uint16_t size, uint32_t uptime_seconds);

#ifdef __cplusplus
}
#endif

#endif /* MQTT_H */