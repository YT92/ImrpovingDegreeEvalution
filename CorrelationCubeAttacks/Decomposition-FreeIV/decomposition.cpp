//实现分解算法
//输入为给定的一组cube变元, 给定的轮数N0, 返回那些时刻的一组基
//同时需要记录选择该基的轮数和对应的反馈位置

//要实现多项式的乘法, 加法, 约化, 还是比较复杂的

//多项式乘法
//约化
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
struct basis {
	char leadcoef[1000][80];
	int round;
	int feedbakpos;
	int size;
}coef;

//比较

int compare(char a[160], char b[160])
{
	int i;
	for (i = 0; i < 160; i++)
	{
		if (a[i] != b[i])
			return 0;
	}
	return 1;

}

//返回约化后的size
int reduce(char **poly, int size)
{
	int i, j, k;
	char *flag,**temp;
	flag = (char *)malloc(sizeof(char)*size);
	memset(flag, 0, sizeof(char)*size);
	temp = (char**)malloc(sizeof(char*)*size);
	for (i = 0; i < size;i++)
	{
		temp[i] = (char *)malloc(sizeof(char) * 160);
	}

	//for (i = 0; i < size-1 && (flag[i]==0); i++)
	for (i = 0; i < size - 1 ; i++)
	{
		if (flag[i] == 0)
		{
			for (j = i + 1; j < size; j++)
			{
				//只与没有被消掉的项对比
				if (flag[j] == 0)
				{
					//如果是相同项, 那么设置两个相同的项的flag都为1
					if (compare(poly[i], poly[j]))
					{
						flag[i] = 1;
						flag[j] = 1;
						break;
					}
				}
			}
		}
	}
	k = 0;
	//取出flag为0的项
	for (i = 0; i < size; i++)
	{
		if (flag[i] == 0)
		{
			for (j = 0; j < 160; j++)
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
		memset(poly[i], 0, sizeof(char) * 160);
	}
	for (i = 0; i < k; i++)
	{
		for (j = 0; j < 160; j++)
		{
			poly[i][j] = temp[i][j];
		}
	}
	for (i = 0; i < size;i++)
	{
		free(temp[i]);
	}
	free(temp);
	free(flag);
	return k;
}


//不需要考虑序, 或者乘完之后在排序
//int multi(char **s1[][160], char s2[][160], int size1, int size2, char res[][160])
int multi(char **s1, char **s2, int size1, int size2, char **res)
{
	int i, j, k;
	int size;
	char **temp;
	size = size1*size2;
	temp = (char **)malloc(sizeof(char *)*size);
	for (i = 0; i < size; i++)
	{
		temp[i] = (char *)malloc(sizeof(char) * 160);
	}
	for (i = 0; i < size1; i++)
	{
		for (j = 0; j < size2; j++)
		{
			for (k = 0; k < 160; k++)
			{
				temp[i*size2 + j][k] = max(s1[i][k], s2[j][k]);//(s1[i][k]+ s2[j][k])&0x01+ s1[i][k]*s2[j][k];
				//printf("%d", temp[i*size2 + j][k]);
			}
			//printf("\n");	
		}
	}
	//for (k = 0; k < size; k++)
	//{
	//	//for (j = 0; j < 160; j++)
	//	//printf("%d", s[91][k][j]);
	//	for (j = 80; j < 160; j++)
	//	{
	//		if (temp[k][j] == 1)
	//			printf("k%d", j - 80);
	//	}
	//	printf("\n");
	//}
	//reduce size
	size=reduce(temp, size1*size2);
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < 160; j++)
		{
			res[i][j] = temp[i][j];
		}
	}
	for (i = 0; i <  size1*size2;i++)
	{
		free(temp[i]);
	}
	free(temp);
	return size;
}

//多项式加法
//int addition(char s1[][160], char s2[][160], char s3[][160], char s4[][160], int size1, int size2, int size3, int size4, char res[][160])
int addition(char **s1, char **s2, char **s3, char **s4, int size1, int size2, int size3, int size4, char **res)
{

	//printf("%d,%d,%d,%d\n", size1, size2, size3, size4);
	int i, j;
	char **temp;
	int size;
	size = size1 + size2 + size3 + size4;
	temp = (char**)malloc(sizeof(char*)*size);
	//直接放到一块, 然后进行约化即可
	for (i = 0; i < size; i++)
	{
		temp[i] = (char*)malloc(sizeof(char) * 160);
	}
	//吞并s1
	for (i = 0; i < size1; i++)
	{
		for (j = 0; j < 160; j++)
		{
			temp[i][j] = s1[i][j];
		}
	}
	//吞并s2
	for (i = 0; i < size2; i++)
	{
		for (j = 0; j < 160; j++)
		{
			temp[i+size1][j] = s2[i][j];
			//printf("%d", s2[i][j]);
		}
		
	}
	//吞并s3
	for (i = 0; i < size3; i++)
	{
		for (j = 0; j < 160; j++)
		{
			temp[i + size1+size2][j] = s3[i][j];
		}
	}
	//吞并s4
	for (i = 0; i < size4; i++)
	{
		for (j = 0; j < 160; j++)
		{
			temp[i + size1 + size2 + size3][j] = s4[i][j];
			//printf("%d", s4[i][j]);
		}
	}
	size = reduce(temp, size);
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < 160; j++)
		{
			res[i][j] = temp[i][j];
		}
	}

	for (i = 0; i < size1 + size2 + size3 + size4;i++)
	{
		free(temp[i]);
	}
	free(temp);
	return size;
}

int getdeg(char term[160])
{
	int i;
	int deg;
	deg = 0;
	for (i = 0; i < 80; i++)
	{
		deg += term[i];
	}
	return deg;
}

int getdegFreeIV(char term[160],int cube[], int dim)
{
	int i;
	int deg;
	deg = 0;
	for (i = 0; i < dim; i++)
	{
		deg += term[cube[i]];
	}
	return deg;
}

int todeg(char term[160])
{
	int i;
	int deg;
	deg = 0;
	for (i = 0; i < 160; i++)
	{
		deg += term[i];
	}
	return deg;
}
//获取最高次项的系数
//int getleadcoef(char poly[][160],int size, char coef[][80], int DEG[2], int vanpos[], int vansize[])
int getleadcoef(char **poly, int size, char coef[][80], int DEG[2], int vanpos[], int vansize[])
{
	int i, j, k;
	int deg,pos=0; 
	int maxdeg = -10000;
	int submaxdeg = -10000;
	int maxpos[1000];//记录maxdeg的位置
	int m = 0, m1 = 0;
	char *termdeg, *flag;
	termdeg = (char *)malloc(sizeof(char)*size);
	flag = (char *)malloc(sizeof(char)*size);
	memset(flag, 0, sizeof(char)*size);



	//获取最大次数
	for (i = 0; i < size; i++)
	{
		deg = getdeg(poly[i]);
		termdeg[i] = deg;
		if (deg > maxdeg)
		{
			maxdeg = deg;
			pos = i;
		}
	}
	if (maxdeg == 0)
	{
		DEG[0] = 0;
		DEG[1] = 0;
		vansize[0] = 0;
		return 0;
	}
	//printf("******************************************************\n");
	for (i = 0; i < size; i++)
	{
		deg = termdeg[i];
		if ((deg > submaxdeg)&&(deg!=maxdeg))
		{
			submaxdeg = deg;
			pos = i;
		}
		/*for (k = 0; k < 80; k++)
			printf("%d", poly[i][k]);
		printf("\n");*/
	}
	
	m = 0;
	m1 = 0;
	//判断每一项是否是最高次项
	for (i = 0; i < size; i++)
	{
		//如果次数和最高项相等, 那么, 取出这一项的系数
		if (flag[i] == 0)
		{
			if (termdeg[i] == maxdeg)
			{
				//先把这一项的系数放进去,
				for (k = 0; k < 80; k++)
				{
					coef[m][k] = poly[i][80 + k];
					//printf("%d", poly[i][80 + k]);
				}
				//printf("\n");
				vanpos[m1] = i;
				m++;
				m1++;
				for (j = i + 1; j < size; j++)
				{
					if (termdeg[j] == maxdeg)
					{
						for (k = 0; k < 80; k++)
						{
							if (poly[j][k] != poly[i][k])
								break;
						}
						//如果是相等的, 把这个位置的后80比特添加进去, 然后把这个位置设置成不再遍历
						if (k == 80)
						{
							flag[j] = 1;
							for (k = 0; k < 80; k++)
							{
								coef[m][k] = poly[j][k+80];
								//printf("%d", poly[j][k]);
							}
							//printf("\n");
							vanpos[m1] = j;
							m1++;
							m++;
						}
					}
				}
				//循环结束后, 加一个这一项系数结束的标识符,全1表示这一项的系数已经结束
				for (k = 0; k < 80; k++)
				{
					coef[m][k] = 1;
				}
			}
		}
		
	}
	/*for (i = 0; i < m; i++)
	{
		for (k = 0; k < 80; k++)
		{
			printf("%d", coef[i][k]);
		}
		printf("\n");
	}*/
	
	vansize[0] = m1;
	DEG[0] = maxdeg;
	DEG[1] = submaxdeg;

	free(termdeg);
	free(flag);
	return m;
}

