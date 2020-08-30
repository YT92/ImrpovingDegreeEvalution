#pragma once
void sortV(unsigned int **a, int p, int r, int len);
void swapV(unsigned int *pi, unsigned int *pj, int len);
int ComPV(unsigned int *p1, unsigned int *p2, int len);
int partitionV(unsigned int **a, int p, int r, int len);


//全变元专用
void sortFV(char**a, int p, int r);
void swapFV(char*pi, char*pj);
int ComPFV(char*p1, char*p2);
int partitionFV(char**a, int p, int r);