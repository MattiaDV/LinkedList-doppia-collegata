#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUE 100

FILE* openFile(FILE *f, const char *filename, const char *type);
void closeFile(FILE *f);
int somma(FILE *f, char *riga, const int max_size);
int maxNumber(FILE *f, char *riga, const int max_size);


int main() {
    FILE *fp = NULL;
    char riga[MAX_VALUE];

    fp = openFile(fp, "test.txt", "r");

    if (fp == NULL) return 0;

    int so = somma(fp, riga, MAX_VALUE);
    printf("LA SOMMA: %d\n", so);
    closeFile(fp);
    fp = openFile(fp, "test.txt", "r");

    if (fp == NULL) return 0;

    int max = maxNumber(fp, riga, MAX_VALUE);
    printf("NUMERO PIU GRANDE: %d\n", max);
    closeFile(fp);

    return 0;
}

FILE* openFile(FILE *f, const char *filename, const char *type) {
    f = fopen(filename, type);
    return f;
}

void closeFile(FILE *f) {
    fclose(f);
}

int somma(FILE *f, char *riga, const int max_size) {
    int numbers = 0;

    while(fgets(riga, max_size, f) != NULL) {
        numbers += atoi(riga);
    }

    return numbers;
}

int maxNumber(FILE *f, char *riga, const int max_size) {
    int numbers = 0;

    while (fgets(riga, max_size, f) != NULL) {
        if (atoi(riga) > numbers) {
            numbers = atoi(riga);
        }
    }

    return numbers;
}