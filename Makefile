PROJECT := run
CC := gcc
BUILDDIR := obj
CFLAGS := -Wall -Wextra -g -O2
SRCS := $(shell find . -name "*.c")
OBJS := $(patsubst %.c,%.o,$(SRCS))

$(PROJECT): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(PROJECT) $(OBJS)
