#include"input.h"

/*input_onefile:�򿪵��ļ�����ʼ��ȡ*/

bool input_onefile_open(void) {
	fin = fopen("sample.txt", "r");
	if (fin == NULL)
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