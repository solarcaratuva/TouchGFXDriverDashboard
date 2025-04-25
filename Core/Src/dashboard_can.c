#include "dashboard_can.h"

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

int rivanna3_dashboard_commands_pack(
    uint8_t *dst_p,
    const struct rivanna3_dashboard_commands_t *src_p,
    size_t size)
{
    if (size < 1u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 1);

    dst_p[0] |= pack_left_shift_u8(src_p->hazards, 0u, 0x01u);
    dst_p[0] |= pack_left_shift_u8(src_p->left_turn_signal, 1u, 0x02u);
    dst_p[0] |= pack_left_shift_u8(src_p->right_turn_signal, 2u, 0x04u);
    dst_p[0] |= pack_left_shift_u8(src_p->regen_en, 3u, 0x08u);
    dst_p[0] |= pack_left_shift_u8(src_p->cruise_inc, 4u, 0x10u);
    dst_p[0] |= pack_left_shift_u8(src_p->cruise_en, 5u, 0x20u);
    dst_p[0] |= pack_left_shift_u8(src_p->cruise_dec, 6u, 0x40u);

    return (1);
}

int rivanna3_dashboard_commands_unpack(
    struct rivanna3_dashboard_commands_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 1u) {
        return (-EINVAL);
    }

    dst_p->hazards = unpack_right_shift_u8(src_p[0], 0u, 0x01u);
    dst_p->left_turn_signal = unpack_right_shift_u8(src_p[0], 1u, 0x02u);
    dst_p->right_turn_signal = unpack_right_shift_u8(src_p[0], 2u, 0x04u);
    dst_p->regen_en = unpack_right_shift_u8(src_p[0], 3u, 0x08u);
    dst_p->cruise_inc = unpack_right_shift_u8(src_p[0], 4u, 0x10u);
    dst_p->cruise_en = unpack_right_shift_u8(src_p[0], 5u, 0x20u);
    dst_p->cruise_dec = unpack_right_shift_u8(src_p[0], 6u, 0x40u);

    return (0);
}

int rivanna3_dashboard_commands_init(struct rivanna3_dashboard_commands_t *msg_p)
{
    if (msg_p == NULL) return -1;

    memset(msg_p, 0, sizeof(struct rivanna3_dashboard_commands_t));

    return 0;
}

uint8_t rivanna3_dashboard_commands_hazards_encode(double value)
{
    return (uint8_t)(value);
}

double rivanna3_dashboard_commands_hazards_decode(uint8_t value)
{
    return ((double)value);
}

bool rivanna3_dashboard_commands_hazards_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t rivanna3_dashboard_commands_left_turn_signal_encode(double value)
{
    return (uint8_t)(value);
}

double rivanna3_dashboard_commands_left_turn_signal_decode(uint8_t value)
{
    return ((double)value);
}

bool rivanna3_dashboard_commands_left_turn_signal_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t rivanna3_dashboard_commands_right_turn_signal_encode(double value)
{
    return (uint8_t)(value);
}

double rivanna3_dashboard_commands_right_turn_signal_decode(uint8_t value)
{
    return ((double)value);
}

bool rivanna3_dashboard_commands_right_turn_signal_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t rivanna3_dashboard_commands_regen_en_encode(double value)
{
    return (uint8_t)(value);
}

double rivanna3_dashboard_commands_regen_en_decode(uint8_t value)
{
    return ((double)value);
}

bool rivanna3_dashboard_commands_regen_en_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t rivanna3_dashboard_commands_cruise_inc_encode(double value)
{
    return (uint8_t)(value);
}

double rivanna3_dashboard_commands_cruise_inc_decode(uint8_t value)
{
    return ((double)value);
}

bool rivanna3_dashboard_commands_cruise_inc_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t rivanna3_dashboard_commands_cruise_en_encode(double value)
{
    return (uint8_t)(value);
}

double rivanna3_dashboard_commands_cruise_en_decode(uint8_t value)
{
    return ((double)value);
}

bool rivanna3_dashboard_commands_cruise_en_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t rivanna3_dashboard_commands_cruise_dec_encode(double value)
{
    return (uint8_t)(value);
}

double rivanna3_dashboard_commands_cruise_dec_decode(uint8_t value)
{
    return ((double)value);
}

bool rivanna3_dashboard_commands_cruise_dec_is_in_range(uint8_t value)
{
    return (value <= 1u);
}