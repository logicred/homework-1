#include"store.h"
#include"if.h"
#include"malloc.h"
#include"input.h"
#include"string.h"

char *word[WORDNUM] = { NULL };
unsigned int hashtime[WORDNUM] = {0};//hash数组，存储频数

char store_word(int x) {
	int i = 0;
	char c;
	word[x] = (char *)malloc(50 * sizeof(char));

	while (true) {
		c = fgetc(fin);
//		printf("%c\n",c);
//		printf("%ld\n", wordletter);

		if (c == EOF&&wordletter >= WORDLETTER)
		{
			word[x][wordletter] = '\0';
			wordletter = false;
			return(0);
		}
		if (c == EOF&&wordletter < WORDLETTER)
		{
			free(word[x]);
			word[x] = NULL;
			return(0);
		}
		if (if_split(c)) {//若为分隔符
			if (wordletter >= WORDLETTER)//已成单词，返回为真，清空计数
			{
				word[x][wordletter] = '\0';
//				printf("%s\n", word);
				wordletter = false;
				return(1);
			}
			else
			{
//				printf("aa\n");
				free(word[x]);
				word[x] = (char *)malloc(50 * sizeof(char));
				wordletter = false;
			}//未成单词，返回为假，清空计数
		}
		else {//若为字母数字
//			printf("bb\n");
			if (if_letter(c))//若为字母，计数增加
			{
				word[x][wordletter] = c;
				wordletter++;				
			}
			else if (wordletter >= WORDLETTER)//若为数字，已成单词
			{
				word[x][wordletter] = c;
				wordletter++;				
			}
			else//若为数字，未成单词，返回为假
			{
				free(word[x]);
				word[x] = (char *)malloc(50 * sizeof(char));
				wordletter = false;
			}
		}
	}
}

unsigned int store_BKDRHash(char *str)
{
	int n, i;
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..  
	unsigned int hash = 0;
	char copy[50];
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
		hash = hash * seed + copy[n];
		n++;
	}
	return ((hash & 0x7FFFFFFF) % PRIME);//prime为一个大质数
}

void store_hashsave(unsigned int hashtime[]) {

}