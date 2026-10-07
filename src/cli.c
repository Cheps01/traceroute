#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cli.h"

static void print_usage(const char *prog)
{
    printf("Usage: %s [options] <domain>\n"
           "  <domain>        host to trace the route to\n"
           "  -t ttl          initial ttl (default: 1, range: 1-255)\n"
           "  -m max_hops     maximum hops (default: 64, range: 1-255)\n"
           "  -p probes       probes per hop (default: 3, range: 1-255)\n"
           "  -w timeout_sec  timeout per probe in seconds (default: 3, range: 1-3600)\n"
           "  -z pause_ms     pause between probes in ms (default: 100, range: 0-60000)\n"
           "  -h              show this help\n",
           prog);
}

static int read_int(const char *flag, const char *s, int min, int max, int *out)
{
    char *end;
    long val = strtol(s, &end, 10);

    if (*s == '\0' || *end != '\0' || val < min || val > max) {
        fprintf(stderr, "invalid value '%s' for -%s (expected %d..%d)\n",
                s, flag, min, max);
        return -1;
    }

    *out = (int)val;
    return 0;
}

void set_cli_options(cli_options_t *options, int ttl, int max_hops, int probes,
                     int timeout_sec, int pause_ms)
{
    options->ttl = ttl;
    options->max_hops = max_hops;
    options->probes = probes;
    options->timeout_sec = timeout_sec;
    options->pause_ms = pause_ms;
}

int parse_cli(int argc, char **argv, cli_options_t *options, char *domain)
{
    int opt;

    set_cli_options(options, 1, 64, 3, 3, 100);

    while ((opt = getopt(argc, argv, ":t:m:p:w:z:h")) != -1) {
        switch (opt) {
        case 't':
            if (read_int("t", optarg, 1, 255, &options->ttl) < 0)
                return -1;
            break;
        case 'm':
            if (read_int("m", optarg, 1, 255, &options->max_hops) < 0)
                return -1;
            break;
        case 'p':
            if (read_int("p", optarg, 1, 255, &options->probes) < 0)
                return -1;
            break;
        case 'w':
            if (read_int("w", optarg, 1, 3600, &options->timeout_sec) < 0)
                return -1;
            break;
        case 'z':
            if (read_int("z", optarg, 0, 60000, &options->pause_ms) < 0)
                return -1;
            break;
        case 'h':
            print_usage(argv[0]);
            return 1;
        case ':':
            fprintf(stderr, "option -%c requires a value\n", optopt);
            print_usage(argv[0]);
            return -1;
        default:
            print_usage(argv[0]);
            return -1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "missing domain name\n");
        print_usage(argv[0]);
        return -1;
    }

    if (strlen(argv[optind]) >= DOMAIN_NAME_LEN) {
        fprintf(stderr, "domain name too long\n");
        return -1;
    }

    snprintf(domain, DOMAIN_NAME_LEN, "%s", argv[optind]);
    optind++;

    if (optind < argc) {
        fprintf(stderr, "unexpected argument: %s\n", argv[optind]);
        print_usage(argv[0]);
        return -1;
    }

    return 0;
}
