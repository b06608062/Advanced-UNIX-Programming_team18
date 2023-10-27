CC = gcc
CFLAGS = -std=c11 -O2 -Wall
SRCS = q1.c q2.c
TARGETS = $(SRCS:.c=)

all: $(TARGETS)

$(TARGETS): %: %.o
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) $(SRCS:.c=.o)