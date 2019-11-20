#include "pf_material.h"

#include <stdio.h>
#include <QDebug>

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

{
    Jsrc.im=0;
    Jsrc.re=0.;
}

CMaterialProp::~CMaterialProp()
{
//    qDebug()<<Q_FUNC_INFO;
    if(BHpoints>0) free(BHdata);
}

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
        this->BHdata=(CComplex *)calloc(this->BHpoints,sizeof(CComplex));
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

