#include "sparsefemm.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

CEntry::CEntry()
    :x(0)
    ,c(0)
    ,next(nullptr)
{

}

CBigLinProb::CBigLinProb()
    :n(0)
{
}

CBigLinProb::~CBigLinProb()
{
    if (n==0) return;

    int i;
    CEntry *uo,*ui;

    free(b); free(P); free(R);
    free(V); free(U); free(Z);

    for(i=0;i<n;i++)
    {
        ui=M[i];
        do{
            uo=ui;
            ui=uo->next;
            delete uo;
        } while(ui!=nullptr);
    }

    free(M);
}

/*!
 \brief 初始化变量，分配空间

 \param d
 \param bw
 \return int
*/
int CBigLinProb::Create(int d, int bw)
{
    int i;

    bdw = bw;
    b = static_cast<double *>(calloc(d,sizeof(double)));
    V = static_cast<double *>(calloc(d,sizeof(double)));
    P = static_cast<double *>(calloc(d,sizeof(double)));
    R = static_cast<double *>(calloc(d,sizeof(double)));
    U = static_cast<double *>(calloc(d,sizeof(double)));
    Z = static_cast<double *>(calloc(d,sizeof(double)));

    M = static_cast<CEntry **>(calloc(d,sizeof(CEntry *)));
    n = d;

    for(i=0;i<d;i++){
        M[i] = new CEntry;
        M[i]->c = i;
    }

    return 1;
}

/*!
 \brief 将(0,q)处的值设置为v

 \param v
 \param p
 \param q
*/
void CBigLinProb::Put(double v, int p, int q)
{
    CEntry *e,*l = nullptr;
    int i;
    if(q<p){ i=p; p=q; q=i; }//exchange
    e=M[p];
    while((e->c < q) && (e->next != nullptr))
    {
        l=e;
        e=e->next;
    }
    if(e->c == q){//exist the q, fresh it
        e->x=v;
        return;
    }
    CEntry *m = new CEntry;//it is new...
    if((e->next == nullptr) && (q > e->c)){//q it out the index of the end
        e->next = m;
        m->c = q;
        m->x = v;
    }
    else{//the q doesn't exist, intsert the q.
        l->next=m;
        m->next=e;
        m->c=q;
        m->x=v;
    }
    return;
}

double CBigLinProb::Get(int p, int q)
{
    CEntry *e;
    if(q<p){ int i; i=p; p=q; q=i; }//it is symmetric, fint the smaller index to save time.
    e=M[p];//the pointer
    while((e->c < q) && (e->next != nullptr)) e=e->next;//iterative, because it is sparse, so it's fast.
    if(e->c == q) return e->x;
    return 0;
}

void CBigLinProb::MultA(double *X, double *Y)
{
    int i;
    CEntry *e;
    for(i=0;i<n;i++) Y[i]=0;
    for(i=0;i<n;i++){
        Y[i]+=M[i]->x*X[i];
        e=M[i]->next;
        while(e!=nullptr)
        {
            Y[i]+=e->x*X[e->c];
            Y[e->c]+=e->x*X[i];
            e=e->next;
        }
    }
}

double CBigLinProb::Dot(double *X, double *Y)
{
    int i;
    double z;
    for(i=0,z=0;i<n;i++) z+=X[i]*Y[i];
    return z;
}

void CBigLinProb::MultPC(double *X, double *Y)
{
    // Jacobi preconditioner:
    //	int i;
    // for(i=0;i<n;i++) Y[i]=X[i]/M[i]->x;

    // SSOR preconditioner:
    int i;
    double c;
    CEntry *e;

    c= LAMBDA*(2.-LAMBDA);
    for(i=0;i<n;i++) Y[i]=X[i]*c;

    // invert Lower Triangle;
    for(i=0;i<n;i++){
        Y[i]/= M[i]->x;
        e=M[i]->next;
        while(e!=nullptr)
        {
            Y[e->c] -= e->x * Y[i] * LAMBDA;
            e=e->next;
        }
    }
    for(i=0;i<n;i++) Y[i]*=M[i]->x;
    // invert Upper Triangle
    for(i=n-1;i>=0;i--){
        e=M[i]->next;
        while(e!=nullptr)
        {
            Y[i] -= e->x * Y[e->c] * LAMBDA;
            e=e->next;
        }
        Y[i]/= M[i]->x;
    }
}

