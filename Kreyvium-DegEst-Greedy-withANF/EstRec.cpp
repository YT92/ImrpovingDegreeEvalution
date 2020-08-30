#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include"DegEst.h"
#include"ANF.h"
int MaxroundMindeg(int Reslist[][3], int Res[], int remdim)
{
	int i, maxround, mindeg, minroughdeg;
	int loc = 0;
	maxround = 0;
	mindeg = 100000000;
	minroughdeg = 100000000;
	for (i = 0; i < remdim; i++)
	{
		if (maxround < Reslist[i][0])
		{
			maxround = Reslist[i][0];
		}
	}

	//for (i = 0; i < remdim; i++)
	//{
	//	if (maxround == Reslist[i,0])
	//	{
	//		//maxround = Reslist[i][0];
	//		if (mindeg > Reslist[i,1])
	//		{
	//			mindeg = Reslist[i,1];
	//			//loc = i;
	//		}
	//	}
	//}
	for (i = 0; i < remdim; i++)
	{
		//if ((maxround == Reslist[i,0])&&(mindeg==Reslist[i,1]))
		if ((maxround == Reslist[i][0]))
		{
			if (minroughdeg > Reslist[i][2])
			{
				minroughdeg = Reslist[i][2];
				loc = i;
			}
		}
	}
	Res[0] = maxround;
	Res[1] = minroughdeg;
	return loc;
}

int MindegMaxround(int Reslist[][3], int Res[], int remdim)
{
	int i, maxround, mindeg, minroughdeg, loc = 0;
	maxround = 0;
	mindeg = 100000000;
	minroughdeg = 100000000;

	for (i = 0; i < remdim; i++)
	{
		if (minroughdeg > Reslist[i][2])
		{
			minroughdeg = Reslist[i][2];
			//loc = i;
		}
	}

	for (i = 0; i < remdim; i++)
	{
		if (minroughdeg == Reslist[i][2])
		{
			if (maxround < Reslist[i][0])
			{
				maxround = Reslist[i][0];
				loc = i;
			}
		}
	}

	//for (i = 0; i < remdim; i++)
	//{
	//	if (maxround == Reslist[i,0])
	//	{
	//		//maxround = Reslist[i][0];
	//		if (mindeg > Reslist[i,1])
	//		{
	//			mindeg = Reslist[i,1];
	//			//loc = i;
	//		}
	//	}
	//}

	Res[0] = maxround;
	Res[1] = minroughdeg;
	return loc;
}

int MaxroundMindegWithNB(int Reslist[][3], int Res[], int remX[], int X[], int remdim)
{
	int i, maxround, mindeg, minroughdeg, j, nbmin;
	int loc = 0;
	int nbcount[128] = { 0 };
	maxround = 0;
	mindeg = 100000000;
	minroughdeg = 100000000;
	nbmin = 100000000;
	//璁＄畻nbcouunt
	for (i = 0; i < remdim; i++)
	{
		for (j = 0; j < 128 - remdim; j++)
		{
			if ((X[j] == remX[i] + 1) || (X[j] == remX[i] - 1))
			{
				nbcount[i]++;
			}
		}
	}

	for (i = 0; i < remdim; i++)
	{
		if (maxround < Reslist[i][0])
		{
			maxround = Reslist[i][0];
		}
	}
	for (i = 0; i < remdim; i++)
	{
		//if ((maxround == Reslist[i,0])&&(mindeg==Reslist[i,1]))
		if ((maxround == Reslist[i][0]))
		{
			if (minroughdeg > Reslist[i][2])
			{
				minroughdeg = Reslist[i][2];
				//loc = i;
			}
		}
	}
	for (i = 0; i < remdim; i++)
	{
		if ((maxround == Reslist[i][0]) && (minroughdeg == Reslist[i][2]))
		{
			if (nbcount[i] < nbmin)
			{
				nbmin = nbcount[i];
				loc = i;
			}
		}
	}
	Res[0] = maxround;
	Res[1] = minroughdeg;
	return loc;
}

int MindegMaxroundWithNB(int Reslist[][3], int Res[], int remX[], int X[], int remdim)
{
	int i, maxround, mindeg, minroughdeg, j, nbmin;
	int loc = 0;
	int nbcount[128] = { 0 };
	maxround = 0;
	mindeg = 100000000;
	minroughdeg = 100000000;
	nbmin = 100000000;
	//璁＄畻nbcouunt
	for (i = 0; i < remdim; i++)
	{
		for (j = 0; j < 128 - remdim; j++)
		{
			if ((X[j] == remX[i] + 1) || (X[j] == remX[i] - 1))
			{
				nbcount[i]++;
			}
		}
	}

	for (i = 0; i < remdim; i++)
	{
		if (minroughdeg > Reslist[i][2])
		{
			minroughdeg = Reslist[i][2];
			//loc = i;
		}
	}

	for (i = 0; i < remdim; i++)
	{
		if (minroughdeg == Reslist[i][2])
		{
			if (maxround < Reslist[i][0])
			{
				maxround = Reslist[i][0];
				//loc = i;
			}
		}
	}
	for (i = 0; i < remdim; i++)
	{
		if ((maxround == Reslist[i][0]) && (minroughdeg == Reslist[i][2]))
		{
			if (nbcount[i] < nbmin)
			{
				nbmin = nbcount[i];
				loc = i;
			}
		}
	}
	Res[0] = maxround;
	Res[1] = minroughdeg;
	//printf("loc=%d\n", loc);
	return loc;
}

