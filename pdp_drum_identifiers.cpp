#include "adapter_identifiers.h"
#include "adapter_structs.h"
#include "version_helper.h"

const uint8_t PROGMEM announce[] = {
    0x02, 0x20, 0x01, 0x1c, 0x7e, 0xed, 0x82, 0x8b, 0xec, 0x97, 0x00, 0x00, 0x38, 0x07, 0x62, 0x42,
    0x01, 0x00, 0x00, 0x00, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00};

const uint8_t PROGMEM drumidentify1[] = {
    0x04, 0xf0, 0x01, 0x3a, 0xc5, 0x01, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xc5, 0x00, 0x9d, 0x00, 0x16, 0x00, 0x1b, 0x00, 0x1c, 0x00, 0x23, 0x00,
    0x29, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x06, 0x01, 0x02, 0x03, 0x04, 0x06, 0x07, 0x05, 0x01, 0x04, 0x05, 0x06, 0x0a, 0x02};

const uint8_t PROGMEM drumidentify2[] = {
    0x04, 0xa0, 0x01, 0xba, 0x00, 0x3a, 0x17, 0x00, 0x4d, 0x61, 0x64, 0x43, 0x61, 0x74, 0x7a, 0x2e,
    0x58, 0x62, 0x6f, 0x78, 0x2e, 0x44, 0x72, 0x75, 0x6d, 0x73, 0x2e, 0x47, 0x6c, 0x61, 0x6d, 0x27,
    0x00, 0x57, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x73, 0x2e, 0x58, 0x62, 0x6f, 0x78, 0x2e, 0x49, 0x6e,
    0x70, 0x75, 0x74, 0x2e, 0x4e, 0x61, 0x76, 0x69, 0x67, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x43, 0x6f};

const uint8_t PROGMEM drumidentify3[] = {
    0x04, 0xa0, 0x01, 0xba, 0x00, 0x74, 0x6e, 0x74, 0x72, 0x6f, 0x6c, 0x6c, 0x65, 0x72, 0x03, 0x93,
    0x28, 0x18, 0x06, 0xe0, 0xcc, 0x85, 0x4b, 0x92, 0x71, 0x0a, 0x10, 0xdb, 0xab, 0x7e, 0x07, 0xe7,
    0x1f, 0xf3, 0xb8, 0x86, 0x73, 0xe9, 0x40, 0xa9, 0xf8, 0x2f, 0x21, 0x26, 0x3a, 0xcf, 0xb7, 0x56,
    0xff, 0x76, 0x97, 0xfd, 0x9b, 0x81, 0x45, 0xad, 0x45, 0xb6, 0x45, 0xbb, 0xa5, 0x26, 0xd6, 0x01};

const uint8_t PROGMEM drumidentify4[] = {
    0x04, 0xb0, 0x01, 0x17, 0xae, 0x01, 0x17, 0x00, 0x20, 0x0a, 0x00, 0x01, 0x00, 0x14, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t PROGMEM drumidentify5[] = {0x04, 0xa0, 0x01, 0x00, 0xc5, 0x01, 0x00, 0x00};

static void fill_from_pgm(xb_packet_t *packet, const uint8_t *pgm, const uint8_t &size) {
    for (uint8_t i = 0; i < size; i++) {
        packet->buf.buffer[i] = pgm_read_byte(pgm + i);
    }
    packet->header.triggered_time = 0;
    packet->header.length         = size;
}

namespace identifiers {

int get_n_identify() {
    return 5;
}
int get_announce(xb_packet_t *packet) {
    fill_from_pgm(packet, announce, sizeof(announce) / sizeof(announce[0]));
    return 0;
}

int get_identify(const uint8_t &sequence, xb_packet_t *packet) {
    switch (sequence) {
        case 0:
            fill_from_pgm(packet, drumidentify1, sizeof(drumidentify1) / sizeof(drumidentify1[0]));
            return 0;
        case 1:
            fill_from_pgm(packet, drumidentify2, sizeof(drumidentify2) / sizeof(drumidentify2[0]));
            return 0;
        case 2:
            fill_from_pgm(packet, drumidentify3, sizeof(drumidentify3) / sizeof(drumidentify3[0]));
            return 0;
        case 3:
            fill_from_pgm(packet, drumidentify4, sizeof(drumidentify4) / sizeof(drumidentify4[0]));
            return 0;
        case 4:
            fill_from_pgm(packet, drumidentify5, sizeof(drumidentify5) / sizeof(drumidentify5[0]));
            return 0;
        default:
            return 1;
    }
}

}  // namespace identifiers
