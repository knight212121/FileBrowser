PROJECT := run

BUILDDIR := ./build
SRCDIR := ./src

SRCS := $(shell find $(SRCDIR) -name "*.c")

OBJS := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))

CC := gcc
CFLAGS := -Wall -Wextra -O -MMD -MP

$(PROJECT): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(BUILDDIR)
	rm $(PROJECT)

-include $(OBJS:.o=.d)
