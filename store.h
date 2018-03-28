#pragma once
#include"stdio.h"

#define WORDNUM 50331553
#define PRIME 50331553
#define MAX 10
#define LIMIT 1025

extern char *wd;
extern char *ph1, *ph2;
extern char *word[WORDNUM];
extern unsigned int hashtime[WORDNUM];

extern char *ph;
extern unsigned int phrasetime[WORDNUM];
extern char *phf[WORDNUM];//词组前
extern char *phb[WORDNUM];//词组后

extern int wordmax[MAX];
extern int phrasemax[MAX];

char store_word(void);
unsigned int store_BKDRHash(char *str);
void store_hashword(void);
void store_wordfind(void);
char store_phrase(void);
void store_hashphrase(void);
void store_phrasefind(void);