int StrategySet(int stranum, int Reslist[][3], int Res[], int remX[], int X[], int remdim)
{
	int loc = 0;
	if (stranum == 1)
	{
		loc = MaxroundMindeg(Reslist, Res, remdim);
	}
	if (stranum == 2)
	{
		loc = MindegMaxround(Reslist, Res, remdim);
	}
	if (stranum == 3)
	{
		loc = MaxroundMindegWithNB(Reslist, Res, remX, X, remdim);
	}
	if (stranum == 4)
	{
		loc = MindegMaxroundWithNB(Reslist, Res, remX, X, remdim);
	}
	return loc;
}


//初始化Dv
void IniDv(int Dv[],int N0, int cube[], int X[],int dim, int Xdim)
{
	int i, r;
	int tempDv[128] = { 0 };
	for (i = 0; i < 128; i++)
	{
		Dv[i] = -100000;
	}
	for (i = 0; i < dim; i++)
	{
		Dv[127 - cube[i]] = 0;
	}
	for (i = 0; i < Xdim; i++)
	{
		Dv[127 - X[i]] = 1;
	}
	for (i = 0; i < 128; i++)
	{
		tempDv[i] = Dv[i];
	}
	//跑N0轮
	//r = N0&0x7f;
	for (i = 0; i < N0; i++)
	{
		Dv[i + 128] = Dv[i];
	}


}
//初始化Da,Db,Dc
void IniD(int D[], unsigned int ***Reg, int size[], int RegLen, int N0, int cube[], int X[], int dim, int Xdim)
{
	//如果有cube以外的变元，那么不算
	unsigned int cubeterm[4] = {0};
	unsigned int temp[4] = { 0 };
	int i = 0,j=0,k=0;
	int d=0;
	int dmax = -1;
	int flag = 0;
	for (i = 0; i < dim; i++)
	{
		cubeterm[cube[i] >> 5] = cubeterm[cube[i] >> 5] | (0x01 << (cube[i] & 0x1f));
	}
	for (i = 0; i < 4; i++)
	{
		cubeterm[i] ^= 0xffffffff;
	}
	for (i = 0; i < N0 + RegLen; i++)
	{
		dmax = -1;
		flag = 0;
		for (j = 0; j < size[i]; j++)
		{
			//首先检验是否有cube变元以外的变元
			for (k = 0; k < 4; k++)
			{
				temp[k] = cubeterm[k]&Reg[i][j][k];
			}
			if (temp[0] + temp[1] + temp[2] + temp[3] == 0)
			{
				d = getdeg(Reg[i][j], X, Xdim);
				if (dmax < d)
				{
					dmax = d;
				}
				flag = 1;
			}
		}
		if (dmax == -1)
		{
			if (flag == 0)
				dmax = -100000;
			else
				dmax = 0;
		}
		D[i] = dmax;
	}
	
}

int getX(int cube[], int dim, int X[],int loclist[], int loclen)
{
	int i=0, m=0;
	int flag[128] = { 0 };
	for (i = 0; i < dim; i++)
	{
		flag[cube[i]] = 1;
	}
	for (i = 0; i < loclen; i++)
	{
		flag[cube[loclist[i]]] = 0;
	}
	//
	for (i = 0; i < 128; i++)
	{
		if (flag[i] == 1)
			X[m++] = i;
	}
	return m;
}

