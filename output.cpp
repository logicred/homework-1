#include"output.h"

FILE *fout = NULL;//输出文件指针

/*output_onefile_open：打开输出的单个文件*/

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

bool output_file_open(char *file) {
	errno_t err;
	err = fopen_s(&fout, file, "w");
	if (err == 1)
	{
		printf("can't open the file\n");
		fclose(fout);
		return(false);
	}
	else
		return(true);
}

/*output_onefile_close:关闭输出单文件*/

void output_onefile_close(void) {
	fclose(fout);
	return;
}

/*output_print_code：输出字符数*/

void output_print_code(long num) {
	fprintf(fout, "characters:%ld\n", num);
	return;
}

/*output_print_line：输出行数*/

void output_print_line(long num) {
	fprintf(fout, "lines:%ld\n", num);
	return;
}

/*output_print_word：输出单词数*/

void output_print_word(long num) {
	fprintf(fout, "words:%ld\n", num);
	return;
}