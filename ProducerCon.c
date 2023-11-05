// Write a program to implement the solution of producer consumer problem.

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define maxItems 6
#define BufferSize 6

sem_t full;
sem_t empty;
int in = 0, out = 0;
pthread_mutex_t mutex;
int buffer[BufferSize];

void *producer(void *p)
{
	int item;
	for (int i = 0; i < maxItems; i++)
	{
		item = rand();
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		buffer[in] = item;
		printf("Producer %d Insert item %d at %d\n", *((int *)p), buffer[in], in);
		in = (in + 1) % BufferSize;
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
}

void *consumer(void *c)
{
	for (int i = 0; i < maxItems; i++)
	{
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		int item = buffer[out];
		printf("Producer %d Remove item %d at %d\n", *((int *)c), item, out);
		out = (out + 1) % BufferSize;
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
}

int main()
{
	pthread_t prod[6], con[6];
	pthread_mutex_init(&mutex, NULL);
	sem_init(&full, 0, BufferSize);
	sem_init(&empty, 0, 0);

	int a[6] = {1, 2, 3, 4, 5, 6}; // Used for numbering the producers and consumers
	for (int i = 0; i < 6; i++)
	{
		pthread_create(&prod[i], NULL, (void *)producer, (void *)&a[i]);
	}
	for (int i = 0; i < 6; i++)
	{
		pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
	}

	for (int i = 0; i < 6; i++)
	{
		pthread_join(prod[i], NULL);
	}
	for (int i = 0; i < 6; i++)
	{
		pthread_join(con[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);
	return 0;
}
