#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef EINVAL
#    define EINVAL 22
#endif

/* Frame ids. */
#define RIVANNA3_DASHBOARD_COMMANDS_FRAME_ID (0x300u)

/* Frame lengths in bytes. */
#define RIVANNA3_DASHBOARD_COMMANDS_LENGTH (1u)

/* Extended or standard frame types. */
#define RIVANNA3_DASHBOARD_COMMANDS_IS_EXTENDED (0)

/* Frame Names. */
#define RIVANNA3_DASHBOARD_COMMANDS_NAME "DashboardCommands"

/* Signal Names. */
#define RIVANNA3_DASHBOARD_COMMANDS_HAZARDS_NAME "hazards"
#define RIVANNA3_DASHBOARD_COMMANDS_LEFT_TURN_SIGNAL_NAME "left_turn_signal"
#define RIVANNA3_DASHBOARD_COMMANDS_RIGHT_TURN_SIGNAL_NAME "right_turn_signal"
#define RIVANNA3_DASHBOARD_COMMANDS_REGEN_EN_NAME "regen_en"
#define RIVANNA3_DASHBOARD_COMMANDS_CRUISE_INC_NAME "cruise_inc"
#define RIVANNA3_DASHBOARD_COMMANDS_CRUISE_EN_NAME "cruise_en"
#define RIVANNA3_DASHBOARD_COMMANDS_CRUISE_DEC_NAME "cruise_dec"

/**
 * Signals in message DashboardCommands.
 *
 * All signal values are as on the CAN bus.
 */
struct rivanna3_dashboard_commands_t {
    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t hazards;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t left_turn_signal;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t right_turn_signal;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t regen_en;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t cruise_inc;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t cruise_en;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t cruise_dec;
};


/**
 * Pack message DashboardCommands.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int rivanna3_dashboard_commands_pack(
    uint8_t *dst_p,
    const struct rivanna3_dashboard_commands_t *src_p,
    size_t size);

/**
 * Unpack message DashboardCommands.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int rivanna3_dashboard_commands_unpack(
    struct rivanna3_dashboard_commands_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Init message fields to default values from DashboardCommands.
 *
 * @param[in] msg_p Message to init.
 *
 * @return zero(0) on success or (-1) in case of nullptr argument.
 */
int rivanna3_dashboard_commands_init(struct rivanna3_dashboard_commands_t *msg_p);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t rivanna3_dashboard_commands_hazards_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double rivanna3_dashboard_commands_hazards_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool rivanna3_dashboard_commands_hazards_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t rivanna3_dashboard_commands_left_turn_signal_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double rivanna3_dashboard_commands_left_turn_signal_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool rivanna3_dashboard_commands_left_turn_signal_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t rivanna3_dashboard_commands_right_turn_signal_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double rivanna3_dashboard_commands_right_turn_signal_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool rivanna3_dashboard_commands_right_turn_signal_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t rivanna3_dashboard_commands_regen_en_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double rivanna3_dashboard_commands_regen_en_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool rivanna3_dashboard_commands_regen_en_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t rivanna3_dashboard_commands_cruise_inc_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double rivanna3_dashboard_commands_cruise_inc_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool rivanna3_dashboard_commands_cruise_inc_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t rivanna3_dashboard_commands_cruise_en_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double rivanna3_dashboard_commands_cruise_en_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool rivanna3_dashboard_commands_cruise_en_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t rivanna3_dashboard_commands_cruise_dec_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double rivanna3_dashboard_commands_cruise_dec_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool rivanna3_dashboard_commands_cruise_dec_is_in_range(uint8_t value);
