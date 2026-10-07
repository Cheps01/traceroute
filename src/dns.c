#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "dns.h"

void dns_resolve_addr(const char *domain, char *addr)
{
    struct addrinfo hints;
    struct addrinfo *results;
    char host[NI_MAXHOST];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;

    if (getaddrinfo(domain, NULL, &hints, &results) != 0) {
        snprintf(addr, NI_MAXHOST, "%s", domain);
        return;
    }

    if (getnameinfo(results->ai_addr, results->ai_addrlen,
                    host, sizeof(host), NULL, 0, NI_NUMERICHOST) != 0)
        snprintf(addr, NI_MAXHOST, "%s", domain);
    else
        snprintf(addr, NI_MAXHOST, "%s", host);

    freeaddrinfo(results);
}

void dns_resolve_name(const char *addr, char *domain)
{
    struct sockaddr_storage ss;
    struct sockaddr_in *sin4;
    struct sockaddr_in6 *sin6;
    socklen_t ss_len;
    char host[NI_MAXHOST];

    memset(&ss, 0, sizeof(ss));

    sin4 = (struct sockaddr_in *)&ss;
    if (inet_pton(AF_INET, addr, &sin4->sin_addr) == 1) {
        sin4->sin_family = AF_INET;
        ss_len = sizeof(*sin4);
    } else {
        sin6 = (struct sockaddr_in6 *)&ss;
        if (inet_pton(AF_INET6, addr, &sin6->sin6_addr) == 1) {
            sin6->sin6_family = AF_INET6;
            ss_len = sizeof(*sin6);
        } else {
            snprintf(domain, NI_MAXHOST, "%s", addr);
            return;
        }
    }

    if (getnameinfo((struct sockaddr *)&ss, ss_len,
                    host, sizeof(host), NULL, 0, NI_NAMEREQD) != 0)
        snprintf(domain, NI_MAXHOST, "%s", addr);
    else
        snprintf(domain, NI_MAXHOST, "%s", host);
}
