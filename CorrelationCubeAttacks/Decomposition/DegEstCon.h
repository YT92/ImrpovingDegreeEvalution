int DEGLA(int Da[], int Db[], int Dc[], int t, int dim);
int DEGLB(int Da[], int Db[], int Dc[], int t, int dim);
int DEGLC(int Da[], int Db[], int Dc[], int t, int dim);
int DegMulA(int Da[], int Db[], int Dc[], int t, int dim);
int DegMulB(int Da[], int Db[], int Dc[], int t, int dim);
int DegMulC(int Da[], int Db[], int Dc[], int t, int dim);
int DegEst(int Da[], int Db[], int Dc[], int round, int N0, int dim);
int DegEstWithCon(int cube[], int dim, int round, int N0);
int DegEstWithConV(int cube[], int dim, int round, int N0);
void getX(int cube[], int loclist[], int X[], int dim, int loclen);
int DegEstVerify(int cube[], int dim, int round, int N0, int pos, int posr);
void GetandTestX();
void GetandTestXVerify();
void GetandTestXVerifyV2();