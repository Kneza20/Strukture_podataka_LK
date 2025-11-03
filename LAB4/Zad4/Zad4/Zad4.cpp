/*Napisati program za zbrajanje i množenje polinoma. 
Koeficijenti i eksponenti se čitaju iz datoteke. 
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	return 0;
}


/*
U dokumentu npr: 17 1 5 7, prvi broj je koeficj, a drugi potencija od x
napravit provjeru ako su koeficj isti moramo sami obavit zbrajanje

napravit strukturu naziva npr polinom koja sadrži: koeficijent, potencija, pokazivač na idući član
najvj 3 liste, u 2 liste su polinomi a u trecoj rezultat
polinom Head {.next=NULL};
polinom firstPoly = Head
polinom secondPoly = Head

fopen(fp)
buffer->fgets
if(sscanf != 2)
sscanf(buffer, "%d %d %n", &koefic, &potrencija, %n)  n predstavlja koliko je članova prošao

triba provjeravat jeli lista prazna i jeli potencija od p veća od potencije koju dodajemo*/