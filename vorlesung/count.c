#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

const int max = 10000;
volatile int count = 0;
volatile int flag = 0;

void* foo(void* pv)
{
    int myid = (int)pv;
    for (int i = 0; i < max; i++)
    {
        while (flag != myid)
        {
            count++;
            flag = 1 - myid;
        }
    }
    return 0;
}

int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &foo, 0);
    pthread_create(&t2, NULL, &foo, 1);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("count = %d\n", count);
    return 0;
}