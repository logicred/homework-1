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
	testpart();
	getchar();
	return(0);

	input_onefile_open();
	while ((c = fgetc(fin)) != EOF) {
		if (fileflag == false)
		{
			countline++;
			fileflag = true;
		}
		count_code(c);
		count_line(c);
	}
	input_onefile_close();

	input_onefile_open();
	while (true) {
		c = fgetc(fin);
		count_word(c);
		if (c == EOF)
			break;
	}
	input_onefile_close();

	output_onefile_open();

	output_print_code(countcode);
	output_print_line(countline);
	output_print_word(countword);

	output_onefile_close();
	printf("The program ends\n");
	getchar();//让VS别一闪而过
	return(0);
}