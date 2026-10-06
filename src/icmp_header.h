#ifndef ICMP_HEADER_H
#define ICMP_HEADER_H

#define ECHO_REQ    8

#pragma pack(push, 1)
typedef struct {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t ext_head;
} icmp_header_t;
#pragma pack(pop)

#define ICMP_HEADER_LEN sizeof(icmp_header_t);

void build_icmp_header(icmp_header_t *icmphead, uint8_t type);

#endif