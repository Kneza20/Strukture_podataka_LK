#ifndef ARTICLE_H
#define ARTICLE_H
#include "Article.c"

APosition memoryAlloc();

APosition createArticle(char name[], int quantity, float price);

int sortArticles(APosition Q);

int freeArticles(APosition Q);

#endif