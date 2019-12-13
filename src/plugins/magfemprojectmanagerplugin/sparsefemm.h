#ifndef SPARSEFEMM_H
#define SPARSEFEMM_H

class CEntry
{
public:

    double x;				// value stored in the entry
    int c;					// column that the entry lives in
    CEntry *next;			// pointer to next entry in row;
    CEntry();

private:
};

#define LAMBDA 1.5

class  CBigLinProb
{
public:
    // member functions
    CBigLinProb();				// constructor
    ~CBigLinProb();				// destructor
    int Create(int d, int bw);			// initialize the problem
    void Put(double v, int p, int q);
    // use to create/set entries in the matrix
    double Get(int p, int q);
    int PCGSolve(int flag);		 // flag==true if guess for V present;
    void MultPC(double *X, double *Y);
    void MultA(double *X, double *Y);
    void SetValue(int i, double x);
    void Periodicity(int i, int j);
    void AntiPeriodicity(int i, int j);
    void Wipe();
    double Dot(double *X, double *Y);
    void ComputeBandwidth();

public:
    // data members
    double *V;				/** 解 **/
    double *P;				/** 搜索方向 **/
    double *R;				/** 余量 **/
    double *U;				/** A * P **/
    double *Z;
    double *b;				/** RHS，右侧向量 **/
    CEntry **M;				/** 矩阵的数据 **/
    int n;					/** 矩阵维度 **/
    int bdw;				/** Optional matrix bandwidth parameter; **/
    double Precision;		/** error tolerance for solution **/
};


#endif // SPARSEFEMM_H
