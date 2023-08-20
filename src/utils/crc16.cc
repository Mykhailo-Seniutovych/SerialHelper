#include "utils/crc16.hh"

uint16_t crc16_modbus_calculate(const unsigned char* buf, unsigned int len) {
    uint16_t crc = 0xFFFF;
    unsigned int i = 0;
    char bit = 0;

    for (i = 0; i < len; i++) {
        crc ^= buf[i];

        for (bit = 0; bit < 8; bit++) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}