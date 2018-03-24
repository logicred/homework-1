#include"output.h"

bool output_onefile_open(void) {
	fout = fopen("result.txt", "w");
	if (fout == NULL)
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