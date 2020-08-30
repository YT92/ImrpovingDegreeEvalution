#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"qsort.h"

//可变长, 
void sortV(unsigned int **a, int p, int r, int len)
{
	if (p<r) {
		int q = partitionV(a, p, r,len);
		sortV(a, p, q - 1,len);
		sortV(a, q + 1, r,len);
	}
}
void swapV(unsigned int *pi, unsigned int *pj, int len)
{
	unsigned int  *temp;
	temp = (unsigned int *)malloc(sizeof(unsigned int)*len);
	memcpy(temp, pi, len * sizeof(unsigned int));
	memcpy(pi, pj, len * sizeof(unsigned int));
	memcpy(pj, temp, len * sizeof(unsigned int));
	free(temp);
}
int ComPV(unsigned int *p1, unsigned int *p2, int len)
{
	int flag = 0;
	int i;
	for (i = 0; i < len; i++)
	{
		flag = 0;
		if (p1[i] != p2[i])
		{
			if (p1[i] < p2[i])
				flag = 1;
			break;
		}

	}
	return flag;
}
int partitionV(unsigned int **a, int p, int r, int len)
{
	int i = p, j = r + 1;
	unsigned int *x = a[p];


	while (1)
	{
		do
		{
			i++;


		} while ((i<r) && (ComPV(a[i], x,len) == 0));
		do
		{
			j--;
			
		} while ((ComPV(a[j], x,len) == 1));
		if (i >= j)break;
		swapV(a[i],a[j],len);
	}
	swapV(x, a[j],len);

	return j;

}


//全变元专用

void sortFV(char**a, int p, int r)
{
	if (p<r) {
		int q = partitionFV(a, p, r);
		sortFV(a, p, q - 1);
		sortFV(a, q + 1, r);
	}
}
void swapFV(char*pi, char*pj)
{
	char  temp[288];
	memcpy(temp, pi, 288 * sizeof(char));
	memcpy(pi, pj, 288 * sizeof(char));
	memcpy(pj, temp, 288 * sizeof(char));



}
int ComPFV(char*p1, char*p2)
{
	int flag = 0;
	int i;
	for (i = 0; i<288; i++)
	{
		flag = 0;
		if (p1[i] != p2[i])
		{
			if (p1[i]<p2[i])
				flag = 1;
			break;
		}

	}

	return flag;
}
int partitionFV(char**a, int p, int r)
{
	int i = p, j = r + 1;
	char *x = a[p];


	while (1)
	{
		do
		{
			i++;


		} while ((i<r) && (ComPFV(a[i], x) == 0));
		do
		{
			j--;

		} while ((ComPFV(a[j], x) == 1));
		if (i >= j)break;
		swapFV(a[i], a[j]);
	}
	swapFV(x, a[j]);

	return j;

}

