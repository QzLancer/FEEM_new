#ifndef PF_MATERIAL_H
#define PF_MATERIAL_H

#include "material_global.h"

#include <QString>

#define PI 3.141592653589793238462643383
#define SmallNo 1.e-14
#define DEG 0.01745329251994329576923690768

class FEEM_MATERIAL_EXPORT PF_Material
{
public:
    PF_Material();
};
class FEEM_MATERIAL_EXPORT CComplex{
public:
    double im;
    double re;
    // member functions
    CComplex();
    CComplex(double x);
    CComplex(int x);
    CComplex(double x, double y);
    CComplex Sqrt();
    CComplex Conj();
    CComplex Inv();
    void Set(double x, double y);
    double Abs();
    double Arg();
    double Re();
    double Im();
    char* ToString(char *s);
    char* ToStringAlt(char *s);

//operator redefinition
    //Addition
    CComplex operator+( const CComplex& z );
    CComplex operator+(double z);
    CComplex operator+(int z);
    friend CComplex operator+( int x,  const CComplex& y );
    friend CComplex operator+( double x,  const CComplex& y );
    friend CComplex operator+( const CComplex& x,  const CComplex& y );
    void operator+=( const CComplex& z);
    void operator+=(double z);
    void operator+=(int z);

    //Subtraction
    CComplex operator-();
    CComplex operator-( const CComplex& z );
    CComplex operator-(double z);
    CComplex operator-(int z);
    friend CComplex operator-( int x,  const CComplex& y );
    friend CComplex operator-( double x,  const CComplex& y );
    friend CComplex operator-( const CComplex& x,  const CComplex& y );
    friend CComplex operator-( const CComplex& x );
    void operator-=( const CComplex& z);
    void operator-=(double z);
    void operator-=(int z);

    //Multiplication
    CComplex operator*( const CComplex& z );
    CComplex operator*(double z);
    CComplex operator*(int z);
    friend CComplex operator*( int x,  const CComplex& y );
    friend CComplex operator*( double x,  const CComplex& y );
    friend CComplex operator*( const CComplex& x,  const CComplex& y );
    void operator*=( const CComplex& z);
    void operator*=(double z);
    void operator*=(int z);

    //Division
    CComplex operator/( const CComplex& z );
    CComplex operator/(double z);
    CComplex operator/(int z);
    friend CComplex operator/( int x,  const CComplex& y );
    friend CComplex operator/( double x,  const CComplex& y );
    friend CComplex operator/( const CComplex &x,  const CComplex& y );
    void operator/=( const CComplex& z);
    void operator/=(double z);
    void operator/=(int z);

    //Equals
    void operator=(double z);
    void operator=(int z);

    //Tests
    bool operator==( const CComplex& z);
    bool operator==(double z);
    bool operator==(int z);

    bool operator!=( const CComplex& z);
    bool operator!=(double z);
    bool operator!=(int z);

    bool operator<( const CComplex& z);
    bool operator<( double z);
    bool operator<( int z);

    bool operator<=( const CComplex& z);
    bool operator<=( double z);
    bool operator<=( int z);

    bool operator>( const CComplex& z);
    bool operator>( double z);
    bool operator>( int z);

    bool operator>=( const CComplex& z);
    bool operator>=( double z);
    bool operator>=( int z);


private:
};
// useful functions...
#define I CComplex(0,1)
double FEEM_MATERIAL_EXPORT Re( const CComplex& a);
double Im( const CComplex& a);
double abs( const CComplex& x );
double arg( const CComplex& x );
CComplex conj( const CComplex& x);
CComplex exp( const CComplex& x );
CComplex sqrt( const CComplex& x );
CComplex tanh( const CComplex& x );
CComplex sinh( const CComplex& x );
CComplex cosh( const CComplex& x );
CComplex cos( const CComplex& x );
CComplex acos( const CComplex& x );
CComplex sin( const CComplex& x );
CComplex asin( const CComplex& x );
CComplex tan( const CComplex& x );
CComplex atan( const CComplex& x );
CComplex log( const CComplex& x );
CComplex pow( const CComplex& x, int y);
CComplex pow( const CComplex& x, double y);
CComplex pow( const CComplex& x,  const CComplex& y);

class FEEM_MATERIAL_EXPORT CMaterialProp
{
public:

    CMaterialProp();
    CMaterialProp(const CMaterialProp & material);
//    ~CMaterialProp();

    CMaterialProp& operator = (const CMaterialProp & material);

    void StripBHData(QString &b, QString &h);
    void BHDataToCString(QString &b, QString &h);

    void GetSlopes();
    void GetSlopes(double omega);
    CComplex GetH(double B);
    CComplex GetdHdB(double B);
    CComplex Get_dvB2(double B);
    CComplex Get_v(double B);
    void GetBHProps(double B, CComplex &v, CComplex &dv);
    void GetBHProps(double B, double &v, double &dv);
    CComplex LaminatedBH(double omega, int i);

    double getCond(double T);
    double getdConddT(double T);

public:
    QString BlockName;
    double mu_x,mu_y;		// permeabilities, relative

    int    BHpoints;		// number of B-H datapoints;
    CComplex *BHdata;		    // array of B-H pairs;

    int    LamType;			// flag that tells how block is laminated;
    //	0 = not laminated or laminated in plane;
    //  1 = laminated in the x-direction;
    //  2 = laminated in the y-direction;
    double LamFill;			// lamination fill factor, dimensionless;
    double Theta_m;			// direction of the magnetization, degrees
    double H_c;				// magnetization, A/m
    CComplex Jsrc;			// applied current density, MA/m^2
    double Cduct;		    // conductivity of the material, MS/m
    double Lam_d;			// lamination thickness, mm
    double Theta_hn;		// max hysteresis angle, degrees, for nonlinear problems
    double Theta_hx;		// hysteresis angle, degrees, x-directionS
    double Theta_hy;		// and y-direction, for anisotropic linear problems.
    int    NStrands;		// number of strands per wire
    double WireD;			// strand diameter, mm
    bool m_linear;

    /** 温度场相关参数 **/
    bool h_condlinear = true;      //线性or非线性
    bool h_sourcetype = 0;
    double h_lambdax = 0;   //x方向热导率
    double h_lambday = 0;   //y方向热导率
    double h_source = 0;    //内热源强度

    int h_nonlpoints = 0;   //非线性采样点数目
    CComplex *h_nonldata = nullptr; //非线性采样点
};

#endif // PF_MATERIAL_H
