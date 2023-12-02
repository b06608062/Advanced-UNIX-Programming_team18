CC = gcc -g -pthread
CFLAG = -std=c11 -O0 -Wall
TARGET = assignment10
SRCS = assignment10.c
OBJS = assignment10.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)