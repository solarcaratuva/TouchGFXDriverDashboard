#include <string.h>

#include "heartbeat_can.h"

static inline uint8_t pack_left_shift_u8(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

static inline uint8_t pack_left_shift_u16(
    uint16_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

static inline uint8_t pack_right_shift_u16(
    uint16_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value >> shift) & mask);
}

static inline uint16_t unpack_left_shift_u16(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint16_t)((uint16_t)(value & mask) << shift);
}

static inline uint8_t unpack_right_shift_u8(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value & mask) >> shift);
}

static inline uint16_t unpack_right_shift_u16(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint16_t)((uint16_t)(value & mask) >> shift);
}


int rivanna3_heart_beat_pack(
    uint8_t *dst_p,
    const struct rivanna3_heart_beat_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    dst_p[0] |= pack_left_shift_u8(src_p->from_telemetry_board, 0u, 0x01u);
    dst_p[0] |= pack_left_shift_u8(src_p->from_wheel_board, 1u, 0x02u);
    dst_p[0] |= pack_left_shift_u8(src_p->from_power_board, 2u, 0x04u);

    return (8);
}

int rivanna3_heart_beat_unpack(
    struct rivanna3_heart_beat_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    dst_p->from_telemetry_board = unpack_right_shift_u8(src_p[0], 0u, 0x01u);
    dst_p->from_wheel_board = unpack_right_shift_u8(src_p[0], 1u, 0x02u);
    dst_p->from_power_board = unpack_right_shift_u8(src_p[0], 2u, 0x04u);

    return (0);
}

int rivanna3_heart_beat_init(struct rivanna3_heart_beat_t *msg_p)
{
    if (msg_p == NULL) return -1;

    memset(msg_p, 0, sizeof(struct rivanna3_heart_beat_t));

    return 0;
}

uint8_t rivanna3_heart_beat_from_telemetry_board_encode(double value)
{
    return (uint8_t)(value);
}

double rivanna3_heart_beat_from_telemetry_board_decode(uint8_t value)
{
    return ((double)value);
}

bool rivanna3_heart_beat_from_telemetry_board_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t rivanna3_heart_beat_from_wheel_board_encode(double value)
{
    return (uint8_t)(value);
}

double rivanna3_heart_beat_from_wheel_board_decode(uint8_t value)
{
    return ((double)value);
}

bool rivanna3_heart_beat_from_wheel_board_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t rivanna3_heart_beat_from_power_board_encode(double value)
{
    return (uint8_t)(value);
}

double rivanna3_heart_beat_from_power_board_decode(uint8_t value)
{
    return ((double)value);
}

bool rivanna3_heart_beat_from_power_board_is_in_range(uint8_t value)
{
    return (value <= 1u);
}
