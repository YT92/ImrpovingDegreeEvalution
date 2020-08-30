#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"DeCom.h"


void getX(int cube[], int loclist[], int X[], int dim, int loclen)
{
	int i=0,m=0;
	int flag[80]={0};
	memset(X,0,sizeof(int)*80);
	for(i=0;i<loclen;i++)
	{
		flag[loclist[i]]=1;
	}
	for(i=0;i<dim;i++)
	{
		if(flag[cube[i]]==0)
		{
			X[m++]=cube[i];
		}
	}
}

void initial(int cube[], int dim, int X[], int Xlen, int Da[], int Db[], int Dc[], int N0)
{
	int i,j,k;
	for(i=N0-1;i>=0;i--)
	{
		Da[i+93]=Da[i];
		Db[i+84]=Db[i];
		Dc[i+111]=Dc[i];
	}
	for(i=13;i<93;i++)
	{
		Da[i]=0;
	}
	for(i=0;i<13;i++)
	{
		Da[i]=-10000;
	}
	for(i=0;i<84;i++)
	{
		Db[i]=-10000;
	}
	for(i=0;i<dim;i++)
	{
		Db[83-cube[i]]=0;
	}
	for(i=0;i<Xlen;i++)
	{
		Db[83-X[i]]=1;
	}
	for(i=3;i<111;i++)
	{
		Dc[i]=-10000;
	}
	for(i=0;i<3;i++)
	{
		Dc[i]=0;
	}
}
int DEGLA(int Da[], int Db[], int Dc[], int t, int dim)
{
	int t1, t2, t3;
	t1 = Dc[t + 110 - 65];//t时刻的C的内部状态是Dc[t]-Dc[t+100]; 而且顺序是反着的                                               
	t2 = Dc[t + 110 - 110];
	t3 = Da[t + 92 - 68];
	t1 = max(t1, t2);
	t1 = max(t1, t3);
	if (t1 >= dim)
		return dim;
	return t1;
}

int DEGLB(int Da[], int Db[], int Dc[], int t, int dim)
{
	int t1, t2, t3;
	t1 = Da[t + 92 - 65];//t时刻的C的内部状态是Dc[t]-Dc[t+100]; 而且顺序是反着的                                                
	t2 = Da[t + 92 - 92];
	t3 = Db[t + 83 - 77];
	t1 = max(t1, t2);
	t1 = max(t1, t3);
	if (t1 >= dim)
		return dim;
	return t1;
}

int DEGLC(int Da[], int Db[], int Dc[], int t, int dim)
{
	int t1, t2, t3;
	t1 = Db[t + 83 - 68];//t时刻的C的内部状态是Dc[t]-Dc[t+100]; 而且顺序是反着的                                                
	t2 = Db[t + 83 - 83];
	t3 = Dc[t + 110 - 86];
	t1 = max(t1, t2);
	t1 = max(t1, t3);
	if (t1 >= dim)
		return dim;
	return t1;
}
int DegMulA(int Da[], int Db[], int Dc[], int t, int dim)
{
	int t1, t2;
	int temp1, temp2, temp3;
	t1 = t - 110;
	//如果t1<=0,那么直接返回两者相加                                                                                       
	if (t1 <= 0)
	{
		return Dc[t1 + 110] + Dc[t1 + 1 + 110];
		//if((Dc[t1+110]>=0)&&(Dc[t1+1+110]))                                                                                
		//	return Dc[t1+110]+Dc[t1+1+110];//                                                                                
		//else                                                                                                               
		//	return (max(Dc[t1+110],Dc[t1+1+110]));                                                                           
	}
	//否则往回退一步                                                                                                       
	t2 = t1 - 83;

	//                                                                                                                     
	temp1 = Db[t2 + 83] + Dc[t1 + 110 + 1];
	temp2 = Db[t2 + 83 + 2] + Dc[t1 + 110];
	temp3 = Db[t2 + 83] + Db[t2 + 83 + 1] + Db[t2 + 83 + 2];
	temp1 = min(temp1, temp2);
	temp1 = min(temp1, temp3);

	temp2 = DEGLC(Da, Db, Dc, t1, dim) + Dc[t1 + 110];
	temp3 = DEGLC(Da, Db, Dc, t1 - 1, dim) + Dc[t1 + 110 + 1];

	temp1 = max(temp1, temp2);
	temp1 = max(temp1, temp3);
	if (temp1 >= dim)
		return dim;
	return temp1;
}
int DegMulB(int Da[], int Db[], int Dc[], int t, int dim)
{
	int t1, t2;
	int temp1, temp2, temp3;
	t1 = t - 92;
	if (t1 <= 0)
	{
		return Da[t1 + 92] + Da[t1 + 1 + 92];
		//if((Da[t1+92]>=0)&&(Da[t1+1+92]>=0))                                                                               
		//	return Da[t1+92]+Da[t1+1+92];//                                                                                  
		//else                                                                                                               
		//	return max(Da[t1+92],Da[t1+1+92]);                                                                               
	}
	t2 = t1 - 110;
	temp1 = Dc[t2 + 110] + Da[t1 + 92 + 1];
	temp2 = Dc[t2 + 110 + 2] + Da[t1 + 92];
	temp3 = Dc[t2 + 110] + Dc[t2 + 110 + 1] + Dc[t2 + 110 + 2];
	temp1 = min(temp1, temp2);
	temp1 = min(temp1, temp3);

	temp2 = DEGLA(Da, Db, Dc, t1, dim) + Da[t1 + 92];
	temp3 = DEGLA(Da, Db, Dc, t1 - 1, dim) + Da[t1 + 92 + 1];

	temp1 = max(temp1, temp2);
	temp1 = max(temp1, temp3);
	if (temp1 >= dim)
		return dim;
	return temp1;
}
int DegMulC(int Da[], int Db[], int Dc[], int t, int dim)
{
	int t1, t2;
	int temp1, temp2, temp3;
	t1 = t - 83;
	if (t1 <= 0)
	{
		return Db[t1 + 83] + Db[t1 + 1 + 83];//                                                                                      
											 //if((Db[t1+83]>=0)&&(Db[t1+1+83]))                                                                                  
											 //	return Db[t1+83]+Db[t1+1+83];//                                                                                  
											 //else                                                                                                               
											 //	return max(Db[t1+83],Db[t1+1+83]);                                                                               
	}
	t2 = t1 - 92;
	temp1 = Da[t2 + 92] + Db[t1 + 83 + 1];
	temp2 = Da[t2 + 92 + 2] + Db[t1 + 83];
	temp3 = Da[t2 + 92] + Da[t2 + 92 + 1] + Da[t2 + 92 + 2];
	temp1 = min(temp1, temp2);
	temp1 = min(temp1, temp3);

	temp2 = DEGLB(Da, Db, Dc, t1, dim) + Db[t1 + 83];
	temp3 = DEGLB(Da, Db, Dc, t1 - 1, dim) + Db[t1 + 83 + 1];

	temp1 = max(temp1, temp2);
	temp1 = max(temp1, temp3);
	if (temp1 >= dim)
		return dim;
	return temp1;
}

//int DegEst(int Da[], int Db[], int Dc[], int N,int dim)
int DegEst(int Da[], int Db[], int Dc[], int N, int N0, int dim)
{
	int i;
	int t1, t2, t3, d1, d2, d3;
	//FILE *fp;
	//fopen_s(&fp, "RecDeg.txt", "w");
	for (i = 1+N0; i <= N; i++)
	{
		d1 = DegMulA(Da, Db, Dc, i,dim);//                                                                                            
		d2 = DegMulB(Da, Db, Dc, i, dim);
		d3 = DegMulC(Da, Db, Dc, i, dim);

		t1 = DEGLA(Da, Db, Dc, i - 1, dim);//cca                                                                                        
		t2 = DEGLB(Da, Db, Dc, i - 1, dim);//aab                                                                                        
		t3 = DEGLC(Da, Db, Dc, i - 1, dim);//bbc                                                                                        
		Da[i + 92] = max(t1, d1);
		Db[i + 83] = max(t2, d2);
		Dc[i + 110] = max(t3, d3);
		//printf("%d,%d,%d,%d,%d,%d\n",Da[i+92-65],Da[i+92-92],Db[i+83-68],Db[i+83-83],Dc[i+110-65],Dc[i+110-110]);          
		t1 = max(Da[i + 92 - 65], Da[i + 92 - 92]);
		t2 = max(Db[i + 83 - 68], Db[i + 83 - 83]);
		t3 = max(Dc[i + 110 - 65], Dc[i + 110 - 110]);
		t1 = max(t1, t2);
		t1 = max(t1, t3);

		
	}
	/*N=N-1;
	printf("%d,%d,%d,%d,%d,%d\n",Da[N+92-65],Da[N+92-92],Db[N+83-68],Db[N+83-83],Dc[N+110-65],Dc[N+110-110]);*/
	//N=N+1;                                                                                                               
	//printf("%d,%d,%d,%d,%d,%d\n", Da[N + 92 - 65], Da[N + 92 - 92], Db[N + 83 - 68], Db[N + 83 - 83], Dc[N + 110 - 65], Dc[N + 110 - 110]);
	//printf("%d,%d,%d,%d,%d,%d\n", Da[N + 92 - 65], Da[N + 92 - 92], Db[N + 83 - 68], Db[N + 83 - 83], Dc[N + 110 - 65], Dc[N + 110 - 110]);
	t1 = max(Da[N + 92 - 65], Da[N + 92 - 92]);
	t2 = max(Db[N + 83 - 68], Db[N + 83 - 83]);
	t3 = max(Dc[N + 110 - 65], Dc[N + 110 - 110]);
	t1 = max(t1, t2);
	t1 = max(t1, t3);


	/*for (i = 0; i<N + 93; i++)
		printf( "%d,", Da[i]);
	printf("\n");
	for (i = 0; i<N + 84; i++)
		printf("%d,", Db[i]);
	printf("\n");
	for (i = 0; i<N + 111; i++)
		printf("%d,", Dc[i]);*/
	
	/*for (i = 0; i<N + 93; i++)
		fprintf(fp, "%d,", Da[i]);
	fprintf(fp, "\n");
	for (i = 0; i<N + 84; i++)
		fprintf(fp, "%d,", Db[i]);
	fprintf(fp, "\n");
	for (i = 0; i<N + 111; i++)
		fprintf(fp, "%d,", Dc[i]);*/
	//fclose(fp);
	return t1;
}


