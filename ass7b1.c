#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

#define SIZE 4096

int main() {
  int shm_id;
  char *shm_ptr;

  // Create shared memory segment
  shm_id = shmget(IPC_PRIVATE, SIZE, IPC_CREAT | 0666);
  if (shm_id < 0) {
    printf("\nError creating shared memory...\n");
    exit(1);
  }

  printf("Shared Memory created with ID: %d\n", shm_id);

  // Attach to the shared memory segment
  shm_ptr = (char *)shmat(shm_id, NULL, 0);
  if (shm_ptr == (char *)-1) {
    printf("\nError attaching Shared Memory...\n");
    exit(1);
  }

  // Write a message to shared memory
  printf("Enter a message to store in shared memory: ");
  fgets(shm_ptr, SIZE, stdin); // Read input message

  printf("Message written to shared memory: %s\n", shm_ptr);
  printf("Note the shared memory ID for the client program: %d\n", shm_id);

  // Wait for client to read (press a key to end)
  printf("Press Enter after client has read the message...\n");
  getchar();

  // Detach and remove shared memory segment
  shmdt(shm_ptr);
  shmctl(shm_id, IPC_RMID, NULL);
  printf("Shared memory detached and removed.\n");

  return 0;
}
