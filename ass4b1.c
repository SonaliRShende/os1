#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t resource_mutex;  // Mutex for resource (shared data)
pthread_mutex_t readcount_mutex; // Mutex for counting active readers
int read_count = 0;              // Track the number of active readers

// Function executed by each reader thread
void *reader(void *id) {
  int reader_id = *(int *)id;

  // Enter critical section for reading
  pthread_mutex_lock(&readcount_mutex);
  read_count++; // Increment the number of readers
  if (read_count == 1) {
    printf("First reader is trying to lock the resource.\n");
    pthread_mutex_lock(&resource_mutex); // First reader locks the resource
  }
  pthread_mutex_unlock(&readcount_mutex);

  // Reading section (simulated by sleep)
  printf("Reader %d is reading...\n", reader_id);
  sleep(1); // Simulating reading time

  // Exit critical section after reading
  pthread_mutex_lock(&readcount_mutex);
  read_count--; // Decrease the reader count
  if (read_count == 0) {
    printf("Last reader is unlocking the resource.\n");
    pthread_mutex_unlock(&resource_mutex); // Last reader unlocks the resource
  }
  pthread_mutex_unlock(&readcount_mutex);

  printf("Reader %d has finished reading.\n", reader_id);
  sleep(rand() % 3); // Random sleep before next read
  return NULL;
}

// Function executed by each writer thread
void *writer(void *id) {
  int writer_id = *(int *)id;

  // Writing section (exclusive access to the resource)
  printf("Writer %d is waiting for the resource.\n", writer_id);
  pthread_mutex_lock(&resource_mutex); // Lock the resource for writing
  printf("Writer %d is writing...\n", writer_id);
  sleep(2);                              // Simulate writing time
  pthread_mutex_unlock(&resource_mutex); // Unlock resource after writing

  printf("Writer %d has finished writing.\n", writer_id);
  sleep(rand() % 3); // Random sleep before next write
  return NULL;
}

int main() {
  int num_readers, num_writers;

  // Get the number of readers and writers from the user
  printf("Enter the number of readers: ");
  scanf("%d", &num_readers);
  printf("Enter the number of writers: ");
  scanf("%d", &num_writers);

  // Dynamically allocate memory for threads and their IDs
  pthread_t *readers = malloc(num_readers * sizeof(pthread_t));
  pthread_t *writers = malloc(num_writers * sizeof(pthread_t));

  int *reader_ids = malloc(num_readers * sizeof(int));
  int *writer_ids = malloc(num_writers * sizeof(int));

  // Initialize the mutexes
  pthread_mutex_init(&resource_mutex, NULL);
  pthread_mutex_init(&readcount_mutex, NULL);

  // Assign IDs to readers and writers
  for (int i = 0; i < num_readers; i++) {
    reader_ids[i] = i + 1; // Reader IDs start from 1
  }
  for (int i = 0; i < num_writers; i++) {
    writer_ids[i] = i + 1; // Writer IDs start from 1
  }

  // Create reader and writer threads
  for (int i = 0; i < num_readers; i++) {
    pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
  }
  for (int i = 0; i < num_writers; i++) {
    pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
  }

  // Wait for all threads to finish
  for (int i = 0; i < num_readers; i++) {
    pthread_join(readers[i], NULL);
  }
  for (int i = 0; i < num_writers; i++) {
    pthread_join(writers[i], NULL);
  }

  // Clean up: Destroy mutexes and free dynamically allocated memory
  pthread_mutex_destroy(&resource_mutex);
  pthread_mutex_destroy(&readcount_mutex);
  free(readers);
  free(writers);
  free(reader_ids);
  free(writer_ids);

  return 0;
}