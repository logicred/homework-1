#include"output.h"

FILE *fout = NULL;//����ļ�ָ��

/*output_onefile_open��������ĵ����ļ�*/

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

/*output_onefile_close:�ر�������ļ�*/

void output_onefile_close(void) {
	fclose(fout);
	return;
}

/*output_print_code������ַ���*/

void output_print_code(long num) {
	fprintf(fout, "characters:%ld\n", num);
	return;
}

/*output_print_line���������*/

void output_print_line(long num) {
	fprintf(fout, "lines:%ld\n", num);
	return;
}

/*output_print_word�����������*/

void output_print_word(long num) {
	fprintf(fout, "words:%ld\n", num);
	return;
}