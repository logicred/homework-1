#include"input.h"

FILE *fin = NULL;
bool fileflag = false;//�ļ��Ƿ�Ϊ�ձ�ʶ��true�գ�false����

/*input_onefile:�򿪵��ļ�����ʼ��ȡ*/

bool input_onefile_open(void) {
	errno_t err;
	err = fopen_s(&fin,"sample.txt", "r");
	if (err == true)
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