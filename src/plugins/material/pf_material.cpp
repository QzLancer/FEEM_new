#include "pf_material.h"

#include <stdio.h>
#include <QDebug>

CComplex::CComplex(double x)
{
    re=x; im=0.;
}

CComplex::CComplex(int x)
{
    re=(double) x;
    im=0.;
}

CComplex::CComplex()
{
    re=0.;	im=0.;
}

CComplex::CComplex(double x, double y)
{
    re=x; im=y;
}

CComplex CComplex::Sqrt()
{
    double w,z;
    CComplex y;

    if((re==0) && (im==0)) w=0;
    else if(fabs(re)>fabs(im)){
        z=im/re;
        w=sqrt(fabs(re))*sqrt( (1.+sqrt(1.+z*z))/2. );
    }
    else{
        z=re/im;
        w=sqrt(fabs(im))*sqrt( (fabs(z)+sqrt(1.+z*z))/2. );
    }

    if(w==0){
        y.re=0;
        y.im=0;
        return y;
    }

    if(re>=0){
        y.re=w;
        y.im=im/(2.*w);
        return y;
    }

    if(im>=0){
        y.re=fabs(im)/(2.*w);
        y.im=w;
        return y;
    }

    y.re=fabs(im)/(2.*w);
    y.im= (-w);
    return y;
}

CComplex CComplex::Conj()
{
    return CComplex(re,-im);
}

double CComplex::Abs()
{
    if ((re==0) && (im==0)) return 0.;

    if (fabs(re)>fabs(im))
        return fabs(re)*sqrt(1.+(im/re)*(im/re));
    else
        return fabs(im)*sqrt(1.+(re/im)*(re/im));
}

double CComplex::Arg()
{
    if ((re==0) && (im==0)) return 0.;

    return atan2(im,re);
}

CComplex CComplex::Inv()
{
    double c;
    CComplex z;

    if(fabs(re)>fabs(im))
    {
        c=im/re;
        z.re=1./(re*(1.+c*c));
        z.im=(-c)*z.re;
    }
    else{
        c=re/im;
        z.im=(-1.)/(im*(1.+c*c));
        z.re=(-c)*z.im;
    }

    return z;
}

double CComplex::Re()
{
    return re;
}

double CComplex::Im()
{
    return im;
}

void CComplex::Set(double x, double y)
{
    re=x; im=y;
}

char* CComplex::ToString(char *s)
{
    if (im<0)
        sprintf(s,"%.3e - j %.3e",re,fabs(im));
    else
        sprintf(s,"%.3e + j %.3e",re,im);
    return s;
}

//******* Addition ***************************************************

CComplex CComplex::operator+( const CComplex& z )
{
    return CComplex(re+z.re,im+z.im);
};

CComplex CComplex::operator+( int z )
{
    return CComplex(re+((double) z),im);
};

CComplex CComplex::operator+( double z )
{
    return CComplex(re+z,im);
};

void CComplex::operator+=( const CComplex& z)
{
    re+=z.re;
    im+=z.im;
};

void CComplex::operator+=( double z )
{
    re+=z;
};

void CComplex::operator+=( int z )
{
    re+=(double) z;
};

CComplex operator+( int x, const CComplex& y )
{
    return CComplex( ((double) x) + y.re, y.im );
}

CComplex operator+( double x, const CComplex& y )
{
    return CComplex( x + y.re, y.im );
}

CComplex operator+( const CComplex& x, const CComplex& y )
{
    return CComplex( x.re + y.re, x.im + y.im );
}


//******* Subtraction ***************************************************
CComplex CComplex::operator-()
{
    return CComplex(-re,-im);
}

CComplex CComplex::operator-( const CComplex& z)
{
    return CComplex(re-z.re,im-z.im);
};

CComplex CComplex::operator-( int z )
{
    return CComplex(re-((double) z),im);
};

CComplex CComplex::operator-( double z )
{
    return CComplex(re-z,im);
};

void CComplex::operator-=( const CComplex& z)
{
    re-=z.re;
    im-=z.im;
};

void CComplex::operator-=( double z )
{
    re-=z;
};

