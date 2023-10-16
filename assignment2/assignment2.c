#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int show_error(char error_msg[]) {
  printf("%s\n", error_msg);
  exit(-1);
}

int main(int argc, char *argv[]) {
  char *source_file = argv[1];
  char *target_file = argv[2];
  char my_buffer[BUFFER_SIZE] = "";
  int fd1;
  int fd2;

  if ((fd1 = open(source_file, O_RDONLY)) < 0) {
    show_error("open error");
  }

  if ((fd2 = open(target_file, O_CREAT | O_TRUNC | O_WRONLY, 0777)) < 0) {
    show_error("create error");
  }

  ssize_t read_size;
  while ((read_size = read(fd1, my_buffer, BUFFER_SIZE - 1)) > 0) {
    if (write(fd2, my_buffer, read_size) != read_size) {
      show_error("write error");
    }
  }

  struct stat stat_buf;
  stat(source_file, &stat_buf);
  // printf("%o\n", stat_buf.st_mode & 0777);
  fchmod(fd2, stat_buf.st_mode);

  close(fd1);
  close(fd2);

  return 0;
}