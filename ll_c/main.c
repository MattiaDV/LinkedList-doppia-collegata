#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Node {
    int valore;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;

void enqueue(Queue **head, int valore);
void dequeue(Queue **q);
int peek(Queue **q);

int main() {
    Queue *q = NULL;

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    dequeue(&q);
    printf("%d\n", peek(&q));

    while (q && q->head != NULL) {
        dequeue(&q);
    }
    free(q);
    return 0;
}

void enqueue(Queue **q, int valore) {
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL) {
        printf("Errore nell'allocazione in memoria per enqueue!\n");
        return;
    }

    new_node->valore = valore;
    new_node->next = NULL;

    if (*q == NULL) {
        *q = malloc(sizeof(Queue));

        if (*q == NULL) {
            printf("Errore nell'allocazione in memoria della Queue!\n");
            return;
        }

        (*q)->head = new_node;
        (*q)->tail = new_node;
        return;
    }

    (*q)->tail->next = new_node;
    (*q)->tail = new_node;
}

void dequeue(Queue **q) {
    if (*q == NULL) {
        printf("Mi hai passato una queue vuota!\n");
        return;
    }

    Node *temp = (*q)->head;
    (*q)->head = (*q)->head->next;
    free(temp);

    if ((*q)->head == NULL) {
        (*q)->tail = NULL;
    }
}

int peek(Queue **q) {
    if (*q == NULL) {
        printf("Mi hai passato una lista vuota!\n");
        return 0;
    }

    return (*q)->head->valore;
}