int compare(char a[160], char b[160]);
int reduce(char **poly, int size);
int multi(char **s1, char **s2, int size1, int size2, char **res);
int addition(char **s1, char **s2, char **s3, char **s4, int size1, int size2, int size3, int size4, char **res);
int getdeg(char term[160]);
int getleadcoef(char **poly, int size, char coef[][80], int DEG[], int vanpos[], int vansize[]);
int vanish(char **poly, int vanpos[], int size, int vansize);
void decomposition(int cube[], int dim, int Da[], int Db[], int Dc[], int Dav[], int Dbv[], int Dcv[], int N0);
//void decompositionV(int cube[], int dim, char *** upA, char ***upB,char ***upC, int sizeA[], int sizeB[], int sizeC[],int Da[], int Db[], int Dc[],int Dav[], int Dbv[], int Dcv[], int N0);
void decompositionV(int cube[], int dim, char *** upA, char ***upB,char ***upC, int sizeA[], int sizeB[], int sizeC[],int vfA[],int vfB[],int vfC[],int basnum[], int N0);
int todeg(char term[160]);
//void getinideg(char ***up, int size[],int D[], int X[],int dim,int N0);
void getinideg(char ***up, int size[],int vf[], int D[], int X[],int dim,int N0);
void getinidegV2(char ***up, int size[],int vf[], int D[], int Dv[], int X[],int dim,int N0);
void decompositionVerify(int cube[], int dim, char *** upA, char ***upB,char ***upC, int sizeA[], int sizeB[], int sizeC[],int vfA[],int vfB[],int vfC[],int pos, int posr, int basnum[], int N0);


//functions for free non cube variable
int getdegFreeIV(char term[160],int cube[], int dim);
void decompositionFreeNC(int cube[], int dim, int freenc, char *** upA, char ***upB,char ***upC, int sizeA[], int sizeB[], int sizeC[],int vfA[],int vfB[],int vfC[],int pos, int posr, int basnum[], int N0);
int getleadcoefFreeIV(char **poly, int size, char coef[][80], int cube[], int dim, int DEG[2], int vanpos[], int vansize[]);

void decompositionFreeNCV2(int cube[], int dim, int freenc, char *** upA, char ***upB,char ***upC, int sizeA[], int sizeB[], int sizeC[],int vfA[],int vfB[],int vfC[],int pos[], int posr[], int posnum, int basnum[], int N0);