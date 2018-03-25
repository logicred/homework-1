#include"if.h"
#include"stdio.h"

/*if_letter:ÅÐ¶ÏÊäÈë×Ö·ûÊÇ·ñÊÇ×ÖÄ¸*/

bool if_letter(char c) {
	if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))
		return(true);
	else
		return(false);
}

/*if_number:ÅÐ¶ÏÊäÈë×Ö·ûÊÇ·ñÊÇÊý×Ö*/

bool if_number(char c) {
	if (c >= '0'&&c <= '9')
		return(true);
	else
		return(false);
}

/*if_split:ÅÐ¶ÏÊäÈë×Ö·ûÊÇ·ñÊÇ·Ö¸ô·û*/

bool if_split(char c) {
	if (if_letter(c) || if_number(c))
		return(false);
	else
		return(true);
}

/*if_code:ÅÐ¶Ï³öÈëÊÇ·ñÊÇ×Ö·û*/

bool if_code(char c) {
	return(true);
}

/*if_line:ÅÐ¶Ï³öÈëÊÇ·ñÊÇ»»ÐÐ·û*/

bool if_line(char c) {
	if (c == '\n')
		return(true);
	else
		return(false);
}