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

    start_tracing(domain, &options);

    return 0;
}