int CBigLinProb::PCGSolve(int flag)
{
    int i;
    double res,res_o,res_new;
    double er,del,rho,pAp;

    // quick check for most obvious sign of singularity;
    for(i=0;i<n;i++) if(M[i]->x==0){//if the first is zero, then not correct, because no zeros
        fprintf(stderr,"singular flag tripped.");
        return 0;
    }

    // initialize progress bar;
    //    TheView->SetDlgItemText(IDC_FRAME1,"Conjugate Gradient Solver");
    //    TheView->m_prog1.SetPos(0);
    int prg1=0;
    int prg2;

    // residual with V=0
    MultPC(b,Z);
    res_o=Dot(Z,b);
    if(res_o==0) return 1;

    // if flag is false, initialize V with zeros;
    if (flag==0) for(i=0;i<n;i++) V[i]=0;

    // form residual;
    MultA(V,R);
    for(i=0;i<n;i++) R[i]=b[i]-R[i];

    // form initial search direction;
    MultPC(R,Z);
    for(i=0;i<n;i++) P[i]=Z[i];
    res=Dot(Z,R);

    // do iteration;
    do{
        // step i)
        MultA(P,U);
        pAp=Dot(P,U);
        del=res/pAp;

        // step ii)
        for(i=0;i<n;i++) V[i]+=(del*P[i]);

        // step iii)
        for(i=0;i<n;i++) R[i]-=(del*U[i]);

        // step iv)
        MultPC(R,Z);
        res_new=Dot(Z,R);
        rho=res_new/res;
        res=res_new;

        // step v)
        for(i=0;i<n;i++) P[i]=Z[i]+(rho*P[i]);

        // have we converged yet?
        er=sqrt(res/res_o);
        prg2=(int) (20.*log10(er)/(log10(Precision)));
        if(prg2>prg1){
            prg1=prg2;
            prg2=(prg1*5);
            if(prg2>100) prg2=100;
        }

    } while(er>Precision);

    return 1;
}

/*!
 \brief 如果未知量的某个元素是已知的，将矩阵中对应的列置零，
 并且更新右侧向量。

 \param i
 \param x
*/
void CBigLinProb::SetValue(int i, double x)
{
    int k,fst,lst;
    double z;

    if(bdw==0){
        fst=0;
        lst=n;
    }else{
        fst=i-bdw; if (fst<0) fst=0;
        lst=i+bdw; if (lst>n) lst=n;
    }

    for(k=fst;k<lst;k++)
    {
        z=Get(k,i);
        if(z != 0){
            b[k] -= (z*x);
            if(i!=k) Put(0.,k,i);
        }
    }
    b[i] = Get(i,i)*x;
}

void CBigLinProb::Wipe()
{
    int i;
    CEntry *e;

    for(i=0;i<n;i++){
        b[i]=0.;
        e=M[i];
        do{
            e->x=0;
            e=e->next;
        } while(e!=nullptr);
    }
}

void CBigLinProb::AntiPeriodicity(int i, int j)
{
    int k,fst,lst;
    double v1,v2,c;

#ifdef KLUDGE
    int tmpbdw=bdw;
    bdw=0;
#endif

    if (j<i) {k=j;j=i;i=k;}

    if(bdw==0){
        fst=0;
        lst=n;
    }
    else{
        fst=i-bdw; if (fst<0) fst=0;
        lst=j+bdw; if (lst>n) lst=n;
    }

    for(k=fst;k<lst;k++)
    {
        if((k!=i) && (k!=j))
        {
            v1=Get(k,i);
            v2=Get(k,j);
            if ((v1!=0) || (v2!=0)){
                c=(v1-v2)/2.;
                Put(c,k,i);
                Put(-c,k,j);
            }
        }
        if((k==i+bdw) && (k<j-bdw) && (bdw!=0)) k=j-bdw;
    }

    c=0.5*(Get(i,i)+Get(j,j));
    Put(c,i,i);
    Put(c,j,j);

    c=0.5*(b[i]-b[j]);
    b[i]=c;
    b[j]=-c;

#ifdef KLUDGE
    bdw=tmpbdw;
#endif
}

void CBigLinProb::Periodicity(int i, int j)
{
    int k,fst,lst;
    double v1,v2,c;

#ifdef KLUDGE
    int tmpbdw=bdw;
    bdw=0;
#endif

    if (j<i) {k=j;j=i;i=k;}

    if(bdw==0){
        fst=0;
        lst=n;
    }
    else{
        fst=i-bdw; if (fst<0) fst=0;
        lst=j+bdw; if (lst>n) lst=n;
    }

    for(k=fst;k<lst;k++){
        if((k!=i) && (k!=j))
        {
            v1=Get(k,i);
            v2=Get(k,j);
            if ((v1!=0) || (v2!=0)) {
                c=(v1+v2)/2.;
                Put(c,k,i);
                Put(c,k,j);
            }
        }
        if((k==i+bdw) && (k<j-bdw) && (bdw!=0)) k=j-bdw;
    }

    c=(Get(i,i)+Get(j,j))/2.;
    Put(c,i,i);
    Put(c,j,j);

    c=0.5*(b[i]+b[j]);
    b[i]=c;
    b[j]=c;

#ifdef KLUDGE
    bdw=tmpbdw;
#endif
}


// a diagnostic routine to check whether that the bandwidth of the
// constructed matrix is actually consistent with a priori bandwidth.
void CBigLinProb::ComputeBandwidth()
{
    CEntry *e;
    int k,bw,maxbw;

    for(maxbw=0,k=0;k<n;k++)
    {
        e=M[k];
        while(e->next != nullptr) e=e->next;
        bw=e->c - k;
        if (bw>maxbw) maxbw=bw;
    }

    //    MsgBox("Assumed Bandwidth = %i\nActual Bandwidth = %i",bdw,maxbw);
}
