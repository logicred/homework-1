#include"store.h"
#include"if.h"
#include"malloc.h"
#include"input.h"
#include"string.h"

char *wd=NULL;
char *ph1 = NULL, *ph2 = NULL;
char *word[WORDNUM] = { NULL };
unsigned int hashtime[WORDNUM] = { 0 };//hash数组，存储频数

char *ph = NULL;
unsigned int phrasetime[WORDNUM];
char *phf[WORDNUM];//词组前
char *phb[WORDNUM];//词组后

int wordmax[MAX] = { 0 };
int phrasemax[MAX] = { 0 };

char store_word(void) {
	int i = 0;
	char c;
	wd = (char *)malloc(LIMIT * sizeof(char));

	while (true) {
		c = fgetc(fin);

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
				wd = (char *)malloc(LIMIT * sizeof(char));
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
				wd = (char *)malloc(LIMIT * sizeof(char));
				wordletter = false;
			}
		}
	}
}

char store_phrase(void) {
	int i = 0;
	char c;
	ph = (char *)malloc(LIMIT * sizeof(char));
	if (ph == NULL)
	{
		printf("all\n");
		return(1);
	}

	while (true) {
		c = fgetc(fin);
		//		printf("%c\n",c);
		//		printf("%ld\n", wordletter);
		//		printf("hehe\n");
		if (c == EOF&&wordletter >= WORDLETTER)
		{
			ph[wordletter] = '\0';
			wordletter = false;
			return(0);
		}
		if (c == EOF&&wordletter < WORDLETTER)
		{
			free(ph);
			ph = NULL;
			return(0);
		}
		if (if_split(c)) {//若为分隔符
			if (wordletter >= WORDLETTER)//已成单词，返回为真，清空计数
			{
				ph[wordletter] = '\0';
				//				printf("%s\n", word);
				wordletter = false;
				return(1);
			}
			else
			{
				//				printf("aa\n");
				free(ph);
				ph = (char *)malloc(LIMIT * sizeof(char));
				wordletter = false;
			}//未成单词，返回为假，清空计数
		}
		else {//若为字母数字
			  //			printf("bb\n");
			if (if_letter(c))//若为字母，计数增加
			{
				ph[wordletter] = c;
				wordletter++;
			}
			else if (wordletter >= WORDLETTER)//若为数字，已成单词
			{
				ph[wordletter] = c;
				wordletter++;
			}
			else//若为数字，未成单词，返回为假
			{
				free(ph);
				ph = (char *)malloc(LIMIT * sizeof(char));
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
	char copy[LIMIT] = { '\0' };
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

void store_hashword(void) {
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
			if (strcmp(word[flag], wd) > 0)//
			{
//				printf("%s,%s\n", word[flag], wd);
				free(word[flag]);
				word[flag] = wd;//
			}
			else
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
						if (strcmp(word[(flag + i) % WORDNUM], wd) > 0)//	
						{
							free(word[(flag + i) % WORDNUM]);
							word[(flag + i) % WORDNUM] = wd;//
						}
						else
							free(wd);
						break;
					}
				}
			}
		}
	}
}

void store_wordfind(void) {
	int i, j, l;
	int top = 0, bot = MAX - 1;
	int mid = (top + bot) / 2;
	for (j = 0; j < MAX; j++) {
		for (i = 0; i < WORDNUM; i++) {//wordmax内存储hashtime数组的下标，0最大，9最小		
			if (hashtime[i] == 0)
				continue;
			if (hashtime[i] >= hashtime[wordmax[j]]) {
				if (j == 0)
					wordmax[j] = i;
				else {
					for (l = 0; l < j; l++) {
						if (i == wordmax[l])
							goto loop;
					}
					wordmax[j] = i;
				}
			loop:;
			}
		}
	}	
}

