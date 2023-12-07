CC = gcc
CFLAGS = -std=c11 -O2 -Wall
SRCS = q1.c q3.c q4.c
OBJS = $(SRCS:.c=.o)
TARGETS = $(SRCS:.c=)

all: $(TARGETS)

$(TARGETS): %: %.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGETS)
