#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include"qsort.h"

//比较函数
int compareV(unsigned int a[], unsigned int b[], int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		if (a[i] != b[i])
			return 0;
	}
	return 1;

}
//约化函数
int reduceV(unsigned int **poly, int size, int Len)
{
	int i, j, k;
	char *flag;
	unsigned int **temp;
	flag = (char *)malloc(sizeof(char)*size);
	memset(flag, 0, sizeof(char)*size);
	temp = (unsigned int **)malloc(sizeof(unsigned int *)*size);
	for (i = 0; i < size; i++)
	{
		temp[i] = (unsigned int *)malloc(sizeof(unsigned int) * Len);
	}

	//for (i = 0; i < size-1 && (flag[i]==0); i++)
	//排序
	sortV(poly, 0, size - 1, Len);
	//比较
	//for (i = 0; i < size-1; i++)
	i = 0;
	while (i<size - 1)
	{
		if (compareV(poly[i], poly[i + 1],Len))
		{
			flag[i] = 1;
			flag[i + 1] = 1;
			i = i + 2;
		}
		else
		{
			i++;
		}

	}
	k = 0;
	//取出flag为0的项
	for (i = 0; i < size; i++)
	{
		if (flag[i] == 0)
		{
			for (j = 0; j < 8; j++)
			{
				temp[k][j] = poly[i][j];
			}
			k++;
		}
	}
	//将约化后的结果重新赋值给poly
	//
	for (i = 0; i < size; i++)
	{
		memset(poly[i], 0, sizeof(unsigned int) * 8);
	}
	for (i = 0; i < k; i++)
	{
		for (j = 0; j < 8; j++)
		{
			poly[i][j] = temp[i][j];
		}
	}

	for (i = 0; i < size; i++)
	{
		free(temp[i]);
	}
	free(temp);
	free(flag);
	return k;
}

//加法四变元
int addition4V(unsigned int **s1, unsigned int **s2, unsigned int **s3, unsigned int **s4, int size1, int size2, int size3, int size4, unsigned int **res)
{

	//printf("%d,%d,%d,%d\n", size1, size2, size3, size4);
	int i, j;
	unsigned int **temp;
	int size;
	size = size1 + size2 + size3 + size4;
	temp = (unsigned int **)malloc(sizeof(unsigned int*)*size);
	//直接放到一块, 然后进行约化即可
	for (i = 0; i < size; i++)
	{
		temp[i] = (unsigned int *)malloc(sizeof(unsigned int) * 8);
	}
	//吞并s1
	for (i = 0; i < size1; i++)
	{
		for (j = 0; j < 8; j++)
		{
			temp[i][j] = s1[i][j];
		}
	}
	//吞并s2
	for (i = 0; i < size2; i++)
	{
		for (j = 0; j < 8; j++)
		{
			temp[i + size1][j] = s2[i][j];
		}

	}
	//吞并s3
	for (i = 0; i < size3; i++)
	{
		for (j = 0; j < 8; j++)
		{
			temp[i + size1 + size2][j] = s3[i][j];
		}
	}
	//吞并s4
	for (i = 0; i < size4; i++)
	{
		for (j = 0; j < 8; j++)
		{
			temp[i + size1 + size2 + size3][j] = s4[i][j];
			//printf("%d", s4[i][j]);
		}
	}
	//size = reduce(temp, size);
	size = reduceV(temp, size,8);
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < 8; j++)
		{
			res[i][j] = temp[i][j];
		}
	}
	for (i = 0; i < size1 + size2 + size3 + size4; i++)
	{
		free(temp[i]);
	}
	free(temp);
	return size;
}

