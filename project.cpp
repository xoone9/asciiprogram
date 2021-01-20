#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//평문과 KEY 입력조건: 영문자 대소문자, 아스키코드에 존재하는 기호

void trans_text(char text[], int ascii_text[])//평문 ascii코드로 변환
{
	for (int i = 0; i < strlen(text); i++)
		ascii_text[i] = (int)text[i];
}

void trans_key(char key[], int ascii_key[], int size, int len_key)//키 ascii코드로 변환
{

	for (int j = 0; j < size; j++)
	{
		if (key[len_key] != NULL)
		{
			ascii_key[j] = (int)key[len_key];
			len_key++;
		}
		else
		{
			len_key = 0;
			ascii_key[j] = (int)key[len_key];
			len_key++;
		}
	}
}

void add(int ascii_text[], int ascii_key[], int sum_ascii[], int size)//평문 ascii + 키 ascii
{
	for (int k = 0; k < size; k++)
		sum_ascii[k] = ascii_text[k] + ascii_key[k];
}



void mod_array(int sum_ascii[], int smod_ascii[], int mod_ascii[], int size)//평문 ascii + 키 ascii mod 26
{
	for (int l = 0; l < size; l++) {
		mod_ascii[l] = sum_ascii[l] % 26;
		smod_ascii[l] = sum_ascii[l] / 26;
	}
}



void trans_alphabet(int mod_ascii[], char substitution[], char alphabet[], int size)//알파벳으로 치환
{
	for (int m = 0; m < size; m++)
	{
		substitution[m] = alphabet[mod_ascii[m]];
	}


}

void result(char sowon[], char substitution[], int size, char key[])
{
	int replace1 = strlen(key) - 1;
	int rr = 0;
	int e_length = size;
	for (int j = size; j > 0; j--) {
		int replace2 = replace1;
		while (replace2 < e_length) {
			sowon[rr] = substitution[replace2];
			replace2 = replace2 + strlen(key);
			rr++;
		}
		replace1--;
	}
}

//복호화


void replace(char sowon[], char dec_substitution[], int size, char dec_key[])
{
	int replace1 = strlen(dec_key) - 1;
	int rr = 0;
	int e_length = size;
	for (int j = 0; j < size; j++) {
		int replace2 = replace1;
		while (replace2 < e_length) {
			dec_substitution[replace2] = sowon[rr];
			replace2 = replace2 + strlen(dec_key);
			rr++;
		}
		replace1--;
	}
}

void retrans_alphabet(int alphabet_num[], char dec_substitution[], char alphabet[], int size)
{
	for (int m = 0; m < size; m++)
	{
		for (int i = 0; i < 26; i++) {
			if (alphabet[i] == dec_substitution[m])
				alphabet_num[m] = i;
		}
	}
}



void calculate(int alphabet_num[], int smod_ascii[], int cal_ascii[], int size)
{
	for (int l = 0; l < size; l++) {
		cal_ascii[l] = (smod_ascii[l] * 26) + alphabet_num[l];
	}
}



void subtraction(int cal_ascii[], int decascii_text[], int decascii_key[], int size)
{
	for (int k = 0; k < size; k++)
		decascii_text[k] = cal_ascii[k] - decascii_key[k];
}