int EstDegRec(int X[], int dim, char filename[], int N, int p, int Res[])
{
	//
	int i, m;
	// ֱ�Ӽ���ܶ��ֵĴ��������� ���������������ߵĻ�����ô����������ڽ���һ�ֵ�չ��
	int curmaxround, curmaxdeg;
	int maxroundlist[1000] = { 0 }, maxdeglist[1000] = { 0 };
	int testflag[1000] = { 0 };
	int res[2] = { 0 };
	int cvlist[1000] = { 0 };
	int CurX[100] = { 0 };
	int loclist[1000] = { 0 };
	int loclen = 0;
	int recurflag = 1;//���ڱ���Ƿ��������.
	int localmax = 0;
	int pdeg = 0;
	int pdeglist[1000] = { 0 };

	EstimateDegree(X, dim, filename, N, loclist, loclen, 0, p, res);
	curmaxdeg = res[1];
	curmaxround = res[0];
	localmax = curmaxround;
	Res[2] = curmaxdeg;
	pdeg = res[1];
	//printf("%d %d\n", res[0], res[1]);
	//printf("%d ", res[1]);
	//��ʼ��CurX, not needed
	/*for (i = 0; i < dim; i++)
	{
	CurX[i] = X[i];
	}*/
	m = 0;
	int mrec = 0;
	while (recurflag == 1)
	{
		for (i = 0; i < dim; i++)
		{
			if (testflag[i] == 0)
			{
				//printf("%d: ", i);
				//����һ����������Լ���Ӧ�Ĵ�������
				loclist[m] = i;
				loclen = m + 1;
				EstimateDegree(X, dim, filename, N, loclist, loclen, 1, p, res);
				//EstimateDegree(X, dim, filename, N, loclist, loclen, 0, p, res);
				//maxdeglist[i] = res[0];
				maxroundlist[i] = res[0];
				pdeglist[i] = res[1];
				printf("%d %d %d\n", i,res[0], res[1]);
			}
		}
		// ����Ƿ���Ч��������
		//����ж������������, ��ô����������ĺϲ��� ���Ƿֱ������
		//����һ�°�

		//�ϲ�
		//m = 0;
		//memset(testflag, 0, sizeof(int) * 1000);
		for (i = 0; i < dim; i++)
		{
			//if (((maxdeglist[i] + 1 < curmaxdeg)&&(maxroundlist[i]>=curmaxround)) || (maxroundlist[i]>curmaxround))
			if ((maxroundlist[i]>curmaxround))
			{
				cvlist[m] = i;
				loclist[m] = i;
				testflag[i] = 1;
				m++;
				if (localmax < maxroundlist[i])
				{
					localmax = maxroundlist[i];
					pdeg = pdeglist[i];
				}

			}
		}
		loclen = m;
		curmaxround = localmax;
		if (m == 0)
		{
			recurflag = 0;
		}
		//��������,��ô��֮�м���
		if (m == mrec)
		{
			recurflag = 0;
		}
		else
		{
			mrec = m;
		}
		//����loclist����
		/*printf("\n**********************************%d***************************************\n",dim-loclen);
		for (i = 0; i < dim; i++)
		{
		if (testflag[i] == 0)
		printf("%d ", X[i]);
		}
		printf("\n*************************************************************************\n");*/
	}

	printf("Max Round is %d", curmaxround);
	Res[0] = curmaxround;
	Res[1] = pdeg;
	return curmaxround;
}
int EstDegRecV(int X[], int dim, char filename[], int N, int p, int Res[])
{
	//
	int i, m;
	// 直锟接硷拷锟斤拷芏锟斤拷值拇锟斤拷锟斤拷锟斤拷锟斤拷锟?锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟竭的伙拷锟斤拷锟斤拷么锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷诮锟斤拷锟揭伙拷值锟秸癸拷锟?
	int curmaxround, curmaxdeg;
	int maxroundlist[1000] = { 0 }, maxdeglist[1000] = { 0 };
	int testflag[1000] = { 0 };
	int res[2] = { 0 };
	int cvlist[1000] = { 0 };
	int CurX[100] = { 0 };
	int loclist[1000] = { 0 };
	int loclen = 0;
	int recurflag = 1;//锟斤拷锟节憋拷锟斤拷欠锟斤拷锟斤拷锟斤拷锟斤拷.
	int localmax = 0;
	int pdeg = 0;
	int pdeglist[1000] = { 0 };

	EstimateDegree(X, dim, filename, N, loclist, loclen, 0, p, res);
	curmaxdeg = res[1];
	curmaxround = res[0];
	localmax = curmaxround;
	Res[2] = curmaxdeg;
	pdeg = res[1];
	//printf("%d %d\n", res[0], res[1]);
	//printf("%d ", res[1]);
	//锟斤拷始锟斤拷CurX, not needed
	/*for (i = 0; i < dim; i++)
	{
	CurX[i] = X[i];
	}*/
	m = 0;
	int mrec = 0;
	while (recurflag == 1)
	{
		for (i = 0; i < dim; i++)
		{
			if (testflag[i] == 0)
			{
				//printf("%d: ", i);
				//锟斤拷锟斤拷一锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷约锟斤拷锟接︼拷拇锟斤拷锟斤拷锟斤拷锟?
				loclist[m] = i;
				loclen = m + 1;
				EstimateDegree(X, dim, filename, N, loclist, loclen, 1, p, res);
				//EstimateDegree(X, dim, filename, N, loclist, loclen, 0, p, res);
				//maxdeglist[i] = res[0];
				maxroundlist[i] = res[0];
				pdeglist[i] = res[1];
				//printf("%d %d\n", res[0], res[1]);
			}
		}
		// 锟斤拷锟斤拷欠锟斤拷锟叫э拷锟斤拷锟斤拷锟斤拷锟?
		//锟斤拷锟斤拷卸锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷, 锟斤拷么锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷暮喜锟斤拷锟?锟斤拷锟角分憋拷锟斤拷锟斤拷锟?
		//锟斤拷锟斤拷一锟铰帮拷

		//锟较诧拷
		//m = 0;
		//memset(testflag, 0, sizeof(int) * 1000);
		for (i = 0; i < dim; i++)
		{
			//if (((maxdeglist[i] + 1 < curmaxdeg)&&(maxroundlist[i]>=curmaxround)) || (maxroundlist[i]>curmaxround))
			if ((maxroundlist[i]>curmaxround))
			{
				cvlist[m] = i;
				loclist[m] = i;
				testflag[i] = 1;
				m++;
				if (localmax < maxroundlist[i])
				{
					localmax = maxroundlist[i];
					pdeg = pdeglist[i];
				}

			}
		}
		/*for(i=0;i<dim;i++)
		{
		if (pdeg > pdeglist[i])
		{
		pdeg= pdeglist[i];
		}
		}*/
		loclen = m;
		curmaxround = localmax;
		if (m == 0)
		{
			recurflag = 0;
		}
		//锟斤拷锟斤拷锟斤拷锟斤拷,锟斤拷么锟斤拷之锟叫硷拷锟斤拷
		if (m == mrec)
		{
			recurflag = 0;
		}
		else
		{
			mrec = m;
		}
		//锟斤拷锟斤拷loclist锟斤拷锟斤拷
		/*printf("\n**********************************%d***************************************\n",dim-loclen);
		for (i = 0; i < dim; i++)
		{
		if (testflag[i] == 0)
		printf("%d ", X[i]);
		}
		printf("\n*************************************************************************\n");*/
	}

	//printf("Max Round is %d", curmaxround);
	Res[0] = curmaxround;
	Res[1] = pdeg;
	Res[2] = pdeg;
	return curmaxround;
}
int EstDegRecwithANF(unsigned int *** A, unsigned int *** B, unsigned int *** C, int sizeA[], int sizeB[], int sizeC[], int cube[], int dim, int N0, int N, int p, int Res[])
{
	//
	int i, m;
	// 直锟接硷拷锟斤拷芏锟斤拷值拇锟斤拷锟斤拷锟斤拷锟斤拷锟?锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟竭的伙拷锟斤拷锟斤拷么锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷诮锟斤拷锟揭伙拷值锟秸癸拷锟?
	int curmaxround, curmaxdeg;
	int maxroundlist[1000] = { 0 }, maxdeglist[1000] = { 0 };
	int testflag[1000] = { 0 };
	int res[2] = { 0 };
	int cvlist[1000] = { 0 };
	int CurX[100] = { 0 };
	int loclist[1000] = { 0 };
	int loclen = 0;
	int recurflag = 1;//锟斤拷锟节憋拷锟斤拷欠锟斤拷锟斤拷锟斤拷锟斤拷.
	int localmax = 0;
	int pdeg = 0;
	int pdeglist[1000] = { 0 };

	int Da[2000] = { 0 }, Db[2000] = { 0 }, Dc[2000] = { 0 }, Dv[2000] = {0};
	int X[128] = { 0 },Xdim;

	//初始化Da，Db,Dc,Dv
	IniDv(Dv, N0, cube, cube, dim, dim);
	IniD(Da, A, sizeA, 93, N0, cube, cube, dim, dim);
	IniD(Db, B, sizeB, 84, N0, cube, cube, dim, dim);
	IniD(Dc, C, sizeC, 111, N0, cube, cube, dim, dim);
	/*for (i = 0; i < 93 + N0; i++)
		printf("%d,", Da[i]);
	printf("\n");
	for (i = 0; i < 84 + N0; i++)
		printf("%d,", Db[i]);
	printf("\n");
	for (i = 0; i < 111 + N0; i++)
		printf("%d,", Dc[i]);
	printf("\n");*/
	EstimateDegreeV(Da,Db,Dc,Dv,dim,N0, N, loclist, loclen, 0, p, res);

	curmaxdeg = res[1];
	curmaxround = res[0];
	localmax = curmaxround;
	Res[2] = curmaxdeg;
	pdeg = res[1];
	//printf("%d %d\n", res[0], res[1]);
	//printf("%d ", res[1]);
	//锟斤拷始锟斤拷CurX, not needed
	/*for (i = 0; i < dim; i++)
	{
	CurX[i] = X[i];
	}*/
	m = 0;
	int mrec = 0;
	while (recurflag == 1)
	{
		for (i = 0; i < dim; i++)
		{
			if (testflag[i] == 0)
			{
				//printf("%d: ", i);
				//锟斤拷锟斤拷一锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷约锟斤拷锟接︼拷拇锟斤拷锟斤拷锟斤拷锟?
				loclist[m] = i;
				loclen = m + 1;
				Xdim=getX(cube, dim, X, loclist, loclen);
				IniDv(Dv, N0, cube, X, dim, Xdim);
				IniD(Da, A, sizeA, 93, N0, cube, X, dim, Xdim);
				IniD(Db, B, sizeB, 84, N0, cube, X, dim, Xdim);
				IniD(Dc, C, sizeC, 111, N0, cube, X, dim, Xdim);
				/*for (int j = 0; j < 93 + N0; j++)
					printf("%d,", Da[j]);
				printf("\n");
				for (int j = 0; j < 84 + N0; j++)
					printf("%d,", Db[j]);
				printf("\n");
				for (int j = 0; j < 111 + N0; j++)
					printf("%d,", Dc[j]);
				printf("\n");*/
				EstimateDegreeV(Da, Db, Dc, Dv, dim, N0, N, loclist, loclen, 0, p, res);
				maxroundlist[i] = res[0];
				pdeglist[i] = res[1];
				//printf("%d %d %d\n", i,res[0], res[1]);
			}
		}
		// 锟斤拷锟斤拷欠锟斤拷锟叫э拷锟斤拷锟斤拷锟斤拷锟?
		//锟斤拷锟斤拷卸锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷, 锟斤拷么锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷暮喜锟斤拷锟?锟斤拷锟角分憋拷锟斤拷锟斤拷锟?
		//锟斤拷锟斤拷一锟铰帮拷

		//锟较诧拷
		//m = 0;
		//memset(testflag, 0, sizeof(int) * 1000);
		for (i = 0; i < dim; i++)
		{
			//if (((maxdeglist[i] + 1 < curmaxdeg)&&(maxroundlist[i]>=curmaxround)) || (maxroundlist[i]>curmaxround))
			if ((maxroundlist[i]>curmaxround))
			{
				cvlist[m] = i;
				loclist[m] = i;
				testflag[i] = 1;
				m++;
				if (localmax < maxroundlist[i])
				{
					localmax = maxroundlist[i];
					pdeg = pdeglist[i];
				}

			}
		}
		loclen = m;
		curmaxround = localmax;
		if (m == 0)
		{
			recurflag = 0;
		}
		//锟斤拷锟斤拷锟斤拷锟斤拷,锟斤拷么锟斤拷之锟叫硷拷锟斤拷
		if (m == mrec)
		{
			recurflag = 0;
		}
		else
		{
			mrec = m;
		}
		//锟斤拷锟斤拷loclist锟斤拷锟斤拷
		/*printf("\n**********************************%d***************************************\n",dim-loclen);
		for (i = 0; i < dim; i++)
		{
		if (testflag[i] == 0)
		printf("%d ", X[i]);
		}
		printf("\n*************************************************************************\n");*/
	}

	printf("Max Round is %d", curmaxround);
	Res[0] = curmaxround;
	Res[1] = pdeg;
	return curmaxround;
}

