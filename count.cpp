#include"count.h"
#include"input.h"

long countcode = 0;//字符数
long countword = 0;//单词数
long countline = 0;//行数

/*count_code:计数字符个数*/

void count_code(void) {
	countcode++;
	return;
}

/*count_code:计数单词个数*/

void count_word(void) {
	countword++;
	return;
}

/*count_line：计数行数*/

void count_line(void) {
	countline++;
	return;
}