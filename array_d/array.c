#include <stdio.h>
#include <stdlib.h>

typedef struct Numero {
    int valore;
    struct Numero *next;
} Numero;

void addNumber(FILE *fp, Numero **head, int numero);
void caricaArray(Numero **head, int numero);
int sum(Numero **head);
void stampaNumeri(Numero **head);
void caricaNumeri(FILE *fp, Numero **head);
void delNumero(FILE *fp, Numero **head, int valore);

int main() {
    Numero *head = NULL;
    FILE *fp = NULL;
    int scelta = 0;
    int n = 0;

    caricaNumeri(fp, &head);

    while (1) {
        printf("4 -> Cancella numero\n3 -> Inserire numero\n2 -> Calcolare la somma\n1 -> Stampa numeri\n0 -> Esci\n\nScegli: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case 4:
                printf("Inserisci il numero che vuoi aggiungere: ");
                scanf("%d", &n);
                delNumero(fp, &head, n);
                printf("Numero eliminato con successo!\n");
                break;
            case 3:
                printf("Inserisci il numero che vuoi aggiungere: ");
                scanf("%d", &n);
                printf("\n");
                addNumber(fp, &head, n);
                printf("Numero aggiunto!\n");
                printf("\n");
                break;
            case 2:
                int somma = sum(&head);
                printf("La somma di tutti i numeri: %d\n", somma);
                printf("\n");
                break;
            case 1:
                stampaNumeri(&head);
                break;
            case 0:
                printf("Ciao ciao brother!\n");
                while (head != NULL) {
                    Numero *temp = head;
                    head = head->next;
                    free(temp);
                }
                exit(0);
        }
    }

    return 0;
}

void addNumber(FILE *fp, Numero **head, int numero) {
    Numero *new_number = malloc(sizeof(Numero));
    new_number->valore = numero;
    new_number->next = NULL;

    fp = fopen("array.txt", "w");

    if (*head == NULL) {
        *head = new_number;
        fprintf(fp, "%d - %p\n", new_number->valore, (void*)new_number->next);
        fclose(fp);
        return;
    }

    Numero *cur = *head;

    while (cur->next != NULL) {
        fprintf(fp, "%d - %p\n", cur->valore, (void*)cur->next);
        cur = cur->next;
    }

    cur->next = new_number;
    fprintf(fp, "%d - %p\n", cur->valore, (void*)cur->next);
    fprintf(fp, "%d - %p\n", new_number->valore, (void*)new_number->next);
    fclose(fp);
}

void caricaArray(Numero **head, int numero) {
    Numero *new_number = malloc(sizeof(Numero));
    new_number->valore = numero;
    new_number->next = NULL;

    if (*head == NULL) {
        *head = new_number;
        return;
    }

    Numero *cur = *head;

    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = new_number;
}

void caricaNumeri(FILE *fp, Numero **head) {
    fp = fopen("array.txt", "r");
    char riga[100];
    int max_size = 100;

    while (fgets(riga, max_size, fp) != NULL) {
        caricaArray(head, atoi(riga));
    }

    fclose(fp);
}

void delNumero(FILE *fp, Numero **head, int valore) {
    if (*head == NULL) {
        printf("Mi hai passato una lista vuota!\n");
        return;
    }

    fp = fopen("array.txt", "w");

    if ((*head)->valore == valore) {
        Numero *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    Numero *cur = *head;
    Numero *prev = NULL;

    while (cur != NULL && cur->valore != valore) {
        prev = cur;
        cur = cur->next;
    }  

    if (cur == NULL) {
        printf("NON ESISTE IL VALORE: %d\n", valore);
        return;
    }

    prev->next = cur->next;
    free(cur);

    Numero *res = *head;

    while (res != NULL) {
        fprintf(fp, "%d - %p\n", res->valore, (void*)res->next);
        res = res->next;
    }

    fclose(fp);
}

int sum(Numero **head) {
    if (*head == NULL) {
        printf("Errore: lista vuota!\n");
        return 0;
    }

    Numero *cur = *head;
    int somma = 0;

    while (cur != NULL) {
        somma += cur->valore;
        cur = cur->next;
    }

    return somma;
}

void stampaNumeri(Numero **head) {
    if (*head == NULL) {
        printf("Errore: non ci sono numeri nella lista!\n");
        return;
    }

    Numero *cur = *head;

    while (cur != NULL) {
        printf("VALORE: %d\n", cur->valore);
        cur = cur->next;
    }

    printf("\n");
}