#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void process_file(const char *path, const char *file_name);
void find_dir_files(const char *path);

void process_file(const char *path, const char *file_name) {
  char full_path[1024];
  char actual_path[1024];

  strcpy(full_path, path);
  strcat(full_path, "/");
  strcat(full_path, file_name);

  struct stat statbuf;
  if (lstat(full_path, &statbuf) == -1) {
    perror("lstat");
    return;
  }

  ssize_t length;
  if (S_ISLNK(statbuf.st_mode)) {
    length = readlink(full_path, actual_path, sizeof(actual_path));
    if (length > 0) {
      actual_path[length] = '\0';
      printf("\"%s\" -> \"%s\"\n", full_path, actual_path);
    } else {
      perror("readlink");
    }
  }

  if (S_ISDIR(statbuf.st_mode)) {
    find_dir_files(full_path);
  }
}

void find_dir_files(const char *path) {
  DIR *folder = opendir(path);
  if (folder == NULL) {
    perror("opendir");
    return;
  }

  struct dirent *file;
  while ((file = readdir(folder)) != NULL) {
    if (strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0) {
      process_file(path, file->d_name);
    }
  }

  closedir(folder);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    perror("Usage: ./q2 <pathname>");
    exit(1);
  }

  find_dir_files(argv[1]);
  exit(0);
}
