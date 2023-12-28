CC = gcc -pthread
CFLAGS = -std=c11 -O2 -Wall
SRCS = q1.c q2.c q3.c
OBJS = $(SRCS:.c=.o)
TARGETS = $(SRCS:.c=)

all: $(TARGETS)

q1: q1.o
	$(CC) $(CFLAGS) -o q1 q1.o

q2: q2.o
	$(CC) $(CFLAGS) -o q2 q2.o

q3: q3.o
	$(CC) $(CFLAGS) -o q3 q3.o