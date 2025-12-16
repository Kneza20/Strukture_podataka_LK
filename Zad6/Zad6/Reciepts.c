#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#define ERROR_FILE (-1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Reciepts.h"
#include "Article.h"

BPosition memoryAlloc();

BPosition createBill(char date[]);

BPosition sortBills(BPosition Q);

int scanBills(BPosition Q);

int freeBills(BPosition Q);

int billQuerry(BPosition Q, char article[], char beginDate, char stopDate);

BPosition memoryAlloc(){
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
	BPosition bill = NULL, newBill = NULL;
	char billName[MAX_LINE], date[MAX_LINE];
	int quantity;
	float price;

	fp = fopen("racuni.txt", "r");
	if (fp == NULL) {
		printf("Error opening file!");
		return ERROR_FILE;
	}

	bill = createBill(date);
	while (fscanf(fp, "%49[^,] %d %f", billName, &quantity, &price) == 3) {
		newBill = createArticle(billName, quantity, price);
		sortArticles(&bill->articles, newBill);
	}

}

int freeBills(BPosition Q) {
	while (Q != NULL) {
		BPosition temp = Q;
		Q = Q->Next;
		freeBills(temp->articles);
		free(temp);
	}
}

int billQuerry(BPosition Q, char article[], char beginDate, char stopDate) {
	float totalPrice=0.0;
	int totalQuantity=0;

	while (Q) {
		if (strcmp(Q->date, beginDate) >= 0 && strcmp(Q->date, stopDate) <= 0) {
			APosition articles = Q->articles;
			while (articles) {
				if (strcmp(articles->name, article) == 0) {
					totalPrice += articles->quantity * articles->price;
					totalQuantity += articles->quantity;
				}
				articles = articles->Next;
			}
		}
	}

	printf("Article name: %s\n", article);
	printf("Total quantity: %d\n", totalQuantity);
	printf("Total price spent on %s: %.2f\n", article, totalPrice);
}