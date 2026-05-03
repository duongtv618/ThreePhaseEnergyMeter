// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "build_x86/vendor/unity/src/unity.h"
#include "User/lib/inc/modbus_rtu.h"

static uint16_t crc16(const uint8_t *buf, uint16_t len)
{
    static const uint16_t lut[256] = {
        0x0000,0xC0C1,0xC181,0x0140,0xC301,0x03C0,0x0280,0xC241,
        0xC601,0x06C0,0x0780,0xC741,0x0500,0xC5C1,0xC481,0x0440,
        0xCC01,0x0CC0,0x0D80,0xCD41,0x0F00,0xCFC1,0xCE81,0x0E40,
        0x0A00,0xCAC1,0xCB81,0x0B40,0xC901,0x09C0,0x0880,0xC841,
        0xD801,0x18C0,0x1980,0xD941,0x1B00,0xDBC1,0xDA81,0x1A40,
        0x1E00,0xDEC1,0xDF81,0x1F40,0xDD01,0x1DC0,0x1C80,0xDC41,
        0x1400,0xD4C1,0xD581,0x1540,0xD701,0x17C0,0x1680,0xD641,
        0xD201,0x12C0,0x1380,0xD341,0x1100,0xD1C1,0xD081,0x1040,
        0xF001,0x30C0,0x3180,0xF141,0x3300,0xF3C1,0xF281,0x3240,
        0x3600,0xF6C1,0xF781,0x3740,0xF501,0x35C0,0x3480,0xF441,
        0x3C00,0xFCC1,0xFD81,0x3D40,0xFF01,0x3FC0,0x3E80,0xFE41,
        0xFA01,0x3AC0,0x3B80,0xFB41,0x3900,0xF9C1,0xF881,0x3840,
        0x2800,0xE8C1,0xE981,0x2940,0xEB01,0x2BC0,0x2A80,0xEA41,
        0xEE01,0x2EC0,0x2F80,0xEF41,0x2D00,0xEDC1,0xEC81,0x2C40,
        0xE401,0x24C0,0x2580,0xE541,0x2700,0xE7C1,0xE681,0x2640,
        0x2200,0xE2C1,0xE381,0x2340,0xE101,0x21C0,0x2080,0xE041,
        0xA001,0x60C0,0x6180,0xA141,0x6300,0xA3C1,0xA281,0x6240,
        0x6600,0xA6C1,0xA781,0x6740,0xA501,0x65C0,0x6480,0xA441,
        0x6C00,0xACC1,0xAD81,0x6D40,0xAF01,0x6FC0,0x6E80,0xAE41,
        0xAA01,0x6AC0,0x6B80,0xAB41,0x6900,0xA9C1,0xA881,0x6840,
        0x7800,0xB8C1,0xB981,0x7940,0xBB01,0x7BC0,0x7A80,0xBA41,
        0xBE01,0x7EC0,0x7F80,0xBF41,0x7D00,0xBDC1,0xBC81,0x7C40,
        0xB401,0x74C0,0x7580,0xB541,0x7700,0xB7C1,0xB681,0x7640,
        0x7200,0xB2C1,0xB381,0x7340,0xB101,0x71C0,0x7080,0xB041,
        0x5000,0x90C1,0x9181,0x5140,0x9301,0x53C0,0x5280,0x9241,
        0x9601,0x56C0,0x5780,0x9741,0x5500,0x95C1,0x9481,0x5440,
        0x9C01,0x5CC0,0x5D80,0x9D41,0x5F00,0x9FC1,0x9E81,0x5E40,
        0x5A00,0x9AC1,0x9B81,0x5B40,0x9901,0x59C0,0x5880,0x9841,
        0x8801,0x48C0,0x4980,0x8941,0x4B00,0x8BC1,0x8A81,0x4A40,
        0x4E00,0x8EC1,0x8F81,0x4F40,0x8D01,0x4DC0,0x4C80,0x8C41,
        0x4400,0x84C1,0x8581,0x4540,0x8701,0x47C0,0x4680,0x8641,
        0x8201,0x42C0,0x4380,0x8341,0x4100,0x81C1,0x8081,0x4040,
    };
    uint16_t crc = 0xFFFF;
    while (len--) crc = (crc >> 8) ^ lut[(crc ^ *buf++) & 0xFF];
    return crc;
}

