#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define max_readers 5
#define max_writers 2

pthread_mutex_t resource_mutex;
pthread_mutex_t readcount_mutex;
int read_count = 0;

void* reader(void* id) {
    int reader_id = *(int*)id;
    while (1) {
        // Enter critical section for reading
        pthread_mutex_lock(&readcount_mutex);
        read_count++;
        if (read_count == 1) {
            pthread_mutex_lock(&resource_mutex); // Lock resource for the first reader
        }
        pthread_mutex_unlock(&readcount_mutex);

        // Reading section
        printf("Reader %d is reading...\n", reader_id);
        sleep(1);

        // Exit critical section
        pthread_mutex_lock(&readcount_mutex);
        read_count--;
        if (read_count == 0) {
            pthread_mutex_unlock(&resource_mutex); // Unlock resource if last reader
        }
        pthread_mutex_unlock(&readcount_mutex);

        sleep(rand() % 3); // Random sleep before next read
    }
    return NULL;
}

void* writer(void* id) {
    int writer_id = *(int*)id;
    while (1) {
        // Writing section
        pthread_mutex_lock(&resource_mutex); // Lock resource for writing
        printf("Writer %d is writing...\n", writer_id);
        sleep(2); // Simulate writing time
        pthread_mutex_unlock(&resource_mutex); // Unlock resource after writing

        sleep(rand() % 3); // Random sleep before next write
    }
    return NULL;
}

int main() {
    pthread_t readers[max_readers], writers[max_writers];
    int reader_ids[max_readers], writer_ids[max_writers];

    // Initialize mutexes
    pthread_mutex_init(&resource_mutex, NULL);
    pthread_mutex_init(&readcount_mutex, NULL);

    // Initialize reader and writer IDs
    for (int i = 0; i < max_readers; i++) {
        reader_ids[i] = i + 1;
    }
    for (int i = 0; i < max_writers; i++) {
        writer_ids[i] = i + 1;
    }

    // Create reader and writer threads
    for (int i = 0; i < max_readers; i++) {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    for (int i = 0; i < max_writers; i++) {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join reader and writer threads
    for (int i = 0; i < max_readers; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < max_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy mutexes
    pthread_mutex_destroy(&resource_mutex);
    pthread_mutex_destroy(&readcount_mutex);

    return 0;
}
