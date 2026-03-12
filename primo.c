#include <stdio.h>

// Divisibile solo per se stesso o per 1
int numeroPrimo(int n) {
    int a = 1;
    int i = n - 1;

    while (i > 1) {
        if (n % i == 0) {
            a = -1;
            return a;
        }
        i--;
    }

    return a;
}

int main() {
    int numero = 49;
    int siono = numeroPrimo(numero);
    
    if (siono == 1) {
        printf("Si il numero è primo!\n");
    } else {
        printf("Il numero non è primo!\n");
    }

    return 0;
}