//pdeg最小

void Greedy(int p)
{
	int X[128] = {};
	int tempX[128] = {};
	int dim = 0, tempdim = 0;
	int remX[128] = { 0 };
	int remXcopy[128] = { 0 };
	int i, remdim;
	int N = 1152;
	char filename[40] = "RecDeg.txt";
	//int p = 1052;
	int Res[3] = { 0 };
	int tempres[2] = { 0 };
	int Reslist[1000][3] = { 0 };
	int loclist[1000] = { 0 };
	int loclen = 0, flag = 0;
	int templist[2] = { 0 };
	int m, stranum = 0;
	int maxround = 0;
	int mindeg = 0;
	int globalmax = 0;
	int loc = 0;
	int minnb;
	int nbcount[128] = { 0 };
	//璁剧疆绛栫暐
	stranum = 4;
	//if (stranum == 1)
	//{
	//	printf("Greedy Strategy: Maxround-Mindeg\n");
	//}
	//if (stranum == 2)
	//{
	//	printf("Greedy Strategy: Mindeg-Maxround\n");
	//}
	//锟斤拷锟饺斤拷remX锟斤拷锟矫筹拷全锟斤拷
	for (i = 0; i < 128; i++)
	{
		remX[i] = i;
		remXcopy[i] = i;
	}
	remdim = 128;
	while (dim <128)
	{
		//锟斤拷锟斤拷一锟斤拷锟斤拷元然锟斤拷
		m = 0;
		for (i = 0; i < dim; i++)
		{
			tempX[i] = X[i];
		}
		for (i = 0; i < remdim; i++)
		{
			tempX[dim] = remX[i];
			tempdim = dim + 1;
			//EstDegRec(tempX, tempdim, filename, N, p, Res);
			EstDegRec(tempX, tempdim, filename, N, p, Res);
			//EstimateDegree(tempX, tempdim, filename, N, loclist, loclen, 0, p, Res);
			Reslist[m][0] = Res[0];
			Reslist[m][1] = Res[1];
			Reslist[m][2] = Res[2];
			m++;
			//printf("%d: %d %d %d\n", tempX[dim], Res[0], Res[1],Res[2]);
		}
		//if (dim > 54)
		//	stranum = 1;
		//stranum = (rand() % 2) + 1;

		loc = StrategySet(stranum, Reslist, tempres, remX, X, remdim);
		maxround = tempres[0];
		mindeg = tempres[1];

		//printf("loc=%d, maxround=%d,mindeg=%d\n", loc, maxround, mindeg);
		//选锟斤拷锟揭伙拷锟?
		if (maxround > globalmax)
			globalmax = maxround;
		X[dim] = remX[loc];

		//
		memset(remX, 0, sizeof(char) * 128);
		m = 0;
		for (i = 0; i < remdim; i++)
		{
			if (i != loc)
			{
				remX[m++] = remXcopy[i];
			}
		}
		remdim--;
		dim++;
		memset(remXcopy, 0, sizeof(char) * 128);
		//printf("\n");
		for (i = 0; i < remdim; i++)
		{
			remXcopy[i] = remX[i];
			//printf("%d, ", remX[i]);
		}
		//printf("\n");

		/*printf("**************************************************************\n");
		for (i = 0; i < dim; i++)
		{
		printf("%d,", X[i]);
		}
		printf("\n%d %d %d ", maxround,loc,mindeg);
		printf("\n**************************************************************\n");*/
	}
	//printf("%d\n", maxround);
	printf("%d %d\n", maxround, globalmax);
}

