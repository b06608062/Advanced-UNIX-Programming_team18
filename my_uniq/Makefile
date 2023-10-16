CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = my_uniq
SRCS = my_uniq.c
OBJS = my_uniq.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)