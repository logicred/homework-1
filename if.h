#pragma once

const char big_letter[] = { 'A','B','C','D' ,'E','F','G','H','I'
	,'J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X'
	,'Y','Z' };//�洢��д��ĸ

const char small_letter[] = { 'a','b','c','d','e','f','g','h','i'
	,'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x',
	'y','z' };//�洢Сд��ĸ

const char number[] = { '0','1','2','3','4','5','6','7','8','9' };
			  //�洢����

bool if_code(char c);
bool if_split(char c);
bool if_number(char c);
bool if_letter(char c);