int DegEstRec(int cube[], int dim, char ***upA, char ***upB, char ***upC, int sizeA[], int sizeB[], int sizeC[], int vfA[], int vfB[], int vfC[], int round, int N0)
{
	int i,j,k;
	int Da[1000], Db[10000], Dc[10000];
	int mindeg,findeg;
	int findeglist[10000]={0};
	int recurflag=1;
	int m=0,mrec=0,tempdim;
	int loclist[100];
	int loclen;
	int testflag[80]={0};
	int X[1000]={0};
	//首先
	getinideg(upA,sizeA,vfA,Da,cube,dim,N0);
	getinideg(upB,sizeB,vfB,Db,cube,dim,N0);
	getinideg(upC,sizeC,vfC,Dc,cube,dim,N0);
	/*for(i=0;i<N0;i++)
	printf("%d(%d) %d(%d) %d(%d)\n",Da[i],vfA[i],Db[i],vfB[i],Dc[i],vfC[i]);
	system("pause");*/

	//
	

	initial(cube,dim,cube,dim,Da,Db,Dc,N0);
	findeg=DegEst(Da, Db, Dc,round,N0,dim);
	mindeg=findeg;

	//
	while(recurflag==1)
	{
		memset(findeglist,0,sizeof(int)*80);
		for (i = 0; i < dim; i++)
		{
			if (testflag[i] == 0)
			{
				//printf("%d: ", i);
				loclist[m] = i;
				loclen=m+1;
				getX(cube,loclist,X,dim,loclen);
				tempdim=dim-loclen;
				getinideg(upA,sizeA,vfA,Da,X,tempdim,N0);
				getinideg(upB,sizeB,vfB,Db,X,tempdim,N0);
				getinideg(upC,sizeC,vfC,Dc,X,tempdim,N0);
				initial(cube,dim,X,tempdim,Da,Db,Dc,N0);
				/*for(j=0;j<N0+93;j++)
				{
				printf("%d\n",Da[j]);
				}

				for(j=0;j<N0+84;j++)
				{
				printf("%d\n",Db[j]);
				}

				for(j=0;j<N0+111;j++)
				{
				printf("%d\n",Dc[j]);
				}*/
				findeglist[i]=DegEst(Da, Db, Dc,round,N0,dim)+loclen;
			}
		}

		for (i = 0; i < dim; i++)
		{
			if ((findeglist[i]<mindeg)&&(findeglist[i]!=0))
			{
				loclist[m] = i;
				testflag[i] = 1;
				m++;
				if(findeglist[i]<mindeg)
					mindeg=findeglist[i];
			}
		}
		loclen = m;
		if (m == 0)
		{
			recurflag = 0;
		}
		if (m == mrec)
		{
			recurflag = 0;
		}
		else
		{
			mrec = m;
		}
	}
	return mindeg;
}

//按顺序最小化基
int DegEstRecV2(int cube[], int dim, char ***upA, char ***upB, char ***upC, int sizeA[], int sizeB[], int sizeC[], int vfA[], int vfB[], int vfC[],int pos, int round, int N0)
{
	int i,j,k;
	int Da[1000], Db[10000], Dc[10000], Dav[10000], Dbv[10000], Dcv[10000];
	int mindeg,findeg;
	int findeglist[10000]={0};
	int recurflag=1;
	int m=0,mrec=0,tempdim;
	int loclist[100];
	int loclen;
	int testflag[80]={0};
	int X[1000]={0};

	//初始化Dav,Dbv,Dcv
	int maxdeglistA[10000],maxdeglistB[10000],maxdeglistC[10000];
	int submaxdeglistA[10000],submaxdeglistB[10000],submaxdeglistC[10000];
	int tmp=0,maxdeg=0,submaxdeg=0;
	int deg=0;
	for(i=0;i<N0;i++)
	{
		maxdeg=0;
		submaxdeg=0;
		for(j=0;j<sizeA[i];j++)
		{
			deg=0;
			for(k=0;k<80;k++)
			{
				deg+=upA[i][j][k];
			}
			if(deg>maxdeg)
			{
				submaxdeg=maxdeg;
				maxdeg=deg;
			}
			else
			{
				if(deg>submaxdeg)
				{
					submaxdeg=deg;
				}
			}
		}
		maxdeglistA[i]=maxdeg;
		submaxdeglistA[i]=submaxdeg;
	}

	for(i=0;i<N0;i++)
	{
		maxdeg=0;
		submaxdeg=0;
		for(j=0;j<sizeB[i];j++)
		{
			deg=0;
			for(k=0;k<80;k++)
			{
				deg+=upB[i][j][k];
			}
			if(deg>maxdeg)
			{
				submaxdeg=maxdeg;
				maxdeg=deg;
			}
			else
			{
				if(deg>submaxdeg)
				{
					submaxdeg=deg;
				}
			}
		}
		maxdeglistB[i]=maxdeg;
		submaxdeglistB[i]=submaxdeg;
	}

	for(i=0;i<N0;i++)
	{
		maxdeg=0;
		submaxdeg=0;
		for(j=0;j<sizeC[i];j++)
		{
			deg=0;
			for(k=0;k<80;k++)
			{
				deg+=upC[i][j][k];
			}
			if(deg>maxdeg)
			{
				submaxdeg=maxdeg;
				maxdeg=deg;
			}
			else
			{
				if(deg>submaxdeg)
				{
					submaxdeg=deg;
				}
			}
		}
		maxdeglistC[i]=maxdeg;
		submaxdeglistC[i]=submaxdeg;
	}
	//初始化Dav,Dbv,Dcv
	for(i=0;i<13;i++)
	{
		Dav[i]=-10000;
	}
	for(i=13;i<93;i++)
	{
		Dav[i]=0;
	}
	for(i=0;i<4;i++)
	{
		Dbv[i]=-10000;
	}
	for(i=4;i<84;i++)
	{
		Dbv[i]=-10000;
	}
	for(i=0;i<3;i++)
	{
		Dcv[i]=0;
	}
	for(i=3;i<111;i++)
	{
		Dcv[i]=-10000;
	}
	for(i=0;i<N0;i++)
	{
		Dav[i+93]=maxdeglistA[i];
		Dbv[i+84]=maxdeglistB[i];
		Dcv[i+111]=maxdeglistC[i];
	}
	//首先, 
	getinideg(upA,sizeA,vfA,Da,cube,dim,N0);
	getinideg(upB,sizeB,vfB,Db,cube,dim,N0);
	getinideg(upC,sizeC,vfC,Dc,cube,dim,N0);
	initial(cube,dim,cube,dim,Da,Db,Dc,N0);
	for(i=N0;i>pos;i--)
	{
		Da[93+i]=Dav[93+i];
		Db[84+i]=Dbv[84+i];
		Dc[111+i]=Dcv[111+i];
	}
	//for(i=0;i<)
	findeg=DegEst(Da, Db, Dc,round,N0,dim);
	mindeg=findeg;

	//
	while(recurflag==1)
	{
		memset(findeglist,0,sizeof(int)*80);
		for (i = 0; i < dim; i++)
		{
			if (testflag[i] == 0)
			{
				//printf("%d: ", i);
				loclist[m] = i;
				loclen=m+1;
				getX(cube,loclist,X,dim,loclen);
				tempdim=dim-loclen;
				getinidegV2(upA,sizeA,vfA,Da,Dav,X,tempdim,N0);
				getinidegV2(upB,sizeB,vfB,Db,Dbv,X,tempdim,N0);
				getinidegV2(upC,sizeC,vfC,Dc,Dcv,X,tempdim,N0);


				//初始化
				initial(cube,dim,X,tempdim,Da,Db,Dc,N0);
				initial(cube,dim,X,tempdim,Dav,Dbv,Dcv,N0);

				for(j=N0;j>pos;j--)
				{
					Da[93+j]=Dav[93+j];
					Db[84+j]=Dbv[84+j];
					Dc[111+j]=Dcv[111+j];
				}
				findeglist[i]=DegEst(Da, Db, Dc,round,N0,dim)+loclen;
			}
		}

		for (i = 0; i < dim; i++)
		{
			if ((findeglist[i]<mindeg)&&(findeglist[i]!=0))
			{
				loclist[m] = i;
				testflag[i] = 1;
				m++;
				if(findeglist[i]<mindeg)
					mindeg=findeglist[i];
			}
		}
		loclen = m;
		if (m == 0)
		{
			recurflag = 0;
		}
		if (m == mrec)
		{
			recurflag = 0;
		}
		else
		{
			mrec = m;
		}
	}
	return mindeg;
}


