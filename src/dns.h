#ifndef DNS_H
#define DNS_H

void dns_resolve_addr(const char *domain, char *addr);
void dns_resolve_name(const char *addr, char *domain);

#endif