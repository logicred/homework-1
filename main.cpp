#pragma once
#include"stdio.h"
#include"if.h"
#include"input.h"
#include"output.h"
#include"count.h"
#include"store.h"
#include"malloc.h"
#include"string.h"
#include <iostream>
#include <cstring>        // for strcpy(), strcat()
#include <io.h>

void testme(char *file);
void listFiles(const char * dir);
/*testpart:用来测试各文件写好的独立函数*/

void testpart(void) {
	listFiles(dir);//
}

void testme(char *file)
{
	int i;
	char c;
	printf("%s\n",file);
	output_onefile_open();

	input_file_open(file);
	if (fin == NULL)
		printf("%d\n", 1);
	while ((c = fgetc(fin)) != EOF) {
		printf("%c", c);
		if (fileflag == false)
		{
			countline++;
			fileflag = true;
		}
		count_code(c);
		count_line(c);
	}printf("ahah\n");
	input_onefile_close();

	printf("hehe\n");
	input_file_open(file);
	while (true) {
		c = fgetc(fin);
		count_word(c);
		if (c == EOF)
		{
			printf("hh\n");
			break;
		}
	}
	input_onefile_close();

	input_file_open(file);
	wordletter = false;
	for (i = 0; i<WORDNUM; i++)
	{
		c = store_word();
		store_hashword();
		if (c == 0)
			break;
	}
	store_wordfind();
	input_onefile_close();

	printf("phrase start\n");
	input_file_open(file);

	ph1 = (char*)malloc(LIMIT * sizeof(char));
	ph2 = (char*)malloc(LIMIT * sizeof(char));
	ph1[0] = '\0';
	ph2[0] = '\0';

	for (i = 0; i<WORDNUM; i++)
	{
		c = store_phrase();
		if (ph != NULL) {
			strcpy_s(ph2, strlen(ph) + 1, ph);
			free(ph);
			store_hashphrase();

			free(ph1);
			ph1 = (char*)malloc(LIMIT * sizeof(char));
			ph1[0] = '\0';
			strcpy_s(ph1, strlen(ph2) + 1, ph2);

			free(ph2);
			ph2 = (char*)malloc(LIMIT * sizeof(char));
			ph2[0] = '\0';
		}
		if (c == 0)
			break;
	}
	store_phrasefind();
	printf("phrase end\n");
	input_onefile_close();

	output_print_code(countcode);
	output_print_line(countline);
	output_print_word(countword);

	for (i = 0; i < MAX; i++) {
		fprintf(fout, "%s,%u\n", word[wordmax[i]], hashtime[wordmax[i]]);
	}
	for (i = 0; i < MAX; i++) {
		fprintf(fout, "%s,%s,%u\n", phf[phrasemax[i]], phb[phrasemax[i]], phrasetime[phrasemax[i]]);
	}

	output_onefile_close();
}

void listFiles(const char * dir)
{
	char dirNew[200];
	printf("haha\n");
	strcpy_s(dirNew, strlen(dir) + 1, dir);
	strcat_s(dirNew, 200, "\\*.*");    // 在目录后面加上"\\*.*"进行第一次搜索

	int handle;
	_finddata_t findData;

	handle = _findfirst(dirNew, &findData);
	if (handle == -1)        // 检查是否成功
		return;

	do
	{
		if (findData.attrib & _A_SUBDIR)
		{
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;
//
			printf("%s\n", findData.name);
			//			cout << findData.name << "\t<dir>\n";

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			strcpy_s(dirNew, strlen(dir) + 1, dir);
			strcat_s(dirNew, 200, "\\");
			strcat_s(dirNew, 200, findData.name);

			listFiles(dirNew);
		}
		else {
			printf("hehe\n");
			printf("%s,%d\n", findData.name, findData.size);
			testme(findData.name);
		}
		//
		//			cout << findData.name << "\t" << findData.size << " bytes.\n";
	} while (_findnext(handle, &findData) == 0);

	_findclose(handle);    // 关闭搜索句柄
}

int main(int argc,char *argv[]) {
//	char c;
//	int i;
//	printf("%s\n", argv[0]);
//	if (argc == 2)//
//		dir = argv[1];
	dir = "C:\\Users\\asus\\Desktop\\123\\123456";
	testpart();////
	getchar();////C:\\Users\\asus\\Desktop\\123
	return(0);////C:\Users\asus\Documents\Visual Studio 2015\Projects\ConsoleApplication4\Debug\ConsoleApplication4.exe

/*	output_onefile_open();
	input_onefile_open();
	while ((c = fgetc(fin)) != EOF) {
		
		if (fileflag == false)
		{
			countline++;
			fileflag = true;
		}
		count_code(c);
		count_line(c);
	}printf("ahah\n");
	input_onefile_close();
	printf("hehe\n");
	input_onefile_open();
	while (true) {
		c = fgetc(fin);
		count_word(c);
		if (c == EOF)
		{
			printf("hh\n");
			break;
		}
	}
	input_onefile_close();

	input_onefile_open();
	wordletter = false;
	for(i=0;i<WORDNUM;i++)
	{
		c=store_word();
		store_hashword();
		if (c == 0)
			break;
	}		
	store_wordfind();
	input_onefile_close();

	printf("phrase start\n");
	input_onefile_open();

	ph1 = (char*)malloc(LIMIT * sizeof(char));
	ph2 = (char*)malloc(LIMIT * sizeof(char));
	ph1[0] = '\0';
	ph2[0] = '\0';

	for (i = 0; i<WORDNUM; i++)
	{
		c = store_phrase();
		if (ph != NULL) {
			strcpy_s(ph2, strlen(ph) + 1, ph);
			free(ph);
			store_hashphrase();

			free(ph1);
			ph1 = (char*)malloc(LIMIT * sizeof(char));
			ph1[0] = '\0';
			strcpy_s(ph1, strlen(ph2) + 1, ph2);

			free(ph2);
			ph2 = (char*)malloc(LIMIT * sizeof(char));
			ph2[0] = '\0';
		}	
		if (c == 0)
			break;
	}
	store_phrasefind();
	printf("phrase end\n");
	input_onefile_close();

	output_print_code(countcode);
	output_print_line(countline);
	output_print_word(countword);

	for (i = 0; i < MAX; i++) {
		fprintf(fout, "%s,%u\n", word[wordmax[i]],hashtime[wordmax[i]]);
	}
	for (i = 0; i < MAX; i++) {
		fprintf(fout, "%s,%s,%u\n", phf[phrasemax[i]], phb[phrasemax[i]], phrasetime[phrasemax[i]]);
	}

	output_onefile_close();*/
	printf("The program ends\n");
	getchar();//让VS别一闪而过
	return(0);
}