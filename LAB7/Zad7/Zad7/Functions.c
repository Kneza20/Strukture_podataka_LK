#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#define EMPTY_DIR (-2)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"

DPosition memoryAlloc() {
    DPosition Q = (DPosition)malloc(sizeof(Dir));
    if (Q == NULL) {
        printf("Error allocating memory!");
        return NULL;
    }
    return Q;
}

DPosition createDir(char* dirName, DPosition parent) {
    DPosition newDir = NULL;
    newDir = memoryAlloc();
    strcpy(newDir->directoryName, dirName);
    newDir->child = NULL;
    newDir->sibling = NULL;
    newDir->parent = parent;
    return newDir;
}

int mkdir(DPosition current) {
    char directoryName[50];
    printf("Directory name: ");
    scanf_s("%s", directoryName);

    DPosition newDir = createDir(directoryName, current);

    if (current->child == NULL) {
        current->child = newDir;
    }
    else {
        DPosition temp = current->child;
        while (temp->sibling != NULL)
            temp = temp->sibling;
        temp->sibling = newDir;
    }

    return EXIT_SUCCESS;
}

DPosition cdDir(DPosition current) {
    char directoryName[50];
    printf("Directory name: ");
    scanf_s("%s", directoryName);

    DPosition temp = current->child;
    while (temp != NULL) {
        if (strcmp(temp->directoryName, directoryName) == 0) {
            return temp;
        }
        temp = temp->sibling;
    }

    if (temp == NULL) {
        printf("Directory not found\n");
        return NULL;
    }

    return current;
}

DPosition cdBack(DPosition current) {
    if (current->parent != NULL) {
        return current->parent;
    }

    return current;
}

int ls(DPosition current) {
    DPosition temp = current->child;

    if (temp == NULL) {
        printf("Directory empty!\n");
		return EMPTY_DIR;
    }

    while (temp != NULL) {
        printf("%s\n", temp->directoryName);
        temp = temp->sibling;
    }
    return EXIT_SUCCESS;
}