//加法五变元
int addition5V(unsigned int **s1, unsigned int **s2, unsigned int **s3, unsigned int **s4, unsigned int **s5, int size1, int size2, int size3, int size4, int size5, unsigned int **res)
{

	//printf("%d,%d,%d,%d\n", size1, size2, size3, size4);
	int i, j;
	unsigned int **temp;
	int size;
	size = size1 + size2 + size3 + size4+size5;
	temp = (unsigned int **)malloc(sizeof(unsigned int*)*size);
	//直接放到一块, 然后进行约化即可
	for (i = 0; i < size; i++)
	{
		temp[i] = (unsigned int *)malloc(sizeof(unsigned int) * 8);
	}
	//吞并s1
	for (i = 0; i < size1; i++)
	{
		for (j = 0; j < 8; j++)
		{
			temp[i][j] = s1[i][j];
		}
	}
	//吞并s2
	for (i = 0; i < size2; i++)
	{
		for (j = 0; j < 8; j++)
		{
			temp[i + size1][j] = s2[i][j];
		}

	}
	//吞并s3
	for (i = 0; i < size3; i++)
	{
		for (j = 0; j < 8; j++)
		{
			temp[i + size1 + size2][j] = s3[i][j];
		}
	}
	//吞并s4
	for (i = 0; i < size4; i++)
	{
		for (j = 0; j < 8; j++)
		{
			temp[i + size1 + size2 + size3][j] = s4[i][j];
			//printf("%d", s4[i][j]);
		}
	}
	//吞并s5
	for (i = 0; i < size5; i++)
	{
		for (j = 0; j < 8; j++)
		{
			temp[i + size1 + size2 + size3+size4][j] = s5[i][j];
			//printf("%d", s4[i][j]);
		}
	}
	//size = reduce(temp, size);
	size = reduceV(temp, size, 8);
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < 8; j++)
		{
			res[i][j] = temp[i][j];
		}
	}
	for (i = 0; i < size1 + size2 + size3 + size4+size5; i++)
	{
		free(temp[i]);
	}
	free(temp);
	return size;
}

//乘法
int multi(unsigned int **s1, unsigned int **s2, int size1, int size2, unsigned int **res)
{
	int i, j, k;
	int size;
	unsigned int **temp;
	size = size1*size2;
	temp = (unsigned int **)malloc(sizeof(unsigned int *)*size);
	for (i = 0; i < size; i++)
	{
		temp[i] = (unsigned int *)malloc(sizeof(unsigned int) * 8);
	}
	for (i = 0; i < size1; i++)
	{
		for (j = 0; j < size2; j++)
		{
			for (k = 0; k < 8; k++)
			{
				temp[i*size2 + j][k] = s1[i][k] | s2[j][k];//(s1[i][k]+ s2[j][k])&0x01+ s1[i][k]*s2[j][k];
														   //printf("%d", temp[i*size2 + j][k]);
			}
		}
	}
	//size = reduce(temp, size1*size2);
	size = reduceV(temp, size1*size2,8);
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < 8; j++)
		{
			res[i][j] = temp[i][j];
		}
	}
	for (i = 0; i < size1*size2; i++)
	{
		free(temp[i]);
	}
	free(temp);
	return size;
}

