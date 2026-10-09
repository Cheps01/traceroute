#include <string.h>

#include "checksum.h"

uint16_t compute_checksum(uint16_t *buffer, int size) {
    uint32_t sum = 0;
    while (size > 1) {
        sum += *buffer++;
        size -= 2;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    return (uint16_t)~sum;
}

uint16_t icmp_checksum(icmp_header_t *header, uint8_t *payload, int payload_len) {
    uint16_t fields[(sizeof(icmp_header_t) / sizeof(uint16_t)) + payload_len];
    memcpy(fields, header, sizeof(icmp_header_t));
    memcpy(fields + sizeof(icmp_header_t), payload, payload_len);
    return compute_checksum(fields, (int)sizeof(icmp_header_t));
}