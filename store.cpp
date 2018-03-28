#include"store.h"
#include"if.h"
#include"malloc.h"
#include"input.h"
#include"string.h"

char *wd=NULL;
char *ph1 = NULL, *ph2 = NULL;
char *word[WORDNUM] = { NULL };
unsigned int hashtime[WORDNUM] = { 0 };//hash���飬�洢Ƶ��

char *ph = NULL;
unsigned int phrasetime[WORDNUM];
char *phf[WORDNUM];//����ǰ
char *phb[WORDNUM];//�����

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
				wd = (char *)malloc(LIMIT * sizeof(char));
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
		if (if_split(c)) {//��Ϊ�ָ���
			if (wordletter >= WORDLETTER)//�ѳɵ��ʣ�����Ϊ�棬��ռ���
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
			}//δ�ɵ��ʣ�����Ϊ�٣���ռ���
		}
		else {//��Ϊ��ĸ����
			  //			printf("bb\n");
			if (if_letter(c))//��Ϊ��ĸ����������
			{
				ph[wordletter] = c;
				wordletter++;
			}
			else if (wordletter >= WORDLETTER)//��Ϊ���֣��ѳɵ���
			{
				ph[wordletter] = c;
				wordletter++;
			}
			else//��Ϊ���֣�δ�ɵ��ʣ�����Ϊ��
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

void store_hashword(void) {
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
		for (i = 0; i < WORDNUM; i++) {//wordmax�ڴ洢hashtime������±꣬0���9��С		
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
	if (phrasetime[flag] == 0)//����޴ʾ���ס
	{
		phrasetime[flag]++;//Ƶ��+1
		phf[flag] = (char*)malloc((strlen(ph1) + 1) * sizeof(char));
		phb[flag] = (char*)malloc((strlen(ph2) + 1) * sizeof(char));
		phf[flag][0] = '\0';
		phb[flag][0] = '\0';
		strcpy_s(phf[flag], strlen(ph1) + 1, ph1);//
		strcpy_s(phb[flag], strlen(ph2) + 1, ph2);//��¼�����ַ�������±�
	}
	else {
		if (if_sameword(phf[flag], ph1) && if_sameword(phb[flag], ph2)) {
			phrasetime[flag]++;//Ƶ��+1
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
				if (phrasetime[(flag + i) % WORDNUM] == 0)//����޴ʾ���ס
				{
					phrasetime[(flag + i) % WORDNUM]++;//Ƶ��+1
					phf[(flag + i) % WORDNUM] = (char*)malloc((strlen(ph1) + 1) * sizeof(char));
					phb[(flag + i) % WORDNUM] = (char*)malloc((strlen(ph2) + 1) * sizeof(char));
					phf[(flag + i) % WORDNUM][0] = '\0';
					phb[(flag + i) % WORDNUM][0] = '\0';
					strcpy_s(phf[(flag + i) % WORDNUM], strlen(ph1) + 1, ph1);//
					strcpy_s(phb[(flag + i) % WORDNUM], strlen(ph2) + 1, ph2);//��¼�����ַ�������±�
					break;
				}
				else {
					if (if_sameword(phf[(flag + i) % WORDNUM], ph1) && if_sameword(phb[(flag + i) % WORDNUM], ph2))//��ͬ
					{
						phrasetime[(flag + i) % WORDNUM]++;//Ƶ��+1
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
		for (i = 0; i < WORDNUM; i++) {//wordmax�ڴ洢hashtime������±꣬0���9��С		
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
