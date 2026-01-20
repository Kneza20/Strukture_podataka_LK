/*Prepraviti zadatak 10 na nacin da se formira hash tablica drzava. Tablica ima 11 mjesta, a 
funkcija za preslikavanje kljuc racuna da se zbraja ASCII vrijednost prvih pet slova drzave zatim 
racuna ostatak cjelobrojnog dijeljenja te vrijednosti s velicinom tablice. Drzave s istim kljucem se 
pohranjuju u vezanu listu sortiranu po nazivu drzave. Svaki cvor vezane liste sadrzi stablo gradova 
sortirano po broju stanovnika, zatim po nazivu grada.*/

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

	//11. zadatak
	char searchStateH[MAX_LINE];
	int minPopulationH = 0;

	StateLPosition hash[MAX_TABLE];
	tableInitialization(hash);

	readStatesH(hash, "drzave.txt");
	printHash(hash);

	printf("Search a state: ");
	scanf("%s", searchStateH);
	printf("Enter population (entered value is looked as minimal): ");
	scanf("%d", &minPopulationH);

	StateLPosition stateH = NULL;
	for (int i = 0; i < MAX_TABLE && !stateH; ++i) {
		stateH = findState(hash[i], searchStateH);
	}
	if (stateH) {
		printf("State %s found! Towns with more than %d people: \n", searchStateH, minPopulationH);
		findTowns(stateH->Town, minPopulationH);
	}
	else {
		printf("State not found!");
	}

	return 0;
}