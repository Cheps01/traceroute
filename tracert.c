#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "tracing.h"

int main(int argc, char **argv) {
    cli_options_t options;
    char domain[DOMAIN_NAME_LEN];
    int status = parse_cli(argc, argv, &options, domain);

    if (status == 1)
        return 0;
    if (status < 0)
        return 1;

    printf("domain: %s\n"
           "ttl: %d\n"
           "max_hops: %d\n"
           "probes: %d\n"
           "timeout_sec: %d\n"
           "pause_ms: %d\n",
           domain, options.ttl, options.max_hops, options.probes,
           options.timeout_sec, options.pause_ms);

    start_tracing(domain, &options);

    return 0;
}