//
void ComANFwithCubeVariable(unsigned int ***s, int size[], int N0, int cube[], int dim)
{
	int i, j, k, m, l, tempdeg = 0;
	FILE *fp;
	unsigned __int64 memsize = 400000;
	fopen_s(&fp, "ANFs.txt", "w");
	unsigned int **f1, **f2, **f3, **t1, **t2, **t3;
	unsigned int ***SIV, ***SKey;
	unsigned int SizeSIV[128] = { 0 };
	unsigned int SizeSKey[128] = { 0 };
	f1 = (unsigned int  **)malloc(sizeof(unsigned int  *) * memsize);
	f2 = (unsigned int  **)malloc(sizeof(unsigned int  *) * memsize);
	f3 = (unsigned int  **)malloc(sizeof(unsigned int  *) * memsize);
	t1 = (unsigned int  **)malloc(sizeof(unsigned int  *) * memsize);
	t2 = (unsigned int  **)malloc(sizeof(unsigned int  *) * memsize);
	t3 = (unsigned int  **)malloc(sizeof(unsigned int  *) * memsize);
	for (i = 0; i < memsize; i++)
	{
		f1[i] = (unsigned int  *)malloc(sizeof(unsigned int) * 8);
		f2[i] = (unsigned int  *)malloc(sizeof(unsigned int) * 8);
		f3[i] = (unsigned int  *)malloc(sizeof(unsigned int) * 8);
		t1[i] = (unsigned int  *)malloc(sizeof(unsigned int) * 8);
		t2[i] = (unsigned int  *)malloc(sizeof(unsigned int) * 8);
		t3[i] = (unsigned int  *)malloc(sizeof(unsigned int) * 8);
		memset(f1[i], 0, sizeof(unsigned int) * 8);
		memset(f2[i], 0, sizeof(unsigned int) * 8);
		memset(f3[i], 0, sizeof(unsigned int) * 8);
		memset(t1[i], 0, sizeof(unsigned int) * 8);
		memset(t2[i], 0, sizeof(unsigned int) * 8);
		memset(t3[i], 0, sizeof(unsigned int) * 8);
	}
	//Key寄存器和IV寄存器
	SIV = (unsigned int ***)malloc(sizeof(unsigned int **) * 128);
	SKey = (unsigned int ***)malloc(sizeof(unsigned int **) * 128);
	for (i = 0; i < 128; i++)
	{
		SIV[i] = (unsigned int **)malloc(sizeof(unsigned int*) * 1);
		SIV[i][0] = (unsigned int *)malloc(sizeof(unsigned int) * 8);

		SKey[i] = (unsigned int **)malloc(sizeof(unsigned int*) * 1);
		SKey[i][0] = (unsigned int *)malloc(sizeof(unsigned int) * 8);
	}
	int size1, size2, size3, round;
	//int deg[288] = {0};
	int deg = 0;



	//初始化: 密钥比特填充, cube变元填充, 常值填充
	//填充密钥比特
	//每一个比特占用一个8字节的char
	//前80比特表示的是IV 
	//s[i][0][0]: IV0-IV31, 低位表示IV0
	//s[i][0][1]: IV32-IV63, 低位表示IV32
	//s[i][0][2]: IV64-IV79, 低位表示IV64
	//s[i][0][3]: IV80-IV127, 低位表示IV80

	//s[i][0][4]: K0-K31, 低位表示K0
	//s[i][0][5]: K32-K63, 低位表示K32
	//s[i][0][6]: K64-K79, 低位表示K64
	//s[i][0][7]: K80-K127, 低位表示K80

	//初始化住寄存器
	for (i = 0; i < dim; i++)
	{
		if (cube[i] < 84)
		{
			s[93 + cube[i]][0][cube[i] >> 5] = s[93 + cube[i]][0][cube[i] >> 5] | (0x01 << (cube[i] & 0x1f));
			size[93 + cube[i]] = 1;
		}
		else
		{
			s[177+ (cube[i] - 84)][0][cube[i] >> 5] = s[177 + (cube[i] - 84)][0][cube[i] >> 5] | (0x01 << (cube[i] & 0x1f));
			size[177 + (cube[i]-84)] = 1;
		}
	}

	//加载密钥,先填充k0-k92
	for (i = 0; i < 93; i++)
	{
		s[i][0][4 + (i >> 5)] = s[i][0][4 + (i >> 5)] | (0x01 << (i & 0x1f));
		size[i] = 1;
	}

	for (i = 221; i < 287; i++)
		size[i] = 1;

	//初始化IV寄存器和Key寄存器
	//127-0
	for (i = 0; i < 128; i++)
	{
		SIV[127-i][0][i>>5]= (0x01 << (i & 0x1f));
		SKey[127 - i][0][4+(i >> 5)] = (0x01 << (i & 0x1f));
		SizeSIV[127 - i] = 1;
		SizeSKey[127 - i] = 1;
	}
	m = 0;
	round = N0;
	//每一轮最高次项的系数
	for (i = 0; i < round; i++)
	{
		printf("round %d\n", i);
		for (k = 0; k < memsize; k++)
		{
			memset(f1[i], 0, sizeof(unsigned int) * 8);
			memset(f2[i], 0, sizeof(unsigned int) * 8);
			memset(f3[i], 0, sizeof(unsigned int) * 8);
			memset(t1[i], 0, sizeof(unsigned int) * 8);
			memset(t2[i], 0, sizeof(unsigned int) * 8);
			memset(t3[i], 0, sizeof(unsigned int) * 8);
		}
		size1 = multi(s[91 - 1], s[92 - 1], size[91 - 1], size[92 - 1], f1);
		size1 = addition5V(f1, s[66 - 1], s[93 - 1], s[171 - 1], SIV[0], size1, size[66 - 1], size[93 - 1], size[171 - 1], SizeSIV[0], t1);

		//s162+s175*s176+s177+s264
		size2 = multi(s[175 - 1], s[176 - 1], size[175 - 1], size[176 - 1], f2);
		size2 = addition4V(f2, s[162 - 1], s[177 - 1], s[264 - 1], size2, size[162 - 1], size[177 - 1], size[264 - 1], t2);
		//s243+s286*s287+s288+s69
		size3 = multi(s[286 - 1], s[287 - 1], size[286 - 1], size[287 - 1], f3);
		//printf("%d,%d,%d,%d\n", size3, size[243 - 1], size[288 - 1], size[69 - 1]);
		size3 = addition5V(f3, s[243 - 1], s[288 - 1], s[69 - 1],SKey[0], size3, size[243 - 1], size[288 - 1], size[69 - 1],SizeSKey[0],t3);

		//shift咯
		//首先是内部状态比特的移位
		for (j = 92; j >0; j--)
		{
			//首先要memset, 将其余的东西都赋值为0
			for (k = 0; k < size[j]; k++)
				memset(s[j][k], 0, sizeof(unsigned int) * 8);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 8; l++)
				{
					s[j][k][l] = s[j - 1][k][l];
				}
			}
			size[j] = size[j - 1];
		}

		for (j = 176; j >93; j--)
		{
			//首先要memset, 将其余的东西都赋值为0
			for (k = 0; k < size[j]; k++)
				memset(s[j][k], 0, sizeof(unsigned int) * 8);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 8; l++)
				{
					s[j][k][l] = s[j - 1][k][l];
				}
			}
			size[j] = size[j - 1];
		}

		for (j = 287; j >177; j--)
		{
			//首先要memset, 将其余的东西都赋值为0
			for (k = 0; k < size[j]; k++)
				memset(s[j][k], 0, sizeof(unsigned int) * 8);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 8; l++)
				{
					s[j][k][l] = s[j - 1][k][l];
				}
			}
			size[j] = size[j - 1];
		}
		//t1,t2,t3, 分别赋值给s0,s93, s177
		//更新s0
		for (k = 0; k < size[0]; k++)
			memset(s[0][k], 0, sizeof(unsigned int) * 8);
		for (j = 0; j < size3; j++)
		{
			for (k = 0; k < 8; k++)
				s[0][j][k] = t3[j][k];
		}
		size[0] = size3;
		//更新s93
		for (k = 0; k < size[93]; k++)
			memset(s[93][k], 0, sizeof(unsigned int) * 8);
		for (j = 0; j < size1; j++)
		{
			for (k = 0; k < 8; k++)
				s[93][j][k] = t1[j][k];
		}
		size[93] = size1;
		//更新s177
		for (k = 0; k < size[177]; k++)
			memset(s[177][k], 0, sizeof(unsigned int) * 8);
		for (j = 0; j < size2; j++)
		{
			for (k = 0; k < 8; k++)
				s[177][j][k] = t2[j][k];
		}
		size[177] = size2;

		for (j = 0; j < 8; j++)
		{
			t1[0][j] = SIV[0][0][j];
			t2[0][j] = SKey[0][0][j];
		}
		//更新SIV和SKey
		for (j = 0; j < 127; j++)
		{
			for (k = 0; k < 8; k++)
			{
				SIV[j][0][k] = SIV[j + 1][0][k];
				SKey[j][0][k] = SKey[j + 1][0][k];
			}
		}
		for (k = 0; k < 8; k++)
		{
			SIV[127][0][k] = t1[0][k];
			SKey[127][0][k] = t2[0][k];
		}
	}
	for (l = 0; l < 288; l++)
	{
		printf("%d,", size[l]);
		for (i = 0; i < size[l]; i++)
		{
			for (j = 0; j < 4; j++)
			{
				for (k = 0; k < 32; k++)
				{
					if (((s[l][i][j] >> k) & 0x01) == 1)
					{
						fprintf(fp, "v(%d)", j * 32 + k);
					}
				}
			}
			

			for (j = 4; j < 8; j++)
			{
				for (k = 0; k < 32; k++)
				{
					if (((s[l][i][j] >> k) & 0x01) == 1)
					{
						fprintf(fp, "k(%d)", (j - 4) * 32 + k);
					}
				}
			}
			//fprintf(fp, "\n");
			int summ = 0;
			for (j = 0; j < 8; j++)
				summ = summ + s[l][i][j];
			if (summ == 0)
				fprintf(fp, "1");
			if(i<size[l]-1)
				fprintf(fp, "+");
		}
		fprintf(fp, "\n");
	}


	for (i = 0; i < memsize; i++)
	{
		free(f1[i]);
		free(f2[i]);
		free(f3[i]);
		free(t1[i]);
		free(t2[i]);
		free(t3[i]);
	}
	free(f1);
	free(f2);
	free(f3);
	free(t1);
	free(t2);
	free(t3);
	for (i = 0; i < 128; i++)
	{
		free(SIV[i][0]);
		free(SKey[i][0]);
	}
	for (i = 0; i < 128; i++)
	{
		free(SIV[i]);
		free(SKey[i]);
	}
	free(SIV);
	free(SKey);
	fclose(fp);
}