//改进的初始化基
int DegEstRecV3(int cube[], int dim, char ***upA, char ***upB, char ***upC, int sizeA[], int sizeB[], int sizeC[], int vfA[], int vfB[], int vfC[],int minvfA[], int minvfB[], int minvfC[], int round, int N0)
{
	int i,j,k;
	int Da[1000], Db[10000], Dc[10000], Dav[10000], Dbv[10000], Dcv[10000];
	int mindeg,findeg;
	int findeglist[10000]={0};
	int recurflag=1;
	int m=0,mrec=0,tempdim;
	int loclist[100];
	int loclen;
	int testflag[80]={0};
	int X[1000]={0};

	//初始化Dav,Dbv,Dcv
	int maxdeglistA[10000],maxdeglistB[10000],maxdeglistC[10000];
	int submaxdeglistA[10000],submaxdeglistB[10000],submaxdeglistC[10000];
	int tmp=0,maxdeg=0,submaxdeg=0;
	int deg=0;
	for(i=0;i<N0;i++)
	{
		maxdeg=0;
		submaxdeg=0;
		for(j=0;j<sizeA[i];j++)
		{
			deg=0;
			for(k=0;k<80;k++)
			{
				deg+=upA[i][j][k];
			}
			if(deg>maxdeg)
			{
				submaxdeg=maxdeg;
				maxdeg=deg;
			}
			else
			{
				if(deg>submaxdeg)
				{
					submaxdeg=deg;
				}
			}
		}
		maxdeglistA[i]=maxdeg;
		submaxdeglistA[i]=submaxdeg;
	}

	for(i=0;i<N0;i++)
	{
		maxdeg=0;
		submaxdeg=0;
		for(j=0;j<sizeB[i];j++)
		{
			deg=0;
			for(k=0;k<80;k++)
			{
				deg+=upB[i][j][k];
			}
			if(deg>maxdeg)
			{
				submaxdeg=maxdeg;
				maxdeg=deg;
			}
			else
			{
				if(deg>submaxdeg)
				{
					submaxdeg=deg;
				}
			}
		}
		maxdeglistB[i]=maxdeg;
		submaxdeglistB[i]=submaxdeg;
	}

	for(i=0;i<N0;i++)
	{
		maxdeg=0;
		submaxdeg=0;
		for(j=0;j<sizeC[i];j++)
		{
			deg=0;
			for(k=0;k<80;k++)
			{
				deg+=upC[i][j][k];
			}
			if(deg>maxdeg)
			{
				submaxdeg=maxdeg;
				maxdeg=deg;
			}
			else
			{
				if(deg>submaxdeg)
				{
					submaxdeg=deg;
				}
			}
		}
		maxdeglistC[i]=maxdeg;
		submaxdeglistC[i]=submaxdeg;
	}
	//初始化Dav,Dbv,Dcv
	for(i=0;i<13;i++)
	{
		Dav[i]=-10000;
	}
	for(i=13;i<93;i++)
	{
		Dav[i]=0;
	}
	for(i=0;i<4;i++)
	{
		Dbv[i]=-10000;
	}
	for(i=4;i<84;i++)
	{
		Dbv[i]=-10000;
	}
	for(i=0;i<3;i++)
	{
		Dcv[i]=0;
	}
	for(i=3;i<111;i++)
	{
		Dcv[i]=-10000;
	}
	for(i=0;i<N0;i++)
	{
		Dav[i+93]=maxdeglistA[i];
		Dbv[i+84]=maxdeglistB[i];
		Dcv[i+111]=maxdeglistC[i];
	}
	//首先, 
	getinideg(upA,sizeA,vfA,Da,cube,dim,N0);
	getinideg(upB,sizeB,vfB,Db,cube,dim,N0);
	getinideg(upC,sizeC,vfC,Dc,cube,dim,N0);
	initial(cube,dim,cube,dim,Da,Db,Dc,N0);
	for(i=N0;i>=0;i--)
	{
		if(vfA[i]==1 &&minvfA[i]==0)
		{
			Da[i+93]=Dav[i+93];
		}
		if(vfB[i]==1 &&minvfB[i]==0)
		{
			Db[i+84]=Dbv[i+84];
		}
		if(vfC[i]==1 &&minvfC[i]==0)
		{
			Dc[i+111]=Dcv[i+111];
		}
	}
	//for(i=0;i<)
	findeg=DegEst(Da, Db, Dc,round,N0,dim);
	mindeg=findeg;

	//
	while(recurflag==1)
	{
		memset(findeglist,0,sizeof(int)*80);
		for (i = 0; i < dim; i++)
		{
			if (testflag[i] == 0)
			{
				//printf("%d: ", i);
				loclist[m] = i;
				loclen=m+1;
				getX(cube,loclist,X,dim,loclen);
				tempdim=dim-loclen;
				getinidegV2(upA,sizeA,vfA,Da,Dav,X,tempdim,N0);
				getinidegV2(upB,sizeB,vfB,Db,Dbv,X,tempdim,N0);
				getinidegV2(upC,sizeC,vfC,Dc,Dcv,X,tempdim,N0);


				//初始化
				initial(cube,dim,X,tempdim,Da,Db,Dc,N0);
				initial(cube,dim,X,tempdim,Dav,Dbv,Dcv,N0);

				for(j=N0;j>=0;j--)
				{
					if(vfA[j]==1 &&minvfA[j]==0)
					{
						Da[j+93]=Dav[j+93];
					}
					if(vfB[j]==1 &&minvfB[j]==0)
					{
						Db[j+84]=Dbv[j+84];
					}
					if(vfC[j]==1 &&minvfC[j]==0)
					{
						Dc[j+111]=Dcv[j+111];
					}
				}
				findeglist[i]=DegEst(Da, Db, Dc,round,N0,dim)+loclen;
			}
		}

		for (i = 0; i < dim; i++)
		{
			if ((findeglist[i]<mindeg)&&(findeglist[i]!=0))
			{
				loclist[m] = i;
				testflag[i] = 1;
				m++;
				if(findeglist[i]<mindeg)
					mindeg=findeglist[i];
			}
		}
		loclen = m;
		if (m == 0)
		{
			recurflag = 0;
		}
		if (m == mrec)
		{
			recurflag = 0;
		}
		else
		{
			mrec = m;
		}
	}
	return mindeg;
}
int DegEstWithCon(int cube[], int dim, int round, int N0)
{
	int Da[10000], Db[10000], Dc[10000], Dav[10000], Dbv[10000], Dcv[10000];
	int Da_t[10000], Db_t[10000], Dc_t[10000];
	int i;
	int res;
	int findeg = 0;
	int R0=363;
	FILE *fp;
	fopen_s(&fp, "recdeg.txt", "w");
	//获取初始化值
	//Dc[] = Dcv[197];
	decomposition(cube, dim, Da, Db, Dc, Dav, Dbv, Dcv, N0);



	
	
	findeg=DegEst(Da, Db, Dc,round,N0,dim);

	for (i = 0; i < round + 93; i++)
	{
		Da_t[i] = Da[i];
	}
	for (i = 0; i < round + 84; i++)
	{
		Db_t[i] = Db[i];
	}
	for (i = 0; i < round + 111; i++)
	{
		Dc_t[i] = Dc[i];
	}

	printf("\n\n\n**********************************************************\n\n\n");
	//Dc[103 + 111] = Dcv[103 + 111];

	//findeg = DegEst(Da, Db, Dc, round, N0, dim);

	//printf("The difference in Register A\n");
	//for (i = R0; i < R0 + 93; i++)
	//{
	//	if (Da_t[i] < Da[i])
	//	{
	//		//printf("i=%d Da_t[i]=%d  Da[i]=%d\n", i-92, Da_t[i], Da[i]);
	//		printf("i=%d Da_t[i]=%d  Da[i]=%d\n", 92-(i - R0), Da_t[i], Da[i]);
	//	}
	//}

	//printf("The difference in Register B\n");
	//for (i = R0; i < R0 + 84; i++)
	//{
	//	if (Db_t[i] < Db[i])
	//	{
	//		//printf("i=%d Db_t[i]=%d  Db[i]=%d\n", i-84, Db_t[i], Db[i]);
	//		printf("i=%d Db_t[i]=%d  Db[i]=%d\n", 83-(i - R0)+93, Db_t[i], Db[i]);
	//	}
	//}

	//printf("The difference in Register C\n");
	//for (i = R0; i < R0 + 111; i++)
	//{
	//	if (Dc_t[i] < Dc[i])
	//	{
	//		//printf("i=%d Dc_t[i]=%d  Dc[i]=%d\n", i-110, Dc_t[i], Dc[i]);
	//		printf("i=%d Dc_t[i]=%d  Dc[i]=%d\n", 110-(i - R0) +177, Dc_t[i], Dc[i]);
	//	}
	//}


	//Dc[103 + 111] = Dcv[103 + 111];
	//如果最终的findeg<dim, 那么再尝试去掉一些基中的元素
	//printf("\n");
	if (findeg < dim)
	//if(0)
	{
		res = 1;
		for (i = N0; i > 0; i--)//直到出现findeg>dim的情况,
		{
			Da[93 + i] = Dav[93 + i];
			Db[84 + i] = Dbv[84 + i];
			Dc[111 + i] = Dcv[111 + i];
			findeg = DegEst(Da, Db, Dc, round , i, dim);
			if (findeg >=dim)
			{
				printf("\nneed %d rounds", i + 1);
				break;
			}		
		}
	}
	else
	{
		res = 0;
	}
	//printf("\n");
	for (i = 0; i < round + 93; i++)
	{
		fprintf(fp, "%d,", Da[i]);
		//printf("%d,", Da[i]);
	}
	fprintf(fp, "\n");
	//printf("\n");
	for (i = 0; i < round + 84; i++)
	{
		fprintf(fp, "%d,", Db[i]);
		//printf("%d,", Da[i]);
	}
	//printf("\n");
	fprintf(fp, "\n");
	for (i = 0; i < round + 111; i++)
	{
		//printf("%d,", Da[i]);
		fprintf(fp, "%d,", Dc[i]);
	}
	//printf("\n");
	fprintf(fp, "\n");
	//for()
	return res;
}


