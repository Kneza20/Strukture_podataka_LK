#define _CRT_SECURE_NO_WARNINGS
#define ERROR_FILE (-1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"

TPosition memoryAlloc() {
    TPosition Q = (TPosition)malloc(sizeof(Tree));
    if (Q == NULL) {
        printf("Error allocating memory!\n");
        return NULL;
    }

    return Q;
}

TPosition treeAlloc(TPosition Q) {
    if (Q != NULL) {
        treeAlloc(Q->left);
        treeAlloc(Q->right);
        free(Q);
    }
    return NULL;
}

TPosition insertElement(TPosition Q, int value) {
    if (NULL == Q) {
        Q = memoryAlloc();
        if (Q == NULL) {
            return NULL;
        }
        Q->value = value;
        Q->left = NULL;
        Q->right = NULL;
    }
    else if (value > Q->value) {
        Q->left = insertElement(Q->left, value);
    }
    else if (value < Q->value) {
        Q->right = insertElement(Q->right, value);
    }
    return Q;
}

int replace(TPosition Q) {
    if (Q == NULL) {
        return 0;
    }

    int valueBefore = Q->value;
    Q->value = replace(Q->left) + replace(Q->right);
    return Q->value + valueBefore;
}

int printInOrder(TPosition Q, FILE* fp) {
    if (Q == NULL) {
        return;
    }
    printInOrder(Q->left, fp);
    fprintf(fp, "%d ", Q->value);
    printInOrder(Q->right, fp);
    fprintf(fp, "\n");

    return EXIT_SUCCESS;
}

int freeTree(TPosition Q) {
    if (Q != NULL) {
        freeTree(Q->left);
        freeTree(Q->right);
        free(Q);
    }

    return EXIT_SUCCESS;
}