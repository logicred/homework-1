#pragma once
#define WORDLETTER 4

const char big_letter[] = { 'A','B','C','D' ,'E','F','G','H','I'
	,'J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X'
	,'Y','Z' };//´æ´¢´óÐ´×ÖÄ¸

const char small_letter[] = { 'a','b','c','d','e','f','g','h','i'
	,'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x',
	'y','z' };//´æ´¢Ð¡Ð´×ÖÄ¸

const char number[] = { '0','1','2','3','4','5','6','7','8','9' };
			  //´æ´¢Êý×Ö

extern long wordletter;

bool if_code(char c);
bool if_split(char c);
bool if_number(char c);
bool if_letter(char c);
bool if_line(char c);
bool if_word(char c);
int if_wordorder(char *s1, char *s2);
bool if_sameword(char *s1, char *s2);
void if_lettercase(char &c);

