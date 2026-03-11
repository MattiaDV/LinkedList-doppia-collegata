#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

typedef struct SingleFS {
    char filename[255];
    char dirname[255];
    char filepath[255];
    struct SingleFS *next;
} SingleFS;

void addSingleFS(SingleFS **head, const char *fn, const char *dn, const char *fp);
void createFile(const char *fn, const char *dn, const char *fp);
void delSingleFS(SingleFS **head, const char *filename);
void delFile(const char *filepath);

int main() {
    SingleFS *sfs = NULL;
    addSingleFS(&sfs, "test.txt", "test", "test/test.txt");
    addSingleFS(&sfs, "secondo.txt", "test", "test/secondo.txt");
    addSingleFS(&sfs, "terzo.txt", "test", "test/terzo.txt");
    delSingleFS(&sfs, "test/secondo.txt");

    while(sfs != NULL) {
        SingleFS *temp = sfs;
        sfs = sfs->next;
        free(temp);
    }

    return 0;
}

void delFile(const char *filepath) {
    if (unlink(filepath) == -1) {
        perror("Errore: ");
    }

    printf("File eliminato con successo!\n");
}

void delSingleFS(SingleFS **head, const char *filepath) {
    if (*head == NULL) {
        return;
    }

    SingleFS *cur = *head;

    if (strcmp((*head)->filepath, filepath) == 0) {
        delFile(filepath);
        (*head) = (*head)->next;
        free(cur);
    }

    SingleFS *curr = *head;
    SingleFS *prev = NULL;

    while(curr != NULL && strcmp(curr->filepath, filepath) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        return;
    }

    prev->next = curr->next;
    delFile(curr->filepath);
    free(curr);
}

void createFile(const char *fn, const char *dn, const char *fp) {
    if (mkdir(dn, 0744) == -1) {
        if (errno != EEXIST) {
            perror("Error creating directory");
            return;
        }
    }

    int fd = open(fp, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("Error: ");
        return;
    }

    printf("File creato con successo!\n");
    close(fd);
    return;
}

void addSingleFS(SingleFS **head, const char *fn, const char *dn, const char *fp) {
    SingleFS *new = malloc(sizeof(SingleFS));

    if (new == NULL) {
        printf("Errore nell'allocazione in memoria!\n");
        return;
    }

    strcpy(new->filename, fn);
    strcpy(new->dirname, dn);
    strcpy(new->filepath, fp);
    new->next = NULL;

    createFile(new->filename, new->dirname, new->filepath);

    if (*head == NULL) {
        *head = new;
        return;
    }

    SingleFS *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = new;
}