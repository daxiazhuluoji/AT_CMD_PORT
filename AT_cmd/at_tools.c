/*
 * File: at_tools.c
 * Brief:
 * -----
 * File Created: Monday, 11th February 2019 5:50:37 pm
 * Author: ldj
 * -----
 * Last Modified: Tuesday, 12th February 2019 9:43:27 am
 * Modified By: ldj
 * -----
 * Copyright (c) 2019
 */

#include "stdint.h"
#include "string.h"
#include "ctype.h"

void ATCharUpper(uint8_t *at_string)
{
	uint32_t i;
	uint8_t *p = at_string;
	uint8_t str_len = strlen((const char*)at_string);

	for (i = 0; i < str_len; i++)
	{
		if ((*p >= 'a') && (*p <= 'z'))
		{
			*p -= 'a' - 'A';
		}
		p++;
	}
}

const char char_buf[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
char hex2char(uint8_t data)
{
	return char_buf[data];
}

/*
* Conver int to string based on radix (usually 2, 8, 10, and 16)
*/
/*
http://baike.baidu.com/link?url=OEBXFGh29JKAcmOLcN-7BliwpzIP2wi8fIKJSSWpQNJsqkCVh9TfCWpFF_ptB43KNyD71iRa-a7Du-MtfQv9Mq
*/
char *itoa(int num, char *str, int radix)
{
	char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned unum;
	int i = 0, j, k;
	char temp;

	if (radix == 10 && num < 0)
	{
		unum = (unsigned)-num;
		str[i++] = '-';
	}
	else
	{
		unum = (unsigned)num;
	}

	do
	{
		str[i++] = index[unum % (unsigned)radix];
		unum /= radix;
	} while (unum);
	str[i] = '\0';

	if (str[0] == '-')
		k = 1;
	else
		k = 0;

	for (j = k; j <= (i - 1) / 2; j++)
	{
		temp = str[j];
		str[j] = str[i - 1 + k - j];
		str[i - 1 + k - j] = temp;
	}
	return str;
}

/*
// C prototype : void StrToHex(BYTE *pbDest, BYTE *pbSrc, int nLen)
// parameter(s): [OUT] pbDest - 输出缓冲区
// [IN] pbSrc - 字符串
// [IN] nLen - 16进制数的字节数(字符串的长度/2)
// return value:
// remarks : 将字符串转化为16进制数
*/
void StrToHex(uint8_t *pbDest, uint8_t *pbSrc, uint8_t nLen)
{
	char h1, h2;
	uint8_t s1, s2;
	int i;

	for (i = 0; i < nLen; i++)
	{
		h1 = pbSrc[2 * i];
		h2 = pbSrc[2 * i + 1];

		s1 = toupper(h1) - 0x30;
		if (s1 > 9)
			s1 -= 7;

		s2 = toupper(h2) - 0x30;
		if (s2 > 9)
			s2 -= 7;

		pbDest[i] = s1 * 16 + s2;
	}
}
