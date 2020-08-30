//实现Decomposition算法
#include<stdio.h>
#include<Windows.h>
#include"DegEstCon.h"
int main()
{
	FILE *fp;
	//fp = fopen("rec.txt", "r");
	char filename[40] = "rec.txt";
	fopen_s(&fp, filename, "a+");
	//int cube[80] = { 2,4,6,8,10,12,14,17,19,21,23,25,27,29,32,34,36,38,40,42,44,47,49,51,53,57,62,79};
	//int cube[80] = { 0,2,4,5,6,7,9,11,13,14,15,18,20,22,24,26,32,35,37,39,42,44,46,48,53,55,57,61,68,70,72,79 };
	int cube[80] = { 12,63,78,40,56,49,36,7,11,38,0,26,57,71,55,74,22,58,37,62,50,29 };
	int i;
	int dim, roundnum,flag;
	int N0 = 200;
	dim = 22;
	roundnum = 704;
	//有一个循环
	//GetandTestXVerifyV2();
	GetandTestX();
	//GetandTestXVerifyV2();
	system("pause");
	return 0;
}