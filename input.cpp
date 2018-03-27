#include"input.h"

FILE *fin = NULL;
bool fileflag = false;//文件是否为空标识，true空，false不空

/*input_onefile:打开单文件，开始读取*/

bool input_onefile_open(void) {
	errno_t err;
	err = fopen_s(&fin,"123.txt", "r");
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