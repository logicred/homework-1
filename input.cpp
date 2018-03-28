#include"input.h"
#include <iostream>
#include <cstring>        // for strcpy(), strcat()
#include <io.h>

FILE *fin = NULL;
bool fileflag = false;//�ļ��Ƿ�Ϊ�ձ�ʶ��true�գ�false����
char *dir;
/*input_onefile:�򿪵��ļ�����ʼ��ȡ*/

bool input_onefile_open(void) {
	errno_t err;
	err = fopen_s(&fin,"sample.txt", "r");
	if (err == 1)
	{
		printf("can't open the file\n");
		fclose(fin);
		return(false);
	}
	else
		return(true);
}

bool input_file_open(char *file) {
	errno_t err;
	err = fopen_s(&fin, file, "r");
	if (err == 1)
	{
		printf("can't open the file\n");
		fclose(fin);
		return(false);
	}
	else
		return(true);
}

void input_onefile_close(void) {
	fclose(fin);
}