void CComplex::operator-=( int z )
{
    re-=(double) z;
};

CComplex operator-( int x, const CComplex& y )
{
    return CComplex( ((double) x) - y.re, - y.im );
}

CComplex operator-( double x, const CComplex& y )
{
    return CComplex( x - y.re, - y.im );
}

CComplex operator-( const CComplex& x, const CComplex& y )
{
    return CComplex( x.re - y.re, x.im - y.im );
}

CComplex operator-( const CComplex& y )
{
    return CComplex( -y.re,-y.im );
}
//******* Multiplication ***************************************************

CComplex CComplex::operator*( const CComplex& z)
{
    return CComplex(re*z.re - im*z.im,re*z.im + im*z.re);
};

CComplex CComplex::operator*( int z )
{
    return CComplex( re*((double) z),im*((double) z) );
};

CComplex CComplex::operator*( double z )
{
    return CComplex(re*z,im*z);
};

void CComplex::operator*=( const CComplex& z)
{
    CComplex x(re*z.re - im*z.im,re*z.im + im*z.re);
    re=x.re; im=x.im;
};

void CComplex::operator*=( double z )
{
    re*=z; im*=z;
};

void CComplex::operator*=( int z )
{
    re*=(double) z;
    im*=(double) z;
};

CComplex operator*( int x, const CComplex& y )
{
    return CComplex( ((double) x) * y.re, ((double) x)*y.im );
}

CComplex operator*( double x, const CComplex& y )
{
    return CComplex( x*y.re, x*y.im );
}

CComplex operator*( const CComplex& x, const CComplex& y )
{
    return CComplex( x.re*y.re-x.im*y.im, x.re*y.im+x.im*y.re );
}

//******* Division ***************************************************

CComplex CComplex::operator/( const CComplex& z)
{
    double c;
    CComplex y;

    if(fabs(z.re)>fabs(z.im))
    {
        c=z.im/z.re;
        y.re=1./(z.re*(1.+c*c));
        y.im=(-c)*y.re;
    }
    else{
        c=z.re/z.im;
        y.im=(-1.)/(z.im*(1.+c*c));
        y.re=(-c)*y.im;
    }

    return *this * y;
};


CComplex CComplex::operator/( int z )
{
    return CComplex(re/((double) z),im/((double) z));
};

CComplex CComplex::operator/( double z )
{
    return CComplex(re/z,im/z);
};

void CComplex::operator/=( const CComplex& z)
{
    *this=*this/z;
};

void CComplex::operator/=( double z )
{
    re/=z;
    im/=z;
};

void CComplex::operator/=( int z )
{
    re/=(double) z;
    im/=(double) z;
};

CComplex operator/( int x, const CComplex& z )
{
    double c;
    CComplex y;

    if(fabs(z.re)>fabs(z.im))
    {
        c=z.im/z.re;
        y.re=1./(z.re*(1.+c*c));
        y.im=(-c)*y.re;
    }
    else{
        c=z.re/z.im;
        y.im=(-1.)/(z.im*(1.+c*c));
        y.re=(-c)*y.im;
    }

    y.re*=(double) x;
    y.im*=(double) x;

    return y;
}

CComplex operator/( double x, const CComplex& z )
{
    double c;
    CComplex y;

    if(fabs(z.re)>fabs(z.im))
    {
        c=z.im/z.re;
        y.re=1./(z.re*(1.+c*c));
        y.im=(-c)*y.re;
    }
    else{
        c=z.re/z.im;
        y.im=(-1.)/(z.im*(1.+c*c));
        y.re=(-c)*y.im;
    }

    y.re*= x;
    y.im*= x;

    return y;
}

CComplex operator/( const CComplex& x, const CComplex& z )
{
    double c;
    CComplex y;

    if(fabs(z.re)>fabs(z.im))
    {
        c=z.im/z.re;
        y.re=1./(z.re*(1.+c*c));
        y.im=(-c)*y.re;
    }
    else{
        c=z.re/z.im;
        y.im=(-1.)/(z.im*(1.+c*c));
        y.re=(-c)*y.im;
    }

    return x*y;
}