int getleadcoefFreeIV(char **poly, int size, char coef[][80], int cube[], int dim, int DEG[2], int vanpos[], int vansize[])
{
	int i, j, k;
	int deg,pos=0; 
	int maxdeg = -10000;
	int submaxdeg = -10000;
	int maxpos[1000];//记录maxdeg的位置
	int m = 0, m1 = 0;
	char *termdeg, *flag;
	termdeg = (char *)malloc(sizeof(char)*size);
	flag = (char *)malloc(sizeof(char)*size);
	memset(flag, 0, sizeof(char)*size);



	//获取最大次数
	for (i = 0; i < size; i++)
	{
		deg = getdegFreeIV(poly[i],cube,dim);
		termdeg[i] = deg;
		if (deg > maxdeg)
		{
			maxdeg = deg;
			pos = i;
		}
	}
	if (maxdeg == 0)
	{
		DEG[0] = 0;
		DEG[1] = 0;
		vansize[0] = 0;
		return 0;
	}
	//printf("******************************************************\n");
	for (i = 0; i < size; i++)
	{
		deg = termdeg[i];
		if ((deg > submaxdeg)&&(deg!=maxdeg))
		{
			submaxdeg = deg;
			pos = i;
		}
		/*for (k = 0; k < 80; k++)
			printf("%d", poly[i][k]);
		printf("\n");*/
	}
	
	m = 0;
	m1 = 0;
	//判断每一项是否是最高次项
	for (i = 0; i < size; i++)
	{
		//如果次数和最高项相等, 那么, 取出这一项的系数
		if (flag[i] == 0)
		{
			if (termdeg[i] == maxdeg)
			{
				//先把这一项的系数放进去,
				for (k = 0; k < 80; k++)
				{
					coef[m][k] = poly[i][80 + k];
					//printf("%d", poly[i][80 + k]);
				}
				//printf("\n");
				vanpos[m1] = i;
				m++;
				m1++;
				for (j = i + 1; j < size; j++)
				{
					if (termdeg[j] == maxdeg)
					{
						for (k = 0; k < 80; k++)
						{
							if (poly[j][k] != poly[i][k])
								break;
						}
						//如果是相等的, 把这个位置的后80比特添加进去, 然后把这个位置设置成不再遍历
						if (k == 80)
						{
							flag[j] = 1;
							for (k = 0; k < 80; k++)
							{
								coef[m][k] = poly[j][k+80];
								//printf("%d", poly[j][k]);
							}
							//printf("\n");
							vanpos[m1] = j;
							m1++;
							m++;
						}
					}
				}
				//循环结束后, 加一个这一项系数结束的标识符,全1表示这一项的系数已经结束
				for (k = 0; k < 80; k++)
				{
					coef[m][k] = 1;
				}
			}
		}
		
	}
	/*for (i = 0; i < m; i++)
	{
		for (k = 0; k < 80; k++)
		{
			printf("%d", coef[i][k]);
		}
		printf("\n");
	}*/
	
	vansize[0] = m1;
	DEG[0] = maxdeg;
	DEG[1] = submaxdeg;

	free(termdeg);
	free(flag);
	return m;
}
//零化最高项
//int vanish(char poly[][160], int vanpos[], int size, int vansize)
int vanish(char **poly, int vanpos[], int size, int vansize)
{
	int i, j, k,m;
	char *flag;
	char **temp;
	temp = (char **)malloc(sizeof(char*)*size);
	flag = (char *)malloc(sizeof(char)*size);
	memset(flag, 0, sizeof(char)*size);
	for (i = 0; i < size; i++)
	{
		temp[i] = (char *)malloc(sizeof(char) * 160);
	}
	for (i = 0; i < vansize; i++)
	{
		flag[vanpos[i]] = 1;
	}
	m = 0;
	for (i = 0; i < size; i++)
	{
		if (flag[i]==0)
		{
			for (k = 0; k < 160; k++)
			{
				temp[m][k] = poly[i][k];
			}
			m++;
		}
	}
	for (i = 0; i < size; i++)
	{
		memset(poly[i], 0, sizeof(char) * 160);
	}
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < 160; j++)
		{
			poly[i][j] = temp[i][j];
		}
	}
	for (i = 0; i < size;i++)
	{
		free(temp[i]);
	}
	free(temp);
	free(flag);
	return m;
}


//对于不得变元集，确定代数次数
void getinideg(char ***up, int size[],int vf[], int D[], int X[],int dim,int N0)
{
	int i,j,k;
	int deg,tmp;
	int maxdeg=0;
	int maxdeglist[2000]={0};
	//获取最高次
	for(i=0;i<N0;i++)
	{
		for(j=0;j<size[i];j++)
		{
			tmp=getdeg(up[i][j]);
			if(tmp>maxdeglist[i])
				maxdeglist[i]=tmp;
		}
	}

	for(i=0;i<N0;i++)
	{
		maxdeg=0;
		for(j=0;j<size[i];j++)
		{
			deg=0;
			for(k=0;k<dim;k++)
			{
				deg+=up[i][j][X[k]];
			}
			if((vf[i]==0)||(deg!=maxdeglist[i]))
			{
				if(deg>maxdeg)
				{
					maxdeg=deg;
				}
			}
		}
		if(size[i]==0)
			maxdeg=-10000;
		D[i]=maxdeg;
		/*printf("%d %d %d %d\n",i, maxdeg,vf[i],size[i]);*/
	}
}

void getinidegV2(char ***up, int size[],int vf[], int D[], int Dv[], int X[],int dim,int N0)
{
	int i,j,k;
	int deg,tmp;
	int maxdeg=0;
	int maxdeglist[2000]={0};
	int maxdegv=0;
	//获取最高次
	for(i=0;i<N0;i++)
	{
		for(j=0;j<size[i];j++)
		{
			tmp=getdeg(up[i][j]);
			if(tmp>maxdeglist[i])
				maxdeglist[i]=tmp;
		}
	}

	for(i=0;i<N0;i++)
	{
		maxdeg=0;
		maxdegv=0;
		for(j=0;j<size[i];j++)
		{
			deg=0;
			for(k=0;k<dim;k++)
			{
				deg+=up[i][j][X[k]];
			}
			if((vf[i]==0)||(deg!=maxdeglist[i]))
			{
				if(deg>maxdeg)
				{
					maxdeg=deg;
				}
			}
			if(deg>maxdegv)
			{
				maxdegv=deg;
			}
		}
		if(size[i]==0)
			maxdeg=-10000;
		D[i]=maxdeg;
		Dv[i]=maxdegv;
		/*printf("%d %d %d %d\n",i, maxdeg,vf[i],size[i]);*/
	}
}
//给定cube, 然后对其超多项式进行分解
//A,B,C记录代数次数

