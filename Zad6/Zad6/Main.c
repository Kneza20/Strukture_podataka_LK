/* Napisati program koji cita datoteku racuni.txt u kojoj su zapisani nazivi svih datoteka 
koji predstavljaju pojedini racun. Na poèetku svake datoteke je zapisan datum u kojem vremenu je 
racun izdat u formatu YYYY-MM-DD. Svaki sljedeci red u datoteci predstavlja artikl u formatu naziv, 
kolicina, cijena. Potrebno je formirati vezanu listu raèuna sortiranu po datumu. Svaki cvor vezane 
liste sadrzava vezanu listu artikala sortiranu po nazivu artikla. Nakon toga potrebno je omoguciti 
upit kojim ce korisnik saznati koliko je novaca sveukupno potroseno na specificni artikl u odredjenom 
vremenskom razdoblju i u kojoj je kolicini isti kupljen.*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Article.h"
#include "Reciepts.h"


int main() {
	BPosition reciept = NULL;
	reciept = scanBills(reciept);
	char articleName[MAX_LINE], beginDate[MAX_LINE], endDate[MAX_LINE];

	printf("Search item name: ");
	scanf("%c", &articleName);

	printf("Enter starting date: ");
	scanf("&c", &beginDate);

	printf("Enter ending date: ");
	scanf("&c", &endDate);

	billQuerry(reciept, articleName, beginDate, endDate);
	freeBills(reciept);
	
	return 0;
}