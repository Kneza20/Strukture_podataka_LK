/*Napisati program koji èita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih država. 
Uz ime države u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine države. 
Svaka datoteka koja predstavlja državu sadrži popis gradova u formatu naziv_grada, broj_stanovnika. 
a) Potrebno je formirati sortiranu vezanu listu država po nazivu. Svaki èvor vezane liste sadrži stablo 
gradova sortirano po broju stanovnika, zatim po nazivu grada. 
b) Potrebno je formirati stablo država sortirano po nazivu. Svaki èvor stabla sadrži vezanu listu gradova 
sortiranu po broju stanovnika, zatim po nazivu grada. 
Nakon formiranja podataka potrebno je ispisati države i gradove te omoguæiti korisniku putem tastature 
pretragu gradova odreðene države koji imaju broj stanovnika veæi od unosa na tastaturi.*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#define ERROR_FILE -1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Functions.h"

int main() {
	StateLPosition stateList = NULL;
	StateTPosition stateTree = NULL;
	char stateName[MAX_LINE], stateFile[MAX_LINE], searchState[MAX_LINE];
	int minPopulation=0;
	FILE* fp = NULL;
	fp = fopen("drzave.txt", "r");

	if (fp == NULL) {
		printf("Error while opening file!");
		return ERROR_FILE;
	}

	while (fscanf(fp, "%s %s", stateName, stateFile) == 2) {
		stateList = addStateL(stateName, stateList, stateFile);
		stateTree = addStateT(stateName, stateFile, stateTree);
	}

	fclose(fp);

	printf("List of states:\n");
	printLStates(stateList);
	printf("\n");
	printf("Tree of states:\n");
	printTStates(stateTree);
	printf("\n");

	printf("Search a state: ");
	scanf("%s", searchState);
	printf("Enter population (entered value is looked as minimal): ");
	scanf("%d", &minPopulation);

	StateLPosition state = findState(stateList, searchState);
	if (state) {
		printf("State %s found! Towns with more than %d people: \n", searchState, minPopulation);
		findTowns(state->Town, minPopulation);
	}
	else {
		printf("State not found!");
	}

	return 0;
}