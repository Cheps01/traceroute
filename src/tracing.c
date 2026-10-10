#include "tracing.h"

int build_packet(uint8_t *packet, const char *data, size_t data_len) {
    icmp_header_t *icmph = (icmp_header_t*)packet;
    uint8_t *payload = packet + sizeof(icmp_header_t);
    
    memcpy(payload, data, data_len);
    build_icmp_header(icmph, (uint8_t)ECHO_REQ, (uint8_t)0, (uint16_t)1, (uint16_t)1);
    icmph->checksum = icmp_checksum(icmph, payload, (int)data_len);

    return ((int)sizeof(icmp_header_t) + data_len);
}

int send_probe(trace_run_t *trace, const char *data) {
    uint8_t packet[MAX_PACKET_SIZE];
    size_t data_len = strlen(data);

    int packet_len = build_packet(packet, data, data_len);
    send_packet(trace->sockfd, packet, packet_len, trace->dest_ip);
    return packet_len;
}

int receive_echo(trace_run_t *trace, uint8_t *buffer, size_t buf_len) {
    return receive_packet(trace->sockfd, buffer, buf_len, 300);
} 

void start_tracing(const char* domain, cli_options_t *options) {
    trace_run_t trace;
    trace.sockfd = create_raw_socket();
    dns_resolve_addr(domain, trace.dest_ip);
    printf("traceroute to %s (%s), %d hops max, 46 byte packets\n", domain, trace.dest_ip, options->max_hops);
    
    trace.hop_num = 1;
    trace.ttl = options->ttl;
    set_ttl(trace.sockfd, trace.ttl);
    
    char data[] = "trace_probe_1_test";
    int sent = send_probe(&trace, (char *)data);
    printf("Sent %d bytes\n", sent);
    
    uint8_t buffer[MAX_PACKET_SIZE];
    int recv = receive_echo(&trace, buffer, sizeof(buffer));
    printf("Received %d bytes\n", recv);
}