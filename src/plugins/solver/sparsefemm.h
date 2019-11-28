#ifndef SPARSEFEMM_H
#define SPARSEFEMM_H

#include "solver_global.h"

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

class FEEM_SOLVER_EXPORT CBigLinProb
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

//    CFknDlg *TheView;

public:
    // data members
    double *V;				// solution
    double *P;				// search direction;
    double *R;				// residual;
    double *U;				// A * P;
    double *Z;
    double *b;				// RHS of linear equation
    CEntry **M;				// pointer to list of matrix entries;
    int n;					// dimensions of the matrix;
    int bdw;				// Optional matrix bandwidth parameter;
    double Precision;		// error tolerance for solution

};


#endif // SPARSEFEMM_H
