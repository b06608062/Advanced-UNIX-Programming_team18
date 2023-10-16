#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// int open(const char *path, int oflag, ...);
// off_t lseek(int fildes, off_t offset, int whence);
int main() {
    char path_to_file[] = "try_append_flag.txt";
    char my_buffer[100];

    int file_descriptor = open(path_to_file, O_APPEND | O_RDWR);

    lseek(file_descriptor, -10, SEEK_END);
    read(file_descriptor, my_buffer, 10);
    printf("%s\n", my_buffer);

    lseek(file_descriptor, -10, SEEK_END);
    write(file_descriptor, "test", 4);
    
    close(file_descriptor);
    
    return 0;
}