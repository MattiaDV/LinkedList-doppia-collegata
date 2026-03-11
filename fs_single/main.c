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

typedef struct threadArgs {
    SingleFS **head;
    char fn[255];
    char dn[255];
    char fp[255];
} threadArgs;

typedef struct ThreadArgsDel {
    SingleFS **head;
    char filepath[255];
} ThreadArgsDel;

void* threadAdds(void *args);
void* threadDel(void *args);
void addSingleFS(SingleFS **head, const char *fn, const char *dn, const char *fp);
void createFile(const char *fn, const char *dn, const char *fp);
void delSingleFS(SingleFS **head, const char *filepath);
void delFile(const char *filepath);
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        printf("Errore nel fork!\n");
        return 0;
    } else if (pid == 0) {
        SingleFS *sfs = NULL;

        threadArgs args[] = {
            {&sfs, "test.txt", "test", "test/test.txt"},
            {&sfs, "secondo.txt", "test", "test/secondo.txt"},
            {&sfs, "terzo.txt", "test", "test/terzo.txt"},
            {&sfs, "quarto.txt", "test", "test/quarto.txt"},
            {&sfs, "quinto.txt", "test", "test/quinto.txt"}
        };

        const int update = 5;

        pthread_t thread[update];

        for (int i = 0; i < update; i++) {
            pthread_create(&thread[i], NULL, threadAdds, &args[i]);
        }
        for (int i = 0; i < update; i++) {
            pthread_join(thread[i], NULL);
        }

        ThreadArgsDel args_del[] = {
            {&sfs, "test/secondo.txt"},
            {&sfs, "test/quarto.txt"}
        };

        const int deletion = 2;

        pthread_t del_thread[deletion];

        for (int i = 0; i < deletion; i++) {
            pthread_create(&del_thread[i], NULL, threadDel, &args_del[i]);
        }
        for (int i = 0; i < deletion; i++) {
            pthread_join(del_thread[i], NULL);
        }
        
        while(sfs != NULL) {
            SingleFS *temp = sfs;
            sfs = sfs->next;
            free(temp);
        }
        exit(0);
    } else {
        wait(NULL);
        printf("Processo terminato!\n");
    }

    return 0;
}

void* threadAdds(void *args) {
    threadArgs *arg = (threadArgs*)args;
    addSingleFS(arg->head, arg->fn, arg->dn, arg->fp);
    pthread_exit(0);
}

void* threadDel(void *args) {
    ThreadArgsDel *arg = (ThreadArgsDel*)args;
    delSingleFS(arg->head, arg->filepath);
    pthread_exit(0);
}

void delFile(const char *filepath) {
    if (unlink(filepath) == -1) {
        perror("Errore: ");
    }

    printf("File eliminato con successo!\n");
}

void delSingleFS(SingleFS **head, const char *filepath) {
    pthread_mutex_lock(&lock);

    if (*head == NULL) {
        pthread_mutex_unlock(&lock);
        return;
    }

    SingleFS *cur = *head;

    if (strcmp((*head)->filepath, filepath) == 0) {
        delFile(filepath);
        (*head) = (*head)->next;
        free(cur);
        pthread_mutex_unlock(&lock);
        return;
    }

    SingleFS *curr = *head;
    SingleFS *prev = NULL;

    while(curr != NULL && strcmp(curr->filepath, filepath) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        pthread_mutex_unlock(&lock);
        return;
    }

    prev->next = curr->next;
    delFile(curr->filepath);
    free(curr);

    pthread_mutex_unlock(&lock);
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
    pthread_mutex_lock(&lock);
    SingleFS *new = malloc(sizeof(SingleFS));

    if (new == NULL) {
        printf("Errore nell'allocazione in memoria!\n");
        pthread_mutex_unlock(&lock);
        return;
    }

    strcpy(new->filename, fn);
    strcpy(new->dirname, dn);
    strcpy(new->filepath, fp);
    new->next = NULL;

    createFile(new->filename, new->dirname, new->filepath);

    if (*head == NULL) {
        *head = new;
        pthread_mutex_unlock(&lock);
        return;
    }

    SingleFS *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = new;
    pthread_mutex_unlock(&lock);
}