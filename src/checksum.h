#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <string.h>

#include "icmp_header.h"

uint16_t compute_checksum(uint16_t *buffer, int size);
uint16_t icmp_checksum(icmp_header_t *header, uint8_t *payload, int payload_len);

#endif
