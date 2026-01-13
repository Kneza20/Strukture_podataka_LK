#include "Define.h"
#include "Functions.h"

int main() {
	StateLPosition stateList = NULL;
	StateTPosition stateTree = NULL;
	char stateName[MAX_LINE], stateFile[MAX_LINE];
	FILE* fp = NULL;
	fp = fopen("drzave.txt", "r");

	if (fp == NULL) {
		printf("Error while opening file!");
		return ERROR_FILE;
	}

	while (fscanf(fp, "%s %s", stateName, stateFile) == 2) {
		stateList = addStateL(stateList, stateName, stateFile);
	}

	fclose(fp);

	printf("List of states:\n");
	printLStates(stateList);

	return 0;
}