//用两个数组分别记录消项或者不消项的代数次数估计
void decomposition(int cube[], int dim, int Da[], int Db[], int Dc[],int Dav[], int Dbv[], int Dcv[], int N0)
{
	//char s[288][10000][160] = {0};//前80比特表达IV, 后80比特表示key, 最后一比特比较1
	char ***s;
	int size[288] = {0};//记录每一个内部状态比特的单项式的数量. 
	int i, j, k,m,l,tempdeg=0;
	FILE *fp;
	fopen_s(&fp, "basis.txt", "w");
	s = (char***)malloc(sizeof(char**) * 288);
	for (i = 0; i < 288; i++)
	{
		s[i] = (char **)malloc(sizeof(char*) * 10000);
		for (j = 0; j < 10000;j++)
		{
			s[i][j] = (char *)malloc(sizeof(char) * 160);
			memset(s[i][j], 0, sizeof(char) * 160);
		}
	}

	//用于存储中间结果
	//char f1[10000][160], f2[10000][160], f3[10000][160];
	//用于存储更新结果
	//char t1[10000][160], t2[10000][160], t3[10000][160];
	char **f1, **f2, **f3, **t1, **t2, **t3;
	f1 = (char **)malloc(sizeof(char *) * 10000);
	f2 = (char **)malloc(sizeof(char *) * 10000);
	f3 = (char **)malloc(sizeof(char *) * 10000);
	t1 = (char **)malloc(sizeof(char *) * 10000);
	t2 = (char **)malloc(sizeof(char *) * 10000);
	t3 = (char **)malloc(sizeof(char *) * 10000);
	for (i = 0; i < 10000; i++)
	{
		f1[i] = (char *)malloc(sizeof(char) * 160);
		f2[i] = (char *)malloc(sizeof(char) * 160);
		f3[i] = (char *)malloc(sizeof(char) * 160);
		t1[i] = (char *)malloc(sizeof(char) * 160);
		t2[i] = (char *)malloc(sizeof(char) * 160);
		t3[i] = (char *)malloc(sizeof(char) * 160);
		memset(f1[i], 0, sizeof(char) * 160);
		memset(f2[i], 0, sizeof(char) * 160);
		memset(f3[i], 0, sizeof(char) * 160);
		memset(t1[i], 0, sizeof(char) * 160);
		memset(t2[i], 0, sizeof(char) * 160);
		memset(t3[i], 0, sizeof(char) * 160);
	}
	int vanpos1[100], vanpos2[100], vanpos3[100];
	int size1, size2, size3,round,flag1,flag2,flag3;
	int DEG1[2], DEG2[2], DEG3[2];
	int vansizet1[1], vansizet2[1], vansizet3[1];
	int degt1, degt2, degt3;
	int coefnum1, coefnum2, coefnum3;
	char coeft1[1000][80] = { 0 }, coeft2[1000][80] = { 0 }, coeft3[1000][80] = {0};
	basis *leadcoefs;

	leadcoefs = (basis *)malloc(sizeof(basis) * 600);
	//初始化Da,Db,Dc数组.
	for (i = 0; i < 13; i++)
	{
		Da[i] = -10000;
		Dav[i] = -10000;
	}	
	for (i = 13; i < 93; i = i + 1)
	{
		Da[i] = 0;
		Dav[i] = 0;
	}
	for (i = 0; i < 4; i++)
	{
		Db[i] = -10000;
		Dbv[i] = -10000;
	}
	for (i = 4; i < 84; i++)
	{
		Db[i] = -10000;
		Dbv[i] = -10000;
	}
	for (i = 0; i < 3; i++)
	{
		Dc[i] = 0;
		Dcv[i] = 0;
	}
	for (i = 3; i < 111; i++)
	{
		Dc[i] = -10000;
		Dcv[i] = -10000;
	}
		
	//初始化: 密钥比特填充, cube变元填充, 常值填充
	//填充密钥比特
	for (i = 0; i < 80;i++)
	{ 
		s[i][0][80+i] = 1;
		size[i] = 1;
	}
	//填充cube变元
	for (i = 0; i < dim; i++)
	{
		s[93 + cube[i]][0][cube[i]] = 1;
		size[93 + cube[i]] = 1;
		Db[83 - cube[i]] = 1;
		Dbv[83 - cube[i]] = 1;
	}
	//单项式1怎么处理, 再加1比特
	for (i = 285; i < 288; i++)
	{
		size[i] = 1;
	}
	
	m = 0;
	round = N0;
	//每一轮最高次项的系数
	for (i = 0; i < round; i++)
	{
		//if (i == 96)
		//{
		//	for (k = 0; k < size[175 - 1]; k++)
		//	{
		//		//for (j = 0; j < 160; j++)
		//			//printf("%d", s[91][k][j]);
		//		for (j = 80; j < 160; j++)
		//		{
		//			if (s[175-1][k][j] == 1)
		//				printf("k%d", j - 80);
		//		}
		//		printf("\n");
		//	}
		//	for (k = 0; k < size[176 - 1]; k++)
		//	{
		//		/*for (j = 0; j < 160; j++)
		//			printf("%d", s[92][k][j]);*/
		//		for (j = 80; j < 160; j++)
		//		{
		//			if (s[176-1][k][j] == 1)
		//				printf("k%d", j - 80);
		//		}
		//		printf("\n");
		//	}
		//}
		//s66+s91*s92+s93+s171;
		size1=multi(s[91 - 1], s[92 - 1], size[91 - 1], size[92 - 1], f1);
		size1=addition(f1, s[66 - 1], s[93 - 1], s[171 - 1], size1, size[66 - 1], size[93 - 1], size[171 - 1],t1);
		
		/*for (j = 0; j < 160; j++)
			printf("%d", t1[0][j]);*/
		//s162+s175*s176+size177+s264
		size2 = multi(s[175 - 1], s[176 - 1], size[175 - 1], size[176 - 1], f2);
		size2 = addition(f2, s[162 - 1], s[177 - 1], s[264 - 1], size2, size[162 - 1], size[177 - 1], size[264 - 1], t2);
		//s243+s286*s287+size288+s69
		size3= multi(s[286 - 1], s[287 - 1], size[286 - 1], size[287 - 1], f3);
		//printf("%d,%d,%d,%d\n", size3, size[243 - 1], size[288 - 1], size[69 - 1]);
		size3 = addition(f3, s[243 - 1], s[288 - 1], s[69 - 1], size3, size[243 - 1], size[288 - 1], size[69 - 1], t3);
		//下面需要对t1,t2,t3判断最高此项,还需要存储去掉最高项之后的次高项的次数
		//要定义一个结构体来存储
		memset(vanpos1, 0, sizeof(int) * 1000);
		memset(vanpos2, 0, sizeof(int) * 1000);
		memset(vanpos3, 0, sizeof(int) * 1000);
		for (j = 0; j < 1000; j++)
		{
			memset(coeft1[i], 0, sizeof(char) * 80);
			memset(coeft2[i], 0, sizeof(char) * 80);
			memset(coeft3[i], 0, sizeof(char) * 80);
		}

		coefnum1 = getleadcoef(t1, size1, coeft1,DEG1,vanpos1, vansizet1);
		coefnum2 = getleadcoef(t2, size2, coeft2,DEG2,vanpos2, vansizet2);
		coefnum3 = getleadcoef(t3, size3, coeft3,DEG3,vanpos3, vansizet3);

		

		//检验是否有全0项在里面
		flag1 = 0;
		flag2 = 0;
		flag3 = 0;
		if (coefnum1 == 0)
		{
			flag1 = 1;
		}
		if (coefnum2 == 0)
		{
			flag2 = 1;
		}
		if (coefnum3 == 0)
		{
			flag3 = 1;
		}
		for (k = 0; k < coefnum1; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft1[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag1 = 1;
				break;
			}
		}
		//检验是否有全0项在里面for t2
		for (k = 0; k < coefnum2; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft2[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag2 = 1;
				break;
			}
		}

		//检验是否有全0项在里面for t3
		for (k = 0; k < coefnum3; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft3[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag3 = 1;
				break;
			}
		}
		//直接输出到文件也可以, 反正实际上没有什么用的.
		//如果那个flag1不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if (flag1 == 0)
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 1;
			leadcoefs[m].size = coefnum1;
			for (j = 0; j < coefnum1; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft1[j][k];
				}

			}
			m++;
			//此时将degt1赋值成次高项的次数,
			degt1 = DEG1[1];
			size1=vanish(t1, vanpos1,size1 ,vansizet1[0]);
			//此时不消项的代数次数就是这样
			//Dbv[84 + i] = DEG1[0];
		}
		else
		{
			//说明此时最高项不能被0化, 
			degt1 = DEG1[0];
			//Dbv[84 + i] = DEG1[0];
		}
		//如果那个flag2不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if (flag2 == 0)
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 2;
			leadcoefs[m].size = coefnum2;
			for (j = 0; j < coefnum2; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft2[j][k];
				}

			}
			m++;
			//此时, 将degt2赋值成次高项的系数
			degt2 = DEG2[1];
			size2 = vanish(t2, vanpos2, size2, vansizet2[0]);
		}
		else
		{
			//此时t2中的最高项不能被去掉,
			degt2 = DEG2[0];
		}
	
		//如果那个flag3不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if (flag3 == 0)
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 3;
			leadcoefs[m].size = coefnum3;
			for (j = 0; j < coefnum3; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft3[j][k];
				}
			}
			m++;
			//此时, 最高项系数能够被去掉, 因此, degt3应该被赋值成次高项的次数
			degt3 = DEG3[1];
			size3 = vanish(t3, vanpos3, size3, vansizet3[0]);
		}
		else
		{
			//此时, 最高次项不能够被零花, 此时, degt3应该被赋值成最高次项
			degt3 = DEG3[0];
		}



		//shift咯
		//首先是内部状态比特的移位
		for (j = 92; j >0; j--)
		{
			//首先要memset, 将其余的东西都赋值为0
			for (k = 0; k < size[j];k++)
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
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
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
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
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
				{
					s[j][k][l] = s[j - 1][k][l];
				}
			}
			size[j] = size[j - 1];
		}
		//t1,t2,t3, 分别赋值给s0,s93, s177
		//更新s0
		for (k = 0; k < size[0]; k++)
			memset(s[0][k], 0, sizeof(char) * 160);
		for (j = 0; j < size3; j++)
		{
			for (k = 0; k < 160; k++)
				s[0][j][k] = t3[j][k];
		}
		size[0] = size3;
		//更新s93
		for (k = 0; k < size[93]; k++)
			memset(s[93][k], 0, sizeof(char) * 160);
		for (j = 0; j < size1; j++)
		{
			for (k = 0; k < 160; k++)
				s[93][j][k] = t1[j][k];
		}
		size[93] = size1;
		//更新s177
		for (k = 0; k < size[177]; k++)
			memset(s[177][k], 0, sizeof(char) * 160);
		for (j = 0; j < size2; j++)
		{
			for (k = 0; k < 160; k++)
				s[177][j][k] = t2[j][k];
		}
		size[177] = size2;
		Da[93 + i] = degt3;
		Db[84 + i] = degt1;
		Dc[111 + i] = degt2;
		Dav[93 + i] = DEG3[0];
		Dbv[84 + i] = DEG1[0];
		Dcv[111 + i] = DEG2[0];
		/*if (i == 103)
		{
			Dc[111 + i] = Dcv[111 + i];
		}*/
		//if()
	//	printf("%d\n", i+1);
	//	for (j = 0; j < size1; j++)
	//	{
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t1[j][k] == 1)
	//				printf("iv%d", k);
	//		}
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t1[j][k+80] == 1)
	//				printf("k%d", k);
	//		}
	//		if (todeg(t1[j]) == 0)
	//			printf("1");
	//		if (size1>1)
	//			printf("+");

	//	}
	//	printf("\n");

	//	for (j = 0; j < size2; j++)
	//	{
	//		//if(deg)
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t2[j][k] == 1)
	//				printf("iv%d", k);
	//		}
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t2[j][k + 80] == 1)
	//				printf("k%d", k);
	//		}
	//		if (todeg(t2[j]) == 0)
	//			printf("1");
	//		if(size2>1)
	//			printf("+");
	//	}
	//	printf("\n");

	//	for (j = 0; j < size3; j++)
	//	{
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t3[j][k] == 1)
	//				printf("iv%d", k);
	//		}
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t3[j][k + 80] == 1)
	//				printf("k%d", k);
	//		}
	//		if (todeg(t3[j]) == 0)
	//			printf("1");
	//		if (size3>1)
	//			printf("+");
	//	}
	//	printf("\n*****************************************\n\n");
	}

	/*for (i = 0; i < 293; i++)
	{
		printf("%d\n", Da[i]);
	}*/
	for (i = 0; i < m; i++)
	{
		fprintf(fp, "the %dth round leadcoefs of Reg%d\n", leadcoefs[i].round, leadcoefs[i].feedbakpos);
		for (k = 0; k < leadcoefs[i].size; k++)
		{
			for (j = 0; j < 80; j++)
			{
				if (leadcoefs[i].leadcoef[k][j])
					fprintf(fp,"k(%d)", j);
			}
			if(leadcoefs[i].size>1)
				fprintf(fp,"+");
		}
		fprintf(fp, "\n");
	}
	for (i = 0; i < 10000; i++)
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
	for (j = 0; j < 288; j++)
	{
		for (i = 0; i < 10000; i++)
		{
			free(s[j][i]);
		}
		free(s[j]);
	}
	free(leadcoefs);
	
	fclose(fp);
	//往后是正常的代数次数估计, 如果代数次数小于cube的维数则有效
	//现在不好处理的是去掉基的过程.
	//全部记下来
}


