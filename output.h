#pragma once
#include"stdio.h"

extern FILE *fout;

bool output_onefile_open(void);
void output_onefile_close(void);
bool output_file_open(char *file);
void output_print_code(long num);
void output_print_line(long num);
void output_print_word(long num);