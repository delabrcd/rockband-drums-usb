#pragma once
#include <stdint.h>
#include "Config/adapter_config.h"
#include "version_helper.h"

enum frame_command_t {
    CMD_ACKNOWLEDGE         = 0x01,
    CMD_ANNOUNCE            = 0x02,
    CMD_STATUS              = 0x03,
    CMD_IDENTIFY            = 0x04,
    CMD_POWER_MODE          = 0x05,
    CMD_AUTHENTICATE        = 0x06,
    CMD_GUIDE_BTN           = 0x07,
    CMD_AUDIO_CONFIG        = 0x08,
    CMD_RUMBLE              = 0x09,
    CMD_LED_MODE            = 0x0a,
    CMD_SERIAL_NUM          = 0x1e,
    CMD_INPUT               = 0x20,
    CMD_IDENTIFY_INSTRUMENT = 0x22,
    CMD_AUDIO_SAMPLES       = 0x60,
};

enum frame_type_t {
    TYPE_COMMAND = 0x00,
    TYPE_ACK     = 0x01,
    TYPE_REQUEST = 0x02,
};

enum power_mode_t {
    POWER_ON    = 0x00,
    POWER_SLEEP = 0x01,
    POWER_OFF   = 0x04,
};

enum led_mode_t {
    LED_OFF        = 0x00,
    LED_ON         = 0x01,
    LED_BLINK_FAST = 0x02,
    LED_BLINK_MED  = 0x03,
    LED_BLINK_SLOW = 0x04,
    LED_FADE_SLOW  = 0x08,
    LED_FADE_FAST  = 0x09,
};

struct frame_pkt_t {
    uint8_t command;
    uint8_t deviceId : 4;
    uint8_t type : 4;
    uint8_t sequence;
    uint8_t length;
} __attribute__((packed));

struct xb_one_controller_input_pkt_t : public frame_pkt_t {
    struct Buttons {
        uint32_t : 2;
        uint32_t start : 1;
        uint32_t select : 1;

        uint8_t coloredButtonState : 4;

        uint8_t dpadState : 4;

        uint32_t bumperLeft : 1;
        uint32_t bumperRight : 1;
        uint32_t stickLeft : 1;
        uint32_t stickRight : 1;

    } __attribute__((packed)) buttons;

    uint16_t triggerLeft;
    uint16_t triggerRight;
    int16_t  stickLeftX;
    int16_t  stickLeftY;
    int16_t  stickRightX;
    int16_t  stickRightY;

} __attribute__((packed));

struct xb_one_wireless_legacy_adapter_pkt_t : public frame_pkt_t {
    xb_one_wireless_legacy_adapter_pkt_t()
        : frame_pkt_t{CMD_INPUT, TYPE_COMMAND, 0,
                      sizeof(xb_one_wireless_legacy_adapter_pkt_t) - sizeof(frame_pkt_t)} {
        unknown = 0x01;
    }
    uint8_t : 2;
    uint8_t start : 1;
    uint8_t select : 1;

    uint8_t coloredButtonState1 : 4;

    uint8_t dpadState1 : 4;

    uint8_t left_bumper : 1;
    uint8_t right_bumper : 1;
    uint8_t : 2;

    uint8_t playerId;
    uint8_t unknown;
} __attribute__((packed));

struct xb_one_guitar_input_pkt_t : public xb_one_wireless_legacy_adapter_pkt_t {
    xb_one_guitar_input_pkt_t(uint8_t playerId) : xb_one_wireless_legacy_adapter_pkt_t() {
        playerId = playerId;
        length   = sizeof(xb_one_guitar_input_pkt_t) - sizeof(frame_pkt_t);
    }
    uint8_t : 2;
    uint8_t startButton : 1;
    uint8_t selectButton : 1;

    uint8_t coloredButtonState2 : 4;

    uint8_t dpadState2 : 4;

    uint8_t orangeButton : 1;
    uint8_t : 3;

    uint8_t : 8;

    uint8_t whammy;

    uint8_t unused[8];
} __attribute__((packed));