//需要存储200轮的更新比特， 需要存储每一个比特的最高项是否被零花， 
//
void decompositionV(int cube[], int dim, char *** upA, char ***upB,char ***upC, int sizeA[], int sizeB[], int sizeC[],int vfA[],int vfB[],int vfC[],int basnum[], int N0)
{
	//char s[288][10000][160] = {0};//前80比特表达IV, 后80比特表示key, 最后一比特比较1
	char ***s;
	int size[288] = {0};//记录每一个内部状态比特的单项式的数量. 
	int i, j, k,m,l,tempdeg=0;
	FILE *fp;
	fopen_s(&fp, "Res.txt", "a+");
	
	s = (char***)malloc(sizeof(char**) * 288);
	for (i = 0; i < 288; i++)
	{
		s[i] = (char **)malloc(sizeof(char*) * 10000);
		for (j = 0; j < 10000;j++)
		{
			s[i][j] = (char *)malloc(sizeof(char) * 160);
			memset(s[i][j], 0, sizeof(char) * 160);
		}
	}

	//用于存储中间结果
	//char f1[10000][160], f2[10000][160], f3[10000][160];
	//用于存储更新结果
	//char t1[10000][160], t2[10000][160], t3[10000][160];
	char **f1, **f2, **f3, **t1, **t2, **t3;
	f1 = (char **)malloc(sizeof(char *) * 10000);
	f2 = (char **)malloc(sizeof(char *) * 10000);
	f3 = (char **)malloc(sizeof(char *) * 10000);
	t1 = (char **)malloc(sizeof(char *) * 10000);
	t2 = (char **)malloc(sizeof(char *) * 10000);
	t3 = (char **)malloc(sizeof(char *) * 10000);
	for (i = 0; i < 10000; i++)
	{
		f1[i] = (char *)malloc(sizeof(char) * 160);
		f2[i] = (char *)malloc(sizeof(char) * 160);
		f3[i] = (char *)malloc(sizeof(char) * 160);
		t1[i] = (char *)malloc(sizeof(char) * 160);
		t2[i] = (char *)malloc(sizeof(char) * 160);
		t3[i] = (char *)malloc(sizeof(char) * 160);
		memset(f1[i], 0, sizeof(char) * 160);
		memset(f2[i], 0, sizeof(char) * 160);
		memset(f3[i], 0, sizeof(char) * 160);
		memset(t1[i], 0, sizeof(char) * 160);
		memset(t2[i], 0, sizeof(char) * 160);
		memset(t3[i], 0, sizeof(char) * 160);
	}
	int vanpos1[100], vanpos2[100], vanpos3[100];
	int size1, size2, size3,round,flag1,flag2,flag3;
	int DEG1[2], DEG2[2], DEG3[2];
	int vansizet1[1], vansizet2[1], vansizet3[1];
	int degt1, degt2, degt3;
	int coefnum1, coefnum2, coefnum3;
	char coeft1[1000][80] = { 0 }, coeft2[1000][80] = { 0 }, coeft3[1000][80] = {0};
	basis *leadcoefs;
	int Da[1000], Db[1000],Dc[1000];
	int Dav[1000], Dbv[1000],Dcv[1000];
	leadcoefs = (basis *)malloc(sizeof(basis) * 600);
	//初始化Da,Db,Dc数组.
	for (i = 0; i < 13; i++)
	{
		Da[i] = -10000;
		Dav[i] = -10000;
	}	
	for (i = 13; i < 93; i = i + 1)
	{
		Da[i] = 0;
		Dav[i] = 0;
	}
	for (i = 0; i < 4; i++)
	{
		Db[i] = -10000;
		Dbv[i] = -10000;
	}
	for (i = 4; i < 84; i++)
	{
		Db[i] = -10000;
		Dbv[i] = -10000;
	}
	for (i = 0; i < 3; i++)
	{
		Dc[i] = 0;
		Dcv[i] = 0;
	}
	for (i = 3; i < 111; i++)
	{
		Dc[i] = -10000;
		Dcv[i] = -10000;
	}
		
	//初始化: 密钥比特填充, cube变元填充, 常值填充
	//填充密钥比特
	for (i = 0; i < 80;i++)
	{ 
		s[i][0][80+i] = 1;
		size[i] = 1;
	}
	//填充cube变元
	for (i = 0; i < dim; i++)
	{
		s[93 + cube[i]][0][cube[i]] = 1;
		size[93 + cube[i]] = 1;
		Db[83 - cube[i]] = 1;
		Dbv[83 - cube[i]] = 1;
	}
	//单项式1怎么处理, 再加1比特
	for (i = 285; i < 288; i++)
	{
		size[i] = 1;
	}
	
	m = 0;
	round = N0;
	//每一轮最高次项的系数
	for (i = 0; i < round; i++)
	{
		//if (i == 96)
		//{
		//	for (k = 0; k < size[175 - 1]; k++)
		//	{
		//		//for (j = 0; j < 160; j++)
		//			//printf("%d", s[91][k][j]);
		//		for (j = 80; j < 160; j++)
		//		{
		//			if (s[175-1][k][j] == 1)
		//				printf("k%d", j - 80);
		//		}
		//		printf("\n");
		//	}
		//	for (k = 0; k < size[176 - 1]; k++)
		//	{
		//		/*for (j = 0; j < 160; j++)
		//			printf("%d", s[92][k][j]);*/
		//		for (j = 80; j < 160; j++)
		//		{
		//			if (s[176-1][k][j] == 1)
		//				printf("k%d", j - 80);
		//		}
		//		printf("\n");
		//	}
		//}
		//s66+s91*s92+s93+s171;
		size1=multi(s[91 - 1], s[92 - 1], size[91 - 1], size[92 - 1], f1);
		size1=addition(f1, s[66 - 1], s[93 - 1], s[171 - 1], size1, size[66 - 1], size[93 - 1], size[171 - 1],t1);
		
		/*for (j = 0; j < 160; j++)
			printf("%d", t1[0][j]);*/
		//s162+s175*s176+size177+s264
		size2 = multi(s[175 - 1], s[176 - 1], size[175 - 1], size[176 - 1], f2);
		size2 = addition(f2, s[162 - 1], s[177 - 1], s[264 - 1], size2, size[162 - 1], size[177 - 1], size[264 - 1], t2);
		//s243+s286*s287+size288+s69
		size3= multi(s[286 - 1], s[287 - 1], size[286 - 1], size[287 - 1], f3);
		//printf("%d,%d,%d,%d\n", size3, size[243 - 1], size[288 - 1], size[69 - 1]);
		size3 = addition(f3, s[243 - 1], s[288 - 1], s[69 - 1], size3, size[243 - 1], size[288 - 1], size[69 - 1], t3);
		//下面需要对t1,t2,t3判断最高此项,还需要存储去掉最高项之后的次高项的次数
		//要定义一个结构体来存储
		//直接复制完全的ANF
		for (j = 0; j < size3; j++)
		{
			for (k = 0; k < 160; k++)
			{
				upA[i][j][k]=t3[j][k];
			}
		}
		sizeA[i]=size3;
		
		for (j = 0; j < size1; j++)
		{
			for (k = 0; k < 160; k++)
			{
				upB[i][j][k] = t1[j][k];
			}
		}
		sizeB[i]=size1;
		

		for (j = 0; j < size2; j++)
		{
			for (k = 0; k < 160; k++)
			{
				upC[i][j][k] = t2[j][k];
			}
		}
		sizeC[i]=size2;

		memset(vanpos1, 0, sizeof(int) * 1000);
		memset(vanpos2, 0, sizeof(int) * 1000);
		memset(vanpos3, 0, sizeof(int) * 1000);
		for (j = 0; j < 1000; j++)
		{
			memset(coeft1[i], 0, sizeof(char) * 80);
			memset(coeft2[i], 0, sizeof(char) * 80);
			memset(coeft3[i], 0, sizeof(char) * 80);
		}

		coefnum1 = getleadcoef(t1, size1, coeft1,DEG1,vanpos1, vansizet1);
		coefnum2 = getleadcoef(t2, size2, coeft2,DEG2,vanpos2, vansizet2);
		coefnum3 = getleadcoef(t3, size3, coeft3,DEG3,vanpos3, vansizet3);

		

		//检验是否有全0项在里面
		flag1 = 0;
		flag2 = 0;
		flag3 = 0;
		if (coefnum1 == 0)
		{
			flag1 = 1;
		}
		if (coefnum2 == 0)
		{
			flag2 = 1;
		}
		if (coefnum3 == 0)
		{
			flag3 = 1;
		}
		for (k = 0; k < coefnum1; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft1[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag1 = 1;
				break;
			}
		}
		//检验是否有全0项在里面for t2
		for (k = 0; k < coefnum2; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft2[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag2 = 1;
				break;
			}
		}

		//检验是否有全0项在里面for t3
		for (k = 0; k < coefnum3; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft3[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag3 = 1;
				break;
			}
		}
		//直接输出到文件也可以, 反正实际上没有什么用的.
		//如果那个flag1不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if (flag1 == 0)
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 1;
			leadcoefs[m].size = coefnum1;
			for (j = 0; j < coefnum1; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft1[j][k];
				}

			}
			m++;
			//此时将degt1赋值成次高项的次数,
			degt1 = DEG1[1];
			size1=vanish(t1, vanpos1,size1 ,vansizet1[0]);
			vfB[i]=1;
			//此时不消项的代数次数就是这样
			//Dbv[84 + i] = DEG1[0];
		}
		else
		{
			//说明此时最高项不能被0化, 
			degt1 = DEG1[0];
			vfB[i]=0;
			//Dbv[84 + i] = DEG1[0];
		}
		//如果那个flag2不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if (flag2 == 0)
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 2;
			leadcoefs[m].size = coefnum2;
			for (j = 0; j < coefnum2; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft2[j][k];
				}

			}
			m++;
			//此时, 将degt2赋值成次高项的系数
			degt2 = DEG2[1];
			size2 = vanish(t2, vanpos2, size2, vansizet2[0]);
			vfC[i]=1;
		}
		else
		{
			//此时t2中的最高项不能被去掉,
			degt2 = DEG2[0];
			vfC[i]=0;
		}
	
		//如果那个flag3不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if (flag3 == 0)
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 3;
			leadcoefs[m].size = coefnum3;
			for (j = 0; j < coefnum3; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft3[j][k];
				}
			}
			m++;
			//此时, 最高项系数能够被去掉, 因此, degt3应该被赋值成次高项的次数
			degt3 = DEG3[1];
			size3 = vanish(t3, vanpos3, size3, vansizet3[0]);
			vfA[i]=1;
		}
		else
		{
			//此时, 最高次项不能够被零花, 此时, degt3应该被赋值成最高次项
			degt3 = DEG3[0];
			vfA[i]=0;
		}



		//shift咯
		//首先是内部状态比特的移位
		for (j = 92; j >0; j--)
		{
			//首先要memset, 将其余的东西都赋值为0
			for (k = 0; k < size[j];k++)
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
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
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
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
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
				{
					s[j][k][l] = s[j - 1][k][l];
				}
			}
			size[j] = size[j - 1];
		}
		//t1,t2,t3, 分别赋值给s0,s93, s177
		//更新s0
		for (k = 0; k < size[0]; k++)
			memset(s[0][k], 0, sizeof(char) * 160);
		for (j = 0; j < size3; j++)
		{
			for (k = 0; k < 160; k++)
			{
				s[0][j][k] = t3[j][k];
			}
		}
		size[0] = size3;
		//更新s93
		for (k = 0; k < size[93]; k++)
			memset(s[93][k], 0, sizeof(char) * 160);
		for (j = 0; j < size1; j++)
		{
			for (k = 0; k < 160; k++)
			{
				s[93][j][k] = t1[j][k];
			}
		}
		size[93] = size1;
		//更新s177
		for (k = 0; k < size[177]; k++)
			memset(s[177][k], 0, sizeof(char) * 160);
		for (j = 0; j < size2; j++)
		{
			for (k = 0; k < 160; k++)
			{
				s[177][j][k] = t2[j][k];
			}
		}
		size[177] = size2;

		Da[93 + i] = degt3;
		Db[84 + i] = degt1;
		Dc[111 + i] = degt2;
		Dav[93 + i] = DEG3[0];
		Dbv[84 + i] = DEG1[0];
		Dcv[111 + i] = DEG2[0];
		//printf("%d(%d) %d(%d) %d  %d(%d)\n", Da[93 + i], flag1, Db[84 + i], flag2, size1,Dc[111 + i],flag3);
		//printf("%d %d %d\n", vfA[i], vfB[i], vfC[i]);
		/*if (i == 103)
		{
			Dc[111 + i] = Dcv[111 + i];
		}*/
		//if()
	//	printf("%d\n", i+1);
	//	for (j = 0; j < size1; j++)
	//	{
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t1[j][k] == 1)
	//				printf("iv%d", k);
	//		}
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t1[j][k+80] == 1)
	//				printf("k%d", k);
	//		}
	//		if (todeg(t1[j]) == 0)
	//			printf("1");
	//		if (size1>1)
	//			printf("+");

	//	}
	//	printf("\n");

	//	for (j = 0; j < size2; j++)
	//	{
	//		//if(deg)
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t2[j][k] == 1)
	//				printf("iv%d", k);
	//		}
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t2[j][k + 80] == 1)
	//				printf("k%d", k);
	//		}
	//		if (todeg(t2[j]) == 0)
	//			printf("1");
	//		if(size2>1)
	//			printf("+");
	//	}
	//	printf("\n");

	//	for (j = 0; j < size3; j++)
	//	{
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t3[j][k] == 1)
	//				printf("iv%d", k);
	//		}
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t3[j][k + 80] == 1)
	//				printf("k%d", k);
	//		}
	//		if (todeg(t3[j]) == 0)
	//			printf("1");
	//		if (size3>1)
	//			printf("+");
	//	}
	//	printf("\n*****************************************\n\n");
	}

	/*for (i = 0; i < N0; i++)
	{
	printf("%d %d %d\n", Da[i+93],Db[i+84],Dc[i+111]);
	}*/
	for(i=0;i<N0;i++)
	{
		for(j=0;j<m;j++)
		{
			if(i>=leadcoefs[j].round)
			{
				basnum[i]++;
			}
		}
	}
	
	for (i = 0; i < m; i++)
	{
		fprintf(fp, "the %dth round leadcoefs of Reg%d\n", leadcoefs[i].round, leadcoefs[i].feedbakpos);
		//printf("Done!!!");
		for (k = 0; k < leadcoefs[i].size; k++)
		{
			for (j = 0; j < 80; j++)
			{
				if (leadcoefs[i].leadcoef[k][j])
					fprintf(fp,"k(%d)", j);
			}
			if(leadcoefs[i].size>1)
				fprintf(fp,"+");
		}
		fprintf(fp, "\n");
	}
	for (i = 0; i < 10000; i++)
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
	for (j = 0; j < 288; j++)
	{
		for (i = 0; i < 10000; i++)
		{
			free(s[j][i]);
		}
		free(s[j]);
	}
	free(s);
	free(leadcoefs);
	
	fclose(fp);
	//往后是正常的代数次数估计, 如果代数次数小于cube的维数则有效
	//现在不好处理的是去掉基的过程.
	//全部记下来
}