//利用ANF来初始化代数次数估计的初值
void GreedyANFInner(int p, int N0, unsigned int ***A, unsigned int ***B, unsigned int ***C, int sizeA[], int sizeB[], int sizeC[])
{
	int X[128] = {};
	int tempX[128] = {};
	int dim = 0, tempdim = 0;
	int remX[128] = { 0 };
	int remXcopy[128] = { 0 };
	int i, remdim;
	int N = 1152;
	char filename[40] = "RecDeg.txt";
	//int p = 1052;
	int Res[3] = { 0 };
	int tempres[2] = { 0 };
	int Reslist[1000][3] = { 0 };
	int loclist[1000] = { 0 };
	int loclen = 0, flag = 0;
	int templist[2] = { 0 };
	int m, stranum = 0;
	int maxround = 0;
	int mindeg = 0;
	int globalmax = 0;
	int loc = 0;
	int minnb;
	int nbcount[128] = { 0 };
	//璁剧疆绛栫暐
	stranum = 4;
	//if (stranum == 1)
	//{
	//	printf("Greedy Strategy: Maxround-Mindeg\n");
	//}
	//if (stranum == 2)
	//{
	//	printf("Greedy Strategy: Mindeg-Maxround\n");
	//}
	//锟斤拷锟饺斤拷remX锟斤拷锟矫筹拷全锟斤拷
	for (i = 0; i < 128; i++)
	{
		remX[i] = i;
		remXcopy[i] = i;
	}
	remdim = 128;
	while (dim <128)
	{
		//锟斤拷锟斤拷一锟斤拷锟斤拷元然锟斤拷
		m = 0;
		for (i = 0; i < dim; i++)
		{
			tempX[i] = X[i];
		}
		for (i = 0; i < remdim; i++)
		{
			tempX[dim] = remX[i];
			tempdim = dim + 1;
			//EstDegRec(tempX, tempdim, filename, N, p, Res);

			//EstDegRec(tempX, tempdim, filename, N, p, Res);
			//EstimateDegree(tempX, tempdim, filename, N, loclist, loclen, 0, p, Res);
			EstDegRecwithANF(A, B, C, sizeA, sizeB, sizeC, tempX, tempdim, N0, N, p, Res);
			Reslist[m][0] = Res[0];
			Reslist[m][1] = Res[1];
			Reslist[m][2] = Res[2];
			m++;
			//printf("%d: %d %d %d\n", tempX[dim], Res[0], Res[1],Res[2]);
		}
		//if (dim > 54)
		//	stranum = 1;
		//stranum = (rand() % 2) + 1;

		loc = StrategySet(stranum, Reslist, tempres, remX, X, remdim);
		maxround = tempres[0];
		mindeg = tempres[1];

		//printf("loc=%d, maxround=%d,mindeg=%d\n", loc, maxround, mindeg);
		//选锟斤拷锟揭伙拷锟?
		if (maxround > globalmax)
			globalmax = maxround;
		X[dim] = remX[loc];

		//
		memset(remX, 0, sizeof(char) * 128);
		m = 0;
		for (i = 0; i < remdim; i++)
		{
			if (i != loc)
			{
				remX[m++] = remXcopy[i];
			}
		}
		remdim--;
		dim++;
		memset(remXcopy, 0, sizeof(char) * 128);
		//printf("\n");
		for (i = 0; i < remdim; i++)
		{
			remXcopy[i] = remX[i];
			//printf("%d, ", remX[i]);
		}
		//printf("\n");

		/*printf("**************************************************************\n");
		for (i = 0; i < dim; i++)
		{
		printf("%d,", X[i]);
		}
		printf("\n%d %d %d ", maxround,loc,mindeg);
		printf("\n**************************************************************\n");*/
	}
	//printf("%d\n", maxround);
	printf("%d %d\n", maxround, globalmax);
}

