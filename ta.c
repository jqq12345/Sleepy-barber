/**
 * General structure of the teaching assistant.
 *
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void* ta_loop(void* param)
{
	int sleep_time;
	while (1)
	{
		sem_wait(&students_sem); /*如果没有学生，则进入睡眠*/
                                printf("A student is served!");
		pthread_mutex_lock(&mutex_lock);   /*上互斥锁*/
		waiting_students--; /*等待的顾客-1*/
		sem_post(&ta_sem);

		pthread_mutex_unlock(&mutex_lock);
		/* seed random generator */
		sleep_time = rand() % rand() % 10;
		sleep(rand() % sleep_time);
                                help_student(sleep_time);
	}
}

