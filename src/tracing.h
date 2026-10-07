#ifndef TRACING_H
#define TRACING_H

#include <stdio.h>

#include "cli.h"
#include "dns.h"

void start_tracing(const char* dest, cli_options_t *options);

#endif