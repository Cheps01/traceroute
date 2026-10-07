#include "tracing.h"

void start_tracing(const char* dest, cli_options_t *options) {
    char ip[16];
    dns_resolve_addr(dest, ip);
}