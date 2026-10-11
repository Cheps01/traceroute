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
    hints.ai_family = AF_INET;

    if (getaddrinfo(domain, NULL, &hints, &results) != 0) {
        snprintf(addr, NI_MAXHOST, "%s", domain);
        return;
    }

    if (getnameinfo(results->ai_addr, results->ai_addrlen, host, sizeof(host), NULL, 0, NI_NUMERICHOST) != 0)
        snprintf(addr, NI_MAXHOST, "%s", domain);
    else
        snprintf(addr, NI_MAXHOST, "%s", host);

    freeaddrinfo(results);
}
void dns_resolve_name(const char *addr, char *domain)
{
    struct sockaddr_in sin;
    char host[NI_MAXHOST];

    memset(&sin, 0, sizeof(sin));

    if (inet_pton(AF_INET, addr, &sin.sin_addr) != 1) {
        snprintf(domain, NI_MAXHOST, "%s", addr);
        return;
    }
    sin.sin_family = AF_INET;

    if (getnameinfo((struct sockaddr *)&sin, sizeof(sin),
                    host, sizeof(host), NULL, 0, NI_NAMEREQD) != 0)
        snprintf(domain, NI_MAXHOST, "%s", addr);
    else
        snprintf(domain, NI_MAXHOST, "%s", host);
}
