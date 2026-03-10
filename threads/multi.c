#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* even(void *arg) {
    for (int i = 0; i < 11; i++) {
        if (i % 2 == 0) {
            printf("PARI: %d\n", i);
        }
    }

    pthread_exit(0);
}

void* odd(void *arg) {
    for (int i = 0; i < 11; i++) {
        if (i % 2 != 0) {
            printf("DISPARI: %d\n", i);
        }
    }

    pthread_exit(0);
}

int main() {
    pthread_t prima, seconda;

    pthread_create(&prima, NULL, even, NULL);
    pthread_create(&seconda, NULL, odd, NULL);

    pthread_join(prima, NULL);
    pthread_join(seconda, NULL);

    return 0;
}