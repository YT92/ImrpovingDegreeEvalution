#include<stdio.h>
#include<windows.h>
#include"DegEst.h"

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

int MaxroundMindegWithNB(int Reslist[][3], int Res[],int remX[],int X[],int remdim)
{
	int i, maxround, mindeg, minroughdeg,j,nbmin;
	int loc = 0;
	int nbcount[128] = {0};
	maxround = 0;
	mindeg = 100000000;
	minroughdeg = 100000000;
	nbmin = 100000000;
	//计算nbcouunt
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
	//计算nbcouunt
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
		loc=MaxroundMindeg(Reslist, Res, remdim);
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
	int recurflag = 1;//是否回溯
	int localmax = 0;
	int pdeg = 0;
	int pdeglist[1000] = { 0 };
	int pdegsum = 0;

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
				//printf("%d %d\n", res[0], res[1]);
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

	//printf("Max Round is %d", curmaxround);
	Res[0] = curmaxround;
	Res[1] = pdeg;
	return curmaxround;
}

//pdeg取最小值
int EstDegRecV(int X[], int dim, char filename[], int N, int p, int Res[])
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
				//printf("%d %d\n", res[0], res[1]);
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

	//printf("Max Round is %d", curmaxround);
	Res[0] = curmaxround;
	Res[1] = pdeg;
	Res[2] = pdeg;
	return curmaxround;
}
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
	int m,stranum=0;
	int maxround = 0;
	int mindeg = 0;
	int globalmax = 0;
	int maxrounddim = 0;
	int loc = 0;
	int minnb;
	int nbcount[128] = { 0 };
	FILE *fpout;
	fopen_s(&fpout, "ResProcedure", "a+");
	//设置策略
	stranum = 4;
	//if (stranum == 1)
	//{
	//	printf("Greedy Strategy: Maxround-Mindeg\n");
	//}
	//if (stranum == 2)
	//{
	//	printf("Greedy Strategy: Mindeg-Maxround\n");
	//}
	//���Ƚ�remX���ó�ȫ��
	for (i = 0; i < 128; i++)
	{
		remX[i] = i;
		remXcopy[i] = i;
	}
	fprintf(fpout, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   round=%d    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n", p);
	remdim = 128;
	while (dim <128)
	{
		//����һ����ԪȻ��
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
		/*if (dim > 30)
			stranum = 3;*/
		//stranum = (rand() % 2) + 1;

		loc=StrategySet(stranum, Reslist, tempres, remX, X, remdim);
		maxround = tempres[0];
		mindeg = tempres[1];

		//printf("loc=%d, maxround=%d,mindeg=%d\n", loc, maxround, mindeg);
		//ѡ���һ��
		if (maxround >= globalmax)
		{
			globalmax = maxround;
			maxrounddim = dim+1;
		}
			
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

		printf("**************************************************************\n");
		fprintf(fpout, "**************************************************************\n");
		for (i = 0; i < dim; i++)
		{
			printf("%d,", X[i]);
			fprintf(fpout, "%d,", X[i]);
		}
		printf("\n%d %d %d ", maxround, loc, mindeg);
		fprintf(fpout, "\n%d %d %d ", maxround, loc, mindeg);
		printf("\n**************************************************************\n");
		fprintf(fpout, "\n**************************************************************\n");
	}
	//printf("%d\n", maxround);
	printf("%d %d %d\n", maxround, globalmax,maxrounddim);
	fprintf(fpout, "%d %d %d\n", maxround, globalmax, maxrounddim);

	fprintf(fpout, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
	fprintf(fpout, "\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	fclose(fpout);
}
int main()
{
	//int X[100] = { 1,3,5,7,9,11,13,16,18,20,22,25,27,29,31,33,35,37,40,42,44,46,48,50,53,55,57,59,61,63,68,70,72,74,76,81,83,85,87,90,92,94,96,98,100,103,105,107,109,111,113,115,118,120,122,124};
	int X[100] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30,
		32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60,
		62, 64, 66, 68, 70, 72, 74, 76, 78, 81, 83, 85, 87, 89, 91,
		93, 95, 97, 99, 101, 103, 105, 107, 109, 111, 113, 115,
		117, 121, 123, 125, 127};
	int X2[100] = { 22,3,1,16,18,20,11,13,85,9,5,7,35,37,55,87,33,103,31,29,79,81,105,48,24,72,50,83
		,39,89,44,59,109,70,27,46,61,94,96,98,100,107,111,113,115,42,57,53,74,92,124,68,
		126,76,122,120,118 };
	int N = 1000;
	int dim = 57;
	int i = 0;
	int Res[2] = { 0 };
	char filename[40] = "rec.txt";
	//EstDegRec(X, dim, filename, N);
	//int roundlist[128] = {629,781,742,796,820,873,1133,793,807,871,885,915,917,944,959,978,990,995,998,1002,1021,1068,1077,1114,1130,1132,1136,1143,1145};
	int roundlist[128] = {788,787};
	for (i = 1131; i <1132; i++)
	{
		printf("%d:", i);
		Greedy(i);
	}
	//EstDegRec(X2, dim, filename, N,968,Res);
	system("pause");
	return 0;
}