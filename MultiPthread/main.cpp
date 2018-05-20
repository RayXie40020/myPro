
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>

#define COUNT 3

pthread_t thread[3];                        //There are three thread
pthread_mutex_t mut_info;	            //
sem_t sem_info;                             //

int mut_number=0;
int const sem_number=666;

void *thread1(void*)
{

	int i;
	printf ("thread1 : I'm thread 1\n");

        for(i=0;i<COUNT;i++)
	{
		sleep(3);
		pthread_mutex_lock(&mut_info);
		mut_number++;
		pthread_mutex_unlock(&mut_info);
		sem_wait(&sem_info);
		//sem_number++;
		sem_post(&sem_info);
		printf ("thread1 : I'm thread 1 mut_number:%d sem_num:%d \n",mut_number,sem_number);

	}

        printf("thread1 : I'm Done\n");
        pthread_exit(NULL);
}


void *thread2(void*)
{
	int i;
	printf("thread2 : I'm thread 2\n");

        for(i=0;i<COUNT;i++)
	{
		sleep(2);
		pthread_mutex_lock(&mut_info);
		mut_number++;
		pthread_mutex_unlock(&mut_info);
		sem_wait(&sem_info);
		//sem_number++;
		sem_post(&sem_info);
		printf ("thread2 : I'm thread 2 mut_number:%d sem_num:%d \n",mut_number,sem_number);

	}

        printf("thread2 : I'm Done\n");
        pthread_exit(NULL);
}


void *thread3(void*)
{
	int i;
	printf("thread3 : I'm thread 3\n");

        for(i=0;i<COUNT;i++)
        {
		sleep(1);
		pthread_mutex_lock(&mut_info);
		mut_number++;
		pthread_mutex_unlock(&mut_info);
		sem_wait(&sem_info);
		//sem_number++;
		sem_post(&sem_info);
		printf ("thread3 : I'm thread 3 mut_number:%d sem_num:%d \n",mut_number,sem_number);

        }

	printf("thread3 : I'm Done\n");
        pthread_exit(NULL);
}


void thread_create(void)
{
        int temp;
        memset(&thread, 0, sizeof(thread));

        if((temp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0)
                printf("Can not build up Thread 1\n");
        else
                printf("Successfully build up Thread 1\n");

        if((temp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0)
                printf("Can not build up Thread 2\n");
        else
                printf("Successfully build up Thread 2\n");

 	if((temp = pthread_create(&thread[2], NULL, thread3, NULL)) != 0)
                printf("Can not build up Thread 3\n");
        else
                printf("Successfully build up Thread 3\n");
}


void thread_wait(void)
{

        if(thread[0] !=0)

           {
               pthread_join(thread[0],NULL);
               printf("Thread 1 has been ended\n");
          }
        if(thread[1] !=0)

           {
               pthread_join(thread[1],NULL);
               printf("Thread 2 has been ended\n");
          }
	if(thread[2] !=0)

           {
               pthread_join(thread[2],NULL);
               printf("Thread 3 has been ended\n");
          }
}

int main()
{

        pthread_mutex_init(&mut_info,NULL);
	sem_init(&sem_info,0,3);

        printf("I am main,I will build up three Threads\n");
        thread_create();
        printf("I am main,I am waiting for the ending of the before three Threads\n");
        thread_wait();

        return 0;
}

