CC = gcc -g -pthread
CFLAG = -std=c11 -O0 -Wall
TARGET = assignment11
SRCS = assignment11.c
OBJS = assignment11.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)