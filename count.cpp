#include"count.h"
#include"input.h"

long countcode = 0;//�ַ���
long countword = 0;//������
long countline = 0;//����

/*count_code:�����ַ�����*/

void count_code(void) {
	countcode++;
	return;
}

/*count_code:�������ʸ���*/

void count_word(void) {
	countword++;
	return;
}

/*count_line����������*/

void count_line(void) {
	countline++;
	return;
}