//****** Equals definitions ********************************

void CComplex::operator=(double z)
{
    re=z;
    im=0;
}

void CComplex::operator=(int z)
{
    re=(double) z;
    im=0;

}

//***** Tests ***********************************************
bool CComplex::operator==( const CComplex& z){
    if ((z.im==im) && (z.re==re)) return true;
    return false;
}

bool CComplex::operator==(double z){
    if ((z==re) && (im==0)) return true;
    return false;
}

bool CComplex::operator==(int z){
    if ((re==(double) z) && (im==0)) return true;
    return false;
}

bool CComplex::operator!=( const CComplex& z){
    if ((z.re==re) && (z.im==im)) return false;
    return true;
}

bool CComplex::operator!=(double z){
    if ((re!=z) || (im!=0)) return true;
    return false;
}

bool CComplex::operator!=(int z){
    if ((re!=(double) z) || (im!=0)) return true;
    return false;
}

//***** Useful functions ************************************

CComplex conj( const CComplex& x)
{
    return CComplex(x.re,-x.im);
}

CComplex exp( const CComplex& x)
{
    CComplex y;

    y.re=cos(x.im)*exp(x.re);
    y.im=sin(x.im)*exp(x.re);

    return y;
}

CComplex sqrt( const CComplex& x)
{
    double w,z;
    CComplex y;

    if((x.re==0) && (x.im==0)) w=0;
    else if(fabs(x.re)>fabs(x.im)){
        z=x.im/x.re;
        w=sqrt(fabs(x.re))*sqrt( (1.+sqrt(1.+z*z))/2. );
    }
    else{
        z=x.re/x.im;
        w=sqrt(fabs(x.im))*sqrt( (fabs(z)+sqrt(1.+z*z))/2. );
    }

    if(w==0){
        y.re=0;
        y.im=0;
        return y;
    }

    if(x.re>=0){
        y.re=w;
        y.im=x.im/(2.*w);
        return y;
    }

    if(x.im>=0){
        y.re=fabs(x.im)/(2.*w);
        y.im=w;
        return y;
    }

    y.re=fabs(x.im)/(2.*w);
    y.im= (-w);

    return y;
}

CComplex tanh( const CComplex& x)
{
    CComplex y;

    if (x.re>0){
        y=(1-exp(-2*x))/(1+exp(-2*x));
    }
    else{
        y=(exp(2*x)-1)/(exp(2*x)+1);
    }

    return y;
}

CComplex sinh( const CComplex& x)
{
    return (exp(x)-exp(-x))/2;
}

CComplex cosh( const CComplex& x)
{
    return (exp(x)+exp(-x))/2;
}


CComplex cos( const CComplex& x)
{
    return (exp(I*x)+exp(-I*x))/2;
}

CComplex acos( const CComplex& x)
{
    return PI/2. - arg(I*x + sqrt(1 - x*x)) + I*log(abs(I*x + sqrt(1 - x*x)));
}

CComplex sin( const CComplex& x)
{
    return (exp(I*x)-exp(-I*x))/(2*I);
}

CComplex asin( const CComplex& x)
{
    return arg(I*x + sqrt(1 - x*x)) - I*log(abs(I*x + sqrt(1 - x*x)));
}

CComplex tan( const CComplex& x)
{
    return sin(x)/cos(x);
}

CComplex atan( const CComplex& x)
{
    return (arg(1+I*x) - arg(1-I*x) - I*(log(abs(1+I*x)/abs(1-I*x))))/ 2;
}

double abs( const CComplex& x)
{
    if ((x.re==0) && (x.im==0)) return 0.;

    if (fabs(x.re)>fabs(x.im))
        return fabs(x.re)*sqrt(1.+(x.im/x.re)*(x.im/x.re));
    else
        return fabs(x.im)*sqrt(1.+(x.re/x.im)*(x.re/x.im));
}

double arg( const CComplex& x)
{
    if ((x.re==0) && (x.im==0)) return 0.;

    return atan2(x.im,x.re);
}

