#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define OUTPUT_FILE "/tmp/output.txt"
#define BUFFER_SIZE 1024

void count_details(const char *text, int *chars, int *words, int *lines) {
  *chars = *words = *lines = 0;
  int in_word = 0;

  for (int i = 0; text[i] != '\0'; i++) {
    (*chars)++;
    if (text[i] == '\n' || text[i] == '.') {
      (*lines)++;
    }
    if (isspace(text[i]) || text[i] == '\n' || text[i] == '.') {
      in_word = 0;
    } else if (!in_word) {
      in_word = 1;
      (*words)++;
    }
  }

  if (text[strlen(text) - 1] != '\n') {
    (*lines)++;
  }
}

int main() {
  int fd1, fd2;
  char sentence[BUFFER_SIZE], result[BUFFER_SIZE];
  int chars, words, lines;

  mkfifo(FIFO1, 0666);
  mkfifo(FIFO2, 0666);

  while (1) {
    fd1 = open(FIFO1, O_RDONLY);
    read(fd1, sentence, sizeof(sentence));
    close(fd1);
    if (strncmp(sentence, "exit", 4) == 0) {
      break;
    }
    count_details(sentence, &chars, &words, &lines);
    FILE *file = fopen(OUTPUT_FILE, "w");
    if (file != NULL) {
      fprintf(file, "Characters: %d\nWords: %d\nLines: %d\n", chars, words,
              lines);
      fclose(file);
    }
    file = fopen(OUTPUT_FILE, "r");
    fread(result, sizeof(char), BUFFER_SIZE, file);
    fclose(file);
    fd2 = open(FIFO2, O_WRONLY);
    write(fd2, result, strlen(result) + 1);
    close(fd2);
  }

  return 0;
}
