#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPT_C_FLAG 0x01 // 001 in binary
#define OPT_U_FLAG 0x02 // 010 in ｀binary

typedef struct {
  int i_flag;
  int flags;
} Options;

static int comp(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}

void sort(const char *arr[], int n) {
  qsort(arr, n, sizeof(const char *), comp);
}

int main(int argc, char *argv[]) {
  int opt;
  Options options = {0};
  while ((opt = getopt(argc, argv, "ciu")) != -1) {
    switch (opt) {
    case 'c':
      options.flags |= OPT_C_FLAG;
      break;
    case 'i':
      options.i_flag = 1;
      break;
    case 'u':
      options.flags |= OPT_U_FLAG;
      break;
    default:
      perror("Can not use unknown argument.");
      exit(1);
    }
  }

  int left_args = argc - optind;
  FILE *input = stdin;
  FILE *output = stdout;
  if (left_args == 1) {
    input = fopen(argv[optind], "r");
  } else if (left_args == 2) {
    input = fopen(argv[optind], "r");
    output = fopen(argv[optind + 1], "w");
  }
  if (input == NULL || output == NULL) {
    perror("Failed to open the file.");
    exit(1);
  }

  char words[1024][1024];
  char word[256] = {0};
  int input_count = 0;

  while (fgets(word, sizeof(word), input) != NULL) {
    strcpy(words[input_count++], word);
  }

  char temp[1024];
  for (int i = 0; i < input_count; i++) {
    for (int j = i + 1; j < input_count; j++) {
      if (strcmp(words[i], words[j]) > 0) {
        strcpy(temp, words[i]);
        strcpy(words[i], words[j]);
        strcpy(words[j], temp);
      }
    }
  }

  //   for (int i = 0; i < input_count; i++) {
  //     printf("%s", words[i]);
  //   }

  char previous_ori_word[256] = {0};
  char previous_word[256] = {0};
  char current_ori_word[256] = {0};
  char current_word[256] = {0};
  int count = 0;
  int i = 0;
  while (input_count--) {
    strcpy(current_word, words[i++]);
    strcpy(current_ori_word, current_word);
    if (current_word[strlen(current_word) - 1] != '\n') {
      current_word[strlen(current_word)] = '\n';
    }
    if (options.i_flag) {
      for (int i = 0; i < strlen(current_word); i++) {
        current_word[i] = (char)tolower(current_word[i]);
      }
    }

    if (strcmp(previous_word, current_word) == 0) {
      count++;
    } else {
      if (count != 0) {
        switch (options.flags) {
        case 0:
          fputs(previous_ori_word, output);
          break;
        case 1:
          fprintf(output, "   %d %s", count, previous_ori_word);
          break;
        case 2:
          if (count == 1)
            fputs(previous_ori_word, output);
          break;
        case 3:
          if (count == 1) {
            fprintf(output, "   %d %s", count, previous_ori_word);
          }
          break;
        }
      }
      count = 1;
      strcpy(previous_ori_word, current_ori_word);
    }
    strcpy(previous_word, current_word);
  }

  if (count != 0) {
    switch (options.flags) {
    case 0:
      fputs(previous_ori_word, output);
      break;
    case 1:
      fprintf(output, "   %d %s", count, previous_ori_word);
      break;
    case 2:
      if (count == 1)
        fputs(previous_ori_word, output);
      break;
    case 3:
      if (count == 1) {
        fprintf(output, "   %d %s", count, previous_ori_word);
      }
      break;
    }
  }

  exit(0);
}