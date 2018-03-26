#pragma once
#include"stdio.h"

#define WORDNUM 100000000
#define PRIME 50331553

extern char *word[WORDNUM];
extern unsigned int hashtime[WORDNUM];

char store_word(int x);
unsigned int store_BKDRHash(char *str);
