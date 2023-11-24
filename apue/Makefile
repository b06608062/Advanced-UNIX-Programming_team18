CC = gcc
CFLAGS = -std=c11 -O2 -Wall
SRCS = ch1-4.c ch1-5.c ch4-8.c ch5-2.c ch6-4.c echoarg.c fig8.20-exec2.c
TARGETS = $(SRCS:.c=)

all: $(TARGETS)

$(TARGETS): %: %.o
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) $(SRCS:.c=.o)
