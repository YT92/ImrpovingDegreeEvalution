#pragma once
int compareV(unsigned int a[], unsigned int b[], int len);
int reduceV(unsigned int **poly, int size, int Len);
int addition4V(unsigned int **s1, unsigned int **s2, unsigned int **s3, unsigned int **s4, int size1, int size2, int size3, int size4, unsigned int **res);
int addition5V(unsigned int **s1, unsigned int **s2, unsigned int **s3, unsigned int **s4, unsigned int **s5, int size1, int size2, int size3, int size4, int size5, unsigned int **res);
int multi(unsigned int **s1, unsigned int **s2, int size1, int size2, unsigned int **res);
void ComANFwithCubeVariable(unsigned int ***s, int size[], int N0, int cube[], int dim);
void ComANFwithCubeVariableV2(unsigned int ***A, unsigned int ***B, unsigned int ***C, int sizeA[], int sizeB[], int sizeC[], int N0, int cube[], int dim);
int getdeg(unsigned int *t, int X[], int Xdim);