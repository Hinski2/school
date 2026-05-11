CC = gcc
CFLAGS = -std=gnu18 -Wall -Wextra -Wpedantic -pedantic-errors \
	-Warray-bounds -Wcast-qual -Wconversion -Wdisabled-optimization -Wfloat-equal -Wformat=2 \
	-Wmissing-declarations -Wmissing-field-initializers -Wmissing-format-attribute \
	-Wmissing-noreturn -Wnull-dereference -Wredundant-decls -Wshadow -Wsign-conversion \
	-Wstrict-aliasing=2 -Wstrict-overflow=5 -Wswitch-enum -Wundef -Wunreachable-code -Wunused

TARGETS = icmp_receive udp_server udp_client udp_client_flood \
    tcp_server tcp_client tcp_client_fixed tcp_server_fixed

all: $(TARGETS)

tidy:
	clang-tidy $(TARGETS:=.c) -- $(CFLAGS)

clean:
	rm -f $(TARGETS)

.PHONY: all tidy distclean
