#pragma once
int MaxroundMindeg(int Reslist[][3], int Res[], int remdim);

int MindegMaxround(int Reslist[][3], int Res[], int remdim);

int MaxroundMindegWithNB(int Reslist[][3], int Res[], int remX[], int X[], int remdim);

int MindegMaxroundWithNB(int Reslist[][3], int Res[], int remX[], int X[], int remdim);

int StrategySet(int stranum, int Reslist[][3], int Res[], int remX[], int X[], int remdim);
int EstDegRec(int X[], int dim, char filename[], int N, int p, int Res[]);

//pdeg最小
int EstDegRecV(int X[], int dim, char filename[], int N, int p, int Res[]);
void Greedy(int p);
//利用ANF初始化
int EstDegRecwithANF(unsigned int *** A, unsigned int *** B, unsigned int *** C, int sizeA[], int sizeB[], int sizeC[], int cube[], int dim, int N0, int N, int p, int Res[]);
void GreedyANFInner(int p, int N0, unsigned int ***A, unsigned int ***B, unsigned int ***C, int sizeA[], int sizeB[], int sizeC[]);
void GreedyANFOuter(int p);