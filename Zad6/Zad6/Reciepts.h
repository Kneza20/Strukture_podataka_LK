#ifndef RECIEPTS_H
#define RECIEPTS_H
#include "Article.h"

typedef struct Bill* BPosition;

typedef struct Bill {
	char date[MAX_LINE];
	APosition articles;
	BPosition Next;
}Bill;

BPosition createBill(char date[]);

BPosition sortBills(BPosition Q);

int scanBills(BPosition Q);

int freeBills(BPosition Q);

int billQuerry(BPosition Q, char article[], char beginDate, char stopDate);

#endif