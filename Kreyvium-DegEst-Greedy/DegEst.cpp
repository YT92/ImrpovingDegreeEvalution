#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<stdlib.h>
int DIM = 800;

//需要初始化Dv
void initialize(int Da[], int Db[], int Dc[], int Dv[],int X[], int dim, char filename[], int loclist[], int loclen, int flag)//D被初始化，X是变量集合，索引              
{
	int i, j, k;
	for (i = 0; i<93; i++)
		Da[i] = 0;
	for (i = 0; i<84; i++)
		Db[i] = -10000;

	//IV
	for (i = 0; i<44; i++)
		Dc[110-i] = -10000;

	//66个1
	for (i = 44; i<110; i++)
		Dc[110-i] = 0;
	
	Dc[0] = -10000;
	//初始化                                                                                                               
	for (i = 0; i < dim; i++)
	{
		if (X[i] < 84)
			Db[83 - X[i]] = 1;
		else
		{
			Dc[110 - (X[i] - 84)] = 1;
		}
	}
	//Db[83 - 46] = 0;

	//初始化Dv[]
	for (i = 0; i < 128; i++)
	{
		Dv[i] = -10000;
	}
	for (i = 0; i < dim; i++)
	{
		Dv[127 - X[i]] = 1;
	}

	//那也就是需要在两个地方进行处理,
	if (flag == 1)
	{
		for (i = 0; i < loclen; i++)
		{
			//主寄存器上次数设置为0
			if (X[loclist[i]] < 84)
				Db[83 - X[loclist[i]]] =0;
			else
			{
				Dc[110 - (X[loclist[i]] - 84)] = 0;
			}
			//辅助寄存器上次数设置为0
			Dv[127 - X[loclist[i]]] = 0;
		}
	}

}


int DEGLA(int Da[], int Db[], int Dc[], int t)
{
	int t1, t2, t3;
	t1 = Dc[t + 110 - 65];//t时刻的C的内部状态是Dc[t]-Dc[t+100]; 而且顺序是反着的                                               
	t2 = Dc[t + 110 - 110];
	t3 = Da[t + 92 - 68];
	t1 = max(t1, t2);
	t1 = max(t1, t3);
	t1 = max(t1, 0);
	/*if (t1 >= DIM)
		return DIM;*/
	return t1;
}

int DEGLB(int Da[], int Db[], int Dc[], int Dv[],int t)
{
	int t1, t2, t3;
	t1 = Da[t + 92 - 65];//t时刻的C的内部状态是Dc[t]-Dc[t+100]; 而且顺序是反着的                                                
	t2 = Da[t + 92 - 92];
	t3 = Db[t + 83 - 77];
	t1 = max(t1, t2);
	t1 = max(t1, t3);
	t1 = max(t1, Dv[t]);
	/*if (t1 >= DIM)
		return DIM;*/
	return t1;
}

int DEGLC(int Da[], int Db[], int Dc[], int t)
{
	int t1, t2, t3;
	t1 = Db[t + 83 - 68];//t时刻的C的内部状态是Dc[t]-Dc[t+100]; 而且顺序是反着的                                                
	t2 = Db[t + 83 - 83];
	t3 = Dc[t + 110 - 86];
	t1 = max(t1, t2);
	t1 = max(t1, t3);
	/*if (t1 >= DIM)
		return DIM;*/
	return t1;
}

//A寄存器中t时刻的状态是Da[t]-Da[t+92] //无需修改                                                                         
int DegMulA(int Da[], int Db[], int Dc[], int t)
{
	int t1, t2;
	int d1, d2, d3;
	int temp1, temp2, temp3;
	t1 = t - 110;
	//如果t1<=0,那么直接返回两者相加                                                                                       
	if (t1 <= 0)
	{
		return Dc[t1 + 110] + Dc[t1 + 1 + 110];
	}
	//否则往回退一步                                                                                                       
	t2 = t1 - 83;

	//                                                                                                                     
	temp1 = Db[t2 + 83] + Dc[t1 + 110 + 1];
	temp2 = Db[t2 + 83 + 2] + Dc[t1 + 110];
	temp3 = Db[t2 + 83] + Db[t2 + 83 + 1] + Db[t2 + 83 + 2];
	temp1 = min(temp1, temp2);
	temp1 = min(temp1, temp3);

	temp2 = DEGLC(Da, Db, Dc, t1) + Dc[t1 + 110];
	temp3 = DEGLC(Da, Db, Dc, t1 - 1) + Dc[t1 + 110 + 1];

	temp1 = max(temp1, temp2);
	temp1 = max(temp1, temp3);
	/*if (temp1 >= DIM)
		return DIM;*/
	return temp1;
}

