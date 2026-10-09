#include "icmp_header.h"

void build_icmp_header(icmp_header_t *icmphead, uint8_t type, uint8_t code, uint16_t id, uint16_t seq) {
    icmphead->type      = type;
    icmphead->code      = code;
    icmphead->checksum  = 0;
    icmphead->id        = htons(id);
    icmphead->seq       = htons(seq);
}