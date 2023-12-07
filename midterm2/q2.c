#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void process_file(const char *path, const char *file_name);
void print_links(const char *path);

void process_file(const char *path, const char *file_name) {
  char complete_path[1024];
  char target[512];
  struct stat buffer;

  strcpy(complete_path, path);
  strcat(complete_path, "/");
  strcat(complete_path, file_name);

  ssize_t length;
  if (lstat(complete_path, &buffer) == -1) {
    perror("lstat");
    return;
  } else {
    if (S_ISDIR(buffer.st_mode)) {
      print_links(complete_path);
    } else if (S_ISLNK(buffer.st_mode)) {
      length = readlink(complete_path, target, sizeof(target) - 1);
      target[length] = '\0';
      printf("\"%s\" -> \"%s\"\n", complete_path, target);
    }
  }
}

void print_links(const char *path) {
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
  print_links(argv[1]);
  exit(0);
}
