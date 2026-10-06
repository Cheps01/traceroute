#ifndef RAW_SOCKET_H
#define RAW_SOCKET_H

int create_raw_socket(void);
void set_ttl(int sockfd, uint32_t ttl);
int send_packet(int sockfd, uint8_t *packet, size_t packet_len, const char *dst_ip);
int recieve_packet(int sockfd, uint8_t *buffer, size_t buffer_len, int timeout_ms);
void close_raw_socket(int sockfd);

#endif