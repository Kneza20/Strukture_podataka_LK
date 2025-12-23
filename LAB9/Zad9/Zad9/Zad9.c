/*Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u cvorove binarnog stabla. 
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za 
   sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraca pokazivac na korijen stabla. 
b) Napisati funkciju replace koja æe svaki element stabla zamijeniti sumom elemenata u njegovom lijevom i desnom 
   podstablu (tj. sumom svih potomaka prije zamjene vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat 
   ce se u stablo na slici Slika 2. 
c) Prepraviti program na naèin da umjesto predefiniranog cjelobrojnog polja korištenjem funkcije rand() generira 
   slucajne brojeve u rasponu <10, 90>. Takodjer, potrebno je upisati u datoteku sve brojeve u inorder 
   prolasku nakon koristenja funkcije iz a), zatim b) dijela zadatka.*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Functions.h"

int main(){
	TPosition root = NULL;
	FILE* fp = NULL;
	fp = fopen("file.txt", "w");
	root = treeAlloc(root);
	int nums[] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
	for (int i = 0; i < 10; i++) {
		root = insertElement(root, nums[i]);
	}
	printInOrder(root, fp);
	replace(root);
	printInOrder(root, fp);

	freeTree(root);
	root = NULL;
	
	fprintf(fp, "\nWITH RANDOM GENERATOR\n");
	int randNums[10] = {0};
	srand(time(NULL));
	for (int i = 0; i < (sizeof(randNums) / sizeof(randNums[0])); i++) {
		randNums[i] = rand() % (90 - 10 + 1) + 10;
		root = insertElement(root, randNums[i]);
	}
	printInOrder(root, fp);
	replace(root);
	printInOrder(root, fp);

	fclose(fp);

	return 0;
}