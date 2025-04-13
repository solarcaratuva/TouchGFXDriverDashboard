#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef EINVAL
#    define EINVAL 22
#endif

/* Frame ids. */
#define RIVANNA3_HEART_BEAT_FRAME_ID (0x400u)

/* Frame lengths in bytes. */
#define RIVANNA3_HEART_BEAT_LENGTH (8u)

/* Extended or standard frame types. */
#define RIVANNA3_HEART_BEAT_IS_EXTENDED (0)

/* Frame Names. */
#define RIVANNA3_HEART_BEAT_NAME "HeartBeat"

/* Signal Names. */
#define RIVANNA3_HEART_BEAT_FROM_TELEMETRY_BOARD_NAME "FromTelemetryBoard"
#define RIVANNA3_HEART_BEAT_FROM_WHEEL_BOARD_NAME "FromWheelBoard"
#define RIVANNA3_HEART_BEAT_FROM_POWER_BOARD_NAME "FromPowerBoard"

/**
 * Signals in message HeartBeat.
 *
 * All signal values are as on the CAN bus.
 */
 struct rivanna3_heart_beat_t {
    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t from_telemetry_board;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t from_wheel_board;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t from_power_board;
};


/**
 * Pack message HeartBeat.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
 int rivanna3_heart_beat_pack(
    uint8_t *dst_p,
    const struct rivanna3_heart_beat_t *src_p,
    size_t size);

/**
 * Unpack message HeartBeat.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int rivanna3_heart_beat_unpack(
    struct rivanna3_heart_beat_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Init message fields to default values from HeartBeat.
 *
 * @param[in] msg_p Message to init.
 *
 * @return zero(0) on success or (-1) in case of nullptr argument.
 */
int rivanna3_heart_beat_init(struct rivanna3_heart_beat_t *msg_p);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t rivanna3_heart_beat_from_telemetry_board_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double rivanna3_heart_beat_from_telemetry_board_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool rivanna3_heart_beat_from_telemetry_board_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t rivanna3_heart_beat_from_wheel_board_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double rivanna3_heart_beat_from_wheel_board_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool rivanna3_heart_beat_from_wheel_board_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t rivanna3_heart_beat_from_power_board_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double rivanna3_heart_beat_from_power_board_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool rivanna3_heart_beat_from_power_board_is_in_range(uint8_t value);