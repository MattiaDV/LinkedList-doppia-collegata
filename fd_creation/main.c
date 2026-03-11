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

typedef struct FSys {
    char filename[255];
    char dirname[255];
    char filepath[255];
    struct FSys *left;
    struct FSys *right;
} FSys;

typedef struct QueueNode {
    FSys *treeNode;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;

void addFile(FSys **root, const char *fn, const char *dn, const char *fp);
void freeTree(FSys *root);
void viewTree(FSys *root);
int isEmpty(Queue *q);
void enqueue(Queue *head, FSys *file);
FSys* dequeue(Queue *q);
void createFile(const char *dirname, const char *filename, const char*filepath);
void deleteNodeBFS(FSys **root, const char *filename);
void deleteFile(const char *dirname, const char *filename, const char*filepath);
void deleteDir(const char *dirname);

int main() {
    FSys *root = NULL;
    addFile(&root, "primo.txt", "primo", "primo/primo.txt");
    addFile(&root, "secondo.txt", "primo", "primo/secondo.txt");
    addFile(&root, "terzo.txt", "primo", "primo/terzo.txt");
    addFile(&root, "quarto.txt", "primo", "primo/quarto.txt");
    addFile(&root, "quinto.txt", "primo", "primo/quinto.txt");
    addFile(&root, "sesto.txt", "primo", "primo/sesto.txt");
    addFile(&root, "settimo.txt", "primo", "primo/settimo.txt");
    addFile(&root, "ottavo.txt", "primo", "primo/ottavo.txt");
    deleteNodeBFS(&root, "sesto.txt");
    viewTree(root);

    freeTree(root);
    return 0;
}

void deleteDir(const char *dirname) {
    if (rmdir(dirname) == -1) {
        perror("Errore nell'eliminazione della dir: ");
        return;
    } else {
        printf("Cartella eliminata con successo!\n");
        return;
    }
}

void deleteFile(const char *dirname, const char *filename, const char*filepath) {
    if (unlink(filepath) == -1) {
        perror("Errore nell'eliminazione del file: ");
        return;
    }
    printf("File eliminato correttamente!\n");
}

void deleteNodeBFS(FSys **root, const char *filename) {
    if (*root == NULL) return;

    if (strcmp((*root)->filename, filename) == 0) {
        deleteFile((*root)->dirname, (*root)->filename, (*root)->filepath);
        free(*root);
        *root = NULL;
        return;
    }

    Queue q = {NULL, NULL};
    enqueue(&q, *root);

    FSys *cur;
    while (!isEmpty(&q)) {
        cur = dequeue(&q);

        if (cur->left) {
            if (strcmp(cur->left->filename, filename) == 0) {
                deleteFile(cur->left->dirname, cur->left->filename, cur->left->filepath);
                free(cur->left);
                cur->left = NULL;
                return;
            } else {
                enqueue(&q, cur->left);
            }
        }

        if (cur->right) {
            if (strcmp(cur->right->filename, filename) == 0) {
                deleteFile(cur->right->dirname, cur->right->filename, cur->right->filepath);
                free(cur->right);
                cur->right = NULL;
                return;
            } else {
                enqueue(&q, cur->right);
            }
        }
    }

    printf("Nodo %s non trovato!\n", filename);
}

FSys* dequeue(Queue *q) {
    if (q->front == NULL)
        return NULL;

    QueueNode *temp = q->front;
    FSys *node = temp->treeNode;

    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return node;
}

void enqueue(Queue *q, FSys *file) {
    QueueNode *new_node = malloc(sizeof(QueueNode));
    new_node->treeNode = file;
    new_node->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = new_node;
        return;
    }

    q->rear->next = new_node;
    q->rear = new_node;
}

int isEmpty(Queue *q) {
    return (q->front == NULL);
}

void freeTree(FSys *root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void viewTree(FSys *root) {
    if (root == NULL) {
        return;
    }

    printf("FILE: %s\nDIR: %s\nFILEPATH: %s\nLEFT: %p\nRIGHT: %p\n\n", root->filename, root->dirname, root->filepath, root->left, root->right);
    viewTree(root->left);
    viewTree(root->right);
}

void createFile(const char *dirname, const char *filename, const char*filepath) {
    if (mkdir(dirname, 0755) == -1) {
        if (errno == EEXIST) {
            printf("La directory esiste già.\n");
        } else {
            fprintf(stderr, "Errore nella creazione della directory\n");
            return;
        }
    } else {
        printf("Success: folder created!\n");
    }

    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) return;
    close(fd);
}

void addFile(FSys **root, const char *fn, const char *dn, const char *fp) {
    FSys *new_file = malloc(sizeof(FSys));

    if (new_file == NULL) {
        perror("Error: impossible to allocate memory for new file!");
        return;
    }

    strncpy(new_file->dirname, dn, sizeof(new_file->dirname));
    strncpy(new_file->filename, fn, sizeof(new_file->filename));
    strncpy(new_file->filepath, fp, sizeof(new_file->filepath));
    new_file->left = NULL;
    new_file->right = NULL;

    createFile(new_file->dirname, new_file->filename, new_file->filepath);

    if (*root == NULL) {
        *root = new_file;
        return;
    }

    Queue q = {NULL, NULL};
    enqueue(&q, *root);

    while (!isEmpty(&q)) {
        FSys *cur = dequeue(&q);

        if (cur->left == NULL) {
            cur->left = new_file;
            return;
        } else {
            enqueue(&q, cur->left);
        }

        if (cur->right == NULL) {
            cur->right = new_file;
            return;
        } else {
            enqueue(&q, cur->right);
        }
    }
}