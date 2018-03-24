#include"stdio.h"
#include"if.h"
#include"input.h"
#include"output.h"

int main(void) {
	char c;
	input_onefile_open();
	while (true) {
		c = fscanf(fin, "%c");
		
		if (c == EOF)
			break;
	}
	input_onefile_close();
	output_onefile_open();
	output_onefile_close();
	return(0);
}