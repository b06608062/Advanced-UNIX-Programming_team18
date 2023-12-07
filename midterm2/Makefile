CC = gcc
CFLAGS = -std=c11 -O2 -Wall
SRCS = q1.c
OBJS = $(SRCS:.c=.o)
TARGETS = $(SRCS:.c=)

all: $(TARGETS)

q1: q1.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) $(OBJS)