//
int DegMulB(int Da[], int Db[], int Dc[],int t)
{
	int t1, t2;
	int d1, d2, d3;
	int temp1, temp2, temp3;
	t1 = t - 92;
	if (t1 <= 0)
	{
		return Da[t1 + 92] + Da[t1 + 1 + 92];                                                                           
	}
	t2 = t1 - 110;
	temp1 = Dc[t2 + 110] + Da[t1 + 92 + 1];
	temp2 = Dc[t2 + 110 + 2] + Da[t1 + 92];
	temp3 = Dc[t2 + 110] + Dc[t2 + 110 + 1] + Dc[t2 + 110 + 2];
	temp1 = min(temp1, temp2);
	temp1 = min(temp1, temp3);

	temp2 = DEGLA(Da, Db, Dc, t1) + Da[t1 + 92];
	temp3 = DEGLA(Da, Db, Dc, t1 - 1) + Da[t1 + 92 + 1];


	temp1 = max(temp1, temp2);
	temp1 = max(temp1, temp3);
	/*if (temp1 >= DIM)
		return DIM;*/
	return temp1;
}
int DegMulC(int Da[], int Db[], int Dc[], int Dv[], int t)
{
	int t1, t2;
	int d1, d2, d3;
	int temp1, temp2, temp3;
	t1 = t - 83;
	if (t1 <= 0)
	{
		return Db[t1 + 83] + Db[t1 + 1 + 83];//                                                                                                                                                                
	}
	t2 = t1 - 92;
	temp1 = Da[t2 + 92] + Db[t1 + 83 + 1];
	temp2 = Da[t2 + 92 + 2] + Db[t1 + 83];
	temp3 = Da[t2 + 92] + Da[t2 + 92 + 1] + Da[t2 + 92 + 2];
	temp1 = min(temp1, temp2);
	temp1 = min(temp1, temp3);

	temp2 = DEGLB(Da, Db, Dc, Dv, t1) + Db[t1 + 83];
	temp3 = DEGLB(Da, Db, Dc, Dv, t1 - 1) + Db[t1 + 83 + 1];

	temp1 = max(temp1, temp2);
	temp1 = max(temp1, temp3);
	/*if (temp1 >= DIM)
		return DIM;*/
	return temp1;
}

void EstimateDegree(int X[], int dim, char filename[], int N, int loclist[], int loclen, int flag, int p,int res[])
{
	int Da[1300], Db[1300], Dc[1300],Dv[1300];//存储每个寄存器上上的内部状态的次数估计                                                
									 //int da[1300],db[1300],dc[1300];    
	int i, j, k;
	int t1, t2, t3, d1, d2, d3;
	int pdegsum = 0;
	//int RegA[2000], int RegB[2000], int RegC[2000], int RegS[2000];
	FILE *fp;
	//fp = fopen(filename, "w");
	fopen_s(&fp, filename, "w");
	//int D[13000];                                                                                                        
	//初始化     
	int N0 = 200;
	initialize(Da, Db, Dc, Dv,X, dim, filename,loclist,loclen,flag);
	for (i = 1; i <= N; i++)
	{
		//printf("%d\n",Db[0]);
		/*if(i == (N0+1))
		{
			for (j = 0; j < 93 + N0; j++)
				printf("%d,", Da[j]);
			printf("\n");
			for (j = 0; j < 84 + N0; j++)
				printf("%d,", Db[j]);
			printf("\n");
			for (j = 0; j < 111 + N0; j++)
				printf("%d,", Dc[j]);
			printf("\n");
		}*/
		d1 = DegMulA(Da, Db, Dc, i);//                                                                                            
		d2 = DegMulB(Da, Db, Dc, i);
		d3 = DegMulC(Da, Db, Dc, Dv,i);

		//printf("Round %d: %d %d %d\n", i,d1,d2,d3);
		

		t1 = DEGLA(Da, Db, Dc, i - 1);//cca                                                                                        
		t2 = DEGLB(Da, Db, Dc,Dv,i - 1);//aab                                                                                        
		t3 = DEGLC(Da, Db, Dc, i - 1);//bbc                                                                                        

		Da[i + 92] = max(t1, d1);
		Db[i + 83] = max(t2, d2);
		Dc[i + 110] = max(t3, d3);
		Dv[i + 127] = Dv[i-1];
		//printf("%d,%d,%d,%d,%d,%d\n",Da[i+92-65],Da[i+92-92],Db[i+83-68],Db[i+83-83],Dc[i+110-65],Dc[i+110-110]);          
		t1 = max(Da[i + 92 - 65], Da[i + 92 - 92]);
		t2 = max(Db[i + 83 - 68], Db[i + 83 - 83]);
		t3 = max(Dc[i + 110 - 65], Dc[i + 110 - 110]);
		t1 = max(t1, t2);
		t1 = max(t1, t3);
		if (t1 + loclen < dim)
		{
			res[0] = i;
			//res[1] = i;
		}
		if (i == p)
		{
			res[1] = t1 + loclen;
		}
		pdegsum = pdegsum + t1 + loclen;
	}
	
	//res[1] = pdegsum;

	fclose(fp);
}