//verify,用于验证是否为单机
void decompositionVerify(int cube[], int dim, char *** upA, char ***upB,char ***upC, int sizeA[], int sizeB[], int sizeC[],int vfA[],int vfB[],int vfC[],int pos, int posr, int basnum[], int N0)
{
	//char s[288][10000][160] = {0};//前80比特表达IV, 后80比特表示key, 最后一比特比较1
	char ***s;
	int size[288] = {0};//记录每一个内部状态比特的单项式的数量. 
	int i, j, k,m,l,tempdeg=0;
	FILE *fp;
	fopen_s(&fp, "Res.txt", "a+");
	
	s = (char***)malloc(sizeof(char**) * 288);
	for (i = 0; i < 288; i++)
	{
		s[i] = (char **)malloc(sizeof(char*) * 10000);
		for (j = 0; j < 10000;j++)
		{
			s[i][j] = (char *)malloc(sizeof(char) * 160);
			memset(s[i][j], 0, sizeof(char) * 160);
		}
	}

	//用于存储中间结果
	//char f1[10000][160], f2[10000][160], f3[10000][160];
	//用于存储更新结果
	//char t1[10000][160], t2[10000][160], t3[10000][160];
	char **f1, **f2, **f3, **t1, **t2, **t3;
	f1 = (char **)malloc(sizeof(char *) * 10000);
	f2 = (char **)malloc(sizeof(char *) * 10000);
	f3 = (char **)malloc(sizeof(char *) * 10000);
	t1 = (char **)malloc(sizeof(char *) * 10000);
	t2 = (char **)malloc(sizeof(char *) * 10000);
	t3 = (char **)malloc(sizeof(char *) * 10000);
	for (i = 0; i < 10000; i++)
	{
		f1[i] = (char *)malloc(sizeof(char) * 160);
		f2[i] = (char *)malloc(sizeof(char) * 160);
		f3[i] = (char *)malloc(sizeof(char) * 160);
		t1[i] = (char *)malloc(sizeof(char) * 160);
		t2[i] = (char *)malloc(sizeof(char) * 160);
		t3[i] = (char *)malloc(sizeof(char) * 160);
		memset(f1[i], 0, sizeof(char) * 160);
		memset(f2[i], 0, sizeof(char) * 160);
		memset(f3[i], 0, sizeof(char) * 160);
		memset(t1[i], 0, sizeof(char) * 160);
		memset(t2[i], 0, sizeof(char) * 160);
		memset(t3[i], 0, sizeof(char) * 160);
	}
	int vanpos1[100], vanpos2[100], vanpos3[100];
	int size1, size2, size3,round,flag1,flag2,flag3;
	int DEG1[2], DEG2[2], DEG3[2];
	int vansizet1[1], vansizet2[1], vansizet3[1];
	int degt1, degt2, degt3;
	int coefnum1, coefnum2, coefnum3;
	char coeft1[1000][80] = { 0 }, coeft2[1000][80] = { 0 }, coeft3[1000][80] = {0};
	basis *leadcoefs;
	int Da[1000], Db[1000],Dc[1000];
	int Dav[1000], Dbv[1000],Dcv[1000];
	leadcoefs = (basis *)malloc(sizeof(basis) * 600);
	//初始化Da,Db,Dc数组.
	for (i = 0; i < 13; i++)
	{
		Da[i] = -10000;
		Dav[i] = -10000;
	}	
	for (i = 13; i < 93; i = i + 1)
	{
		Da[i] = 0;
		Dav[i] = 0;
	}
	for (i = 0; i < 4; i++)
	{
		Db[i] = -10000;
		Dbv[i] = -10000;
	}
	for (i = 4; i < 84; i++)
	{
		Db[i] = -10000;
		Dbv[i] = -10000;
	}
	for (i = 0; i < 3; i++)
	{
		Dc[i] = 0;
		Dcv[i] = 0;
	}
	for (i = 3; i < 111; i++)
	{
		Dc[i] = -10000;
		Dcv[i] = -10000;
	}
		
	//初始化: 密钥比特填充, cube变元填充, 常值填充
	//填充密钥比特
	for (i = 0; i < 80;i++)
	{ 
		s[i][0][80+i] = 1;
		size[i] = 1;
	}
	//填充cube变元
	for (i = 0; i < dim; i++)
	{
		s[93 + cube[i]][0][cube[i]] = 1;
		size[93 + cube[i]] = 1;
		Db[83 - cube[i]] = 1;
		Dbv[83 - cube[i]] = 1;
	}
	//单项式1怎么处理, 再加1比特
	for (i = 285; i < 288; i++)
	{
		size[i] = 1;
	}
	
	m = 0;
	round = N0;
	//每一轮最高次项的系数
	for (i = 0; i < round; i++)
	{
		//if (i == 96)
		//{
		//	for (k = 0; k < size[175 - 1]; k++)
		//	{
		//		//for (j = 0; j < 160; j++)
		//			//printf("%d", s[91][k][j]);
		//		for (j = 80; j < 160; j++)
		//		{
		//			if (s[175-1][k][j] == 1)
		//				printf("k%d", j - 80);
		//		}
		//		printf("\n");
		//	}
		//	for (k = 0; k < size[176 - 1]; k++)
		//	{
		//		/*for (j = 0; j < 160; j++)
		//			printf("%d", s[92][k][j]);*/
		//		for (j = 80; j < 160; j++)
		//		{
		//			if (s[176-1][k][j] == 1)
		//				printf("k%d", j - 80);
		//		}
		//		printf("\n");
		//	}
		//}
		//s66+s91*s92+s93+s171;
		size1=multi(s[91 - 1], s[92 - 1], size[91 - 1], size[92 - 1], f1);
		size1=addition(f1, s[66 - 1], s[93 - 1], s[171 - 1], size1, size[66 - 1], size[93 - 1], size[171 - 1],t1);
		
		/*for (j = 0; j < 160; j++)
			printf("%d", t1[0][j]);*/
		//s162+s175*s176+size177+s264
		size2 = multi(s[175 - 1], s[176 - 1], size[175 - 1], size[176 - 1], f2);
		size2 = addition(f2, s[162 - 1], s[177 - 1], s[264 - 1], size2, size[162 - 1], size[177 - 1], size[264 - 1], t2);
		//s243+s286*s287+size288+s69
		size3= multi(s[286 - 1], s[287 - 1], size[286 - 1], size[287 - 1], f3);
		//printf("%d,%d,%d,%d\n", size3, size[243 - 1], size[288 - 1], size[69 - 1]);
		size3 = addition(f3, s[243 - 1], s[288 - 1], s[69 - 1], size3, size[243 - 1], size[288 - 1], size[69 - 1], t3);
		//下面需要对t1,t2,t3判断最高此项,还需要存储去掉最高项之后的次高项的次数
		//要定义一个结构体来存储
		//直接复制完全的ANF
		for (j = 0; j < size3; j++)
		{
			for (k = 0; k < 160; k++)
			{
				upA[i][j][k]=t3[j][k];
			}
		}
		sizeA[i]=size3;
		
		for (j = 0; j < size1; j++)
		{
			for (k = 0; k < 160; k++)
			{
				upB[i][j][k] = t1[j][k];
			}
		}
		sizeB[i]=size1;
		

		for (j = 0; j < size2; j++)
		{
			for (k = 0; k < 160; k++)
			{
				upC[i][j][k] = t2[j][k];
			}
		}
		sizeC[i]=size2;

		memset(vanpos1, 0, sizeof(int) * 1000);
		memset(vanpos2, 0, sizeof(int) * 1000);
		memset(vanpos3, 0, sizeof(int) * 1000);
		for (j = 0; j < 1000; j++)
		{
			memset(coeft1[i], 0, sizeof(char) * 80);
			memset(coeft2[i], 0, sizeof(char) * 80);
			memset(coeft3[i], 0, sizeof(char) * 80);
		}

		coefnum1 = getleadcoef(t1, size1, coeft1,DEG1,vanpos1, vansizet1);
		coefnum2 = getleadcoef(t2, size2, coeft2,DEG2,vanpos2, vansizet2);
		coefnum3 = getleadcoef(t3, size3, coeft3,DEG3,vanpos3, vansizet3);

		

		//检验是否有全0项在里面
		flag1 = 0;
		flag2 = 0;
		flag3 = 0;
		if (coefnum1 == 0)
		{
			flag1 = 1;
		}
		if (coefnum2 == 0)
		{
			flag2 = 1;
		}
		if (coefnum3 == 0)
		{
			flag3 = 1;
		}
		for (k = 0; k < coefnum1; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft1[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag1 = 1;
				break;
			}
		}
		//检验是否有全0项在里面for t2
		for (k = 0; k < coefnum2; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft2[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag2 = 1;
				break;
			}
		}

		//检验是否有全0项在里面for t3
		for (k = 0; k < coefnum3; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft3[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag3 = 1;
				break;
			}
		}
		//直接输出到文件也可以, 反正实际上没有什么用的.
		//如果那个flag1不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if ((i==posr)&&(pos==1))
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 1;
			leadcoefs[m].size = coefnum1;
			for (j = 0; j < coefnum1; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft1[j][k];
				}

			}
			m++;
			//此时将degt1赋值成次高项的次数,
			degt1 = DEG1[1];
			size1=vanish(t1, vanpos1,size1 ,vansizet1[0]);
			vfB[i]=1;
			//此时不消项的代数次数就是这样
			//Dbv[84 + i] = DEG1[0];
		}
		else
		{
			//说明此时最高项不能被0化, 
			degt1 = DEG1[0];
			vfB[i]=0;
			//Dbv[84 + i] = DEG1[0];
		}
		//如果那个flag2不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if ((i==posr)&&(pos==2))
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 2;
			leadcoefs[m].size = coefnum2;
			for (j = 0; j < coefnum2; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft2[j][k];
				}

			}
			m++;
			//此时, 将degt2赋值成次高项的系数
			degt2 = DEG2[1];
			size2 = vanish(t2, vanpos2, size2, vansizet2[0]);
			vfC[i]=1;
		}
		else
		{
			//此时t2中的最高项不能被去掉,
			degt2 = DEG2[0];
			vfC[i]=0;
		}
	
		//如果那个flag3不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if ((i==posr)&&(pos==3))
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 3;
			leadcoefs[m].size = coefnum3;
			for (j = 0; j < coefnum3; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft3[j][k];
				}
			}
			m++;
			//此时, 最高项系数能够被去掉, 因此, degt3应该被赋值成次高项的次数
			degt3 = DEG3[1];
			size3 = vanish(t3, vanpos3, size3, vansizet3[0]);
			vfA[i]=1;
		}
		else
		{
			//此时, 最高次项不能够被零花, 此时, degt3应该被赋值成最高次项
			degt3 = DEG3[0];
			vfA[i]=0;
		}



		//shift咯
		//首先是内部状态比特的移位
		for (j = 92; j >0; j--)
		{
			//首先要memset, 将其余的东西都赋值为0
			for (k = 0; k < size[j];k++)
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
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
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
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
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
				{
					s[j][k][l] = s[j - 1][k][l];
				}
			}
			size[j] = size[j - 1];
		}
		//t1,t2,t3, 分别赋值给s0,s93, s177
		//更新s0
		for (k = 0; k < size[0]; k++)
			memset(s[0][k], 0, sizeof(char) * 160);
		for (j = 0; j < size3; j++)
		{
			for (k = 0; k < 160; k++)
			{
				s[0][j][k] = t3[j][k];
			}
		}
		size[0] = size3;
		//更新s93
		for (k = 0; k < size[93]; k++)
			memset(s[93][k], 0, sizeof(char) * 160);
		for (j = 0; j < size1; j++)
		{
			for (k = 0; k < 160; k++)
			{
				s[93][j][k] = t1[j][k];
			}
		}
		size[93] = size1;
		//更新s177
		for (k = 0; k < size[177]; k++)
			memset(s[177][k], 0, sizeof(char) * 160);
		for (j = 0; j < size2; j++)
		{
			for (k = 0; k < 160; k++)
			{
				s[177][j][k] = t2[j][k];
			}
		}
		size[177] = size2;

		Da[93 + i] = degt3;
		Db[84 + i] = degt1;
		Dc[111 + i] = degt2;
		Dav[93 + i] = DEG3[0];
		Dbv[84 + i] = DEG1[0];
		Dcv[111 + i] = DEG2[0];
		//printf("%d(%d) %d(%d) %d  %d(%d)\n", Da[93 + i], flag1, Db[84 + i], flag2, size1,Dc[111 + i],flag3);
		//printf("%d %d %d\n", vfA[i], vfB[i], vfC[i]);
		/*if (i == 103)
		{
			Dc[111 + i] = Dcv[111 + i];
		}*/
		//if()
	//	printf("%d\n", i+1);
	//	for (j = 0; j < size1; j++)
	//	{
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t1[j][k] == 1)
	//				printf("iv%d", k);
	//		}
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t1[j][k+80] == 1)
	//				printf("k%d", k);
	//		}
	//		if (todeg(t1[j]) == 0)
	//			printf("1");
	//		if (size1>1)
	//			printf("+");

	//	}
	//	printf("\n");

	//	for (j = 0; j < size2; j++)
	//	{
	//		//if(deg)
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t2[j][k] == 1)
	//				printf("iv%d", k);
	//		}
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t2[j][k + 80] == 1)
	//				printf("k%d", k);
	//		}
	//		if (todeg(t2[j]) == 0)
	//			printf("1");
	//		if(size2>1)
	//			printf("+");
	//	}
	//	printf("\n");

	//	for (j = 0; j < size3; j++)
	//	{
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t3[j][k] == 1)
	//				printf("iv%d", k);
	//		}
	//		for (k = 0; k < 80; k++)
	//		{
	//			if (t3[j][k + 80] == 1)
	//				printf("k%d", k);
	//		}
	//		if (todeg(t3[j]) == 0)
	//			printf("1");
	//		if (size3>1)
	//			printf("+");
	//	}
	//	printf("\n*****************************************\n\n");
	}

	/*for (i = 0; i < N0; i++)
	{
	printf("%d %d %d\n", Da[i+93],Db[i+84],Dc[i+111]);
	}*/
	for(i=0;i<N0;i++)
	{
		for(j=0;j<m;j++)
		{
			if(i>=leadcoefs[j].round)
			{
				basnum[i]++;
			}
		}
	}
	
	for (i = 0; i < m; i++)
	{
		fprintf(fp, "the %dth round leadcoefs of Reg%d\n", leadcoefs[i].round, leadcoefs[i].feedbakpos);
		//printf("Done!!!");
		for (k = 0; k < leadcoefs[i].size; k++)
		{
			for (j = 0; j < 80; j++)
			{
				if (leadcoefs[i].leadcoef[k][j])
					fprintf(fp,"k(%d)", j);
			}
			if(leadcoefs[i].size>1)
				fprintf(fp,"+");
		}
		fprintf(fp, "\n");
	}
	for (i = 0; i < 10000; i++)
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
	for (j = 0; j < 288; j++)
	{
		for (i = 0; i < 10000; i++)
		{
			free(s[j][i]);
		}
		free(s[j]);
	}
	free(s);
	free(leadcoefs);
	
	fclose(fp);
	//往后是正常的代数次数估计, 如果代数次数小于cube的维数则有效
	//现在不好处理的是去掉基的过程.
	//全部记下来
}



