#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct MAXER {
    int min;
    int max;
} MAXER;

void* welcome(void *arg) {
    MAXER* max = (MAXER*)arg;
    int num = max->min;

    for (int i = 0; i < max->max; i++) {
        num = max->min;
        num = num * i;
        printf("Moltiplicazione per numero: %d\n", num);
    }
}

void* divi(void *arg) {
    MAXER* max = (MAXER*)arg;
    int num = max->min;

    for (int i = 0; i < max->max; i++) {
        num = max->min;
        num = num + i;
        printf("Somma per numero: %d\n", num);
    }
}

void* even(void *arg) {
    MAXER* max = (MAXER*)arg;
    for (int i = max->min; i < max->max; i++) {
        if (i % 2 == 0) {
            printf("PARI: %d\n", i);
        }
    }

    pthread_exit(0);
}

void* odd(void *arg) {
    MAXER* max = (MAXER*)arg;
    for (int i = max->min; i < max->max; i++) {
        if (i % 2 != 0) {
            printf("DISPARI: %d\n", i);
        }
    }

    pthread_exit(0);
}

int main() {
    pthread_t prima, seconda;
    pthread_t mol, som;
    MAXER *max = malloc(sizeof(MAXER));
    pid_t pid = fork();

    max->min = 10;
    max->max = 101;

    if (pid == 0) {
        pthread_create(&mol, NULL, welcome, max);
        pthread_create(&som, NULL, divi, max);

        pthread_join(mol, NULL);
        pthread_join(som, NULL);
        exit(0);
    } else {
        pthread_create(&prima, NULL, even, max);
        pthread_create(&seconda, NULL, odd, max);

        pthread_join(prima, NULL);
        pthread_join(seconda, NULL);
        wait(NULL);
    }

    free(max);

    return 0;
}