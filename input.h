#pragma once
#include"stdio.h"

extern FILE *fin;
extern bool fileflag;//文件是否为空标识，true空，false不空

bool input_onefile_open(void);
void input_onefile_close(void);
