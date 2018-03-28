#pragma once
#include"stdio.h"

extern FILE *fin;
extern bool fileflag;//文件是否为空标识，true空，false不空
extern char *dir;

bool input_onefile_open(void);
void input_onefile_close(void);
bool input_file_open(char *file);