int DegEstWithConV(int cube[], int dim, int round, int N0)
{
	int Da[10000], Db[10000], Dc[10000], Dav[10000], Dbv[10000], Dcv[10000];
	int Da_t[10000], Db_t[10000], Dc_t[10000];
	int baisnum[1000]={0};
	int i,j,k;
	int res,tempdim;
	int testflag[80]={0};
	int recurflag=1;
	int findeg = 0;
	int R0=363;
	FILE *fp;
	char ***upA, ***upB,***upC;
	int X[80]={0},sizeA[1000]={0},sizeB[1000]={0},sizeC[1000]={0};
	int vfA[1000]={0},vfB[1000]={0},vfC[1000]={0};
	int findeglist[80]={0};
	int mindeg=1000000;
	int m=0, mrec=0;
	upA=(char ***)malloc(sizeof(char **)*N0);
	upB=(char ***)malloc(sizeof(char **)*N0);
	upC=(char ***)malloc(sizeof(char **)*N0);
	for (i = 0; i < N0; i++)
	{
		upA[i] = (char **)malloc(sizeof(char*) * 10000);
		upB[i] = (char **)malloc(sizeof(char*) * 10000);
		upC[i] = (char **)malloc(sizeof(char*) * 10000);
		for (j = 0; j < 10000;j++)
		{
			upA[i][j] = (char *)malloc(sizeof(char) * 160);
			upB[i][j] = (char *)malloc(sizeof(char) * 160);
			upC[i][j] = (char *)malloc(sizeof(char) * 160);
			memset(upA[i][j], 0, sizeof(char) * 160);
			memset(upB[i][j], 0, sizeof(char) * 160);
			memset(upC[i][j], 0, sizeof(char) * 160);
		}
	}
	
	memset(baisnum,0,sizeof(int)*10000);
	decompositionV(cube, dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,baisnum,N0);
	
	
	//需要根据不同的设置初始化，然后估计次数。
	

	findeg=DegEstRec(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,round,N0);

	fopen_s(&fp, "recdeg.txt", "w");
	//获取初始化值
	//Dc[] = Dcv[197];
	//decompositionV(cube, dim, Da, Db, Dc, Dav, Dbv, Dcv, N0);

	//findeg=DegEst(Da, Db, Dc,round,N0,dim);

	for (i = 0; i < round + 93; i++)
	{
		Da_t[i] = Da[i];
	}
	for (i = 0; i < round + 84; i++)
	{
		Db_t[i] = Db[i];
	}
	for (i = 0; i < round + 111; i++)
	{
		Dc_t[i] = Dc[i];
	}
	if (findeg < dim)
	{
		res = 1;
		for (i = N0; i > 0; i--)//直到出现findeg>dim的情况,
		{
			Da[93 + i] = Dav[93 + i];
			Db[84 + i] = Dbv[84 + i];
			Dc[111 + i] = Dcv[111 + i];
			findeg = DegEstRecV2(cube,dim,upA, upB, upC,sizeA,sizeB,sizeC,vfA,vfB, vfC,i,round,N0);//需要改进的
			//printf("%d %d\n", i, findeg);
			if (findeg >=dim)
			{
				printf("\nneed %d rounds\n", i + 1);
				printf("\n%d basis are needed\n", baisnum[i+1]);
				FILE *fpout;
				fopen_s(&fpout,"Res.txt","a+");
				fprintf(fpout, "\nneed %d rounds\n", i + 1);
				fprintf(fpout,"\n%d basis are needed\n", baisnum[i+1]);
				fclose(fpout);
				break;
			}		
		}
	}
	else
	{
		res = 0;
	}
	//printf("\n");
	for (i = 0; i < round + 93; i++)
	{
		fprintf(fp, "%d,", Da[i]);
		//printf("%d,", Da[i]);
	}
	fprintf(fp, "\n");
	//printf("\n");
	for (i = 0; i < round + 84; i++)
	{
		fprintf(fp, "%d,", Db[i]);
		//printf("%d,", Da[i]);
	}
	//printf("\n");
	fprintf(fp, "\n");
	for (i = 0; i < round + 111; i++)
	{
		//printf("%d,", Da[i]);
		fprintf(fp, "%d,", Dc[i]);
	}
	//printf("\n");
	fprintf(fp, "\n");
	//for()
	for (j = 0; j < N0; j++)
	{
		for (i = 0; i < 10000; i++)
		{
			free(upA[j][i]);
			free(upB[j][i]);
			free(upC[j][i]);
		}
		free(upA[j]);
		free(upB[j]);
		free(upC[j]);
	}
	free(upA);
	free(upB);
	free(upC);
	fclose(fp);
	return res;
}

