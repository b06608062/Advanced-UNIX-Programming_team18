CC = gcc
CFLAGS = -std=c11 -O2 -Wall
SRCS = q1.c
OBJS = $(SRCS:.c=.o)
TARGETS = $(SRCS:.c=)

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) $(OBJS)
