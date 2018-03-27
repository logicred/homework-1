#pragma once
#include"stdio.h"
#include"if.h"
#include"input.h"
#include"output.h"
#include"count.h"
#include"store.h"

/*testpart:用来测试各文件写好的独立函数*/

void testpart(void) {
	printf("%d\n", if_sameword("windows", "windows95"));//1
	printf("%d\n", if_sameword("windows7", "windows95"));//1
	printf("%d\n", if_sameword("windows7", "windows"));//1
	printf("%d\n", if_sameword("iphone4", "iphone5"));//1
	printf("%d\n", if_sameword("windows", "windows32a"));//0
}

int main() {
	char c;
	int i;
//	testpart();
//	getchar();
//	return(0);
	
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
	
	input_onefile_open();
	while (true) {
		c = fgetc(fin);
		count_word(c);
		if (c == EOF)
			break;
	}printf("hehe\n");
	input_onefile_close();

	input_onefile_open();
	wordletter = false;
	for(i=0;i<WORDNUM;i++)
	{
		c=store_word();
		store_hashword(i);
		if (c == 0)
			break;
	}

	input_onefile_close();/**/

	output_onefile_open();

	output_print_code(countcode);
	output_print_line(countline);
	output_print_word(countword);

	printf("kkk\n");
	for (i = 0; i < WORDNUM; i++)
	{
		if (i % 1000000 == 0)
			printf("turn:%d\n", i);
		store_hashword(i);
	}
	store_wordfind();
	printf("jjj\n");

	for (i = 0; i < MAX; i++) {
		fprintf(fout, "%s,%u\n", word[wordmax[i]],hashtime[wordmax[i]]);
			//fprintf(fout, "%s,%u\n", word[hashtime[wordmax[i]][1]], hashtime[wordmax[i]][0]);
	}/**/


	output_onefile_close();
	printf("The program ends\n");
	getchar();//让VS别一闪而过
	return(0);
}