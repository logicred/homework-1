#include"store.h"
#include"if.h"
#include"malloc.h"
#include"input.h"
#include"string.h"

char *wd=NULL;
char *word[WORDNUM] = { NULL };
unsigned int hashtime[WORDNUM] = { 0 };//hash���飬�洢Ƶ��

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
		if (if_split(c)) {//��Ϊ�ָ���
			if (wordletter >= WORDLETTER)//�ѳɵ��ʣ�����Ϊ�棬��ռ���
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
			}//δ�ɵ��ʣ�����Ϊ�٣���ռ���
		}
		else {//��Ϊ��ĸ����
//			printf("bb\n");
			if (if_letter(c))//��Ϊ��ĸ����������
			{
				wd[wordletter] = c;
				wordletter++;				
			}
			else if (wordletter >= WORDLETTER)//��Ϊ���֣��ѳɵ���
			{
				wd[wordletter] = c;
				wordletter++;				
			}
			else//��Ϊ���֣�δ�ɵ��ʣ�����Ϊ��
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
	copy[n + 1] = '\0';  //ȥ�����ֽ�β
	n = 0;
	while (copy[n] != '\0')
	{
		if_lettercase(copy[n]);
		hash = hash * seed + copy[n];
		n++;
	}
	return ((hash & 0x7FFFFFFF) % PRIME);//primeΪһ��������
}

void store_hashword(int x) {
	if (wd == NULL)
		return;
	unsigned int i=0;
	unsigned int flag = store_BKDRHash(wd);
//	printf("%u\n", flag);
	if (hashtime[flag] == 0)//����޴ʾ���ס
	{
		hashtime[flag]++;//Ƶ��+1
		word[flag] = wd;//��¼�����ַ�������±�
	}
	else {
		if (if_sameword(word[flag], wd))//��ͬ
		{
			hashtime[flag]++;//Ƶ��+1
			free(wd);
		}
		else {
			for (i = 0; i<WORDNUM; i++)
			{
				if (hashtime[(flag+i)%WORDNUM] == 0)//����޴ʾ���ס
				{
					hashtime[(flag + i) % WORDNUM]++;//Ƶ��+1
					word[(flag + i) % WORDNUM] = wd;//��¼�����ַ�������±�
					break;
				}
				else {
					if (if_sameword(word[(flag + i) % WORDNUM], wd))//��ͬ
					{
						hashtime[(flag + i) % WORDNUM]++;//Ƶ��+1
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
		for (i = 0; i < WORDNUM; i++) {//wordmax�ڴ洢hashtime������±꣬0���9��С		
			if (hashtime[i] == 0)
				continue;
			if (hashtime[i] >= hashtime[wordmax[j]]) {
				if (j == 0 || (j > 0 && hashtime[i] < hashtime[wordmax[j - 1]]))
					wordmax[j] = i;
			}
		}
	}	
}

