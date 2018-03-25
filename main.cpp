#pragma once
#include"stdio.h"
#include"if.h"
#include"input.h"
#include"output.h"
#include"count.h"
#include"store.h"

int main() {
	char c;
	input_onefile_open();
	while ((c = fgetc(fin)) != EOF) {
		if (fileflag == false)
		{
			count_line();
			fileflag = true;
		}
		if (if_code(c))
			count_code();
		if (if_line(c))
			count_line();
	}
	input_onefile_close();

	output_onefile_open();

	output_print_code(countcode);
	output_print_line(countline);

	output_onefile_close();
	printf("The program ends\n");
	getchar();//让VS别一闪而过
	return(0);
}