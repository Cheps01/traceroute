#ifndef CLI_H
#define CLI_H

#include <stdint.h>

typedef struct {
    int ttl;            // initial ttl (default = 1)
    int max_hops;       // max amount of hops (default = 64)
    int probes;         // probes for each hop (default = 3)
    int timeout_sec;    // timeout before stop waiting (default = 3 sec)
    int pause_ms;       // pause between probes (default = 100 ms)
} cli_options_t;

#define DOMAIN_NAME_LEN 256

int parse_cli(int argc, char **argv, cli_options_t *options, char *domain);
void set_cli_options(cli_options_t *options, int ttl, int max_hops, int probes, 
                        int timeout_sec, int pause_ms);

#endif