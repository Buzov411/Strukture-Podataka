#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int read_from_file(char* file_name)
{
	char buffer[128];
	int a, b, c;
//	char garbage1[32], garbage2[32];
	FILE* fp;
	fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		printf("Error!");
		return -1;
	}
	while (!feof(fp)) 
	{
		fgets(buffer, sizeof(buffer), fp);
//		sscanf("%d %n %d %n", &a, &garbage1,&b, &garbage2);
		sscanf(buffer, "%d %d", &a, &b);
		c = a * b;
		printf("%d", c);
	}
	return 0;
}


int main()
{
	read_from_file("datoteka.txt");
	return 0;
}