//search for free non-cube variable
void decompositionFreeNC(int cube[], int dim, int freenc, char *** upA, char ***upB,char ***upC, int sizeA[], int sizeB[], int sizeC[],int vfA[],int vfB[],int vfC[],int pos, int posr, int basnum[], int N0)
{
	//char s[288][10000][160] = {0};//前80比特表达IV, 后80比特表示key, 最后一比特比较1

	char ***s;
	int size[288] = {0};//记录每一个内部状态比特的单项式的数量. 
	int i, j, k,m,l,tempdeg=0;
	
	FILE *fp;
	//fopen_s(&fp, "Res.txt", "a+");	
	s = (char***)malloc(sizeof(char**) * 288);
	for (i = 0; i < 288; i++)
	{
		s[i] = (char **)malloc(sizeof(char*) * 10000);
		for (j = 0; j < 10000;j++)
		{
			s[i][j] = (char *)malloc(sizeof(char) * 160);
			memset(s[i][j], 0, sizeof(char) * 160);
		}
	}

	//用于存储中间结果
	//char f1[10000][160], f2[10000][160], f3[10000][160];
	//用于存储更新结果
	//char t1[10000][160], t2[10000][160], t3[10000][160];
	char **f1, **f2, **f3, **t1, **t2, **t3;
	f1 = (char **)malloc(sizeof(char *) * 10000);
	f2 = (char **)malloc(sizeof(char *) * 10000);
	f3 = (char **)malloc(sizeof(char *) * 10000);
	t1 = (char **)malloc(sizeof(char *) * 10000);
	t2 = (char **)malloc(sizeof(char *) * 10000);
	t3 = (char **)malloc(sizeof(char *) * 10000);
	for (i = 0; i < 10000; i++)
	{
		f1[i] = (char *)malloc(sizeof(char) * 160);
		f2[i] = (char *)malloc(sizeof(char) * 160);
		f3[i] = (char *)malloc(sizeof(char) * 160);
		t1[i] = (char *)malloc(sizeof(char) * 160);
		t2[i] = (char *)malloc(sizeof(char) * 160);
		t3[i] = (char *)malloc(sizeof(char) * 160);
		memset(f1[i], 0, sizeof(char) * 160);
		memset(f2[i], 0, sizeof(char) * 160);
		memset(f3[i], 0, sizeof(char) * 160);
		memset(t1[i], 0, sizeof(char) * 160);
		memset(t2[i], 0, sizeof(char) * 160);
		memset(t3[i], 0, sizeof(char) * 160);
	}
	int vanpos1[100], vanpos2[100], vanpos3[100];
	int size1, size2, size3,round,flag1,flag2,flag3;
	int DEG1[2], DEG2[2], DEG3[2];
	int vansizet1[1], vansizet2[1], vansizet3[1];
	int degt1, degt2, degt3;
	int coefnum1, coefnum2, coefnum3;
	char coeft1[1000][80] = { 0 }, coeft2[1000][80] = { 0 }, coeft3[1000][80] = {0};
	basis *leadcoefs;
	int Da[1000], Db[1000],Dc[1000];
	int Dav[1000], Dbv[1000],Dcv[1000];
	leadcoefs = (basis *)malloc(sizeof(basis) * 600);
	//初始化Da,Db,Dc数组.
	for (i = 0; i < 13; i++)
	{
		Da[i] = -10000;
		Dav[i] = -10000;
	}	
	for (i = 13; i < 93; i = i + 1)
	{
		Da[i] = 0;
		Dav[i] = 0;
	}
	for (i = 0; i < 4; i++)
	{
		Db[i] = -10000;
		Dbv[i] = -10000;
	}
	for (i = 4; i < 84; i++)
	{
		Db[i] = -10000;
		Dbv[i] = -10000;
	}
	for (i = 0; i < 3; i++)
	{
		Dc[i] = 0;
		Dcv[i] = 0;
	}
	for (i = 3; i < 111; i++)
	{
		Dc[i] = -10000;
		Dcv[i] = -10000;
	}
		
	//初始化: 密钥比特填充, cube变元填充, 常值填充
	//填充密钥比特
	for (i = 0; i < 80;i++)
	{ 
		s[i][0][80+i] = 1;
		size[i] = 1;
	}
	//填充cube变元
	for (i = 0; i < dim; i++)
	{
		s[93 + cube[i]][0][cube[i]] = 1;
		size[93 + cube[i]] = 1;
		Db[83 - cube[i]] = 1;
		Dbv[83 - cube[i]] = 1;
	}
	
	s[93+freenc][0][freenc]=1;
	size[93 + freenc] = 1;
	//单项式1怎么处理, 再加1比特
	for (i = 285; i < 288; i++)
	{
		size[i] = 1;
	}
	
	m = 0;
	round = N0;
	//每一轮最高次项的系数
	for (i = 0; i < round; i++)
	{
		size1=multi(s[91 - 1], s[92 - 1], size[91 - 1], size[92 - 1], f1);
		size1=addition(f1, s[66 - 1], s[93 - 1], s[171 - 1], size1, size[66 - 1], size[93 - 1], size[171 - 1],t1);
		
		/*for (j = 0; j < 160; j++)
			printf("%d", t1[0][j]);*/
		//s162+s175*s176+size177+s264
		size2 = multi(s[175 - 1], s[176 - 1], size[175 - 1], size[176 - 1], f2);
		size2 = addition(f2, s[162 - 1], s[177 - 1], s[264 - 1], size2, size[162 - 1], size[177 - 1], size[264 - 1], t2);
		//s243+s286*s287+size288+s69
		size3= multi(s[286 - 1], s[287 - 1], size[286 - 1], size[287 - 1], f3);
		//printf("%d,%d,%d,%d\n", size3, size[243 - 1], size[288 - 1], size[69 - 1]);
		size3 = addition(f3, s[243 - 1], s[288 - 1], s[69 - 1], size3, size[243 - 1], size[288 - 1], size[69 - 1], t3);
		//下面需要对t1,t2,t3判断最高此项,还需要存储去掉最高项之后的次高项的次数
		//要定义一个结构体来存储
		//直接复制完全的ANF
		for (j = 0; j < size3; j++)
		{
			for (k = 0; k < 160; k++)
			{
				upA[i][j][k]=t3[j][k];
			}
		}
		sizeA[i]=size3;
		
		for (j = 0; j < size1; j++)
		{
			for (k = 0; k < 160; k++)
			{
				upB[i][j][k] = t1[j][k];
			}
		}
		sizeB[i]=size1;
		

		for (j = 0; j < size2; j++)
		{
			for (k = 0; k < 160; k++)
			{
				upC[i][j][k] = t2[j][k];
			}
		}
		sizeC[i]=size2;

		memset(vanpos1, 0, sizeof(int) * 1000);
		memset(vanpos2, 0, sizeof(int) * 1000);
		memset(vanpos3, 0, sizeof(int) * 1000);
		for (j = 0; j < 1000; j++)
		{
			memset(coeft1[i], 0, sizeof(char) * 80);
			memset(coeft2[i], 0, sizeof(char) * 80);
			memset(coeft3[i], 0, sizeof(char) * 80);
		}

		coefnum1 = getleadcoefFreeIV(t1, size1, coeft1,cube, dim,DEG1,vanpos1, vansizet1);
		coefnum2 = getleadcoefFreeIV(t2, size2, coeft2,cube, dim,DEG2,vanpos2, vansizet2);
		coefnum3 = getleadcoefFreeIV(t3, size3, coeft3,cube, dim,DEG3,vanpos3, vansizet3);

		

		//检验是否有全0项在里面
		flag1 = 0;
		flag2 = 0;
		flag3 = 0;
		if (coefnum1 == 0)
		{
			flag1 = 1;
		}
		if (coefnum2 == 0)
		{
			flag2 = 1;
		}
		if (coefnum3 == 0)
		{
			flag3 = 1;
		}
		for (k = 0; k < coefnum1; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft1[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag1 = 1;
				break;
			}
		}
		//检验是否有全0项在里面for t2
		for (k = 0; k < coefnum2; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft2[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag2 = 1;
				break;
			}
		}

		//检验是否有全0项在里面for t3
		for (k = 0; k < coefnum3; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft3[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag3 = 1;
				break;
			}
		}
		//直接输出到文件也可以, 反正实际上没有什么用的.
		//如果那个flag1不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if ((i==posr)&&(pos==1))
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 1;
			leadcoefs[m].size = coefnum1;
			for (j = 0; j < coefnum1; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft1[j][k];
				}

			}
			m++;
			//此时将degt1赋值成次高项的次数,
			degt1 = DEG1[1];
			size1=vanish(t1, vanpos1,size1 ,vansizet1[0]);
			vfB[i]=1;
			//此时不消项的代数次数就是这样
			//Dbv[84 + i] = DEG1[0];
		}
		else
		{
			//说明此时最高项不能被0化, 
			degt1 = DEG1[0];
			vfB[i]=0;
			//Dbv[84 + i] = DEG1[0];
		}
		//如果那个flag2不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if ((i==posr)&&(pos==2))
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 2;
			leadcoefs[m].size = coefnum2;
			for (j = 0; j < coefnum2; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft2[j][k];
				}

			}
			m++;
			//此时, 将degt2赋值成次高项的系数
			degt2 = DEG2[1];
			size2 = vanish(t2, vanpos2, size2, vansizet2[0]);
			vfC[i]=1;
		}
		else
		{
			//此时t2中的最高项不能被去掉,
			degt2 = DEG2[0];
			vfC[i]=0;
		}
	
		//如果那个flag3不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if ((i==posr)&&(pos==3))
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 3;
			leadcoefs[m].size = coefnum3;
			for (j = 0; j < coefnum3; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft3[j][k];
				}
			}
			m++;
			//此时, 最高项系数能够被去掉, 因此, degt3应该被赋值成次高项的次数
			degt3 = DEG3[1];
			size3 = vanish(t3, vanpos3, size3, vansizet3[0]);
			vfA[i]=1;
		}
		else
		{
			//此时, 最高次项不能够被零花, 此时, degt3应该被赋值成最高次项
			degt3 = DEG3[0];
			vfA[i]=0;
		}



		//shift咯
		//首先是内部状态比特的移位
		for (j = 92; j >0; j--)
		{
			//首先要memset, 将其余的东西都赋值为0
			for (k = 0; k < size[j];k++)
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
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
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
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
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
				{
					s[j][k][l] = s[j - 1][k][l];
				}
			}
			size[j] = size[j - 1];
		}
		//t1,t2,t3, 分别赋值给s0,s93, s177
		//更新s0
		for (k = 0; k < size[0]; k++)
			memset(s[0][k], 0, sizeof(char) * 160);
		for (j = 0; j < size3; j++)
		{
			for (k = 0; k < 160; k++)
			{
				s[0][j][k] = t3[j][k];
			}
		}
		size[0] = size3;
		//更新s93
		for (k = 0; k < size[93]; k++)
			memset(s[93][k], 0, sizeof(char) * 160);
		for (j = 0; j < size1; j++)
		{
			for (k = 0; k < 160; k++)
			{
				s[93][j][k] = t1[j][k];
			}
		}
		size[93] = size1;
		//更新s177
		for (k = 0; k < size[177]; k++)
			memset(s[177][k], 0, sizeof(char) * 160);
		for (j = 0; j < size2; j++)
		{
			for (k = 0; k < 160; k++)
			{
				s[177][j][k] = t2[j][k];
			}
		}
		size[177] = size2;

		Da[93 + i] = degt3;
		Db[84 + i] = degt1;
		Dc[111 + i] = degt2;
		Dav[93 + i] = DEG3[0];
		Dbv[84 + i] = DEG1[0];
		Dcv[111 + i] = DEG2[0];
	}
	for(i=0;i<N0;i++)
	{
		for(j=0;j<m;j++)
		{
			if(i>=leadcoefs[j].round)
			{
				basnum[i]++;
			}
		}
	}
	
	//for (i = 0; i < m; i++)
	//{
	//	fprintf(fp, "the %dth round leadcoefs of Reg%d\n", leadcoefs[i].round, leadcoefs[i].feedbakpos);
	//	//printf("Done!!!");
	//	for (k = 0; k < leadcoefs[i].size; k++)
	//	{
	//		for (j = 0; j < 80; j++)
	//		{
	//			if (leadcoefs[i].leadcoef[k][j])
	//				fprintf(fp,"k(%d)", j);
	//		}
	//		if(leadcoefs[i].size>1)
	//			fprintf(fp,"+");
	//	}
	//	fprintf(fp, "\n");
	//}
	for (i = 0; i < 10000; i++)
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
	for (j = 0; j < 288; j++)
	{
		for (i = 0; i < 10000; i++)
		{
			free(s[j][i]);
		}
		free(s[j]);
	}
	free(s);
	free(leadcoefs);
	
	//fclose(fp);
	//往后是正常的代数次数估计, 如果代数次数小于cube的维数则有效
	//现在不好处理的是去掉基的过程.
	//全部记下来
}

