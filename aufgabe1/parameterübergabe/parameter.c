#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
/* Thread-Funktion */
void *name_fct(void *name);

struct name_structure{
        char firstname[50];
        uint16_t length;
    };


int main()
{
    // ----------------------------------------------------------------------------
    // Aufgabe Stringübergabe
    // ----------------------------------------------------------------------------

    pthread_t namethread;
    
    // Struktur initialisieren
    struct name_structure name;
    struct name_structure *nameptr;
    strcpy(name.firstname, "Jakob");

    // Thread Funktionen
    pthread_create(&namethread, NULL, &name_fct, (void*)&name);
    pthread_join(namethread, (void**)(&nameptr));

    // Ausgabe nach der Thread Funktion
    printf("Name nach der Thread Funktion: %s\n", name.firstname);
    printf("Laenge nach der Thread Funktion: %d\n", name.length);


    return 0;
}

void *name_fct(void *name)
{
    struct name_structure* name1 = /*(struct name_structure*)*/ name;
    name1->length = strlen(name1->firstname);
    return (void *)name1;
}