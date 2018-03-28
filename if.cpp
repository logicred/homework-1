#include"if.h"
#include"stdio.h"
#include"string.h"
#include"math.h"

long wordletter = false;

/*if_letter:�ж������ַ��Ƿ�����ĸ*/

bool if_letter(char c) {
	if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))
		return(true);
	else
		return(false);
}

/*if_number:�ж������ַ��Ƿ�������*/

bool if_number(char c) {
	if (c >= '0'&&c <= '9')
		return(true);
	else
		return(false);
}

/*if_split:�ж������ַ��Ƿ��Ƿָ���*/

bool if_split(char c) {
	if (if_letter(c) || if_number(c))
		return(false);
	else
		return(true);
}

/*if_code:�жϳ����Ƿ����ַ�*/

bool if_code(char c) {
	if (c >= 32&&c <= 126)
		return(true);
	else
		return(false);
}

/*if_line:�жϳ����Ƿ��ǻ��з�*/

bool if_line(char c) {
	if (c == '\n')
		return(true);
	else
		return(false);
}

/*if_word:�ж��Ƿ�Ϊ����*/

bool if_word(char c) {
	if (c == EOF&&wordletter >= WORDLETTER)
	{
		wordletter = false;
		return(true);
	}
	if (if_split(c)) {//��Ϊ�ָ���
		if (wordletter >= WORDLETTER)//�ѳɵ��ʣ�����Ϊ�棬��ռ���
		{
			wordletter = false;
			return(true);
		}
		else
		{
			wordletter = false;
			return(false);
		}//δ�ɵ��ʣ�����Ϊ�٣���ռ���
	}
	else {//��Ϊ��ĸ����
		if (if_letter(c))//��Ϊ��ĸ����������
			wordletter++;
		else if (wordletter >= WORDLETTER)//��Ϊ���֣��ѳɵ���
			;
		else//��Ϊ���֣�δ�ɵ��ʣ�����Ϊ��
			wordletter = false;
		return(false);
	}
}

/*if_wordorder���ж����ַ������ֵ��򣬷���1==s1��ǰ������-1==s2��ǰ������0==���*/

int if_wordorder(char *s1, char *s2) {
	int i;
	for (i = 0; *(s1 + i) != '\0'&&*(s2 + i) != '\0'; i++) {
		if (*(s1 + i) < *(s2 + i))//s1�ֵ�����ǰ
			return(1);
		else if (*(s1 + i) > *(s2 + i))//s2�ֵ�����ǰ
			return(-1);
		else
			;
	}
	if (*(s1 + i) == '\0'&&*(s2 + i) != '\0')//s2���ж�,s1�ֵ�����ǰ
		return(1);
	if (*(s1 + i) != '\0'&&*(s2 + i) == '\0')//s1���ж࣬s2�ֵ�����ǰ
		return(-1);
	return(0);
}

/*if_sameword:�ж����������Ƿ���ͬ*/

bool if_sameword(char *s1, char *s2) {
	int i, j;
	bool flag = false;//�ж��м��з�������ֲ�ͬ�ı�־
	for (i = 0; *(s1 + i) != '\0'&&*(s2 + i) != '\0'; i++) {
		if (if_letter(*(s1 + i)) && if_letter(*(s2 + i))) {//����λ�����߾�Ϊ��ĸ
			if (*(s1 + i) != *(s2 + i)&&abs(*(s1 + i)- *(s2 + i))!=32)//������ȣ�����Ϊ��
				return(false);
		}
		else {//����λ�����߾�Ϊ����
			if (*(s1 + i) != *(s2 + i))//������ȣ���ֹѭ���������Ƿ�Ϊ���ֽ�β
			{
				flag = true;
				break;
			}
		}
	}
	if (flag||(*(s1 + i) != '\0'||*(s2 + i) != '\0')) {
		for (j = i; *(s1 + j) != '\0'; j++) {//�Ӳ�ͬ����
			if (if_number(*(s1 + j)))//��ͬΪ���֣���
				;
			else//��Ϊ���ֽ�β������Ϊ��
				return(false);
		}
		for (j = i; *(s2 + j) != '\0'; j++) {//�Ӳ�ͬ����
			if (if_number(*(s2 + j)))//��ͬΪ���֣���
				;
			else//��Ϊ���ֽ�β������Ϊ��
				return(false);
		}
	}
	return(true);
}

void if_lettercase(char &c)
{
	if (c <= 'z'&&c >= 'a')
		c = c - 32;
	return;
}