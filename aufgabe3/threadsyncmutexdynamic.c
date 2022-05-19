#include "pthread.h"
#include "stdio.h"
#include "semaphore.h"
#include "stdint.h"
#include "stdlib.h"

// Definiere globale Variablen / Konstanten
#define MAXCOUNT 1000000
int var;
int i;
pthread_mutex_t globale_mutex;

// Funktionsdeklarationen
void incthread();
void decthread();
void* threadfc(void* uebergabe);

// Main-Funktion
int main(int argc, char **argv)
{
    // Erstellung der Mutex
    pthread_mutex_init(&globale_mutex,NULL);

    // Initialisierung der globalen Variable bei Programmstart mit 0
    var = 0;

    // Wie viele Threads will ich erzeugen?
    i = atoi(argv[1]);

    // Erstellung der Threads
    pthread_t thread[i];

    for(size_t j=0; j<i; j++)
    {
        pthread_create(&thread[j], NULL, &threadfc, (void*)j);
    }

    // Warten auf Beendigung der Threads
    for(int j=0; j<i; j++)
    {
        pthread_join(thread[j], NULL);
    }
    
    printf("Die Variable ist: %d\n", var);
    pthread_mutex_destroy(&globale_mutex);

    return 0;
}

void* threadfc(void* uebergabe)
{
    size_t cnt = (size_t) uebergabe;
    if(cnt%2 == 0)
    {
        decthread();
    }
    if(cnt%2 != 0)
    {
        incthread();
    }
    return NULL;
}

void incthread()
{
    for(int i=0; i<MAXCOUNT; i++)
    {
        pthread_mutex_lock(&globale_mutex);
        var++;
        pthread_mutex_unlock(&globale_mutex);
    }
}

void decthread()
{
    for(int i=0; i<MAXCOUNT; i++)
    {
        pthread_mutex_lock(&globale_mutex);
        var--;
        pthread_mutex_unlock(&globale_mutex);
    }
}

// pthread_mutex_lock
// pthread_mutex_unlock