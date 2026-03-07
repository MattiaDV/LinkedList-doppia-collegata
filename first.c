#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Persona {
	char name[100];
	int eta;
	struct Persona *next;
} Persona;

typedef struct Task {
	char titolo[100];
	char descrizione[200];
	Persona *per_chi;
	struct Task *next;
} Task;

void addTask(Task **head, const char *tit, const char *desc, Persona *chi);
void visTask(Task *head, Persona *head_p);
void delTask(Task **head, const char *tit);

void addPersona(Persona **head, const char *name, int eta);
Persona* ritornaPersona(Persona **head, const char *name);
void delPersona(Persona **head, Task **head_t, const char *name);

int main() {
	Task *head = NULL;
	Persona *head_p = NULL;
	
	addPersona(&head_p, "Mattia", 21);
	
	addTask(&head, "Prima", "La mia prima Task", ritornaPersona(&head_p, "Mattia"));
	addTask(&head, "Seconda", "La mia seconda Task", ritornaPersona(&head_p, "Mattia"));
	addTask(&head, "Terza", "La mia terza Task", ritornaPersona(&head_p, "Mattia"));
	
	visTask(head, head_p);
	
	delTask(&head, "Seconda");
	visTask(head, head_p);
	
	delPersona(&head_p, &head, "Mattia");
	visTask(head, head_p);
	
	while (head != NULL) {
		Task *temp = head;
		head = head->next;
		free(temp);
	}

	return 0;
}

void addTask(Task **head, const char *tit, const char *desc, Persona *chi) {
	Task *new_task = malloc(sizeof(Task));
	if (new_task == NULL) {
		printf("Errore: Memoria insufficente!\n");
		return;
	}
	
	strcpy(new_task->titolo, tit);
	strcpy(new_task->descrizione, desc);
	new_task->per_chi = chi;
	new_task->next = NULL;

	if (*head == NULL) {
		*head = new_task;
		return;
	}
	
	Task *cur = *head;
	
	while (cur->next != NULL) {
		cur = cur->next;
	}
	
	cur->next = new_task;
}

void visTask(Task *head, Persona *head_p) {
	if (head == NULL) {
		printf("Mi hai passato una lista vuota!\n");
		return;
	}
	
	Task *cur = head;
	Persona *cur_p = head_p;
	
	while (cur != NULL) {
		printf("TITOLO: %s | DESCRIZIONE: %s | NEXT: %p\n", cur->titolo, cur->descrizione, (void*)cur->next);
		
		while (cur_p != NULL) {
			if (cur->per_chi == cur_p) {
				printf("DI %s | ETA: %d\n", cur_p->name, cur_p->eta);
			}
			cur_p = cur_p->next;
		}
		
		cur_p = head_p;
		cur = cur->next;
	}
}

void delTask(Task **head, const char *tit) {
	if (*head == NULL) {
		printf("Errore: mi hai passato un array vuoto!\n");
		return;
	}
	
	if (strcmp((*head)->titolo, tit) == 0) {
		Task *temp = *head;
		*head = temp->next;
		free(temp);
		return;
	}
	
	Task *cur = *head;
	Task *prev = NULL;
	
	while (cur != NULL && strcmp(cur->titolo, tit) != 0) {
		prev = cur;
		cur = cur->next;
	}
	
	if (cur == NULL) {
		printf("Mi dispiace ma nessuna task dal titolo %s trovata!\n", tit);
		return;
	}
	
	prev->next = cur->next;
	free(cur);
}

void addPersona(Persona **head, const char *name, int eta) {
	Persona *new_persona = malloc(sizeof(Persona));
	
	if (new_persona == NULL) {
		printf("Errore: memoria insufficente!\n");
		return;
	}
	
	strcpy(new_persona->name, name);
	new_persona->eta = eta;
	new_persona->next = NULL;

	if (*head == NULL) {
		*head = new_persona;
		return;
	}
	
	Persona *cur = *head;
	
	while (cur->next != NULL) {
		cur = cur->next;
	}
	
	cur->next = new_persona;
}

Persona* ritornaPersona(Persona **head, const char *name) {
	if (*head == NULL) {
		printf("Mi hai passato una lista vuota");
		return NULL;
	}
	
	Persona *cur = *head;
	
	while (cur != NULL && strcmp(cur->name, name) != 0) {
		cur = cur->next;
	}
	
	if (cur == NULL) {
		printf("Nessun utente con nome %s esistente!\n", name);
		return NULL;
	}
	
	return cur;
}

void delPersona(Persona **head, Task **head_t, const char *name) {
	if (*head == NULL) {
		printf("Errore: lista persone vuota!\n");
		return;
	}
	
	if (strcmp((*head)->name, name) == 0) {
		Persona *temp = *head;
		Task *cur = *head_t;
		
		while (cur != NULL) {
			if (cur->per_chi == temp) {
				delTask(head_t, cur->titolo);
			}
			cur = cur->next;
		}
		
		*head = temp->next;
		free(temp);
		return;
	}
	
	Persona *cur_p = *head;
	Persona *prev_p = NULL;
	
	while (cur_p != NULL && strcmp(cur_p->name, name) != 0) {
		prev_p = cur_p;
		cur_p = cur_p->next;
	}
	
	if (cur_p == NULL) {
		printf("Errore: nessuna persona con nome %s trovata\n", name);
		return;
	}
	
	Task *cur_tt = *head_t;
	
	while (cur_tt != NULL) {
		if (cur_tt->per_chi == cur_p) {
			delTask(head_t, cur_tt->titolo);
		}
		cur_tt = cur_tt->next;
	}
	
	prev_p->next = cur_p->next;
	free(cur_p);
}