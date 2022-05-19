#include "pthread.h"
#include "stdint.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"

#define ZAHL 1000000
#define BILLION 1000000000
int NUM_OF_THREADS;

struct Infos
{
    int zahl;
    int startval;
    int anzahl;
};

int primzahl_fct(int zahl, int threadanzahl);
void *thread_func(void *info);
struct timespec start, stop;

// ---------------------------------------------------------------------
// MAIN-FUNKTION
// ---------------------------------------------------------------------

int main(int argc, char **argv)
{
    NUM_OF_THREADS = atoi(argv[1]);   
    clock_gettime(CLOCK_REALTIME, &start);
    pthread_t thread[NUM_OF_THREADS];
    struct Infos s[NUM_OF_THREADS];
    for(int i = 0; i<NUM_OF_THREADS; i++)
    {
        s[i].zahl = ZAHL;
        s[i].startval = i+1;
        s[i].anzahl = 0;
    }

    // -----------------------------------------------------------------
    // TESTS
    // -----------------------------------------------------------------

    for(int i=0; i<NUM_OF_THREADS; i++)
    {
        pthread_create(&thread[i], NULL, &thread_func, (void*)&s[i]);
    }
    for(int i=0; i<NUM_OF_THREADS; i++)
    {
        pthread_join(thread[i], NULL);
    }

    // -----------------------------------------------------------------
    // AUSGABE
    // -----------------------------------------------------------------
    int sum;
    for(int i=0; i<NUM_OF_THREADS; i++)
    {
        sum += s[i].anzahl;
    }
    clock_gettime(CLOCK_REALTIME, &stop);
    double time = (stop.tv_sec - start.tv_sec)+(stop.tv_nsec - start.tv_nsec) / (double)BILLION;
    printf("Zeit der Ausführung: %6.3f sek\n", time);

    return 0;
}

// ---------------------------------------------------------------------
// FUNKTIONS-IMPLEMENTIERUNG
// ---------------------------------------------------------------------

int primzahl_fct(int zahl, int startval)
{
    int cnt = startval * 2 - 1;
    int anzahl = 0;

    if (NUM_OF_THREADS > 1)
    {
        while (cnt < zahl)
        {
            int i = 2;
            while (i < cnt)
            {
                if (cnt % i == 0)
                {
                    anzahl++;
                    break;
                }
                i++;
            }
            cnt++;
            i = 2;
            while (i < cnt)
            {
                if (cnt % i == 0)
                {
                    anzahl++;
                    break;
                }
                i++;
            }
            cnt = cnt + (NUM_OF_THREADS * 2 - 1);
        }
    }
    if (NUM_OF_THREADS == 1)
    {
        while (cnt < zahl)
        {
            int i = 2;
            while (i < cnt)
            {
                if (cnt % i == 0)
                {
                    anzahl++;
                    break;
                }
                i++;
            }
            cnt++;
        }
    }

    return anzahl;
}

void *thread_func(void *info)
{
    struct Infos *infos = (struct Infos *)info;
    infos->anzahl = primzahl_fct(infos->zahl, infos->startval);
    return (void *)infos;
}