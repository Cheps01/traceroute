#ifndef RAW_SOCKET_H
#define RAW_SOCKET_H

#include <stddef.h>
#include <stdint.h>

int create_raw_socket(void);
int set_ttl(int sockfd, uint32_t ttl);
int send_packet(int sockfd, uint8_t *packet, size_t packet_len, const char *dst_ip);
int recieve_packet(int sockfd, uint8_t *buffer, size_t buffer_len, int timeout_ms);
void close_raw_socket(int sockfd);

#endif