CComplex log( const CComplex& x)
{
    CComplex y;

    y.im=arg(x);
    y.re=log(abs(x));

    return y;
}

CComplex pow( const CComplex& x, double y)
{
    return exp(y*log(x));
}

CComplex pow( const CComplex& x, int y)
{
    if (y==0) return CComplex(1,0);

    int i;
    CComplex z;

    if (y>0){
        z=x;
        for(i=1;i<y;i++) z*=x;
    }
    else{
        z=1/x;
        CComplex w=z;
        for(i=1;i<(-y);i++) z*=w;
    }

    return z;
}

CComplex pow( const CComplex& x, const CComplex& y)
{
    return exp(y*log(x));
}

double Re( const CComplex& a)
{
    return a.re;
}

double Im( const CComplex& a)
{
    return a.im;
}

PF_Material::PF_Material()
{

}

CMaterialProp::CMaterialProp()
    :BlockName(QObject::tr("New Material"))
    ,mu_x(1.)
    ,mu_y(1.)
    ,BHpoints(0)
    ,BHdata(nullptr)
    ,LamType(0)
    ,LamFill(1.)
    ,Theta_m(0)
    ,H_c(0)
    ,Cduct(0)
    ,Lam_d(0)
    ,Theta_hn(0)
    ,Theta_hx(0)
    ,Theta_hy(0)
    ,NStrands(0)
    ,WireD(0)
    ,m_linear(true)

{
    Jsrc.im=0;
    Jsrc.re=0.;
}

CMaterialProp::CMaterialProp(const CMaterialProp &material)
{
    qDebug()<<"CMaterialProp copy constructor";
    this->BlockName = material.BlockName;
    this->mu_x = material.mu_x;
    this->mu_y = material.mu_y;
    this->LamType = material.LamType;
    this->LamFill = material.LamFill;
    this->Theta_m = material.Theta_m;
    this->H_c = material.H_c;
    this->Cduct = material.Cduct;
    this->Lam_d = material.Lam_d;
    this->Theta_hn = material.Theta_hn;
    this->Theta_hx = material.Theta_hx;
    this->Theta_hy = material.Theta_hy;
    this->NStrands = material.NStrands;
    this->WireD = material.WireD;
    this->Jsrc.im = material.Jsrc.im;
    this->Jsrc.re = material.Jsrc.re;

    this->m_linear = material.m_linear;
    this->BHpoints = material.BHpoints;
    if(this->BHpoints > 0){
        this->m_linear = false;
        this->BHdata=static_cast<CComplex *>(calloc(this->BHpoints,sizeof(CComplex)));
        memcpy(this->BHdata,material.BHdata,this->BHpoints*sizeof(CComplex));
    }
}

//CMaterialProp::~CMaterialProp()
//{
////    qDebug()<<Q_FUNC_INFO;
//    if(BHpoints>0) free(BHdata);
//}

/*!
 \brief 拷贝函数。

 \param material
 \return CMaterialProp &CMaterialProp::operator
*/
CMaterialProp &CMaterialProp::operator =(const CMaterialProp &material)
{
    this->BlockName = material.BlockName;
    this->mu_x = material.mu_x;
    this->mu_y = material.mu_y;
    this->LamType = material.LamType;
    this->LamFill = material.LamFill;
    this->Theta_m = material.Theta_m;
    this->H_c = material.H_c;
    this->Cduct = material.Cduct;
    this->Lam_d = material.Lam_d;
    this->Theta_hn = material.Theta_hn;
    this->Theta_hx = material.Theta_hx;
    this->Theta_hy = material.Theta_hy;
    this->NStrands = material.NStrands;
    this->WireD = material.WireD;
    this->Jsrc.im = material.Jsrc.im;
    this->Jsrc.re = material.Jsrc.re;

    this->BHpoints = material.BHpoints;
    if(this->BHpoints > 0){
        this->BHdata=static_cast<CComplex *>(calloc(this->BHpoints,sizeof(CComplex)));
        memcpy(this->BHdata,material.BHdata,this->BHpoints*sizeof(CComplex));
    }
    return *this;
}