static uint16_t build_frame(uint8_t *buf, uint8_t addr, uint8_t fc,
                             uint16_t reg, uint16_t val)
{
    buf[0] = addr;
    buf[1] = fc;
    buf[2] = (uint8_t)(reg >> 8);
    buf[3] = (uint8_t)(reg & 0xFF);
    buf[4] = (uint8_t)(val >> 8);
    buf[5] = (uint8_t)(val & 0xFF);
    uint16_t c = crc16(buf, 6);
    buf[6] = (uint8_t)(c & 0xFF);
    buf[7] = (uint8_t)(c >> 8);
    return 8;
}

static void inject_and_poll(uint8_t *frame, uint16_t len)
{
    (void)frame; (void)len;
}

void setUp(void)
{
    struct mb_data_store *ds = mb_get_data_store();
    memset(ds, 0, sizeof(*ds));
}

void tearDown(void)
{}
void test_crc16_known_vector(void)
{
    uint8_t frame[8];
    build_frame(frame, 0x01, 0x03, 0x0000, 0x0001);

    uint16_t crc = crc16(frame, 6);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )(((uint8_t)(crc & 0xFF))), (UNITY_INT)(UNITY_INT8 )((frame[6])), (
   ((void *)0)
   ), (UNITY_UINT)(125), UNITY_DISPLAY_STYLE_HEX8);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )(((uint8_t)(crc >> 8))), (UNITY_INT)(UNITY_INT8 )((frame[7])), (
   ((void *)0)
   ), (UNITY_UINT)(126), UNITY_DISPLAY_STYLE_HEX8);
}

void test_crc16_single_byte(void)
{
    uint8_t data = 0x01;
    uint16_t crc = crc16(&data, 1);
    do { if (((0x0000) != (crc)))
{ } else { UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((133))); } } while (0);
    do { if (((0xFFFF) != (crc)))
{ } else { UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((134))); } } while (0);
}

void test_crc16_all_zeros(void)
{
    uint8_t data[4] = {0};
    uint16_t crc = crc16(data, 4);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x2400)), (UNITY_INT)(UNITY_INT16)((crc)), (
   ((void *)0)
   ), (UNITY_UINT)(142), UNITY_DISPLAY_STYLE_HEX16);
}

void test_crc16_bit_flip_changes_crc(void)
{
    uint8_t frame1[6] = {0x01,0x03,0x00,0x00,0x00,0x01};
    uint8_t frame2[6] = {0x01,0x03,0x00,0x00,0x00,0x02};
    do { if (((crc16(frame1,6)) != (crc16(frame2,6))))
{ } else { UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((149))); } } while (0);
}

void test_mb_float_roundtrip_50Hz(void)
{
    mb_set_float(0, 50.0f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((mb_get_float(0))), (
   ((void *)0)
   ), (UNITY_UINT)(159));
}

void test_mb_float_roundtrip_negative(void)
{
    mb_set_float(2, -230.5f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((-230.5f)), (UNITY_FLOAT)((mb_get_float(2))), (
   ((void *)0)
   ), (UNITY_UINT)(165));
}

void test_mb_float_roundtrip_zero(void)
{
    mb_set_float(4, 0.0f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-9f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((mb_get_float(4))), (
   ((void *)0)
   ), (UNITY_UINT)(171));
}

void test_mb_float_roundtrip_large(void)
{
    mb_set_float(6, 999999.0f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((1.0f)), (UNITY_FLOAT)((999999.0f)), (UNITY_FLOAT)((mb_get_float(6))), (
   ((void *)0)
   ), (UNITY_UINT)(177));
}

void test_mb_float_uses_two_registers(void)
{
    mb_set_float(0, 1.0f);

    uint16_t hi = mb_get_holding_reg(0);
    uint16_t lo = mb_get_holding_reg(1);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x3F80)), (UNITY_INT)(UNITY_INT16)((hi)), (
   ((void *)0)
   ), (UNITY_UINT)(186), UNITY_DISPLAY_STYLE_HEX16);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((lo)), (
   ((void *)0)
   ), (UNITY_UINT)(187), UNITY_DISPLAY_STYLE_HEX16);
}

