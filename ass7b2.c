#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>

#define SIZE 4096

int main() {
  int shm_id;
  char *shm_ptr;

  // Input shared memory ID from user
  printf("Enter the shared memory ID provided by the server: ");
  scanf("%d", &shm_id);

  // Attach to the shared memory segment
  shm_ptr = (char *)shmat(shm_id, NULL, 0);
  if (shm_ptr == (char *)-1) {
    printf("\nError attaching Shared Memory...\n");
    exit(1);
  }

  // Read and display the message from shared memory
  printf("Message read from shared memory: %s\n", shm_ptr);

  // Detach the shared memory segment
  shmdt(shm_ptr);
  printf("Shared memory detached.\n");

  return 0;
}
