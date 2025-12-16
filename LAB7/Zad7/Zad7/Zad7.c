/*Napisati program koji pomocu vezanih listi (stabala) predstavlja strukturu direktorija. 
Omoguciti unos novih direktorija i pod-direktorija, ispis sadrzaja direktorija i povratak u 
prethodni direktorij. Tocnije program treba preko menija simulirati korištenje DOS 
naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#define FAILED_CHOICE (-1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"

int main() {
    int choice;
    DPosition root = createDir("root", NULL);
    DPosition current = root;

    while (1) {
        printf("\nCurrent location: %s\n", current->directoryName);
        printf("1 - md\n");
        printf("2 - cd dir\n");
        printf("3 - cd..\n");
        printf("4 - dir\n");
        printf("5 - exit\n");
        printf("Make ur choice: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            mkdir(current);
            break;
        case 2:
            current = cdDir(current);
            break;
        case 3:
            current = cdBack(current);
            break;
        case 4:
            ls(current);
            break;
        case 5:
            printf("Program exit!\n");
            return 0;
        default:
            printf("Choice not found!\n");
            return FAILED_CHOICE;
        }
    }
}