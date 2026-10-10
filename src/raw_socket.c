#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#include "raw_socket.h"

int create_raw_socket(void)
{
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("[raw_socket] Failed to create socket.\n");
        return -1;
    }

    int one = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_RECVTTL, &one, sizeof(one)) < 0) {
        perror("[raw_socket] Failed to set socket options.\n");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int set_ttl(int sockfd, uint32_t ttl)
{
    return setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
}

int send_packet(int sockfd, uint8_t *packet, size_t packet_len, const char *dst_ip)
{
    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;

    if (inet_pton(AF_INET, dst_ip, &dest.sin_addr) != 1)
        return -1;

    return sendto(sockfd, packet, packet_len, 0,
                  (struct sockaddr *)&dest, sizeof(dest));
}

int receive_packet(int sockfd, uint8_t *buffer, size_t buffer_len, int timeout_ms)
{
    struct timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
        return -1;

    struct sockaddr_storage src_addr;
    socklen_t src_len = sizeof(src_addr);

    return recvfrom(sockfd, buffer, buffer_len, 0,
                    (struct sockaddr *)&src_addr, &src_len);
}

void close_raw_socket(int sockfd)
{
    close(sockfd);
}