void CMaterialProp::StripBHData(QString &b, QString &h)
{
//    int i,k;
//    char *buff,*nptr,*endptr;
//    double z;
//    CArray <double, double> B;
//    CArray <double, double> H;

//    if (BHpoints>0) free(BHdata);
//    B.RemoveAll();
//    H.RemoveAll();

//    k=b.GetLength()+10;
//    buff=(char *)calloc(k,sizeof(char));
//    strcpy(buff,b);
//    nptr=buff;
//    while (sscanf(nptr,"%lf",&z)!=EOF){
//        z=strtod(nptr,&endptr );
//        if(nptr==endptr) nptr++; //catch special case
//        else nptr=endptr;
//        if(B.GetSize()>0){ // enforce monotonicity
//            if (z<=B[B.GetSize()-1])
//                break;
//        }
//        else if(z!=0) B.Add(0);
//        B.Add(z);
//    }
//    free(buff);

//    k=h.GetLength()+10;
//    buff=(char *)calloc(k,sizeof(char));
//    strcpy(buff,h);
//    nptr=buff;
//    while (sscanf(nptr,"%lf",&z)!=EOF){
//        z=strtod(nptr,&endptr );
//        if(nptr==endptr) nptr++;
//        else nptr=endptr;
//        if(H.GetSize()>0){
//            if (z<=H[H.GetSize()-1])
//                break;
//        }
//        else if(z!=0) H.Add(0);
//        H.Add(z);
//    }

//    k=B.GetSize();
//    if (H.GetSize()<k) k=H.GetSize();

//    if (k>1){
//        BHpoints=k;
//        {
//            BHdata=(CComplex *)calloc(k,sizeof(CComplex));
//            for(i=0;i<k;i++) BHdata[i].Set(B[i],H[i]);
//        }
//    }
//    else BHpoints=0;
//    free(buff);

    return;
}

void CMaterialProp::BHDataToCString(QString &b, QString &h)
{
//    int i;
//    char c[80];

//    b.Empty();
//    h.Empty();

//    for(i=0;i<BHpoints;i++){
//        sprintf(c,"%f%c%c",BHdata[i].re,0x0D,0x0A);
//        b+=c;
//        sprintf(c,"%f%c%c",BHdata[i].im,0x0D,0x0A);
//        h+=c;
//    }

//    b.AnsiToOem();
    //    h.AnsiToOem();
}

void CMaterialProp::GetBHProps(double B, double &v, double &dv)
{

}

double CMaterialProp::getCond(double T)
{
    double dCond;
    double dT;
    double k;
    for(int i = 0; i < h_nonlpoints - 1; ++i){
        if(T > h_nonldata[i].Im()){
            dCond = h_nonldata[i+1].Re() - h_nonldata[i].Re();
            dT = h_nonldata[i+1].Im() - h_nonldata[i].Im();
            k = dCond/dT;
            return h_nonldata[i].Re() + k*(T - h_nonldata[i].Im());
        }
    }
    dCond = h_nonldata[h_nonlpoints - 1].Re() - h_nonldata[h_nonlpoints - 2].Re();
    dT = h_nonldata[h_nonlpoints - 1].Im() - h_nonldata[h_nonlpoints - 2].Im();
    k = dCond/dT;
    return h_nonldata[h_nonlpoints - 1].Re() + k*(T - h_nonldata[h_nonlpoints - 1].Im());
}

double CMaterialProp::getdConddT(double T)
{
    /** 分段线性插值 **/
    double dCond;
    double dT;
    for(int i = 0; i < h_nonlpoints - 1; ++i){
        if(T > h_nonldata[i].Im()){
            dCond = h_nonldata[i+1].Re() - h_nonldata[i].Re();
            dT = h_nonldata[i+1].Im() - h_nonldata[i].Im();
            return dCond/dT;
        }
    }
    dCond = h_nonldata[h_nonlpoints - 1].Re() - h_nonldata[h_nonlpoints - 2].Re();
    dT = h_nonldata[h_nonlpoints - 1].Im() - h_nonldata[h_nonlpoints - 2].Im();
    return dCond/dT;
}

