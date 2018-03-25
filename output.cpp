#include"output.h"

FILE *fout = NULL;//输出文件指针

bool output_onefile_open(void) {
	errno_t err;
	err = fopen_s(&fout, "result.txt", "w");
	if (err == 1)
	{
		printf("can't open the file\n");
		fclose(fout);
		return(false);
	}
	else
		return(true);
}

void output_onefile_close(void) {
	fclose(fout);
}

void output_print_code(long num) {
	fprintf(fout, "characters:%ld\n", num);
	return;
}

void output_print_line(long num) {
	fprintf(fout, "lines:%ld\n", num);
	return;
}