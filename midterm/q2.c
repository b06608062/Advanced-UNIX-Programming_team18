#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <time.h>

void tryDiffBufferSize(size_t bufferSize, int writeMode, char *outputFileName) {
  FILE *f1 = fopen("./source2", "rb");
  if (!f1) {
    perror("fopen");
    exit(1);
  }

  char *membuf = malloc(sizeof(char) * 20971520);
  FILE *f2 = fmemopen(membuf, 20971520, "wb");
  if (!f2) {
    perror("fmemopen");
    exit(1);
  }

  struct tms t1;
  struct tms t2;

  long clockticks1 = times(&t1);

  char *buf = malloc(sizeof(char) * bufferSize);
  size_t readCount;

  if (writeMode == 0) {
    while ((readCount = fread(buf, sizeof(char), bufferSize, f1)) > 0) {
      // printf("readCount = %zu\n", readCount);
      fwrite(buf, sizeof(char), readCount, f2);
    }
  } else if (writeMode == 1) {
    while (fgets(buf, sizeof(buf), f1) != NULL) {
      fputs(buf, f2);
    }
  } else {
    int ch;
    while ((ch = fgetc(f1)) != EOF) {
      fputc(ch, f2);
    }
  }

  long clockticks2 = times(&t2);

  printf("%zu bytes: User CPU: %lf, System CPU: %lf, Clock Time: %ld\n",
         bufferSize, (double)(t2.tms_utime - t1.tms_utime) / CLOCKS_PER_SEC,
         (double)(t2.tms_stime - t1.tms_stime) / CLOCKS_PER_SEC,
         clockticks2 - clockticks1);

  FILE *f3 = fopen(outputFileName, "wb");
  fwrite(membuf, sizeof(char), 20971520, f3);

  free(buf);
  fclose(f1);
  fclose(f2);
  fclose(f3);
}

int main() {
  tryDiffBufferSize(1, 0, "output1");
  tryDiffBufferSize(32, 0, "output2");
  tryDiffBufferSize(1024, 0, "output3");
  tryDiffBufferSize(4096, 0, "output4");
  tryDiffBufferSize(4096, 1, "output5");
  tryDiffBufferSize(1, 2, "output6");

  return 0;
}