int main(void)
{
	char *text = 0;
	char *key = 0;
	int *ascii_text = 0;
	int *mod_ascii = 0;
	int *smod_ascii = 0;
	char *substitution = 0;
	int *ascii_key = 0;
	int *sum_ascii = 0;
	char *sowon = 0;

	int *cal_ascii = 0;
	char *dec_key = 0;
	int *decascii_key = 0;
	char *dec_substitution = 0;
	int *decascii_text = 0;
	int *alphabet_num = 0;


	int a = 0;//text 입력받을 때 입력 배열 위치
	int b = 0;//key 입력받을 때 입력 배열 위치
	int c = 0;//dec_key 입력받을 때 입력 배열 위치
	int len_key = 0;//key 아스키코드로 바꿀 때 키가 평문보다 짧을 경우 사용
	int size;//text FILE의 크기
	int count;//text FILE 한글자씩 값 읽음

	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

	FILE *fp = fopen("text.txt", "r");//평문파일 입력

	fseek(fp, 0, SEEK_END);//파일 포인터를 파일의 끝으로 이동시킴
	size = ftell(fp);//파일 포인터의 현재 위치를 얻음

	text = (char*)malloc((size + 1) * sizeof(char));
	key = (char*)malloc((size + 1) * sizeof(char));
	ascii_text = (int*)malloc((size + 1) * sizeof(int));
	ascii_key = (int*)malloc((size + 1) * sizeof(int));
	sum_ascii = (int*)malloc((size + 1) * sizeof(int));
	mod_ascii = (int*)malloc((size + 1) * sizeof(int));
	smod_ascii = (int*)malloc((size + 1) * sizeof(int));
	substitution = (char*)malloc((size + 1) * sizeof(char));
	sowon = (char*)malloc((size + 1) * sizeof(char));

	cal_ascii = (int*)malloc((size + 1) * sizeof(int));
	dec_key = (char*)malloc((size + 1) * sizeof(char));
	decascii_key = (int*)malloc((size + 1) * sizeof(int));
	dec_substitution = (char*)malloc((size + 1) * sizeof(char));
	decascii_text = (int*)malloc((size + 1) * sizeof(int));
	alphabet_num = (int*)malloc((size + 1) * sizeof(int));
	//평문파일의 길이만큼 동적메모리 할당

	fseek(fp, 0, SEEK_SET);//파일 포인터를 파일은 처음으로 이동시킴

	for (int i = 0; i < size; i++)
	{
		text[i] = fgetc(fp);
	}
	fclose(fp);

	printf("<key의 조건>\n\n");
	printf("1. key의 길이는 평문의 길이보다 짧아야한다.\n2. key는 영어 소문자, 대문자, 문자(! \" # $ % & \' ( ) * + , . / @ : ; < = > ? [ \ ] ^ _ { | } ~) 가능하다.\n\n--------------------------\n");
	printf("key를 입력하시오. \n"); //키 입력
	while (1)
	{
		key[b] = getchar();
		if (key[b++] == '\n')
			break;
	}
	key[b - 1] = NULL;

	trans_text(text, ascii_text);
	trans_key(key, ascii_key, size, len_key);
	add(ascii_text, ascii_key, sum_ascii, size);
	mod_array(sum_ascii, smod_ascii, mod_ascii, size);
	trans_alphabet(mod_ascii, substitution, alphabet, size);
	result(sowon, substitution, size, key);


	printf("\n");
	printf("치환암호문은->");
	for (int i = 0; i < size; i++)
		printf("%c", substitution[i]);
	printf("\n");

	printf("전치암호문은->");
	for (int i = 0; i < size; i++)
		printf("%c", sowon[i]);
	printf("\n--------------------------\n");


	printf("<복호화를 원하면 key를 한번 더 입력하세요.>\n\n");
	printf("<key의 조건>\n\n");
	printf("1. key의 길이는 평문의 길이보다 짧아야한다.\n2. key는 영어 소문자, 대문자, 문자(! \" # $ % & \' ( ) * + , . / @ : ; < = > ? [ \ ] ^ _ { | } ~) 가능하다.\n\n--------------------------\n");

	while (1)
	{
		dec_key[c] = getchar();
		if (dec_key[c++] == '\n')
			break;
	}
	dec_key[c - 1] = NULL;

	replace(sowon, dec_substitution, size, dec_key);
	trans_key(dec_key, decascii_key, size, len_key);
	retrans_alphabet(alphabet_num, dec_substitution, alphabet, size);
	calculate(alphabet_num, smod_ascii, cal_ascii, size);
	subtraction(cal_ascii, decascii_text, decascii_key, size);

	printf("\n");
	printf("평문은->");
	for (int i = 0; i < size; i++)
		printf("%c", decascii_text[i]);
	printf("\n");

	free(text);
	free(key);
	free(ascii_text);
	free(ascii_key);
	free(sum_ascii);
	free(mod_ascii);
	free(substitution);
	free(sowon);

	free(cal_ascii);
	free(dec_key);
	free(decascii_key);
	free(decascii_text);
	free(dec_substitution);
	free(alphabet_num);
	//동적메모리 할당 해제
	return 0;
}