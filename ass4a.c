#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#define N 5

sem_t empty, full;
int buffer[N];
pthread_mutex_t mutex;
int in = 0, out = 0;

void *producer(void *pno) {
  int item;
  for (int i = 0; i < N; i++) {
    item = rand();
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    buffer[in] = item;
    printf("Producer %d : Produces value %d on place %d.\n", *(int *)pno,
           buffer[in], in);
    in = (in + 1) % N;
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
  }
}

void *consumer(void *cno) {
  int item;
  for (int i = 0; i < N; i++) {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    item = buffer[out];
    printf("Consumer %d: Consumed value %d on place %d. \n", *(int *)cno, item,
           out);
    out = (out + 1) % N;
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
  }
}

int main() {

  pthread_t prod[N], cons[N];
  pthread_mutex_init(&mutex, NULL);

  sem_init(&empty, 0, N);
  sem_init(&full, 0, 0);

  int a[N] = {1, 2, 3, 4, 5};
  for (int i = 0; i < N; i++) {
    pthread_create(&prod[i], NULL, (void *)producer, (void *)&a[i]);
  }
  for (int i = 0; i < N; i++) {
    pthread_create(&cons[i], NULL, (void *)consumer, (void *)&a[i]);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(prod[i], NULL);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(cons[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  sem_destroy(&empty);
  sem_destroy(&full);
  return 0;
}