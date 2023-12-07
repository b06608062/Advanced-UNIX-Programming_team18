CC = gcc
CFLAGS = -std=c11 -O2 -Wall
SRCS = q1.c q2.c q3.c q4.c
OBJS = $(SRCS:.c=.o)
TARGETS = $(SRCS:.c=)

all: $(TARGETS)

q1: q1.o
	$(CC) $(CFLAGS) -o q1 q1.o

q2: q2.o
	$(CC) $(CFLAGS) -o q2 q2.o

q3: q3.o
	$(CC) $(CFLAGS) -o q3 q3.o

q4: q4.o
	$(CC) $(CFLAGS) -o q4 q4.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGETS)
