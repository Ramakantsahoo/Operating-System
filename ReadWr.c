// Write a program to implement reader writer problem solution.

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1;
int numReader = 0;

void *writer(void *w)
{
	sem_wait(&wrt);
	cnt = cnt * 2;
	printf("Writer %d modified cnt to %d\n", *((int *)w), cnt);
	sem_post(&wrt);
}

void *reader(void *r)
{
	pthread_mutex_lock(&mutex);
	numReader++;
	if (numReader == 1)
		sem_wait(&wrt);
	pthread_mutex_unlock(&mutex);

	printf("Reader %d read cnt as %d\n", *((int *)r), cnt);

	pthread_mutex_lock(&mutex);
	numReader--;
	if (numReader == 0)
		sem_post(&wrt);
	pthread_mutex_unlock(&mutex);
}

int main()
{
	pthread_t read[10], write[5];
	pthread_mutex_init(&mutex, NULL);
	sem_init(&wrt, 0, 1);

	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Just used for numbering reader and writer

	for (int i = 0; i < 10; i++)
	{
		pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		pthread_join(read[i], NULL);
	}
	for (int i = 0; i < 5; i++)
	{
		pthread_join(write[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	sem_destroy(&wrt);
	return 0;
}

// Terminal

// Reader 1 read cnt as 1
// Reader 2 read cnt as 1
// Reader 4 read cnt as 1
// Reader 5 read cnt as 1
// Reader 6 read cnt as 1
// Reader 7 read cnt as 1
// Reader 8 read cnt as 1
// Reader 3 read cnt as 1
// Reader 9 read cnt as 1
// Reader 10 read cnt as 1
// Writer 1 modified cnt to 2
// Writer 2 modified cnt to 4
// Writer 3 modified cnt to 8
// Writer 4 modified cnt to 16
// Writer 5 modified cnt to 32