struct xb_one_drum_input_pkt_t : public xb_one_wireless_legacy_adapter_pkt_t {
    xb_one_drum_input_pkt_t(uint8_t playerId) : xb_one_wireless_legacy_adapter_pkt_t() {
        playerId = playerId;
        length   = sizeof(xb_one_drum_input_pkt_t) - sizeof(frame_pkt_t);
        unknown  = 0x01;
    }
    uint8_t : 2;
    uint8_t start : 1;
    uint8_t select : 1;

    uint8_t coloredButtonState2 : 4;

    uint8_t dpadState2 : 4;

    uint8_t kick : 1;
    uint8_t doublekick : 1;
    uint8_t : 2;

    uint8_t : 3;
    uint8_t padYellow : 1;

    uint8_t : 3;
    uint8_t padRed : 1;

    uint8_t : 3;
    uint8_t padGreen : 1;

    uint8_t : 3;
    uint8_t padBlue : 1;

    uint8_t : 3;
    uint8_t cymbalBlue : 1;

    uint8_t : 3;
    uint8_t cymbalYellow : 1;

    uint8_t : 7;
    uint8_t cymbalGreen : 1;

    uint8_t : 8;
    uint8_t : 8;

    uint8_t unused[4];
} __attribute__((packed));

struct xb_three_gh_input_pkt_t {
    uint8_t unused1;
    uint8_t command;
    uint8_t dpadState : 4;
    uint8_t startButton : 1;
    uint8_t selectButton : 1;
    uint8_t : 2;
    uint8_t orangeButton : 1;
    uint8_t : 3;
    uint8_t coloredButtonState : 4;
    uint8_t unused2[6];

    uint16_t whammy;
    uint16_t tilt;
} __attribute__((packed));

#if 0
struct wla_identify_pkt : public frame_pkt_t {
    wla_identify_pkt(uint8_t playerId, const uint8_t *pgmData, uint8_t connect)
        : frame_pkt_t{CMD_IDENTIFY_INSTRUMENT, TYPE_COMMAND, TYPE_COMMAND,
                      sizeof(wla_identify_pkt) - sizeof(frame_pkt_t)} {
        for (uint8_t i = 0; i < sizeof(buf); i++) {
            buf[i] = pgm_read_byte(pgmData + i);
        }
        playerId = playerId;
        connect  = connect;
    }
    uint8_t playerId;
    uint8_t connect;
    uint8_t buf[16];
};
#endif

struct xb_packet_t {
    struct {
        uint32_t triggered_time = 0;
        uint16_t length         = 0;
    } header;
    union {
        uint8_t     buffer[ADAPTER_OUT_SIZE];
        frame_pkt_t frame;

        xb_one_drum_input_pkt_t   drum_input;
        xb_one_guitar_input_pkt_t guitar_input;
    } buf;
};

static_assert(ADAPTER_OUT_SIZE == sizeof(xb_packet_t::buf), "Wrong Packet size in packet union");

enum adapter_state_t {
    none,
    init_state,
    identifying,
    authenticating,
    running,
    power_off,
};

enum output_e {
    FIRST_OUT,
    OUT_KICK = FIRST_OUT,
    OUT_PAD_RED,
    OUT_PAD_YELLOW,
    OUT_PAD_BLUE,
    OUT_PAD_GREEN,
    OUT_CYM_YELLOW,
    OUT_CYM_BLUE,
    OUT_CYM_GREEN,
    LAST_OUT = OUT_CYM_GREEN,
    NUM_OUT,
    NO_OUT,
};

struct output_state_t {
    typedef uint32_t milliseconds;

    output_state_t() {
        triggeredAt = 0;
        triggered   = false;
    }

    milliseconds triggeredAt;
    bool         triggered;
};

enum state_flags_t {
    no_flag      = 0,
    changed_flag = (1 << 0),
};

enum instruments_e {
    FIRST_INSTRUMENT,
    GUITAR_ONE = FIRST_INSTRUMENT,
    GUITAR_TWO,
    DRUMS,
    N_INSTRUMENTS,
};