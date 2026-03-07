#include <stdio.h>
#include <stdlib.h>

typedef struct Numero {
    int valore;
    struct Numero *next;
} Numero;

void addNumber(Numero **head, int numero);
int sum(Numero **head);
void stampaNumeri(Numero **head);

int main() {
    Numero *head = NULL;
    int scelta = 0;
    int n = 0;

    while (1) {
        printf("3 -> Inserire numero\n2 -> Calcolare la somma\n1 -> Stampa numeri\n0 -> Esci\n\nScegli: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case 3:
                printf("Inserisci il numero che vuoi aggiungere: ");
                scanf("%d", &n);
                printf("\n");
                addNumber(&head, n);
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

void addNumber(Numero **head, int numero) {
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