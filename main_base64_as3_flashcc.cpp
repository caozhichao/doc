#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <bitset>

using std::bitset;
//#include "base64.h"

char _b64Chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//base64编码
unsigned int base64_encode(char buf[],char output[],unsigned int inputLen);
//base64编码后的buf长度
unsigned int base64_encode_enc_len(unsigned int bufLen);
//base64解码
unsigned int base64_decode(char enc_buf[],char output[],unsigned int enc_buf_len);
//base64解码后的buf长度
unsigned int base64_decode_dec_len(char enc_buf[],unsigned int enc_len);
//base64字符对于的值
unsigned char base64_decode_enc_key(char ch);

unsigned int base64_encode_enc_len(unsigned int bufLen)
{
	unsigned int enc_len;
	if(bufLen % 3 == 0)
	{
		enc_len = bufLen / 3 * 4;
	} else 
	{
		enc_len = (bufLen/3+1) * 4;
	}
	return enc_len;
}

unsigned int base64_encode(char buf[],char output[],unsigned int inputLen)
{
	unsigned char* p = (unsigned char*)buf;
	unsigned char* end = p + inputLen;

	int p_len = 0;
	unsigned int buf_position = 0;
	while(p < end)
	{
		p_len = end - p;
		p_len = p_len >=3?3:p_len;
		output[buf_position++] = _b64Chars[*p >> 2];
		switch(p_len)
		{
			case 1:
				output[buf_position++] = _b64Chars[((*p << 4) & 0x30)];
				output[buf_position++] = '='; 
				output[buf_position++] = '='; 
				break;
			case 2:
				output[buf_position++] = _b64Chars[(*p << 4) & 0x30 | *(p+1) >> 4];
				output[buf_position++] = _b64Chars[(*(p+1) << 2) & 0x3c];
				output[buf_position++] = '=';
				break;
			case 3:
				output[buf_position++] = _b64Chars[(*p << 4) & 0x30 | *(p+1) >> 4];
				output[buf_position++] = _b64Chars[(*(p+1) << 2) & 0x3c | *(p+2) >> 6];
				output[buf_position++] = _b64Chars[*(p+2) & 0x3F];
				break;
		}
		p += p_len;
	}
	return buf_position;
}

unsigned int base64_decode_dec_len(char enc_buf[],unsigned int enc_len)
{
	char *p =  enc_buf + enc_len -1;
	unsigned int num = 0;
	while(*p-- == '=')
	{
		++num;
	}
	return (enc_len / 4) * 3 - num;
}

unsigned char base64_decode_enc_key(char ch)
{
	char key;
	if(ch >= 'A' && ch <= 'Z') key = ch - 'A';
	if(ch >= 'a' && ch <= 'z') key = ch - 'a' + 26;
	if(ch >= '0' && ch <= '9') key = ch - '0' + 52;
	if(ch == '+') key = 62;
	if(ch == '/') key = 63;
	if(ch == '=') key = 0;
	return key;
}

unsigned int base64_decode(char enc_buf[],char output[],unsigned int enc_buf_len)
{
	unsigned char* p = (unsigned char*)enc_buf;
	unsigned char* end = p + enc_buf_len;

	int p_len = 0;
	unsigned int buf_position = 0;

	while(p < end)
	{
		///*
		unsigned char charValue1 = base64_decode_enc_key(*p);
		unsigned char charValue2 = base64_decode_enc_key(*(p+1));
		unsigned char charValue3 = base64_decode_enc_key(*(p+2));
		unsigned char charValue4 = base64_decode_enc_key(*(p+3));
		//*/
		output[buf_position++] = charValue1 << 2 | charValue2 >> 4;
		if (*(p+2) != '='){
			output[buf_position++] = charValue2 << 4 | charValue3 >> 2;
		} 
		if (*(p+3) != '=')
		{
			output[buf_position++] = charValue3 << 6 | charValue4;
		} 
		p += 4;
	}

	return buf_position;

}

int main()
{
	{

		///*
		clock_t t1 = clock();
		
		unsigned int len = 4;
		char* ch = (char*)malloc(len);

		for(int i = 0; i < len;++i)
		{
			ch[i] = -1;
		}

		unsigned int enc_len = base64_encode_enc_len(len);
		char* enc = (char*)malloc(enc_len);
		base64_encode(ch,enc,len);
		clock_t t2 = clock();
		printf("%d\n",t2-t1);

		unsigned int dec_len = base64_decode_dec_len(enc,enc_len);
		char* dec = (char*)malloc(dec_len);
		base64_decode(enc,dec,enc_len);

		clock_t t3 = clock();
		printf("%d\n",t3-t2);

		//printf("1111\n");
		//*/

	}

	return 0;
}