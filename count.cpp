#include"count.h"
#include"input.h"
#include"if.h"

long countcode = 0;//字符数
long countword = 0;//单词数
long countline = 0;//行数

/*count_code:计数字符个数*/

void count_code(char c) {
	if (if_code(c))
		countcode++;
	return;
}

/*count_code:计数单词个数*/

void count_word(char c) {
	if (if_word(c))
		countword++;
	return;
}

/*count_line：计数行数*/

void count_line(char c) {
	if (if_line(c))
		countline++;
	return;
}