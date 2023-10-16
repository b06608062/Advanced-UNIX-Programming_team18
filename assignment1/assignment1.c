#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// int open(const char *path, int oflag, ...);
// off_t lseek(int fildes, off_t offset, int whence);

int main() {
  char path_to_file[] = "sample.txt";
  char my_buffer[100];
  int student_offset = 14;

  // open the file with flag O_RDWR
  int file_descriptor = open(path_to_file, O_RDWR);

  // read
  lseek(file_descriptor, student_offset, SEEK_SET);
  read(file_descriptor, my_buffer, 8);
  my_buffer[8] = '\n';
  my_buffer[9] = '\0';
  write(STDOUT_FILENO, my_buffer, 9);

  // write
  lseek(file_descriptor, student_offset, SEEK_SET);
  write(file_descriptor, "NTHU student.", strlen("NTHU student."));
  lseek(file_descriptor, 0, SEEK_SET);

  // read
  read(file_descriptor, my_buffer, 27);
  my_buffer[27] = '\n';
  my_buffer[28] = '\0';
  write(STDOUT_FILENO, my_buffer, 28);

  // close the file
  close(file_descriptor);

  return 0;
}
