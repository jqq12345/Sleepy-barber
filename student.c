/**
 * General structure of a student.
 *
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void* student_loop(void* param)
{
	int* lnumber = (int*)param;
	int number = *lnumber;
	int sleep_time;
	int times_through_loop = 0;

	pthread_mutex_lock(&mutex_lock);//һ��ֻ����һ���˿ͽ������²���������������

	while (1) /*��һ������ѧ�����й䷵�ص�ѧ������ֻ�����귢֮����뿪*/
	{
		if (waiting_students < NUM_OF_SEATS)
		{
			waiting_students++;
			sem_post(&students_sem);
			printf("Student %d wait to be served\n", number);
			pthread_mutex_unlock(&mutex_lock);

			sem_wait(&ta_sem);
			break;
		}
		else
		{

			pthread_mutex_unlock(&mutex_lock);
			times_through_loop = rand() % 15;
			printf("There is no more seats!\n");
			hang_out(number, times_through_loop);
			sleep(times_through_loop);
		}
	}
}

