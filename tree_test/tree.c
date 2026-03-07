#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int valore;
    struct tree *right;
    struct tree *left;
} tree;

int sum(tree *node) {
    if (node == NULL) {
        return 0;
    }

    return node->valore + sum(node->left) + sum(node->right);
}

void conta_nodi(tree *node, int *nodi) {
    if (node == NULL) return;
    (*nodi)++;

    conta_nodi(node->left, nodi); 
    conta_nodi(node->right, nodi);
}

int main() {
    tree *root = malloc(sizeof(tree));
    tree *left = malloc(sizeof(tree));
    tree *right = malloc(sizeof(tree));
    int nodi = 0;

    root->valore = 10;
    root->left = left;
    root->right = right;

    left->valore = 5;
    left->left = NULL;
    left->right = NULL;

    right->valore = 10;
    right->left = NULL;
    right->right = NULL;

    int somma = sum(root);

    printf("Somma dell'albero: %d\n", somma);
    conta_nodi(root, &nodi);

    printf("Ci sono %d nodi!\n", nodi);

    free(left);
    free(right);
    free(root);

    return 0;
}