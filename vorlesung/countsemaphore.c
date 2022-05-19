#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

const int max = 10000000;
volatile int count = 0;
sem_t sem;

void *foo()
{
    for (int i = 0; i < max; i++)
    {
        sem_wait(&sem);
        count++;
        sem_post(&sem);
    }
    return 0;
}

int main()
{
    sem_init(&sem, 0, 1);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, foo, NULL);
    pthread_create(&t2, NULL, foo, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("count = %d\n", count);
    return 0;
}