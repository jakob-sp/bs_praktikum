#include "pthread.h"
#include "stdint.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "semaphore.h"

void *threadfunc(void *infos);
void istprimzahl(int temp);

sem_t sem;
sem_t erh;
int maxprimzahl;
int wo;
int wieviele;

int main(int argc, char **argv)
{
    wo = 0;
    wieviele = 0;

    int threadanzahl = atoi(argv[1]);
    maxprimzahl = atoi(argv[2]);

    pthread_t thread[threadanzahl];

    sem_init(&sem, 0, 1);
    sem_init(&erh, 0, 1);

    for (int j = 0; j < threadanzahl; j++)
    {
        pthread_create(&thread[j], NULL, &threadfunc, NULL);
    }

    for (int j = 0; j < threadanzahl; j++)
    {
        pthread_join(thread[j], NULL);
    }

    printf("%d\n", wieviele);

    return 0;
}

void *threadfunc(void *infos)
{

    while (wo <= maxprimzahl)
    {
        sem_wait(&sem);
        int temp = wo;
        wo++;
        sem_post(&sem);
        istprimzahl(temp);
    }
    return NULL;
}

void istprimzahl(int temp)
{
    int status = 0;
    int i = 2;
    while (i < temp)
    {
        if (temp % i == 0)
        {
            status = 1;
            break;
        }
        i++;
    }
    if (status == 0)
    {
        sem_wait(&erh);
        wieviele++;
        sem_post(&erh);
    }
}