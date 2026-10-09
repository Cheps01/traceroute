#ifndef ICMP_HEADER_H
#define ICMP_HEADER_H

#include <stdint.h>
#include <arpa/inet.h>

#define ECHO_REPLY      0
#define DEST_UNRECH     3
#define REDIRECT_MSG    5
#define ECHO_REQ        8
#define TIME_EXC        11
#define PARAM_PROB      12

#pragma pack(push, 1)
typedef struct {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint16_t id;
    uint16_t seq;
} icmp_header_t;
#pragma pack(pop)

#define ICMP_HEADER_LEN sizeof(icmp_header_t);

void build_icmp_header(icmp_header_t *icmphead, uint8_t type, uint8_t code, uint16_t id, uint16_t seq);

#endif