#pragma once
#pragma once
void initialize(int Da[], int Db[], int Dc[], int Dv[], int X[], int dim, char filename[], int loclist[], int loclen, int flag);


int DEGLA(int Da[], int Db[], int Dc[], int t);

int DEGLB(int Da[], int Db[], int Dc[], int t);

int DEGLC(int Da[], int Db[], int Dc[], int t);


//A寄存器中t时刻的状态是Da[t]-Da[t+92]//                                                                                 
int DegMulA(int Da[], int Db[], int Dc[], int t);
int DegMulB(int Da[], int Db[], int Dc[], int t);
int DegMulC(int Da[], int Db[], int Dc[], int t);

void EstimateDegree(int X[], int dim, char filename[], int N, int loclist[], int loclen, int flag, int p, int res[]);
//int DegEstMIM(char X[], int dim, int N, int M, int maxdeg, char path[]);

void EstimateDegreeV(int Da[], int Db[], int Dc[], int Dv[], int dim, int N0, int N, int loclist[], int loclen, int flag, int p, int res[]);
void DegEstANFOuter(int X[], int dim, int N, int p);