void decompositionFreeNCV2(int cube[], int dim, int freenc, char *** upA, char ***upB,char ***upC, int sizeA[], int sizeB[], int sizeC[],int vfA[],int vfB[],int vfC[],int pos[], int posr[], int posnum, int basnum[], int N0)
{
	//char s[288][10000][160] = {0};//前80比特表达IV, 后80比特表示key, 最后一比特比较1

	char ***s;
	int size[288] = {0};//记录每一个内部状态比特的单项式的数量. 
	int i, j, k,m,l,tempdeg=0;
	
	FILE *fp;
	//fopen_s(&fp, "Res.txt", "a+");	
	s = (char***)malloc(sizeof(char**) * 288);
	for (i = 0; i < 288; i++)
	{
		s[i] = (char **)malloc(sizeof(char*) * 10000);
		for (j = 0; j < 10000;j++)
		{
			s[i][j] = (char *)malloc(sizeof(char) * 160);
			memset(s[i][j], 0, sizeof(char) * 160);
		}
	}

	//用于存储中间结果
	//char f1[10000][160], f2[10000][160], f3[10000][160];
	//用于存储更新结果
	//char t1[10000][160], t2[10000][160], t3[10000][160];
	char **f1, **f2, **f3, **t1, **t2, **t3;
	f1 = (char **)malloc(sizeof(char *) * 10000);
	f2 = (char **)malloc(sizeof(char *) * 10000);
	f3 = (char **)malloc(sizeof(char *) * 10000);
	t1 = (char **)malloc(sizeof(char *) * 10000);
	t2 = (char **)malloc(sizeof(char *) * 10000);
	t3 = (char **)malloc(sizeof(char *) * 10000);
	for (i = 0; i < 10000; i++)
	{
		f1[i] = (char *)malloc(sizeof(char) * 160);
		f2[i] = (char *)malloc(sizeof(char) * 160);
		f3[i] = (char *)malloc(sizeof(char) * 160);
		t1[i] = (char *)malloc(sizeof(char) * 160);
		t2[i] = (char *)malloc(sizeof(char) * 160);
		t3[i] = (char *)malloc(sizeof(char) * 160);
		memset(f1[i], 0, sizeof(char) * 160);
		memset(f2[i], 0, sizeof(char) * 160);
		memset(f3[i], 0, sizeof(char) * 160);
		memset(t1[i], 0, sizeof(char) * 160);
		memset(t2[i], 0, sizeof(char) * 160);
		memset(t3[i], 0, sizeof(char) * 160);
	}
	int vanpos1[100], vanpos2[100], vanpos3[100];
	int size1, size2, size3,round,flag1,flag2,flag3;
	int DEG1[2], DEG2[2], DEG3[2];
	int vansizet1[1], vansizet2[1], vansizet3[1];
	int degt1, degt2, degt3;
	int coefnum1, coefnum2, coefnum3;
	char coeft1[1000][80] = { 0 }, coeft2[1000][80] = { 0 }, coeft3[1000][80] = {0};
	basis *leadcoefs;
	int Da[1000], Db[1000],Dc[1000];
	int Dav[1000], Dbv[1000],Dcv[1000];
	int p=0;
	leadcoefs = (basis *)malloc(sizeof(basis) * 600);
	//初始化Da,Db,Dc数组.
	for (i = 0; i < 13; i++)
	{
		Da[i] = -10000;
		Dav[i] = -10000;
	}	
	for (i = 13; i < 93; i = i + 1)
	{
		Da[i] = 0;
		Dav[i] = 0;
	}
	for (i = 0; i < 4; i++)
	{
		Db[i] = -10000;
		Dbv[i] = -10000;
	}
	for (i = 4; i < 84; i++)
	{
		Db[i] = -10000;
		Dbv[i] = -10000;
	}
	for (i = 0; i < 3; i++)
	{
		Dc[i] = 0;
		Dcv[i] = 0;
	}
	for (i = 3; i < 111; i++)
	{
		Dc[i] = -10000;
		Dcv[i] = -10000;
	}
		
	//初始化: 密钥比特填充, cube变元填充, 常值填充
	//填充密钥比特
	for (i = 0; i < 80;i++)
	{ 
		s[i][0][80+i] = 1;
		size[i] = 1;
	}
	//填充cube变元
	for (i = 0; i < dim; i++)
	{
		s[93 + cube[i]][0][cube[i]] = 1;
		size[93 + cube[i]] = 1;
		Db[83 - cube[i]] = 1;
		Dbv[83 - cube[i]] = 1;
	}
	
	s[93+freenc][0][freenc]=1;
	size[93 + freenc] = 1;
	//单项式1怎么处理, 再加1比特
	for (i = 285; i < 288; i++)
	{
		size[i] = 1;
	}
	
	m = 0;
	round = N0;
	//每一轮最高次项的系数
	for (i = 0; i < round; i++)
	{
		size1=multi(s[91 - 1], s[92 - 1], size[91 - 1], size[92 - 1], f1);
		size1=addition(f1, s[66 - 1], s[93 - 1], s[171 - 1], size1, size[66 - 1], size[93 - 1], size[171 - 1],t1);
		
		/*for (j = 0; j < 160; j++)
			printf("%d", t1[0][j]);*/
		//s162+s175*s176+size177+s264
		size2 = multi(s[175 - 1], s[176 - 1], size[175 - 1], size[176 - 1], f2);
		size2 = addition(f2, s[162 - 1], s[177 - 1], s[264 - 1], size2, size[162 - 1], size[177 - 1], size[264 - 1], t2);
		//s243+s286*s287+size288+s69
		size3= multi(s[286 - 1], s[287 - 1], size[286 - 1], size[287 - 1], f3);
		//printf("%d,%d,%d,%d\n", size3, size[243 - 1], size[288 - 1], size[69 - 1]);
		size3 = addition(f3, s[243 - 1], s[288 - 1], s[69 - 1], size3, size[243 - 1], size[288 - 1], size[69 - 1], t3);
		//下面需要对t1,t2,t3判断最高此项,还需要存储去掉最高项之后的次高项的次数
		//要定义一个结构体来存储
		//直接复制完全的ANF
		for (j = 0; j < size3; j++)
		{
			for (k = 0; k < 160; k++)
			{
				upA[i][j][k]=t3[j][k];
			}
		}
		sizeA[i]=size3;
		
		for (j = 0; j < size1; j++)
		{
			for (k = 0; k < 160; k++)
			{
				upB[i][j][k] = t1[j][k];
			}
		}
		sizeB[i]=size1;
		

		for (j = 0; j < size2; j++)
		{
			for (k = 0; k < 160; k++)
			{
				upC[i][j][k] = t2[j][k];
			}
		}
		sizeC[i]=size2;

		memset(vanpos1, 0, sizeof(int) * 1000);
		memset(vanpos2, 0, sizeof(int) * 1000);
		memset(vanpos3, 0, sizeof(int) * 1000);
		for (j = 0; j < 1000; j++)
		{
			memset(coeft1[i], 0, sizeof(char) * 80);
			memset(coeft2[i], 0, sizeof(char) * 80);
			memset(coeft3[i], 0, sizeof(char) * 80);
		}

		coefnum1 = getleadcoefFreeIV(t1, size1, coeft1,cube, dim,DEG1,vanpos1, vansizet1);
		coefnum2 = getleadcoefFreeIV(t2, size2, coeft2,cube, dim,DEG2,vanpos2, vansizet2);
		coefnum3 = getleadcoefFreeIV(t3, size3, coeft3,cube, dim,DEG3,vanpos3, vansizet3);

		

		//检验是否有全0项在里面
		flag1 = 0;
		flag2 = 0;
		flag3 = 0;
		if (coefnum1 == 0)
		{
			flag1 = 1;
		}
		if (coefnum2 == 0)
		{
			flag2 = 1;
		}
		if (coefnum3 == 0)
		{
			flag3 = 1;
		}
		for (k = 0; k < coefnum1; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft1[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag1 = 1;
				break;
			}
		}
		//检验是否有全0项在里面for t2
		for (k = 0; k < coefnum2; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft2[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag2 = 1;
				break;
			}
		}

		//检验是否有全0项在里面for t3
		for (k = 0; k < coefnum3; k++)
		{
			tempdeg = 0;
			for (j = 0; j < 80; j++)
			{
				tempdeg += coeft3[k][j];
			}
			//如果首相系数中有1的话说明这个并不能将次,因此, 不能放到机里面
			if (tempdeg == 0)
			{
				flag3 = 1;
				break;
			}
		}
		//直接输出到文件也可以, 反正实际上没有什么用的.
		//如果那个flag1不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if((i==posr[p])&&(pos[p]==1)&&(p<posnum))
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 1;
			leadcoefs[m].size = coefnum1;
			for (j = 0; j < coefnum1; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft1[j][k];
				}

			}
			m++;
			//此时将degt1赋值成次高项的次数,
			degt1 = DEG1[1];
			size1=vanish(t1, vanpos1,size1 ,vansizet1[0]);
			vfB[i]=1;
			p++;
			//此时不消项的代数次数就是这样
			//Dbv[84 + i] = DEG1[0];
		}
		else
		{
			//说明此时最高项不能被0化, 
			degt1 = DEG1[0];
			vfB[i]=0;
			//Dbv[84 + i] = DEG1[0];
		}
		//如果那个flag2不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if((i==posr[p])&&(pos[p]==2)&&(p<posnum))
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 2;
			leadcoefs[m].size = coefnum2;
			for (j = 0; j < coefnum2; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft2[j][k];
				}

			}
			m++;
			//此时, 将degt2赋值成次高项的系数
			degt2 = DEG2[1];
			size2 = vanish(t2, vanpos2, size2, vansizet2[0]);
			vfC[i]=1;
			p++;
		}
		else
		{
			//此时t2中的最高项不能被去掉,
			degt2 = DEG2[0];
			vfC[i]=0;
		}
	
		//如果那个flag3不是1,那么就将这些放到基中
		//需要记录的信息有: 轮数, 还有系数, 反馈位置
		if((i==posr[p])&&(pos[p]==3)&&(p<posnum))
		{
			leadcoefs[m].round = i;
			leadcoefs[m].feedbakpos = 3;
			leadcoefs[m].size = coefnum3;
			for (j = 0; j < coefnum3; j++)
			{
				for (k = 0; k < 80; k++)
				{
					leadcoefs[m].leadcoef[j][k] = coeft3[j][k];
				}
			}
			m++;
			//此时, 最高项系数能够被去掉, 因此, degt3应该被赋值成次高项的次数
			degt3 = DEG3[1];
			size3 = vanish(t3, vanpos3, size3, vansizet3[0]);
			vfA[i]=1;
			p++;
		}
		else
		{
			//此时, 最高次项不能够被零花, 此时, degt3应该被赋值成最高次项
			degt3 = DEG3[0];
			vfA[i]=0;
		}



		//shift咯
		//首先是内部状态比特的移位
		for (j = 92; j >0; j--)
		{
			//首先要memset, 将其余的东西都赋值为0
			for (k = 0; k < size[j];k++)
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
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
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
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
				memset(s[j][k], 0, sizeof(char) * 160);
			for (k = 0; k < size[j - 1]; k++)
			{
				for (l = 0; l < 160; l++)
				{
					s[j][k][l] = s[j - 1][k][l];
				}
			}
			size[j] = size[j - 1];
		}
		//t1,t2,t3, 分别赋值给s0,s93, s177
		//更新s0
		for (k = 0; k < size[0]; k++)
			memset(s[0][k], 0, sizeof(char) * 160);
		for (j = 0; j < size3; j++)
		{
			for (k = 0; k < 160; k++)
			{
				s[0][j][k] = t3[j][k];
			}
		}
		size[0] = size3;
		//更新s93
		for (k = 0; k < size[93]; k++)
			memset(s[93][k], 0, sizeof(char) * 160);
		for (j = 0; j < size1; j++)
		{
			for (k = 0; k < 160; k++)
			{
				s[93][j][k] = t1[j][k];
			}
		}
		size[93] = size1;
		//更新s177
		for (k = 0; k < size[177]; k++)
			memset(s[177][k], 0, sizeof(char) * 160);
		for (j = 0; j < size2; j++)
		{
			for (k = 0; k < 160; k++)
			{
				s[177][j][k] = t2[j][k];
			}
		}
		size[177] = size2;

		Da[93 + i] = degt3;
		Db[84 + i] = degt1;
		Dc[111 + i] = degt2;
		Dav[93 + i] = DEG3[0];
		Dbv[84 + i] = DEG1[0];
		Dcv[111 + i] = DEG2[0];
	}
	for(i=0;i<N0;i++)
	{
		for(j=0;j<m;j++)
		{
			if(i>=leadcoefs[j].round)
			{
				basnum[i]++;
			}
		}
	}
	
	//for (i = 0; i < m; i++)
	//{
	//	fprintf(fp, "the %dth round leadcoefs of Reg%d\n", leadcoefs[i].round, leadcoefs[i].feedbakpos);
	//	//printf("Done!!!");
	//	for (k = 0; k < leadcoefs[i].size; k++)
	//	{
	//		for (j = 0; j < 80; j++)
	//		{
	//			if (leadcoefs[i].leadcoef[k][j])
	//				fprintf(fp,"k(%d)", j);
	//		}
	//		if(leadcoefs[i].size>1)
	//			fprintf(fp,"+");
	//	}
	//	fprintf(fp, "\n");
	//}
	for (i = 0; i < 10000; i++)
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
	for (j = 0; j < 288; j++)
	{
		for (i = 0; i < 10000; i++)
		{
			free(s[j][i]);
		}
		free(s[j]);
	}
	free(s);
	free(leadcoefs);
	
	//fclose(fp);
	//往后是正常的代数次数估计, 如果代数次数小于cube的维数则有效
	//现在不好处理的是去掉基的过程.
	//全部记下来
}