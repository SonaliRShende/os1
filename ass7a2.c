#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define BUFFER_SIZE 1024

int main() {
  int fd1, fd2;
  char sentence[BUFFER_SIZE], result[BUFFER_SIZE];

  // Creating FIFOs if they don't exist
  mkfifo(FIFO1, 0666);
  mkfifo(FIFO2, 0666);

  while (1) {
    // Read the sentence from the user
    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);

    // Open FIFO1 for writing and send the sentence
    fd1 = open(FIFO1, O_WRONLY);
    write(fd1, sentence, strlen(sentence) + 1);
    close(fd1);

    // If the user types 'exit', exit the loop
    if (strncmp(sentence, "exit", 4) == 0) {
      break;
    }

    // Open FIFO2 for reading the result
    fd2 = open(FIFO2, O_RDONLY);
    read(fd2, result, sizeof(result));
    close(fd2);

    // Display the result from Process 2
    printf("Result from Process 2: %s\n", result);
  }

  return 0;
}