void test_mb_float_big_endian_word_order(void)
{
    mb_set_float(0, 50.0f);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x4248)), (UNITY_INT)(UNITY_INT16)((mb_get_holding_reg(0))), (
   ((void *)0)
   ), (UNITY_UINT)(194), UNITY_DISPLAY_STYLE_HEX16);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((mb_get_holding_reg(1))), (
   ((void *)0)
   ), (UNITY_UINT)(195), UNITY_DISPLAY_STYLE_HEX16);
}

void test_holding_reg_set_and_get(void)
{
    mb_set_holding_reg(0, 0x1234);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x1234)), (UNITY_INT)(UNITY_INT16)((mb_get_holding_reg(0))), (
   ((void *)0)
   ), (UNITY_UINT)(205), UNITY_DISPLAY_STYLE_HEX16);
}

void test_holding_reg_boundary_last(void)
{
    uint16_t last = (0x004A + ((((0x0128 + 2) + 2)) + 2)) - 1;
    mb_set_holding_reg(last, 0xABCD);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xABCD)), (UNITY_INT)(UNITY_INT16)((mb_get_holding_reg(last))), (
   ((void *)0)
   ), (UNITY_UINT)(212), UNITY_DISPLAY_STYLE_HEX16);
}

void test_holding_reg_out_of_bounds_read_returns_zero(void)
{
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((mb_get_holding_reg((0x004A + ((((0x0128 + 2) + 2)) + 2))))), (
   ((void *)0)
   ), (UNITY_UINT)(217), UNITY_DISPLAY_STYLE_HEX16);
}

void test_holding_reg_out_of_bounds_write_no_crash(void)
{
    mb_set_holding_reg((0x004A + ((((0x0128 + 2) + 2)) + 2)), 0xDEAD);
    longjmp(Unity.AbortFrame, 1);
}

void test_holding_reg_independent_addresses(void)
{
    mb_set_holding_reg(0, 0x0001);
    mb_set_holding_reg(1, 0x0002);
    mb_set_holding_reg(2, 0x0003);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0001)), (UNITY_INT)(UNITY_INT16)((mb_get_holding_reg(0))), (
   ((void *)0)
   ), (UNITY_UINT)(231), UNITY_DISPLAY_STYLE_HEX16);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0002)), (UNITY_INT)(UNITY_INT16)((mb_get_holding_reg(1))), (
   ((void *)0)
   ), (UNITY_UINT)(232), UNITY_DISPLAY_STYLE_HEX16);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0003)), (UNITY_INT)(UNITY_INT16)((mb_get_holding_reg(2))), (
   ((void *)0)
   ), (UNITY_UINT)(233), UNITY_DISPLAY_STYLE_HEX16);
}

void test_coil_set_true_get_true(void)
{
    mb_set_coil(0,
                  1
                      );
    do { if ((mb_get_coil(0)))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((243))); } } while (0);
}

void test_coil_set_false_get_false(void)
{
    mb_set_coil(0,
                  1
                      );
    mb_set_coil(0,
                  0
                       );
    do { if (!(mb_get_coil(0)))
{ } else { UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((250))); } } while (0);
}

void test_coil_adjacent_bits_independent(void)
{
    mb_set_coil(0,
                  1
                      );
    mb_set_coil(1,
                  0
                       );
    mb_set_coil(2,
                  1
                      );
    do { if ((mb_get_coil(0)))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((258))); } } while (0);
    do { if (!(mb_get_coil(1)))
{ } else { UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((259))); } } while (0);
    do { if ((mb_get_coil(2)))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((260))); } } while (0);
}

void test_coil_boundary_last(void)
{
    mb_set_coil(64 - 1,
                                      1
                                          );
    do { if ((mb_get_coil(64 - 1)))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((266))); } } while (0);
}