void GreedyANFOuter(int p)
{
	//计算一次ANF,所有的都可以用
	unsigned int ***A, ***B, ***C;
	int sizeA[1000] = { 0 };
	int sizeB[1000] = { 0 };
	int sizeC[1000] = { 0 };
	int i, j, k;
	int cube[128] = {};
	int N0 = 280;
	int dim = 128;
	int termnum = 200000;
	int malsizeA[10000], malsizeB[10000], malsizeC[10000];
	for (i = 0; i < 1000; i++)
	{
		if (i<93)
			malsizeA[i] = 1;
		if ((i >= 93) && (i<193))
			malsizeA[i] = 1000;
		if ((i >= 193) && (i<293))
			malsizeA[i] = 10000;
		if ((i >= 293)&&(i<373))
			malsizeA[i] = 15000;
		if ((i >= 373) && (i<393))
			malsizeA[i] = 150000;
		if ((i >= 393))
			malsizeA[i] = 400000;
	}
	for (i = 0; i < 1000; i++)
	{
		if (i<84)
			malsizeB[i] = 1;
		if ((i >= 84) && (i<184))
			malsizeB[i] = 1000;
		if ((i >= 184) && (i<284))
			malsizeB[i] = 10000;
		if ((i >= 284) && (i<364))
			malsizeB[i] = 15000;
		if ((i >= 364) && (i<384))
			malsizeB[i] = 150000;
		if (i >= 384)
			malsizeB[i] = 400000;
	}
	for (i = 0; i < 1000; i++)
	{
		if (i<111)
			malsizeC[i] = 1;
		if ((i >= 111) && (i<211))
			malsizeC[i] = 1000;
		if ((i >= 211) && (i<311))
			malsizeC[i] = 10000;
		if ((i >= 311) && (i<391))
			malsizeC[i] = 15000;
		if ((i >= 391) && (i<411))
			malsizeC[i] = 150000;
		if (i >= 411)
			malsizeC[i] = 400000;
	}
	//开辟s的内存空间
	A = (unsigned int ***)malloc(sizeof(unsigned int **) * (N0 + 93));
	B = (unsigned int ***)malloc(sizeof(unsigned int **) * (N0 + 84));
	C = (unsigned int ***)malloc(sizeof(unsigned int **) * (N0 + 111));
	//前93
	for (i = 0; i < N0 + 93; i++)
	{
		A[i] = (unsigned int **)malloc(sizeof(unsigned int*) * malsizeA[i]);
		for (j = 0; j < malsizeA[i]; j++)
		{
			A[i][j] = (unsigned int *)malloc(sizeof(unsigned int) * 8);
			memset(A[i][j], 0, sizeof(unsigned int) * 8);
		}
	}

	for (i = 0; i < N0 + 84; i++)
	{
		B[i] = (unsigned int **)malloc(sizeof(unsigned int*) * malsizeB[i]);
		for (j = 0; j < malsizeB[i]; j++)
		{
			B[i][j] = (unsigned int *)malloc(sizeof(unsigned int) * 8);
			memset(B[i][j], 0, sizeof(unsigned int) * 8);
		}
	}

	for (i = 0; i < N0 + 111; i++)
	{
		C[i] = (unsigned int **)malloc(sizeof(unsigned int*) * malsizeC[i]);
		for (j = 0; j < malsizeC[i]; j++)
		{
			C[i][j] = (unsigned int *)malloc(sizeof(unsigned int) * 8);
			memset(C[i][j], 0, sizeof(unsigned int) * 8);
		}
	}


	//
	for (i = 0; i < 128; i++)
	{
		cube[i] = i;
	}
	//计算ANF
	ComANFwithCubeVariableV2(A, B, C, sizeA, sizeB, sizeC, N0, cube, dim);
	//调用贪心算法

	GreedyANFInner(p, N0, A, B, C, sizeA, sizeB, sizeC);

	//释放内存
	for (i = 0; i < N0 + 93; i++)
	{
		for (j = 0; j < malsizeA[i]; j++)
		{
			free(A[i][j]);
		}
	}
	for (i = 0; i < malsizeA[i]; i++)
	{
		free(A[i]);
	}

	for (i = 0; i < N0 + 84; i++)
	{
		for (j = 0; j < malsizeB[i]; j++)
		{
			free(B[i][j]);
		}
	}
	for (i = 0; i < malsizeB[i]; i++)
	{
		free(B[i]);
	}

	for (i = 0; i < N0 + 111; i++)
	{
		for (j = 0; j < malsizeC[i]; j++)
		{
			free(C[i][j]);
		}
	}
	for (i = 0; i < malsizeC[i]; i++)
	{
		free(C[i]);
	}
	free(A);
	free(B);
	free(C);

}


