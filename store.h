#pragma once
#include"stdio.h"

#define WORDNUM 50331553
#define PRIME 50331553
#define MAX 10

extern char *wd;
extern char *word[WORDNUM];
extern unsigned int hashtime[WORDNUM];

extern int wordmax[MAX];

char store_word(void);
unsigned int store_BKDRHash(char *str);
void store_hashword(int x);
void store_wordfind(void);