void test_coil_out_of_bounds_read_returns_false(void)
{
    do { if (!(mb_get_coil(64)))
{ } else { UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((271))); } } while (0);
}

void test_coil_byte_boundary(void)
{
    mb_set_coil(7,
                  1
                      );
    mb_set_coil(8,
                  0
                       );
    do { if ((mb_get_coil(7)))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((279))); } } while (0);
    do { if (!(mb_get_coil(8)))
{ } else { UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((280))); } } while (0);
}

void test_discrete_input_set_and_get(void)
{
    mb_set_discrete_input(0,
                            1
                                );
    do { if ((mb_get_discrete_input(0)))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((290))); } } while (0);
}

void test_discrete_input_clear(void)
{
    mb_set_discrete_input(5,
                            1
                                );
    mb_set_discrete_input(5,
                            0
                                 );
    do { if (!(mb_get_discrete_input(5)))
{ } else { UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((297))); } } while (0);
}

void test_discrete_input_out_of_bounds_returns_false(void)
{
    do { if (!(mb_get_discrete_input(64)))
{ } else { UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((302))); } } while (0);
}

void test_input_reg_set_and_get(void)
{
    mb_set_input_reg(0, 0x5678);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x5678)), (UNITY_INT)(UNITY_INT16)((mb_get_input_reg(0))), (
   ((void *)0)
   ), (UNITY_UINT)(312), UNITY_DISPLAY_STYLE_HEX16);
}

void test_input_reg_boundary_last(void)
{
    uint16_t last = 32 - 1;
    mb_set_input_reg(last, 0xFFFF);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((mb_get_input_reg(last))), (
   ((void *)0)
   ), (UNITY_UINT)(319), UNITY_DISPLAY_STYLE_HEX16);
}

void test_input_reg_out_of_bounds_returns_zero(void)
{
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((mb_get_input_reg(32))), (
   ((void *)0)
   ), (UNITY_UINT)(324), UNITY_DISPLAY_STYLE_HEX16);
}

void test_get_data_store_not_null(void)
{
    do { if ((((mb_get_data_store())) !=
   ((void *)0)
   ))
{ } else { UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)(((333)))); } } while (0);
}

void test_get_data_store_reflects_set_reg(void)
{
    mb_set_holding_reg(0, 0xCAFE);
    struct mb_data_store *ds = mb_get_data_store();
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xCAFE)), (UNITY_INT)(UNITY_INT16)((ds->holding_regs[0])), (
   ((void *)0)
   ), (UNITY_UINT)(340), UNITY_DISPLAY_STYLE_HEX16);
}

void test_get_data_store_reflects_set_coil(void)
{
    mb_set_coil(3,
                  1
                      );
    struct mb_data_store *ds = mb_get_data_store();
    do { if (((ds->coils[0] >> 3) & 1u))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((347))); } } while (0);
}
void test_fc03_holding_reg_read_via_accessor(void)
{
    mb_set_holding_reg(10, 0x1234);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x1234)), (UNITY_INT)(UNITY_INT16)((mb_get_holding_reg(10))), (
   ((void *)0)
   ), (UNITY_UINT)(363), UNITY_DISPLAY_STYLE_HEX16);
}

void test_fc06_write_single_reg_via_accessor(void)
{
    mb_set_holding_reg(5, 0xABCD);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xABCD)), (UNITY_INT)(UNITY_INT16)((mb_get_holding_reg(5))), (
   ((void *)0)
   ), (UNITY_UINT)(369), UNITY_DISPLAY_STYLE_HEX16);
}

void test_fc05_write_single_coil_via_accessor(void)
{
    mb_set_coil(10,
                   1
                       );
    do { if ((mb_get_coil(10)))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((375))); } } while (0);
    mb_set_coil(10,
                   0
                        );
    do { if (!(mb_get_coil(10)))
{ } else { UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((377))); } } while (0);
}

void test_mb_poll_no_frame_no_crash(void)
{
    mb_poll();
    longjmp(Unity.AbortFrame, 1);
}

void test_mb_enable_tx_rx_no_crash(void)
{
    mb_enable_tx();
    mb_enable_rx();
    longjmp(Unity.AbortFrame, 1);
}