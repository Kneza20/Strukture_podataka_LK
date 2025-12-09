#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#define ERROR_FILE (-1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Reciepts.h"
#include "Article.h"

typedef struct Bill* BPosition;

typedef struct Bill {
	char date[MAX_LINE];
	APosition articles;
	BPosition Next;
}Bill;

BPosition memoryAlloc();

BPosition createBill(char date[]);

BPosition sortBills(BPosition Q);

int scanBills(BPosition Q);

int freeBills(BPosition Q);

int billQuerry(BPosition Q, char article[], char BDate, char Sdate, int quantity, float price);

BPosition memmoryAlloc() {
	BPosition Q = NULL;
	Q = (BPosition)malloc(sizeof(Bill));
	if (Q == NULL) {
		printf("Error memory allocation!");
		return NULL;
	}
	return Q;
}

BPosition createBill(char date[]) {
	BPosition Q = NULL;
	Q = memoryAlloc();

	strcpy(Q->date, date);
	Q->articles = NULL;
	Q->Next = NULL;

	return Q;
}

BPosition sortBills(BPosition Q) {
	BPosition temp = createBill(Q->date);

	while (Q->Next != NULL && Q->Next->date > Q->date) {
		Q = Q->Next;
	}

	if (Q->Next != NULL && Q->Next->date < temp->date) {
		temp->Next = Q->Next;
		Q->Next = temp;
	}

	return EXIT_SUCCESS;
}

int scanBills(BPosition Q) {
	FILE* fp = NULL;
	fp = fopen("racuni.txt", "r");
	if (fp == NULL) {
		printf("Error opening file!");
		return ERROR_FILE;
	}


}