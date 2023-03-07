#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include "ta.h"

pthread_t ta;
pthread_t students[NUM_OF_STUDENTS];

/**
 * Initialize all relevant data structures and
 * synchronization objects.
 */
void init()
{
	waiting_students = 0;
	sem_init(&students_sem, 0, 0);
	sem_init(&ta_sem, 0, 1);
	pthread_mutex_init(&mutex_lock, NULL);
}

void create_students()
{
	int i, j = 0;
	int static k, l, n;
	while (j < 15)
	{
		if (i = rand() % NUM_OF_STUDENTS)
		{
			if (i != k && i != l && i != n) {
				if (j % 3 == 0)k = i;
				if (j % 3 == 1)l = i;
				if (j % 3 == 2)n = i;
				student_id[i] = i + 1;
				pthread_create(&students[i], NULL, student_loop, (void*)&student_id[i]);
				sleep(2); j++;
			}
		}
	}

}

void create_ta()
{
	pthread_create(&ta, NULL, ta_loop, NULL);
}

int main(void)
{
	int i, j = 15;

	init();
	create_ta();
	create_students();
	pthread_join(ta, NULL);
	for (i = 0; i < NUM_OF_STUDENTS; i++)
	{
		pthread_join(students[i], NULL);

	}

	return 0;
}

