CC = gcc
CFLAGS = -Wall -Wextra -g -Isrc
TARGET = tracert
OBJDIR = bin
OBJS = tracert.o checksum.o cli.o icmp_header.o tracing.o raw_socket.o dns.o
OBJS := $(addprefix $(OBJDIR)/,$(OBJS))

VPATH = src

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -lpcap
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
