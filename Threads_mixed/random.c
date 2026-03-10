#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

typedef struct Numeri {
	int valore;
	struct Numeri *next;
} Numeri;

void* pari(void *arg);
void* dispari(void *arg);
void* saluta(void *arg);
void* boh(void *arg);
void* caricaArray(Numeri **head);
void *visualizza(Numeri *head);

int main() {
	Numeri *head = malloc(sizeof(Numeri));
	caricaArray(&head);
	visualizza(head);
	pthread_t primo, secondo;
	pthread_t terzo, quattro;
	pid_t pid;
	pid = fork();
	
	if (pid < 0) {
		printf("Fork failed!\n");
		return 0;
	} else if (pid == 0) {
		printf("SONO IL PROCESSO FIGLIO:\n");
		pthread_create(&primo, NULL, pari, head);
		pthread_create(&secondo, NULL, dispari, head);
		
		pthread_join(primo, NULL);
		pthread_join(secondo, NULL);
		
		exit(0);
	} else {
		printf("SONO IL PROCESSO PADRE:\n");
		pthread_create(&terzo, NULL, saluta, NULL);
		pthread_create(&quattro, NULL, boh, NULL);
		
		pthread_join(terzo, NULL);
		pthread_join(quattro, NULL);
		
		exit(0);
	}
	
	Numeri *cur = head;
	
	while (cur != NULL) {
		Numeri *temp = cur;
		cur = cur->next;
		free(temp);
	}
	
	return 0;
}

void* caricaArray(Numeri **head) {
	Numeri *new_number = malloc(sizeof(Numeri));
	new_number->next = NULL;
	new_number->valore = 0;
	*head = new_number;
	
	Numeri *cur = *head;
	for (int i = 1; i < 10; i++) {
		Numeri *new = malloc(sizeof(Numeri));
		new->valore = i;
		new->next = NULL;
		cur->next = new;
		cur = cur->next;
	}
}

void *visualizza(Numeri *head) {
	Numeri *cur = head;
	
	while (cur != NULL) {
		printf("VALORE: %d\n", cur->valore);
		cur = cur->next;
	}
}

void* saluta(void *arg) {
	for (int i = 0; i < 10; i++) {
		printf("CIAOOOOOOOO\n");
	}
	
	pthread_exit(0);
}

void* boh(void *arg) {
	for (int i = 0; i < 10; i++) {
		printf("OOOOOOOOAIC\n");
	}
	
	pthread_exit(0);
}

void* pari(void *arg) {
	Numeri* head = (Numeri*)arg;
	Numeri *cur = head;
	
	while (cur != NULL) {
		if (cur->valore % 2 == 0) {
			printf("PARI: %d\n", cur->valore);
		}
		cur = cur->next;
	}
	
	pthread_exit(0);
}

void* dispari(void *arg) {
	Numeri* head = (Numeri*)arg;
	Numeri *cur = head;
	
	while (cur != NULL) {
		if (cur->valore % 2 != 0) {
			printf("DISPARI: %d\n", cur->valore);
		}
		cur = cur->next;
	}
	
	pthread_exit(0);
}
