#pragma once
#include"stdio.h"

extern FILE *fin;
extern bool fileflag;//�ļ��Ƿ�Ϊ�ձ�ʶ��true�գ�false����
extern char *dir;

bool input_onefile_open(void);
void input_onefile_close(void);
bool input_file_open(char *file);