void store_hashphrase(void) {
	if (ph1 == NULL || ph2 == NULL|| ph1[0] == '\0' ||ph2[0] == '\0')
		return;
//	printf("hehe\n");
	unsigned int i = 0;
	unsigned int flag = (store_BKDRHash(ph1)+ store_BKDRHash(ph2))%PRIME;
	if (phrasetime[flag] == 0)//如果无词就入住
	{
		phrasetime[flag]++;//频数+1
		phf[flag] = (char*)malloc((strlen(ph1) + 1) * sizeof(char));
		phb[flag] = (char*)malloc((strlen(ph2) + 1) * sizeof(char));
		phf[flag][0] = '\0';
		phb[flag][0] = '\0';
		strcpy_s(phf[flag], strlen(ph1) + 1, ph1);//
		strcpy_s(phb[flag], strlen(ph2) + 1, ph2);//记录所在字符数组的下标
	}
	else {
		if (if_sameword(phf[flag], ph1) && if_sameword(phb[flag], ph2)) {
			phrasetime[flag]++;//频数+1
			if (strcmp(phf[flag], ph1) > 0)//
			{
				//			printf("%s,%s\n", word[flag], wd);
				free(phf[flag]);
				phf[flag] = (char*)malloc((strlen(ph1) + 1) * sizeof(char));
				phf[flag][0] = '\0';
				strcpy_s(phf[flag], strlen(ph1) + 1, ph1);//
			}
			else
				;
			if (strcmp(phb[flag], ph2) > 0)//
			{
				free(phb[flag]);
				phb[flag] = (char*)malloc((strlen(ph2) + 1) * sizeof(char));
				phb[flag][0] = '\0';
				strcpy_s(phb[flag], strlen(ph2) + 1, ph2);
			}
			else
				;//ph2 not free
		}
		else {
			for (i = 0; i<WORDNUM; i++)
			{
				if (phrasetime[(flag + i) % WORDNUM] == 0)//如果无词就入住
				{
					phrasetime[(flag + i) % WORDNUM]++;//频数+1
					phf[(flag + i) % WORDNUM] = (char*)malloc((strlen(ph1) + 1) * sizeof(char));
					phb[(flag + i) % WORDNUM] = (char*)malloc((strlen(ph2) + 1) * sizeof(char));
					phf[(flag + i) % WORDNUM][0] = '\0';
					phb[(flag + i) % WORDNUM][0] = '\0';
					strcpy_s(phf[(flag + i) % WORDNUM], strlen(ph1) + 1, ph1);//
					strcpy_s(phb[(flag + i) % WORDNUM], strlen(ph2) + 1, ph2);//记录所在字符数组的下标
					break;
				}
				else {
					if (if_sameword(phf[(flag + i) % WORDNUM], ph1) && if_sameword(phb[(flag + i) % WORDNUM], ph2))//相同
					{
						phrasetime[(flag + i) % WORDNUM]++;//频数+1
						if (strcmp(phf[(flag + i) % WORDNUM], ph1) > 0)//	
						{
							free(phf[(flag + i) % WORDNUM]);
							phf[(flag + i) % WORDNUM] = (char*)malloc((strlen(ph1) + 1) * sizeof(char));
							phf[(flag + i) % WORDNUM][0] = '\0';
							strcpy_s(phf[(flag + i) % WORDNUM], strlen(ph1) + 1, ph1);//
						}
						else
							;
						if (strcmp(phb[(flag + i) % WORDNUM], ph2) > 0)//	
						{
							free(phb[(flag + i) % WORDNUM]);
							phb[(flag + i) % WORDNUM] = (char*)malloc((strlen(ph2) + 1) * sizeof(char));
							phb[(flag + i) % WORDNUM][0] = '\0';
							strcpy_s(phb[(flag + i) % WORDNUM], strlen(ph2) + 1, ph2);
						}
						else
							;
						break;
					}
				}
			}
		}
	}
}

void store_phrasefind(void) {
	int i, j, l;
	int top = 0, bot = MAX - 1;
	int mid = (top + bot) / 2;
	for (j = 0; j < MAX; j++) {
		for (i = 0; i < WORDNUM; i++) {//wordmax内存储hashtime数组的下标，0最大，9最小		
			if (phrasetime[i] == 0)
				continue;
			if (phrasetime[i] >= phrasetime[phrasemax[j]]) {
				if (j == 0)
					phrasemax[j] = i;
				else {
					for (l = 0; l < j; l++) {
						if (i == phrasemax[l])
							goto loop;
					}
					phrasemax[j] = i;
				}
			loop:;
			}
		}
	}

}
