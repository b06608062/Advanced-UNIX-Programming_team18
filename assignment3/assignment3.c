#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 16

typedef struct {
  char *buf;
  size_t buf_size;
  size_t position;
} TmpFile;

int my_read(void *tmp, char *buf, int size) {
  // printf("%d\n", size);
  TmpFile *tmp_file_ptr = tmp;

  int rem_space = tmp_file_ptr->buf_size - tmp_file_ptr->position;
  if (size > rem_space)
    size = rem_space;

  memcpy(buf, tmp_file_ptr->buf + tmp_file_ptr->position, size);
  tmp_file_ptr->position += size;

  return size;
}

int my_write(void *tmp, const char *buf, int size) {
  TmpFile *tmp_file_ptr = tmp;

  int rem_space = tmp_file_ptr->buf_size - tmp_file_ptr->position;
  if (size > rem_space)
    size = rem_space;

  memcpy(tmp_file_ptr->buf + tmp_file_ptr->position, buf, size);
  tmp_file_ptr->position += size;

  return size;
}

fpos_t my_seek(void *tmp, fpos_t offset, int whence) {
  TmpFile *tmp_file_ptr = tmp;

  int new_position;
  if (whence == SEEK_SET)
    new_position = offset;
  else if (whence == SEEK_CUR)
    new_position = tmp_file_ptr->position + offset;
  else if (whence == SEEK_END)
    new_position = tmp_file_ptr->buf_size - 1 + offset;

  if (new_position < 0 || new_position >= tmp_file_ptr->buf_size)
    return -1;
  tmp_file_ptr->position = new_position;

  return tmp_file_ptr->position;
}

int my_close(void *tmp) {
  TmpFile *tmp_file_ptr = tmp;

  free(tmp_file_ptr);

  return 0;
}

FILE *myfmemopen(char *buf, size_t size) {
  TmpFile *tmp_file_ptr = malloc(sizeof(TmpFile));
  tmp_file_ptr->buf = buf;
  tmp_file_ptr->buf_size = size;
  tmp_file_ptr->position = 0;

  return funopen(tmp_file_ptr, my_read, my_write, my_seek, my_close);
}

// FILE *funopen(const void *cookie, int (*readfn)(void *, char *, int),
//               int (*writefn)(void *, const char *, int),
//               fpos_t (*seekfn)(void *, fpos_t, int), int (*closefn)(void *));

int main() {
  char my_tmp_buffer[BUFFER_SIZE] = {0};
  FILE *my_stream = myfmemopen(my_tmp_buffer, BUFFER_SIZE);
  setvbuf(my_stream, NULL, _IONBF, 0);
  char my_buffer[] = "hello, world";
  fwrite(my_buffer, 1, strlen(my_buffer), my_stream);
  fseek(my_stream, 7, SEEK_SET);
  fread(my_buffer, 1, 5, my_stream);
  my_buffer[5] = '\0';
  printf("%s\n", my_buffer);
  fseek(my_stream, 0, SEEK_SET);
  fread(my_buffer, 1, 12, my_stream);
  my_buffer[12] = '\0';
  printf("%s\n", my_buffer);
  fclose(my_stream);

  return 0;
}