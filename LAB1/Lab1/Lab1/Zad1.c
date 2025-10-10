/*Napisati program koji prvo pročita koliko redaka ima datoteka, tj. 
koliko ima studenata zapisanih u datoteci. Nakon toga potrebno je dinamički 
alocirati prostor za niz struktura studenata (ime, prezime, bodovi) i učitati 
iz datoteke sve zapise. Na ekran ispisati ime, prezime, apsolutni i relativni 
broj bodova. Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te 
broj bodova na kolokviju. relatvan_br_bodova = br_bodova/max_br_bodova*100*/
#define MAX_LINE (1024)
#define _CRT_SECURE_NO_WARNINGS
#define FILE_NOT_OPENED (-1)
#define ERROR_MEMMORY_ALLOCATION (-2)
#include <stdio.h>
#include <stdlib.h>

typedef struct student {
	char name[20];
	char surname[20];
	int pointsNum;
}Student;

int studentNum(int i);
int studentStat(int studentNum, Student* s);

int main() {
	int i = 0;
	Student* s=NULL;
	FILE* fp = NULL;
	int k = studentNum(i);
	printf("There is %d students in the file.\n", k);

	s = (Student*)malloc(k * sizeof(Student));  //alokacija memorije velicine brojStud
	if (s == NULL) {
		printf("Error while allocating memory!\n");
		return ERROR_MEMMORY_ALLOCATION;
	}
	else {
		fp = fopen("doc.txt", "r");
		for (int i = 0; i < studentNum; i++) {
			fscanf(fp, "%s %s %d", s[i].name, s[i].surname, s[i].pointsNum);
			int relPointsNum = (s[i].pointsNum / 100) * 100;  //relativni broj bodova	
			printf("Student: %s %s, has an absolute number of points: %d, and relative number of points: %d\n", s[i].name, s[i].surname, s[i].pointsNum, (s[i].pointsNum / 100) * 100);
		}
		fp = fclose(fp);
		free(s);
	}

	return 0;
}

int studentNum(int i) {     //fja za prebrojavanje studenata
	FILE* fp;
	char buffer[MAX_LINE];
	fp = fopen("doc.txt", "r");

	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.\n");
		return FILE_NOT_OPENED;
	}
	else {
		while (fgets(buffer, MAX_LINE, fp) != NULL) {
			i = i + 1;
		}
		fp = fclose(fp);
		return i;
	}
}

int studentStat(int studentNum, Student* s) {
	FILE* fp;
	s = (Student*)malloc(studentNum * sizeof(Student));  //alokacija memorije velicine brojStud
	if (s == NULL) {
		printf("Error while allocating memory!\n");
		return ERROR_MEMMORY_ALLOCATION;
	}
	else {
		fp = fopen("doc.txt", "r");
		for (int i = 0; i < studentNum; i++) {
			fscanf(fp, "%s %s %d", s[i].name, s[i].surname, s[i].pointsNum);
			int relPointsNum = (s[i].pointsNum / 100) * 100;  //relativni broj bodova		
		}
		fp = fclose(fp);
		free(s);
	}
}