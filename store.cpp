#include"store.h"
#include"if.h"
#include"malloc.h"
#include"input.h"
#include"string.h"

char *wd=NULL;
char *word[WORDNUM] = { NULL };
unsigned int hashtime[WORDNUM] = { 0 };//hash数组，存储频数

int wordmax[MAX] = { 0 };

char store_word(void) {
	int i = 0;
	char c;
	wd = (char *)malloc(50 * sizeof(char));

	while (true) {
		c = fgetc(fin);
//		printf("%c\n",c);
//		printf("%ld\n", wordletter);
//		printf("hehe\n");
		if (c == EOF&&wordletter >= WORDLETTER)
		{
			wd[wordletter] = '\0';
			wordletter = false;
			return(0);
		}
		if (c == EOF&&wordletter < WORDLETTER)
		{
			free(wd);
			wd = NULL;
			return(0);
		}
		if (if_split(c)) {//若为分隔符
			if (wordletter >= WORDLETTER)//已成单词，返回为真，清空计数
			{
				wd[wordletter] = '\0';
//				printf("%s\n", word);
				wordletter = false;
				return(1);
			}
			else
			{
//				printf("aa\n");
				free(wd);
				wd = (char *)malloc(50 * sizeof(char));
				wordletter = false;
			}//未成单词，返回为假，清空计数
		}
		else {//若为字母数字
//			printf("bb\n");
			if (if_letter(c))//若为字母，计数增加
			{
				wd[wordletter] = c;
				wordletter++;				
			}
			else if (wordletter >= WORDLETTER)//若为数字，已成单词
			{
				wd[wordletter] = c;
				wordletter++;				
			}
			else//若为数字，未成单词，返回为假
			{
				free(wd);
				wd = (char *)malloc(50 * sizeof(char));
				wordletter = false;
			}
		}
	}
}

unsigned int store_BKDRHash(char *str)
{
	int n = 0, i;
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..  
	unsigned int hash = 0;
	char copy[50] = { '\0' };	
	n = strlen(str);
	n--;
	while ((int)str[n] > 47 && (int)str[n] < 58) {
		n--;
	}
	for (i = 0; i < n + 1; i++)
		copy[i] = str[i];
	copy[n + 1] = '\0';  //去掉数字结尾
	n = 0;
	while (copy[n] != '\0')
	{
		if_lettercase(copy[n]);
		hash = hash * seed + copy[n];
		n++;
	}
	return ((hash & 0x7FFFFFFF) % PRIME);//prime为一个大质数
}

void store_hashword(int x) {
	if (wd == NULL)
		return;
	unsigned int i=0;
	unsigned int flag = store_BKDRHash(wd);
//	printf("%u\n", flag);
	if (hashtime[flag] == 0)//如果无词就入住
	{
		hashtime[flag]++;//频数+1
		word[flag] = wd;//记录所在字符数组的下标
	}
	else {
		if (if_sameword(word[flag], wd))//相同
		{
			hashtime[flag]++;//频数+1
			free(wd);
		}
		else {
			for (i = 0; i<WORDNUM; i++)
			{
				if (hashtime[(flag+i)%WORDNUM] == 0)//如果无词就入住
				{
					hashtime[(flag + i) % WORDNUM]++;//频数+1
					word[(flag + i) % WORDNUM] = wd;//记录所在字符数组的下标
					break;
				}
				else {
					if (if_sameword(word[(flag + i) % WORDNUM], wd))//相同
					{
						hashtime[(flag + i) % WORDNUM]++;//频数+1
						free(wd);
						break;
					}
				}
			}
		}
	}
}

void store_wordfind(void) {
	int i, j;
	int top = 0, bot = MAX - 1;
	int mid = (top + bot) / 2;
	for (j = 0; j < MAX; j++) {
		for (i = 0; i < WORDNUM; i++) {//wordmax内存储hashtime数组的下标，0最大，9最小		
			if (hashtime[i] == 0)
				continue;
			if (hashtime[i] >= hashtime[wordmax[j]]) {
				if (j == 0 || (j > 0 && hashtime[i] < hashtime[wordmax[j - 1]]))
					wordmax[j] = i;
			}
		}
	}	
}

