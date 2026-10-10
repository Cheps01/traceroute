#ifndef TRACING_H
#define TRACING_H

#include <stdio.h>
#include <string.h>

#include "cli.h"
#include "dns.h"
#include "icmp_header.h"
#include "checksum.h"
#include "raw_socket.h"

#define MAX_PACKET_SIZE     64

typedef struct {
    int sockfd;
    char dest_ip[16];
    int hop_num;
    uint32_t ttl;    
} trace_run_t;

void start_tracing(const char* dest, cli_options_t *options);

#endif