#include"count.h"
#include"input.h"
#include"if.h"

long countcode = 0;//�ַ���
long countword = 0;//������
long countline = 0;//����

/*count_code:�����ַ�����*/

void count_code(char c) {
	if (if_code(c))
		countcode++;
	return;
}

/*count_code:�������ʸ���*/

void count_word(char c) {
	if (if_word(c))
		countword++;
	return;
}

/*count_line����������*/

void count_line(char c) {
	if (if_line(c))
		countline++;
	return;
}