//分寄存器版本
void ComANFwithCubeVariableV2(unsigned int ***A, unsigned int ***B, unsigned int ***C, int sizeA[], int sizeB[], int sizeC[], int N0, int cube[], int dim)
{
	int i, j, k, m, l, tempdeg = 0;
	FILE *fp;
	unsigned __int64 memsize = 400000;
	fopen_s(&fp, "ANFs.txt", "w");
	unsigned int **f1, **f2, **f3, **t1, **t2, **t3;
	unsigned int ***SIV, ***SKey;
	unsigned int SizeSIV[128] = { 0 };
	unsigned int SizeSKey[128] = { 0 };
	f1 = (unsigned int  **)malloc(sizeof(unsigned int  *) * memsize);
	f2 = (unsigned int  **)malloc(sizeof(unsigned int  *) * memsize);
	f3 = (unsigned int  **)malloc(sizeof(unsigned int  *) * memsize);
	t1 = (unsigned int  **)malloc(sizeof(unsigned int  *) * memsize);
	t2 = (unsigned int  **)malloc(sizeof(unsigned int  *) * memsize);
	t3 = (unsigned int  **)malloc(sizeof(unsigned int  *) * memsize);
	for (i = 0; i < memsize; i++)
	{
		f1[i] = (unsigned int  *)malloc(sizeof(unsigned int) * 8);
		f2[i] = (unsigned int  *)malloc(sizeof(unsigned int) * 8);
		f3[i] = (unsigned int  *)malloc(sizeof(unsigned int) * 8);
		t1[i] = (unsigned int  *)malloc(sizeof(unsigned int) * 8);
		t2[i] = (unsigned int  *)malloc(sizeof(unsigned int) * 8);
		t3[i] = (unsigned int  *)malloc(sizeof(unsigned int) * 8);
		memset(f1[i], 0, sizeof(unsigned int) * 8);
		memset(f2[i], 0, sizeof(unsigned int) * 8);
		memset(f3[i], 0, sizeof(unsigned int) * 8);
		memset(t1[i], 0, sizeof(unsigned int) * 8);
		memset(t2[i], 0, sizeof(unsigned int) * 8);
		memset(t3[i], 0, sizeof(unsigned int) * 8);
	}
	//Key寄存器和IV寄存器
	SIV = (unsigned int ***)malloc(sizeof(unsigned int **) * 128);
	SKey = (unsigned int ***)malloc(sizeof(unsigned int **) * 128);
	for (i = 0; i < 128; i++)
	{
		SIV[i] = (unsigned int **)malloc(sizeof(unsigned int*) * 1);
		SIV[i][0] = (unsigned int *)malloc(sizeof(unsigned int) * 8);
		memset(SIV[i][0], 0, sizeof(unsigned int) * 8);

		SKey[i] = (unsigned int **)malloc(sizeof(unsigned int*) * 1);
		SKey[i][0] = (unsigned int *)malloc(sizeof(unsigned int) * 8);
		memset(SKey[i][0], 0, sizeof(unsigned int) * 8);
	}
	int size1, size2, size3, round;
	//int deg[288] = {0};
	int deg = 0;



	//初始化: 密钥比特填充, cube变元填充, 常值填充
	//填充密钥比特
	//每一个比特占用一个8字节的char
	//前80比特表示的是IV 
	//s[i][0][0]: IV0-IV31, 低位表示IV0
	//s[i][0][1]: IV32-IV63, 低位表示IV32
	//s[i][0][2]: IV64-IV79, 低位表示IV64
	//s[i][0][3]: IV80-IV127, 低位表示IV80

	//s[i][0][4]: K0-K31, 低位表示K0
	//s[i][0][5]: K32-K63, 低位表示K32
	//s[i][0][6]: K64-K79, 低位表示K64
	//s[i][0][7]: K80-K127, 低位表示K80

	//初始化住寄存器
	for (i = 0; i < dim; i++)
	{
		if (cube[i] < 84)
		{
			B[83 - cube[i]][0][cube[i] >> 5] = B[83 - cube[i]][0][cube[i] >> 5] | (0x01 << (cube[i] & 0x1f));
			sizeB[83 - cube[i]] = 1;
		}
		else
		{
			C[110 - (cube[i] - 84)][0][cube[i] >> 5] = C[110 - (cube[i] - 84)][0][cube[i] >> 5] | (0x01 << (cube[i] & 0x1f));
			sizeC[110 - (cube[i] - 84)] = 1;
		}
	}

	//加载密钥,先填充k0-k92
	for (i = 0; i < 93; i++)
	{
		A[92 - i][0][4 + (i >> 5)] = A[92 - i][0][4 + (i >> 5)] | (0x01 << (i & 0x1f));
		sizeA[92 - i] = 1;
	}

	for (i = 1; i < 67; i++)
		sizeC[i] = 1;

	//初始化IV寄存器和Key寄存器
	//127-0
	for (i = 0; i < 128; i++)
	{
		SIV[127 - i][0][i >> 5] = (0x01 << (i & 0x1f));
		SKey[127 - i][0][4 + (i >> 5)] = (0x01 << (i & 0x1f));
		SizeSIV[127 - i] = 1;
		SizeSKey[127 - i] = 1;
	}
	m = 0;
	round = N0;
	//每一轮最高次项的系数
	for (i = 0; i < round; i++)
	{
		//printf("round %d\n", i);
		for (k = 0; k < memsize; k++)
		{
			memset(f1[i], 0, sizeof(unsigned int) * 8);
			memset(f2[i], 0, sizeof(unsigned int) * 8);
			memset(f3[i], 0, sizeof(unsigned int) * 8);
			memset(t1[i], 0, sizeof(unsigned int) * 8);
			memset(t2[i], 0, sizeof(unsigned int) * 8);
			memset(t3[i], 0, sizeof(unsigned int) * 8);
		}
		size1 = multi(A[i + 2], A[i + 1], sizeA[i + 2], sizeA[i + 1], f1);
		size1 = addition5V(f1, A[i + 27], A[i], B[i + 6], SIV[0], size1, sizeA[i + 27], sizeA[i], sizeB[i + 6], SizeSIV[0], t1);

		//s162+s175*s176+s177+s264
		size2 = multi(B[i + 2], B[i + 1], sizeB[i + 2], sizeB[i + 1], f2);
		size2 = addition4V(f2, B[i + 15], B[i], C[i + 24], size2, sizeB[i + 15], sizeB[i], sizeC[i + 24], t2);
		//s243+s286*s287+s288+s69
		size3 = multi(C[i + 2], C[i + 1], sizeC[i + 2], sizeC[i + 1], f3);
		//printf("%d,%d,%d,%d\n", size3, size[243 - 1], size[288 - 1], size[69 - 1]);
		size3 = addition5V(f3, C[i + 45], C[i], A[i + 24], SKey[0], size3, sizeC[i + 45], sizeC[i], sizeA[i + 24], SizeSKey[0], t3);


		//t1,t2,t3, 分别赋值给B[i+84],C[i+110], A[i+93]
		//更新s0

		for (j = 0; j < size3; j++)
		{
			for (k = 0; k < 8; k++)
				A[i + 93][j][k] = t3[j][k];
		}
		sizeA[i + 93] = size3;
		//更新s93
		for (j = 0; j < size1; j++)
		{
			for (k = 0; k < 8; k++)
				B[i + 84][j][k] = t1[j][k];
		}
		sizeB[i + 84] = size1;
		//更新s177
		for (j = 0; j < size2; j++)
		{
			for (k = 0; k < 8; k++)
				C[i + 111][j][k] = t2[j][k];
		}
		sizeC[i + 111] = size2;

		for (j = 0; j < 8; j++)
		{
			t1[0][j] = SIV[0][0][j];
			t2[0][j] = SKey[0][0][j];
		}
		//更新SIV和SKey
		for (j = 0; j < 127; j++)
		{
			for (k = 0; k < 8; k++)
			{
				SIV[j][0][k] = SIV[j + 1][0][k];
				SKey[j][0][k] = SKey[j + 1][0][k];
			}
		}
		for (k = 0; k < 8; k++)
		{
			SIV[127][0][k] = t1[0][k];
			SKey[127][0][k] = t2[0][k];
		}


	}

	//输出ANF
	for (l = 0; l < N0 + 93; l++)
	{
		//printf("%d\n", sizeA[l]);
		for (i = 0; i < sizeA[l]; i++)
		{
			for (j = 0; j < 4; j++)
			{
				for (k = 0; k < 32; k++)
				{
					if (((A[l][i][j] >> k) & 0x01) == 1)
					{
						fprintf(fp, "v(%d)", j * 32 + k);
						//printf("v(%d)", j * 32 + k);
					}
				}
			}


			for (j = 4; j < 8; j++)
			{
				for (k = 0; k < 32; k++)
				{
					if (((A[l][i][j] >> k) & 0x01) == 1)
					{
						fprintf(fp, "k(%d)", (j - 4) * 32 + k);
						//printf("k(%d)", (j - 4) * 32 + k);
					}
				}
			}
			//fprintf(fp, "\n");
			int summ = 0;
			for (j = 0; j < 8; j++)
				summ = summ + A[l][i][j];
			if (summ == 0)
				fprintf(fp, "1");
			if (i<sizeA[l] - 1)
				fprintf(fp, "+");
		}
		if (sizeA[l] == 0)
			fprintf(fp, "0");
		fprintf(fp, "\n");
	}

	for (l = 0; l < N0 + 84; l++)
	{
		//printf("%d\n", sizeB[l]);
		for (i = 0; i < sizeB[l]; i++)
		{
			for (j = 0; j < 4; j++)
			{
				for (k = 0; k < 32; k++)
				{
					if (((B[l][i][j] >> k) & 0x01) == 1)
					{
						fprintf(fp, "v(%d)", j * 32 + k);
					}
				}
			}


			for (j = 4; j < 8; j++)
			{
				for (k = 0; k < 32; k++)
				{
					if (((B[l][i][j] >> k) & 0x01) == 1)
					{
						fprintf(fp, "k(%d)", (j - 4) * 32 + k);
					}
				}
			}
			//fprintf(fp, "\n");
			int summ = 0;
			for (j = 0; j < 8; j++)
				summ = summ + B[l][i][j];
			if (summ == 0)
				fprintf(fp, "1");
			if (i<sizeB[l] - 1)
				fprintf(fp, "+");
		}
		if (sizeB[l] == 0)
			fprintf(fp, "0");
		fprintf(fp, "\n");
	}

	for (l = 0; l < N0 + 111; l++)
	{
		//printf("%d\n", sizeC[l]);
		for (i = 0; i < sizeC[l]; i++)
		{
			for (j = 0; j < 4; j++)
			{
				for (k = 0; k < 32; k++)
				{
					if (((C[l][i][j] >> k) & 0x01) == 1)
					{
						fprintf(fp, "v(%d)", j * 32 + k);
					}
				}
			}


			for (j = 4; j < 8; j++)
			{
				for (k = 0; k < 32; k++)
				{
					if (((C[l][i][j] >> k) & 0x01) == 1)
					{
						fprintf(fp, "k(%d)", (j - 4) * 32 + k);
					}
				}
			}
			//fprintf(fp, "\n");
			int summ = 0;
			for (j = 0; j < 8; j++)
				summ = summ + C[l][i][j];
			if (summ == 0)
				fprintf(fp, "1");
			if (i<sizeC[l] - 1)
				fprintf(fp, "+");
		}
		if (sizeC[l] == 0)
			fprintf(fp, "0");
		fprintf(fp, "\n");
	}

	for (i = 0; i < memsize; i++)
	{
		free(f1[i]);
		free(f2[i]);
		free(f3[i]);
		free(t1[i]);
		free(t2[i]);
		free(t3[i]);
	}
	free(f1);
	free(f2);
	free(f3);
	free(t1);
	free(t2);
	free(t3);
	for (i = 0; i < 128; i++)
	{
		free(SIV[i][0]);
		free(SKey[i][0]);
	}
	for (i = 0; i < 128; i++)
	{
		free(SIV[i]);
		free(SKey[i]);
	}
	free(SIV);
	free(SKey);
	fclose(fp);
}

int getdeg(unsigned int *t, int X[], int Xdim)
{
	//
	int d = 0;
	int i = 0;
	for (i = 0; i < Xdim; i++)
	{
		d = d + ((t[X[i] >> 5] >> (X[i] & 0x1f)) & 0x01);
	}
	return d;
}