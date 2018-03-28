#include"if.h"
#include"stdio.h"
#include"string.h"
#include"math.h"

long wordletter = false;

/*if_letter:判断输入字符是否是字母*/

bool if_letter(char c) {
	if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))
		return(true);
	else
		return(false);
}

/*if_number:判断输入字符是否是数字*/

bool if_number(char c) {
	if (c >= '0'&&c <= '9')
		return(true);
	else
		return(false);
}

/*if_split:判断输入字符是否是分隔符*/

bool if_split(char c) {
	if (if_letter(c) || if_number(c))
		return(false);
	else
		return(true);
}

/*if_code:判断出入是否是字符*/

bool if_code(char c) {
	if (c >= 32&&c <= 126)
		return(true);
	else
		return(false);
}

/*if_line:判断出入是否是换行符*/

bool if_line(char c) {
	if (c == '\n')
		return(true);
	else
		return(false);
}

/*if_word:判断是否为单词*/

bool if_word(char c) {
	if (c == EOF&&wordletter >= WORDLETTER)
	{
		wordletter = false;
		return(true);
	}
	if (if_split(c)) {//若为分隔符
		if (wordletter >= WORDLETTER)//已成单词，返回为真，清空计数
		{
			wordletter = false;
			return(true);
		}
		else
		{
			wordletter = false;
			return(false);
		}//未成单词，返回为假，清空计数
	}
	else {//若为字母数字
		if (if_letter(c))//若为字母，计数增加
			wordletter++;
		else if (wordletter >= WORDLETTER)//若为数字，已成单词
			;
		else//若为数字，未成单词，返回为假
			wordletter = false;
		return(false);
	}
}

/*if_wordorder：判断两字符串的字典序，返回1==s1在前，返回-1==s2在前，返回0==相等*/

int if_wordorder(char *s1, char *s2) {
	int i;
	for (i = 0; *(s1 + i) != '\0'&&*(s2 + i) != '\0'; i++) {
		if (*(s1 + i) < *(s2 + i))//s1字典序在前
			return(1);
		else if (*(s1 + i) > *(s2 + i))//s2字典序在前
			return(-1);
		else
			;
	}
	if (*(s1 + i) == '\0'&&*(s2 + i) != '\0')//s2还有多,s1字典序在前
		return(1);
	if (*(s1 + i) != '\0'&&*(s2 + i) == '\0')//s1还有多，s2字典序在前
		return(-1);
	return(0);
}

/*if_sameword:判断两个单词是否相同*/

bool if_sameword(char *s1, char *s2) {
	int i, j;
	bool flag = false;//判断中间有否出现数字不同的标志
	for (i = 0; *(s1 + i) != '\0'&&*(s2 + i) != '\0'; i++) {
		if (if_letter(*(s1 + i)) && if_letter(*(s2 + i))) {//若该位置两者均为字母
			if (*(s1 + i) != *(s2 + i)&&abs(*(s1 + i)- *(s2 + i))!=32)//若不相等，返回为假
				return(false);
		}
		else {//若该位置两者均为数字
			if (*(s1 + i) != *(s2 + i))//若不相等，终止循环，检验是否为数字结尾
			{
				flag = true;
				break;
			}
		}
	}
	if (flag||(*(s1 + i) != '\0'||*(s2 + i) != '\0')) {
		for (j = i; *(s1 + j) != '\0'; j++) {//从不同处起步
			if (if_number(*(s1 + j)))//若同为数字，过
				;
			else//不为数字结尾，返回为假
				return(false);
		}
		for (j = i; *(s2 + j) != '\0'; j++) {//从不同处起步
			if (if_number(*(s2 + j)))//若同为数字，过
				;
			else//不为数字结尾，返回为假
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