//改进求最小基的方法
int DegEstWithConV2(int cube[], int dim, int round, int N0)
{
	int Da[10000], Db[10000], Dc[10000], Dav[10000], Dbv[10000], Dcv[10000];
	int Da_t[10000], Db_t[10000], Dc_t[10000];
	int baisnum[1000]={0};
	int i,j,k;
	int res,tempdim;
	int testflag[80]={0};
	int recurflag=1;
	int findeg = 0;
	int R0=363;
	FILE *fp;
	char ***upA, ***upB,***upC;
	int X[80]={0},sizeA[1000]={0},sizeB[1000]={0},sizeC[1000]={0};
	int vfA[1000]={0},vfB[1000]={0},vfC[1000]={0};
	int findeglist[80]={0};
	int mindeg=1000000;
	int m=0, mrec=0;
	int bsnum=0;
	int minvfA[1000]={0},minvfB[1000]={0},minvfC[1000]={0};
	upA=(char ***)malloc(sizeof(char **)*N0);
	upB=(char ***)malloc(sizeof(char **)*N0);
	upC=(char ***)malloc(sizeof(char **)*N0);
	for (i = 0; i < N0; i++)
	{
		upA[i] = (char **)malloc(sizeof(char*) * 10000);
		upB[i] = (char **)malloc(sizeof(char*) * 10000);
		upC[i] = (char **)malloc(sizeof(char*) * 10000);
		for (j = 0; j < 10000;j++)
		{
			upA[i][j] = (char *)malloc(sizeof(char) * 160);
			upB[i][j] = (char *)malloc(sizeof(char) * 160);
			upC[i][j] = (char *)malloc(sizeof(char) * 160);
			memset(upA[i][j], 0, sizeof(char) * 160);
			memset(upB[i][j], 0, sizeof(char) * 160);
			memset(upC[i][j], 0, sizeof(char) * 160);
		}
	}

	memset(baisnum,0,sizeof(int)*10000);
	decompositionV(cube, dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,baisnum,N0);


	//需要根据不同的设置初始化，然后估计次数。


	findeg=DegEstRec(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,round,N0);

	fopen_s(&fp, "recdeg.txt", "w");
	//获取初始化值
	//Dc[] = Dcv[197];
	//decompositionV(cube, dim, Da, Db, Dc, Dav, Dbv, Dcv, N0);

	//findeg=DegEst(Da, Db, Dc,round,N0,dim);

	for (i = 0; i < round + 93; i++)
	{
		Da_t[i] = Da[i];
	}
	for (i = 0; i < round + 84; i++)
	{
		Db_t[i] = Db[i];
	}
	for (i = 0; i < round + 111; i++)
	{
		Dc_t[i] = Dc[i];
	}


	//Dc[103 + 111] = Dcv[103 + 111];

	//findeg = DegEst(Da, Db, Dc, round, N0, dim);

	//printf("The difference in Register A\n");
	//for (i = R0; i < R0 + 93; i++)
	//{
	//	if (Da_t[i] < Da[i])
	//	{
	//		//printf("i=%d Da_t[i]=%d  Da[i]=%d\n", i-92, Da_t[i], Da[i]);
	//		printf("i=%d Da_t[i]=%d  Da[i]=%d\n", 92-(i - R0), Da_t[i], Da[i]);
	//	}
	//}

	//printf("The difference in Register B\n");
	//for (i = R0; i < R0 + 84; i++)
	//{
	//	if (Db_t[i] < Db[i])
	//	{
	//		//printf("i=%d Db_t[i]=%d  Db[i]=%d\n", i-84, Db_t[i], Db[i]);
	//		printf("i=%d Db_t[i]=%d  Db[i]=%d\n", 83-(i - R0)+93, Db_t[i], Db[i]);
	//	}
	//}

	//printf("The difference in Register C\n");
	//for (i = R0; i < R0 + 111; i++)
	//{
	//	if (Dc_t[i] < Dc[i])
	//	{
	//		//printf("i=%d Dc_t[i]=%d  Dc[i]=%d\n", i-110, Dc_t[i], Dc[i]);
	//		printf("i=%d Dc_t[i]=%d  Dc[i]=%d\n", 110-(i - R0) +177, Dc_t[i], Dc[i]);
	//	}
	//}


	//Dc[103 + 111] = Dcv[103 + 111];
	//如果最终的findeg<dim, 那么再尝试去掉一些基中的元素
	//printf("\n");
	if (findeg < dim)
	{
		res = 1;
		//然后挨个试？
		for(i=0;i<N0;i++)
		{
			minvfA[i]=vfA[i];
			minvfB[i]=vfB[i];
			minvfC[i]=vfC[i];
		}
		for(i=N0;i>=0;i--)
		{
			if(vfA[i]==1)
			{
				//调一次, 更新
				minvfA[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfA[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			if(vfB[i]==1)
			{
				minvfB[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfB[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			if(vfC[i]==1)
			{
				minvfC[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfC[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			//printf("\n");
		}
		bsnum=0;
		for(i=0;i<N0;i++)
		{
			if((minvfA[i]==1)||(minvfB[i]==1)||(minvfC[i]==1))
			{
				bsnum++;
			}
		}
		FILE *fpout;
		fopen_s(&fpout,"Res.txt","a+");
		fprintf(fpout,"\n%d basis are needed: ", bsnum);
		for(i=0;i<N0;i++)
		{
			if((minvfA[i]==1)||(minvfB[i]==1)||(minvfC[i]==1))
			{
				fprintf(fpout,"%d ", i);
			}
		}
		fprintf(fpout,"\n");

		//第二种顺序
		int bsnum=0;
		for(i=0;i<N0;i++)
		{
			minvfA[i]=vfA[i];
			minvfB[i]=vfB[i];
			minvfC[i]=vfC[i];
		}
		for(i=0;i<=N0;i++)
		{
			if(vfA[i]==1)
			{
				//调一次, 更新
				minvfA[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfA[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			if(vfB[i]==1)
			{
				minvfB[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfB[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			if(vfC[i]==1)
			{
				minvfC[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfC[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			//printf("\n");
		}
		for(i=0;i<N0;i++)
		{
			if((minvfA[i]==1)||(minvfB[i]==1)||(minvfC[i]==1))
			{
				bsnum++;
			}
		}
		//printf("bsnum=%d tmp=%d\n",bsnum,tmp);
		fprintf(fpout,"\n%d basis are needed: ", bsnum);
		
		for(i=0;i<N0;i++)
		{
			if((minvfA[i]==1)||(minvfB[i]==1)||(minvfC[i]==1))
			{
				fprintf(fpout,"%d ", i);
			}
		}
		fprintf(fpout,"\n");
		fclose(fpout);
	}
	else
	{
		res = 0;
	}
	//printf("\n");
	for (i = 0; i < round + 93; i++)
	{
		fprintf(fp, "%d,", Da[i]);
		//printf("%d,", Da[i]);
	}
	fprintf(fp, "\n");
	//printf("\n");
	for (i = 0; i < round + 84; i++)
	{
		fprintf(fp, "%d,", Db[i]);
		//printf("%d,", Da[i]);
	}
	//printf("\n");
	fprintf(fp, "\n");
	for (i = 0; i < round + 111; i++)
	{
		//printf("%d,", Da[i]);
		fprintf(fp, "%d,", Dc[i]);
	}
	//printf("\n");
	fprintf(fp, "\n");
	//for()
	for (j = 0; j < N0; j++)
	{
		for (i = 0; i < 10000; i++)
		{
			free(upA[j][i]);
			free(upB[j][i]);
			free(upC[j][i]);
		}
		free(upA[j]);
		free(upB[j]);
		free(upC[j]);
	}
	free(upA);
	free(upB);
	free(upC);
	fclose(fp);
	return res;
}

//验证是否单机
int DegEstVerify(int cube[], int dim, int round, int N0, int pos, int posr)
{
	int Da[10000], Db[10000], Dc[10000], Dav[10000], Dbv[10000], Dcv[10000];
	int Da_t[10000], Db_t[10000], Dc_t[10000];
	int baisnum[1000]={0};
	int i,j,k;
	int res,tempdim;
	int testflag[80]={0};
	int recurflag=1;
	int findeg = 0;
	int R0=363;
	FILE *fp;
	char ***upA, ***upB,***upC;
	int X[80]={0},sizeA[1000]={0},sizeB[1000]={0},sizeC[1000]={0};
	int vfA[1000]={0},vfB[1000]={0},vfC[1000]={0};
	int findeglist[80]={0};
	int mindeg=1000000;
	int m=0, mrec=0;
	int bsnum=0;
	int minvfA[1000]={0},minvfB[1000]={0},minvfC[1000]={0};
	upA=(char ***)malloc(sizeof(char **)*N0);
	upB=(char ***)malloc(sizeof(char **)*N0);
	upC=(char ***)malloc(sizeof(char **)*N0);
	for (i = 0; i < N0; i++)
	{
		upA[i] = (char **)malloc(sizeof(char*) * 10000);
		upB[i] = (char **)malloc(sizeof(char*) * 10000);
		upC[i] = (char **)malloc(sizeof(char*) * 10000);
		for (j = 0; j < 10000;j++)
		{
			upA[i][j] = (char *)malloc(sizeof(char) * 160);
			upB[i][j] = (char *)malloc(sizeof(char) * 160);
			upC[i][j] = (char *)malloc(sizeof(char) * 160);
			memset(upA[i][j], 0, sizeof(char) * 160);
			memset(upB[i][j], 0, sizeof(char) * 160);
			memset(upC[i][j], 0, sizeof(char) * 160);
		}
	}

	memset(baisnum,0,sizeof(int)*10000);
	decompositionVerify(cube, dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,pos,posr,baisnum,N0);


	//需要根据不同的设置初始化，然后估计次数。


	findeg=DegEstRec(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,round,N0);

	fopen_s(&fp, "recdeg.txt", "w");
	//获取初始化值
	//Dc[] = Dcv[197];
	//decompositionV(cube, dim, Da, Db, Dc, Dav, Dbv, Dcv, N0);

	//findeg=DegEst(Da, Db, Dc,round,N0,dim);

	for (i = 0; i < round + 93; i++)
	{
		Da_t[i] = Da[i];
	}
	for (i = 0; i < round + 84; i++)
	{
		Db_t[i] = Db[i];
	}
	for (i = 0; i < round + 111; i++)
	{
		Dc_t[i] = Dc[i];
	}


	//Dc[103 + 111] = Dcv[103 + 111];

	//findeg = DegEst(Da, Db, Dc, round, N0, dim);

	//printf("The difference in Register A\n");
	//for (i = R0; i < R0 + 93; i++)
	//{
	//	if (Da_t[i] < Da[i])
	//	{
	//		//printf("i=%d Da_t[i]=%d  Da[i]=%d\n", i-92, Da_t[i], Da[i]);
	//		printf("i=%d Da_t[i]=%d  Da[i]=%d\n", 92-(i - R0), Da_t[i], Da[i]);
	//	}
	//}

	//printf("The difference in Register B\n");
	//for (i = R0; i < R0 + 84; i++)
	//{
	//	if (Db_t[i] < Db[i])
	//	{
	//		//printf("i=%d Db_t[i]=%d  Db[i]=%d\n", i-84, Db_t[i], Db[i]);
	//		printf("i=%d Db_t[i]=%d  Db[i]=%d\n", 83-(i - R0)+93, Db_t[i], Db[i]);
	//	}
	//}

	//printf("The difference in Register C\n");
	//for (i = R0; i < R0 + 111; i++)
	//{
	//	if (Dc_t[i] < Dc[i])
	//	{
	//		//printf("i=%d Dc_t[i]=%d  Dc[i]=%d\n", i-110, Dc_t[i], Dc[i]);
	//		printf("i=%d Dc_t[i]=%d  Dc[i]=%d\n", 110-(i - R0) +177, Dc_t[i], Dc[i]);
	//	}
	//}


	//Dc[103 + 111] = Dcv[103 + 111];
	//如果最终的findeg<dim, 那么再尝试去掉一些基中的元素
	//printf("\n");
	if (findeg < dim)
	{
		res = 1;
		//然后挨个试？
		for(i=0;i<N0;i++)
		{
			minvfA[i]=vfA[i];
			minvfB[i]=vfB[i];
			minvfC[i]=vfC[i];
		}
		for(i=N0;i>=0;i--)
		{
			if(vfA[i]==1)
			{
				//调一次, 更新
				minvfA[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfA[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			if(vfB[i]==1)
			{
				minvfB[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfB[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			if(vfC[i]==1)
			{
				minvfC[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfC[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			//printf("\n");
		}
		bsnum=0;
		for(i=0;i<N0;i++)
		{
			if((minvfA[i]==1)||(minvfB[i]==1)||(minvfC[i]==1))
			{
				bsnum++;
			}
		}
		FILE *fpout;
		fopen_s(&fpout,"Res.txt","a+");
		fprintf(fpout,"\n%d basis are needed: ", bsnum);
		for(i=0;i<N0;i++)
		{
			if((minvfA[i]==1)||(minvfB[i]==1)||(minvfC[i]==1))
			{
				fprintf(fpout,"%d ", i);
			}
		}
		fprintf(fpout,"\n");

		//第二种顺序
		int bsnum=0;
		for(i=0;i<N0;i++)
		{
			minvfA[i]=vfA[i];
			minvfB[i]=vfB[i];
			minvfC[i]=vfC[i];
		}
		for(i=0;i<=N0;i++)
		{
			if(vfA[i]==1)
			{
				//调一次, 更新
				minvfA[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfA[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			if(vfB[i]==1)
			{
				minvfB[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfB[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			if(vfC[i]==1)
			{
				minvfC[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfC[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			//printf("\n");
		}
		for(i=0;i<N0;i++)
		{
			if((minvfA[i]==1)||(minvfB[i]==1)||(minvfC[i]==1))
			{
				bsnum++;
			}
		}
		//printf("bsnum=%d tmp=%d\n",bsnum,tmp);
		fprintf(fpout,"\n%d basis are needed: ", bsnum);

		for(i=0;i<N0;i++)
		{
			if((minvfA[i]==1)||(minvfB[i]==1)||(minvfC[i]==1))
			{
				fprintf(fpout,"%d ", i);
			}
		}
		fprintf(fpout,"\n");
		fclose(fpout);
	}
	else
	{
		res = 0;
	}
	//printf("\n");
	for (i = 0; i < round + 93; i++)
	{
		fprintf(fp, "%d,", Da[i]);
		//printf("%d,", Da[i]);
	}
	fprintf(fp, "\n");
	//printf("\n");
	for (i = 0; i < round + 84; i++)
	{
		fprintf(fp, "%d,", Db[i]);
		//printf("%d,", Da[i]);
	}
	//printf("\n");
	fprintf(fp, "\n");
	for (i = 0; i < round + 111; i++)
	{
		//printf("%d,", Da[i]);
		fprintf(fp, "%d,", Dc[i]);
	}
	//printf("\n");
	fprintf(fp, "\n");
	//for()
	for (j = 0; j < N0; j++)
	{
		for (i = 0; i < 10000; i++)
		{
			free(upA[j][i]);
			free(upB[j][i]);
			free(upC[j][i]);
		}
		free(upA[j]);
		free(upB[j]);
		free(upC[j]);
	}
	free(upA);
	free(upB);
	free(upC);
	fclose(fp);
	return res;
}

//多基验证
int DegEstVerifyV2(int cube[], int dim, int round, int N0, int pos[], int posr[], int posnum)
{
	int Da[10000], Db[10000], Dc[10000], Dav[10000], Dbv[10000], Dcv[10000];
	int Da_t[10000], Db_t[10000], Dc_t[10000];
	int baisnum[1000]={0};
	int i,j,k;
	int res,tempdim;
	int testflag[80]={0};
	int recurflag=1;
	int findeg = 0;
	int R0=363;
	FILE *fp;
	char ***upA, ***upB,***upC;
	int X[80]={0},sizeA[1000]={0},sizeB[1000]={0},sizeC[1000]={0};
	int vfA[1000]={0},vfB[1000]={0},vfC[1000]={0};
	int findeglist[80]={0};
	int mindeg=1000000;
	int m=0, mrec=0;
	int bsnum=0;
	int minvfA[1000]={0},minvfB[1000]={0},minvfC[1000]={0};
	upA=(char ***)malloc(sizeof(char **)*N0);
	upB=(char ***)malloc(sizeof(char **)*N0);
	upC=(char ***)malloc(sizeof(char **)*N0);
	for (i = 0; i < N0; i++)
	{
		upA[i] = (char **)malloc(sizeof(char*) * 10000);
		upB[i] = (char **)malloc(sizeof(char*) * 10000);
		upC[i] = (char **)malloc(sizeof(char*) * 10000);
		for (j = 0; j < 10000;j++)
		{
			upA[i][j] = (char *)malloc(sizeof(char) * 160);
			upB[i][j] = (char *)malloc(sizeof(char) * 160);
			upC[i][j] = (char *)malloc(sizeof(char) * 160);
			memset(upA[i][j], 0, sizeof(char) * 160);
			memset(upB[i][j], 0, sizeof(char) * 160);
			memset(upC[i][j], 0, sizeof(char) * 160);
		}
	}

	memset(baisnum,0,sizeof(int)*10000);
	decompositionVerifyV2(cube, dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,pos,posr,posnum,baisnum,N0);


	//需要根据不同的设置初始化，然后估计次数。


	findeg=DegEstRec(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,round,N0);

	fopen_s(&fp, "recdeg.txt", "w");
	//获取初始化值
	//Dc[] = Dcv[197];
	//decompositionV(cube, dim, Da, Db, Dc, Dav, Dbv, Dcv, N0);

	//findeg=DegEst(Da, Db, Dc,round,N0,dim);

	for (i = 0; i < round + 93; i++)
	{
		Da_t[i] = Da[i];
	}
	for (i = 0; i < round + 84; i++)
	{
		Db_t[i] = Db[i];
	}
	for (i = 0; i < round + 111; i++)
	{
		Dc_t[i] = Dc[i];
	}


	//Dc[103 + 111] = Dcv[103 + 111];

	//findeg = DegEst(Da, Db, Dc, round, N0, dim);

	//printf("The difference in Register A\n");
	//for (i = R0; i < R0 + 93; i++)
	//{
	//	if (Da_t[i] < Da[i])
	//	{
	//		//printf("i=%d Da_t[i]=%d  Da[i]=%d\n", i-92, Da_t[i], Da[i]);
	//		printf("i=%d Da_t[i]=%d  Da[i]=%d\n", 92-(i - R0), Da_t[i], Da[i]);
	//	}
	//}

	//printf("The difference in Register B\n");
	//for (i = R0; i < R0 + 84; i++)
	//{
	//	if (Db_t[i] < Db[i])
	//	{
	//		//printf("i=%d Db_t[i]=%d  Db[i]=%d\n", i-84, Db_t[i], Db[i]);
	//		printf("i=%d Db_t[i]=%d  Db[i]=%d\n", 83-(i - R0)+93, Db_t[i], Db[i]);
	//	}
	//}

	//printf("The difference in Register C\n");
	//for (i = R0; i < R0 + 111; i++)
	//{
	//	if (Dc_t[i] < Dc[i])
	//	{
	//		//printf("i=%d Dc_t[i]=%d  Dc[i]=%d\n", i-110, Dc_t[i], Dc[i]);
	//		printf("i=%d Dc_t[i]=%d  Dc[i]=%d\n", 110-(i - R0) +177, Dc_t[i], Dc[i]);
	//	}
	//}


	//Dc[103 + 111] = Dcv[103 + 111];
	//如果最终的findeg<dim, 那么再尝试去掉一些基中的元素
	//printf("\n");
	if (findeg < dim)
	{
		res = 1;
		//然后挨个试？
		for(i=0;i<N0;i++)
		{
			minvfA[i]=vfA[i];
			minvfB[i]=vfB[i];
			minvfC[i]=vfC[i];
		}
		for(i=N0;i>=0;i--)
		{
			if(vfA[i]==1)
			{
				//调一次, 更新
				minvfA[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfA[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			if(vfB[i]==1)
			{
				minvfB[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfB[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			if(vfC[i]==1)
			{
				minvfC[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfC[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			//printf("\n");
		}
		bsnum=0;
		for(i=0;i<N0;i++)
		{
			if((minvfA[i]==1)||(minvfB[i]==1)||(minvfC[i]==1))
			{
				bsnum++;
			}
		}
		FILE *fpout;
		fopen_s(&fpout,"Res.txt","a+");
		fprintf(fpout,"\n%d basis are needed: ", bsnum);
		for(i=0;i<N0;i++)
		{
			if((minvfA[i]==1)||(minvfB[i]==1)||(minvfC[i]==1))
			{
				fprintf(fpout,"%d ", i);
			}
		}
		fprintf(fpout,"\n");

		//第二种顺序
		int bsnum=0;
		for(i=0;i<N0;i++)
		{
			minvfA[i]=vfA[i];
			minvfB[i]=vfB[i];
			minvfC[i]=vfC[i];
		}
		for(i=0;i<=N0;i++)
		{
			if(vfA[i]==1)
			{
				//调一次, 更新
				minvfA[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfA[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			if(vfB[i]==1)
			{
				minvfB[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfB[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			if(vfC[i]==1)
			{
				minvfC[i]=0;
				findeg=DegEstRecV3(cube,dim,upA,upB,upC,sizeA,sizeB,sizeC,vfA,vfB,vfC,minvfA,minvfB,minvfC,round,N0);
				if(findeg>=dim)
				{
					minvfC[i]=1;
				}
				//printf("%d %d \n", i, findeg);
			}
			//printf("\n");
		}
		for(i=0;i<N0;i++)
		{
			if((minvfA[i]==1)||(minvfB[i]==1)||(minvfC[i]==1))
			{
				bsnum++;
			}
		}
		//printf("bsnum=%d tmp=%d\n",bsnum,tmp);
		fprintf(fpout,"\n%d basis are needed: ", bsnum);

		for(i=0;i<N0;i++)
		{
			if((minvfA[i]==1)||(minvfB[i]==1)||(minvfC[i]==1))
			{
				fprintf(fpout,"%d ", i);
			}
		}
		fprintf(fpout,"\n");
		fclose(fpout);
	}
	else
	{
		res = 0;
	}
	//printf("\n");
	for (i = 0; i < round + 93; i++)
	{
		fprintf(fp, "%d,", Da[i]);
		//printf("%d,", Da[i]);
	}
	fprintf(fp, "\n");
	//printf("\n");
	for (i = 0; i < round + 84; i++)
	{
		fprintf(fp, "%d,", Db[i]);
		//printf("%d,", Da[i]);
	}
	//printf("\n");
	fprintf(fp, "\n");
	for (i = 0; i < round + 111; i++)
	{
		//printf("%d,", Da[i]);
		fprintf(fp, "%d,", Dc[i]);
	}
	//printf("\n");
	fprintf(fp, "\n");
	//for()
	for (j = 0; j < N0; j++)
	{
		for (i = 0; i < 10000; i++)
		{
			free(upA[j][i]);
			free(upB[j][i]);
			free(upC[j][i]);
		}
		free(upA[j]);
		free(upB[j]);
		free(upC[j]);
	}
	free(upA);
	free(upB);
	free(upC);
	fclose(fp);
	return res;
}
void GetandTestX()
{
	FILE *fp,*fpout,*fpcube;
	fopen_s(&fp, "cubedim37.txt", "r");
	fopen_s(&fpout, "Res.txt", "a+");
	fopen_s(&fpcube,"SuceedCubes","a+");
	//
	int i,j,m=0,l=0;
	int cubenum = 6124;
	char c;
	char buff[1000] = { 0 };
	c = fgetc(fp);
	int X[80] = { 0 };
	int dim = 37;
	int N;
	N = 900;
	int roundnum=840;
	int N0=200;
	int flag=0;
	int maxround = 0;
	char filename[20] = "RecDeg.txt";
	while (c != EOF)
	{
		//
		memset(buff, 0, sizeof(char) * 1000);
		j = 0;
		while (c != '\n')
		{
			buff[j++] = c;
			c = fgetc(fp);
		}
		c = fgetc(fp);
		m = 0;
		i = 0;
		printf("\n**********************************************************\n");
		printf("%d: ", l);
		while(i<j)
			//for (i = 0; i < j; i++)
		{
			if ((buff[i]>='0') && (buff[i]<='9'))
			{
				if (buff[i + 1] == ',')
				{
					X[m++] = buff[i] - '0';
					i = i + 2;
				}
				else
				{
					if (buff[i + 2] = ',')
					{
						X[m++] = (buff[i] - '0')*10+buff[i+1]-'0';
						i = i + 3;
					}
					else
					{
						i++;
					}
				}
			}
		}
		for(i=0;i<dim;i++)
		{
			fprintf(fpout,"%d,", X[i]);
		}
		fprintf(fpout,"\n");
		flag=0;
		fclose(fpout);
		
		flag=DegEstWithConV2(X, dim, roundnum,N0);
		fopen_s(&fpout, "Res.txt", "a+");
		if (flag == 0)
		{
			printf("Usatisified!!! Plaese try another cube\n\n");
			fprintf(fpout,"Usatisified!!! Plaese try another cube\n\n");
		}
		else
		{
			//输出它的基
			printf( "Succeed!!!\n\n");
			fprintf(fpout, "Succeed!!!\n\n");
			for(i=0;i<dim;i++)
			{
				fprintf(fpcube,"%d,", X[i]);
			}
			fprintf(fpcube,"\n");
		}
		//
		l++;
		printf("\n**********************************************************\n");
	}

	fclose(fpout);
	fclose(fp);
	fclose(fpcube);
}

//验证单机
void GetandTestXVerify()
{
	FILE *fp,*fpout,*fpcube;
	fopen_s(&fp, "dim37ver.txt", "r");
	fopen_s(&fpout, "Res.txt", "a+");
	fopen_s(&fpcube,"SuceedCubes","a+");
	//
	int i,j,m=0,l=0;
	int cubenum = 6124;
	char c;
	char buff[1000] = { 0 };
	c = fgetc(fp);
	int X[80] = { 0 };
	int pos[1000]={2,2,2,2,2,2};
	int posr[1000]={139,139,139,98,91,138};
	int dim = 37;
	int N;
	N = 900;
	int roundnum=835;
	int N0=200;
	int flag=0;
	int maxround = 0;
	char filename[20] = "RecDeg.txt";
	while (c != EOF)
	{
		//
		memset(buff, 0, sizeof(char) * 1000);
		j = 0;
		while (c != '\n')
		{
			buff[j++] = c;
			c = fgetc(fp);
		}
		c = fgetc(fp);
		m = 0;
		i = 0;
		printf("\n**********************************************************\n");
		printf("%d: ", l);
		while(i<j)
			//for (i = 0; i < j; i++)
		{
			if ((buff[i]>='0') && (buff[i]<='9'))
			{
				if (buff[i + 1] == ',')
				{
					X[m++] = buff[i] - '0';
					i = i + 2;
				}
				else
				{
					if (buff[i + 2] = ',')
					{
						X[m++] = (buff[i] - '0')*10+buff[i+1]-'0';
						i = i + 3;
					}
					else
					{
						i++;
					}
				}
			}
		}
		for(i=0;i<dim;i++)
		{
			fprintf(fpout,"%d,", X[i]);
		}
		fprintf(fpout,"\n");
		flag=0;
		fclose(fpout);

		flag=DegEstVerify(X, dim, roundnum,N0,pos[l],posr[l]);
		fopen_s(&fpout, "Res.txt", "a+");
		if (flag == 0)
		{
			printf("Usatisified!!! Plaese try another cube\n\n");
			fprintf(fpout,"Usatisified!!! Plaese try another cube\n\n");
		}
		else
		{
			//输出它的基
			printf( "Succeed!!!\n\n");
			fprintf(fpout, "Succeed!!!\n\n");
			for(i=0;i<dim;i++)
			{
				fprintf(fpcube,"%d,", X[i]);
			}
			fprintf(fpcube,"\n");
		}
		//
		l++;
		printf("\n**********************************************************\n");
	}

	fclose(fpout);
	fclose(fp);
	fclose(fpcube);
}

//验证多基
void GetandTestXVerifyV2()
{
	FILE *fp,*fpout,*fpcube;
	fopen_s(&fp, "dim36-837-4b.txt", "r");
	fopen_s(&fpout, "Res.txt", "a+");
	fopen_s(&fpcube,"SuceedCubes","a+");
	//
	int i,j,m=0,l=0;
	int cubenum = 6124;
	char c;
	char buff[1000] = { 0 };
	c = fgetc(fp);
	int X[80] = { 0 };
	//835round 1,2 basis
	/*int pos[1000][10]={{2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},\
	{2,2},{2,2},{2,2}};
	int posr[1000][10]={{91},{92,94},{90,94},{90,92},{93,95},{91,95},{91,93},{92,94},{90,94},{90,92},\
	{92,94},{90,94},{90,92}};
	int posnum[1000]={1,2,2,2,2,2,2,2,2,2,\
		2,2,2};*/
	//835 round 3 basis part 1
	/*int pos[1000][10]={{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},\
	                   {2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},\
	                   {2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},\
	                   {2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},\
					   {2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},\
					   {2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2}};
	int posr[1000][10]={{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{91,93,95},{91,93,95},\
	                    {121,123,125},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},\
	                    {91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},\
	                    {91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{91,93,95},\
	                    {91,93,95},{90,92,94},{92,94,107},{90,94,107},{90,92,107},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{91,93,95},
						{90,92,94},{91,93,95},{91,93,95},{91,93,95},{91,93,95},{90,92,94}};
	int posnum[1000]={3,3,3,3,3,3,3,3,3,3,\
		              3,3,3,3,3,3,3,3,3,3,\
					  3,3,3,3,3,3,3,3,3,3,\
					  3,3,3,3,3,3,3,3,3,3,\
					  3,3,3,3,3,3,3,3,3,3,\
					  3,3,3,3,3,3};*/
	//835 round 3 basis part 2 
	/*int pos[1000][10]={{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},\
	{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},\
	{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},\
	{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2}};
	int posr[1000][10]={{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},\
	{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},\
	{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},\
	{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94},{90,92,94}};
	int posnum[1000]={3,3,3,3,3,3,3,3,3,3,\
	3,3,3,3,3,3,3,3,3,3,\
	3,3,3,3,3,3,3,3,3,3,\
	3,3,3,3,3,3,3,3,3,3};*/
	////round 835-4 bais
	//int pos[1000][10]={{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},\
	//                   {2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},\
	//	               {2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},\
	//				   {2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},\
	//				   {2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},\
	//				   {2,2,2,2}};
	//int posr[1000][10]={{91,93,123,125},{91,93,123,125},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,135,137},\
	//	                {90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},\
	//					{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},\
	//					{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},\
	//					{90,92,94,107},{90,92,94,107},{90,92,94,107},{90,92,94,107},{91,93,104,106},{91,93,106,108},{90,92,94,107},{90,92,94,120},\
	//					{98,113,115,117}};
	//int posnum[1000]={4,4,4,4,4,4,4,4,\
	//				  4,4,4,4,4,4,4,4,\
	//				  4,4,4,4,4,4,4,4,\
	//				  4,4,4,4,4,4,4,4,\
	//				  4,4,4,4,4,4,4,4,\
	//				  4};

	//round 836 3 baisis
	/*int pos[1000][10]={{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},{2,2,2},\
	                   {2,2,2},{2,2,2}};
	int posr[1000][10]={{92,94,96},{90,94,96},{90,92,96},{90,92,94},{91,93,95},{93,95,108},{91,95,108},{91,93,108},{91,93,95},{91,93,95},\
	                    {91,93,95},{91,93,95}
	                    };
	int posnum[1000]={3,3,3,3,3,3,3,3,3,3,\
		              3,3};*/

	//round 836-4 bais
	/*int pos[1000][10]={{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},\
	{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},\
	{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},\
	{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},\
	{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},\
	{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},\
	{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},\
	{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},\
	{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2}};
	int posr[1000][10]={{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},\
						{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},\
						{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},\
						{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{90,92,94,96},{91,93,95,108},
						{91,93,95,108},{90,92,94,96},{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,136,138},{91,93,95,108},{91,93,95,108},\
						{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},\
						{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},\
						{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},{91,93,95,108},\
						{91,93,95,108},{90,92,94,96},{90,92,94,96},{90,92,94,96},{91,93,95,108}};
	int posnum[1000]={4,4,4,4,4,4,4,4,\
		4,4,4,4,4,4,4,4,\
		4,4,4,4,4,4,4,4,\
		4,4,4,4,4,4,4,4,\
		4,4,4,4,4,4,4,4,\
		4,4,4,4,4,4,4,4,\
		4,4,4,4,4,4,4,4,\
		4,4,4,4,4,4,4,4,\
		4,4,4,4,4};*/
	//837-4b
	int pos[1000][10] = { { 2,2,2,2 },{ 2,2,2,2 },{ 2,2,2,2 },{ 2,2,2,2 },{ 2,2,2,2 },{ 2,2,2,2 },{ 2,2,2,2 },{ 2,2,2,2 },\
	{2,2,2,2},{ 2,2,2,2 },{ 2,2,2,2 },{ 2,2,2,2 },{ 2,2,2,2 },{ 2,2,2,2 },{ 2,2,2,2 } };
	int posr[1000][10] = { { 90,92,94,96 },{ 90,92,94,96 },{ 90,92,94,96 },{ 92,94,96,109 },{ 92,94,96,122 },{ 90,94,96,109 },{ 90,92,96,109 },{ 90,92,96,122 },\
						   { 90,92,94,109 },{ 90,92,94,122 },{ 90,92,94,96 },{ 90,92,94,96 },{ 91,93,95,97 },{ 91,93,95,97 },{ 91,93,95,97 } };
	int posnum[1000] = { 4,4,4,4,4,4,4,4,\
		4,4,4,4,4,4,4 };
	int dim = 36;
	int N;
	N = 900;
	int roundnum=837;
	int N0=200;
	int flag=0;
	int maxround = 0;
	char filename[20] = "RecDeg.txt";
	while (c != EOF)
	{
		//
		memset(buff, 0, sizeof(char) * 1000);
		j = 0;
		while (c != '\n')
		{
			buff[j++] = c;
			c = fgetc(fp);
		}
		c = fgetc(fp);
		m = 0;
		i = 0;
		printf("\n**********************************************************\n");
		printf("%d: ", l);
		while(i<j)
			//for (i = 0; i < j; i++)
		{
			if ((buff[i]>='0') && (buff[i]<='9'))
			{
				if (buff[i + 1] == ',')
				{
					X[m++] = buff[i] - '0';
					i = i + 2;
				}
				else
				{
					if (buff[i + 2] = ',')
					{
						X[m++] = (buff[i] - '0')*10+buff[i+1]-'0';
						i = i + 3;
					}
					else
					{
						i++;
					}
				}
			}
		}
		for(i=0;i<dim;i++)
		{
			fprintf(fpout,"%d,", X[i]);
		}
		fprintf(fpout,"\n");
		flag=0;
		fclose(fpout);

		flag=DegEstVerifyV2(X, dim, roundnum,N0,pos[l],posr[l],posnum[l]);
		fopen_s(&fpout, "Res.txt", "a+");
		if (flag == 0)
		{
			printf("Usatisified!!! Plaese try another cube\n\n");
			fprintf(fpout,"Usatisified!!! Plaese try another cube\n\n");
		}
		else
		{
			//输出它的基
			printf( "Succeed!!!\n\n");
			fprintf(fpout, "Succeed!!!\n\n");
			for(i=0;i<dim;i++)
			{
				fprintf(fpcube,"%d,", X[i]);
			}
			fprintf(fpcube,"\n");
		}
		//
		l++;
		printf("\n**********************************************************\n");
	}

	fclose(fpout);
	fclose(fp);
	fclose(fpcube);
}