void DegEstANFOuter(int X[], int dim, int N, int p)
{
	//计算一次ANF,所有的都可以用
	unsigned int ***A, ***B, ***C;
	int sizeA[1000] = { 0 };
	int sizeB[1000] = { 0 };
	int sizeC[1000] = { 0 };
	int i, j, k, maxround;
	int cube[128] = {};
	int N0 = 300;
	//int dim = 128;
	int termnum = 200000;
	int Res[3] = { 0 };
	int malsizeA[10000], malsizeB[10000], malsizeC[10000];
	FILE *fp;
	fopen_s(&fp,"Kreyviumrec.txt", "a+");
	for (i = 0; i < 1000; i++)
	{
		if (i<93)
			malsizeA[i] = 1;
		if ((i >= 93) && (i<193))
			malsizeA[i] = 1000;
		if ((i >= 193) && (i<293))
			malsizeA[i] = 10000;
		if ((i >= 293) && (i<373))
			malsizeA[i] = 15000;
		if ((i >= 373) && (i<393))
			malsizeA[i] = 150000;
		if ((i >= 393))
			malsizeA[i] = 400000;
	}
	for (i = 0; i < 1000; i++)
	{
		if (i<84)
			malsizeB[i] = 1;
		if ((i >= 84) && (i<184))
			malsizeB[i] = 1000;
		if ((i >= 184) && (i<284))
			malsizeB[i] = 10000;
		if ((i >= 284) && (i<364))
			malsizeB[i] = 15000;
		if ((i >= 364) && (i<384))
			malsizeB[i] = 150000;
		if (i >= 384)
			malsizeB[i] = 400000;
	}
	for (i = 0; i < 1000; i++)
	{
		if (i<111)
			malsizeC[i] = 1;
		if ((i >= 111) && (i<211))
			malsizeC[i] = 1000;
		if ((i >= 211) && (i<311))
			malsizeC[i] = 10000;
		if ((i >= 311) && (i<391))
			malsizeC[i] = 15000;
		if ((i >= 391) && (i<411))
			malsizeC[i] = 150000;
		if (i >= 411)
			malsizeC[i] = 400000;
	}
	//开辟s的内存空间
	A = (unsigned int ***)malloc(sizeof(unsigned int **) * (N0 + 93));
	B = (unsigned int ***)malloc(sizeof(unsigned int **) * (N0 + 84));
	C = (unsigned int ***)malloc(sizeof(unsigned int **) * (N0 + 111));
	//前93
	for (i = 0; i < N0 + 93; i++)
	{
		A[i] = (unsigned int **)malloc(sizeof(unsigned int*) * malsizeA[i]);
		for (j = 0; j < malsizeA[i]; j++)
		{
			A[i][j] = (unsigned int *)malloc(sizeof(unsigned int) * 8);
			memset(A[i][j], 0, sizeof(unsigned int) * 8);
		}
	}

	for (i = 0; i < N0 + 84; i++)
	{
		B[i] = (unsigned int **)malloc(sizeof(unsigned int*) * malsizeB[i]);
		for (j = 0; j < malsizeB[i]; j++)
		{
			B[i][j] = (unsigned int *)malloc(sizeof(unsigned int) * 8);
			memset(B[i][j], 0, sizeof(unsigned int) * 8);
		}
	}

	for (i = 0; i < N0 + 111; i++)
	{
		C[i] = (unsigned int **)malloc(sizeof(unsigned int*) * malsizeC[i]);
		for (j = 0; j < malsizeC[i]; j++)
		{
			C[i][j] = (unsigned int *)malloc(sizeof(unsigned int) * 8);
			memset(C[i][j], 0, sizeof(unsigned int) * 8);
		}
	}


	//
	for (i = 0; i < dim; i++)
	{
		cube[i] = X[i];
	}
	//计算ANF
	ComANFwithCubeVariableV2(A, B, C, sizeA, sizeB, sizeC, N0, cube, dim);
	//调用贪心算法

	//GreedyANFInner(p, N0, A, B, C, sizeA, sizeB, sizeC);
	maxround=EstDegRecwithANF(A, B, C, sizeA, sizeB, sizeC, cube, dim, N0, N, p, Res);
	fprintf(fp, "%d\n", maxround);
	//释放内存
	for (i = 0; i < N0 + 93; i++)
	{
		for (j = 0; j < malsizeA[i]; j++)
		{
			free(A[i][j]);
		}
	}
	for (i = 0; i < malsizeA[i]; i++)
	{
		free(A[i]);
	}

	for (i = 0; i < N0 + 84; i++)
	{
		for (j = 0; j < malsizeB[i]; j++)
		{
			free(B[i][j]);
		}
	}
	for (i = 0; i < malsizeB[i]; i++)
	{
		free(B[i]);
	}

	for (i = 0; i < N0 + 111; i++)
	{
		for (j = 0; j < malsizeC[i]; j++)
		{
			free(C[i][j]);
		}
	}
	for (i = 0; i < malsizeC[i]; i++)
	{
		free(C[i]);
	}
	free(A);
	free(B);
	free(C);

	fclose(fp);

}