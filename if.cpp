#include"if.h"
#include"stdio.h"

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
	return(true);
}

/*if_line:�жϳ����Ƿ��ǻ��з�*/

bool if_line(char c) {
	if (c == '\n')
		return(true);
	else
		return(false);
}