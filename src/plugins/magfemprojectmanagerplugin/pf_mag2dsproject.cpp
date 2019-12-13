#include "pf_mag2dsproject.h"
#include "pf_magfemnode.h"
#include "pf_facesettingdialog.h"

#include "sparsefemm.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include <project/pf_node.h>
#include <project/pf_projecttree.h>

#include <CAD/geometry2d.h>
#include <CAD/entity/pf_document.h>
#include <CAD/pf.h>

#include <coreplugin/geometrymanager/geometrymanager.h>
#include <coreplugin/geometrymanager/igeometry.h>
#include <coreplugin/icore.h>

#include <mesh/meshfemm.h>

#include <material/materialplugin.h>
#include <material/pf_magmaterialdialog.h>

#include <output/outputpluginplugin.h>

#include <QString>
#include <QHash>
#include <QDebug>
#include <QDialog>

using namespace ProjectExplorer;

namespace MagFEMProjectManagerPlugin {

PF_Mag2DSProject::PF_Mag2DSProject()
{
    //    m_materialList.push_back(CMaterialProp());
    //    m_materialList.push_back(CMaterialProp());
    //    m_materialList.push_back(CMaterialProp());
    //    m_materialList.push_back(CMaterialProp());

    //    m_variables.add("length",1);
    //    m_variables.add("length1",1);
    //    m_variables.add("length2",1);
    //    m_variables.add("length3",1);
    setRootProjectNode(PF_Mag2DSNodeTreeBuilder::buildTree(this));

    connect(this,&PF_Mag2DSProject::dataChanged,this,&PF_Mag2DSProject::updateData);
    /** 检测cad的变化 **/
    connect(m_document,&PF_Document::EntityChanged,this,&PF_Mag2DSProject::updateData);
}

PF_Mag2DSProject::~PF_Mag2DSProject()
{
    setRootProjectNode(nullptr);
}

void PF_Mag2DSProject::updateData()
{
    setRootProjectNode(PF_Mag2DSNodeTreeBuilder::buildTree(this));
}

/**
 * @brief
 *
 * @return bool
 */
bool PF_Mag2DSProject::Cuthill()
{
//    auto meshele = m_mesh->eles;
//    auto meshnode = m_mesh->nodes;
//    auto NumNodes = m_mesh->numNode;
//    auto NumEls = m_mesh->numEle;

//    FILE *fp;
//    int i,j,k,n0,n1,n;
//    int newwide,*newnum,**ocon;
//    int  *numcon,*nxtnum;
//    CNode swap;
//    char infile[256];

//    // allocate storage
//    nxtnum=static_cast<int *>(calloc(NumNodes,sizeof(int)));
//    newnum=static_cast<int *>(calloc(NumNodes,sizeof(int)));
//    numcon=static_cast<int *>(calloc(NumNodes,sizeof(int)));
//    ocon=static_cast<int **>(calloc(NumNodes,sizeof(int *)));
//    // initialize node array;
//    for(i=0;i<NumNodes;i++)	newnum[i]= -1;

//    // read in connectivity from nodefile
//    sprintf(infile,"%s.edge",PathName);
//    if((fp=fopen(infile,"rt"))==nullptr)
//    {
//        //        MsgBox("Couldn't open %s",infile);
//        return false;
//    }
//    fscanf(fp,"%i",&k);	// read in number of lines
//    fscanf(fp,"%i",&j);	// read in boundarymarker flag;

//    // allocate space for connections;
//    ocon[0]=static_cast<int *>(calloc(2*k,sizeof(int)));

//    // with first pass, figure out how many connections
//    // there are for each node;
//    for(i=0;i<k;i++)
//    {
//        fscanf(fp,"%i",&j);
//        fscanf(fp,"%i",&n0);
//        fscanf(fp,"%i",&n1);
//        fscanf(fp,"%i",&j);

//        numcon[n0]++;
//        numcon[n1]++;
//    }

//    // mete out connection storage space;
//    for(i=1,n=0;i<NumNodes;i++)
//    {
//        n+=numcon[i-1];
//        ocon[i]=ocon[0]+n;
//    }

//    // on second pass through file, store connections;
//    rewind(fp);
//    fscanf(fp,"%li",&k);	// read in number of lines
//    fscanf(fp,"%li",&j);	// read in boundarymarker flag;
//    for(i=0;i<k;i++)
//    {
//        fscanf(fp,"%i",&j);
//        fscanf(fp,"%i",&n0);
//        fscanf(fp,"%i",&n1);
//        fscanf(fp,"%i",&j);

//        ocon[n0][nxtnum[n0]]=n1; nxtnum[n0]++;
//        ocon[n1][nxtnum[n1]]=n0; nxtnum[n1]++;
//    }
//    fclose(fp);
//    //DeleteFile(infile);

//    // sort connections in order of increasing connectivity;
//    // I'm lazy, so I'm doing a bubble sort;
//    for(n0=0;n0<NumNodes;n0++)
//    {
//        for(i=1;i<numcon[n0];i++)
//            for(j=1;j<numcon[n0];j++)
//                if(numcon[ocon[n0][j]]<numcon[ocon[n0][j-1]])
//                {
//                    n1=ocon[n0][j];
//                    ocon[n0][j]=ocon[n0][j-1];
//                    ocon[n0][j-1]=n1;
//                }
//    }


//    // search for a node to start with;
//    j=numcon[0]; n0=0;
//    for(i=1;i<NumNodes;i++){
//        if(numcon[i]<j){
//            j=numcon[i];
//            n0=i;
//        }
//        if(j==2) i=k;	// break out if j==2,
//        // because this is the best we can do
//    }

//    // do renumbering algorithm;
//    for(i=0;i<NumNodes;i++) nxtnum[i]=-1;
//    newnum[n0]=0; n=1; nxtnum[0]=n0;

//    do{
//        // renumber in order of increasing number of connections;

//        for(i=0;i<numcon[n0];i++)
//        {
//            if (newnum[ocon[n0][i]]<0)
//            {
//                newnum[ocon[n0][i]]=n;
//                nxtnum[n]=ocon[n0][i];
//                n++;
//            }
//        }

//        // need to catch case in which problem is multiply
//        // connected and still renumber right.
//        if(nxtnum[newnum[n0]+1]<0){
//            //	AfxMessageBox("Multiply Connected!");
//            //	exit(0);

//            // first, get a node that hasn't been visited yet;
//            for(i=0;i<NumNodes;i++)
//                if(newnum[i]<0){
//                    j=numcon[i];
//                    n0=i;
//                    i=NumNodes;
//                }


//            // now, get a new starting node;
//            for(i=0;i<NumNodes;i++)
//            {
//                if((newnum[i]<0) && (numcon[i]<j))
//                {
//                    j=numcon[i];
//                    n0=i;
//                }
//                if(j==2) i=NumNodes;	// break out if j==2,
//                // because this is the
//                // best we can do
//            }

//            // now, set things to restart;
//            newnum[n0]=n;
//            nxtnum[n]=n0;
//            n++;
//        }
//        else n0=nxtnum[newnum[n0]+1];


//    } while(n<NumNodes);

//    // remap connectivities;
//    for(i=0;i<NumNodes;i++)
//        for(j=0;j<numcon[i];j++)
//            ocon[i][j]=newnum[ocon[i][j]];

//    // remap (anti)periodic boundary points
//    for(i=0;i<NumPBCs;i++)
//    {
//        pbclist[i].x=newnum[pbclist[i].x];
//        pbclist[i].y=newnum[pbclist[i].y];
//    }

//    // find new bandwidth;

//    // PBCs fuck up the banding, som could have to do
//    // something like:
//    // if(NumPBCs!=0) BandWidth=0;
//    // else{
//    // but if we apply the PCBs the last thing before the
//    // solver is called, we can take advantage of banding
//    // speed optimizations without messing things up.
//    for(n0=0,newwide=0;n0<NumNodes;n0++)
//    {
//        for(i=0;i<numcon[n0];i++)
//            if(abs(newnum[n0]-ocon[n0][i])>newwide)
//            {
//                newwide=abs(newnum[n0]-ocon[n0][i]);
//            }
//    }

//    BandWidth=newwide+1;
//    // }

//    // free up the variables that we needed during the routine....
//    free(numcon);
//    free(nxtnum);
//    free(ocon[0]);
//    free(ocon);

//    // new mapping remains in newnum;
//    // apply this mapping to elements first.
//    for(i=0;i<NumEls;i++)
//        for(j=0;j<3;j++)
//            meshele[i].n[j]=newnum[meshele[i].n[j]];

//    // now, sort nodes based on newnum;
//    for(i=0;i<NumNodes;i++)
//        while(newnum[i]!=i)
//        {
//            j=newnum[i];
//            n=newnum[j]; newnum[j]=newnum[i]; newnum[i]=n;
//            swap=meshnode[j]; meshnode[j]=meshnode[i]; meshnode[i]=swap;
//        }

//    free(newnum);
//    SortElements();
    return true;
}

bool PF_Mag2DSProject::SortElements()
{
//    auto meshele = m_mesh->eles;
//    auto meshnode = m_mesh->nodes;
//    auto NumNodes = m_mesh->numNode;
//    auto NumEls = m_mesh->numEle;

//    // Comb Sort -- see http://en.wikipedia.org/wiki/Comb_sort
//    int *Score;
//    int i,j,k,gap;
//    CElement e;

//    Score=(int*)calloc(NumEls,sizeof(int));

//    for(k=0;k<NumEls;k++)
//    {
//        Score[k]=meshele[k].p[0]+meshele[k].p[1]+meshele[k].p[2];
//    }

//    gap = NumEls;

//    do{
//        //update the gap value for a next comb
//        if (gap > 1)
//        {
//            gap=(gap*10)/13;
//            if ((gap==10) || (gap==9)) gap=11;
//        }

//        //a single "comb" over the input list
//        for(j=0,i=0;(j+gap)<NumEls;j++)
//        {
//            if (Score[j]>Score[j+gap])
//            {
//                k=j+gap;
//                i=Score[k];
//                Score[k]=Score[j];
//                Score[j]=i;
//                e=meshele[k];
//                meshele[k]=meshele[j];
//                meshele[j]=e;
//                i=1;
//            }
//        }
//    }while((gap>1)&&(i>0));


//    free(Score);
    return true;
}

/*!
 \brief 二维静磁场求解

 \param L
 \return bool
*/
bool PF_Mag2DSProject::Static2D(CBigLinProb &L)
{
//    auto meshele = m_mesh->eles;
//    auto meshnode = m_mesh->nodes;
//    auto NumNodes = m_mesh->numNode;
//    auto NumEls = m_mesh->numEle;

//    int i, j, k, w, s, sdi_iter, sdin;
//    double Me[3][3], be[3];		// element matrices;
//    double Mx[3][3], My[3][3], Mn[3][3];
//    double l[3], p[3], q[3];		// element shape parameters;
//    int n[3];					// numbers of nodes for a particular element;
//    double a, K, r, t, x, y, B, B1, B2, mu, v[3], u[3], dv, res, lastres, Cduct;
//    double *V_old, *V_sdi, *CircInt1, *CircInt2, *CircInt3;
//    double c = PI*4.e-05;
//    double units[] = { 2.54, 0.1, 1., 100., 0.00254, 1.e-04 };
//    int Iter = 0, pctr;
//    bool LinearFlag = true;
//    bool SDIflag = false;
//    res = 0;
//    CElement *El;
//    V_old = static_cast<double *>(calloc(NumNodes, sizeof(double)));

//    //    for (i = 0; i < NumBlockLabels; i++) GetFillFactor(i);

//    // check to see if there are any SDI boundaries...
//    // lineproplist[ meshele[i].e[j] ].BdryFormat==0
//    //    for (i = 0; i < NumLineProps; i++)
//    //        if (lineproplist[i].BdryFormat == 3) SDIflag = true;

//    //    if (SDIflag == true) {
//    //        // there is an SDI boundary defined; check to see if it is in use
//    //        SDIflag = false;
//    //        for (i = 0; i < NumEls; i++)
//    //            for (j = 0; j < 3; j++)
//    //                if (lineproplist[meshele[i].e[j]].BdryFormat == 3) {
//    //                    SDIflag = true;
//    //                    printf("Problem has SDI boundaries\n");
//    //                    i = NumEls;
//    //                    j = 3;
//    //                }
//    //    }

//    //    if (SDIflag == true) {
//    //        V_sdi = static_cast<double *>(calloc(NumNodes, sizeof(double)));
//    //        sdin = 2;
//    //    } else sdin = 1;

//    // check to see if any circuits have been defined and process them;
//    //    if (NumCircProps > 0) {
//    //        CircInt1 = static_cast<double *>(calloc(NumCircProps, sizeof(double)));
//    //        CircInt2 = static_cast<double *>(calloc(NumCircProps, sizeof(double)));
//    //        CircInt3 = static_cast<double *>(calloc(NumCircProps, sizeof(double)));
//    //        for (i = 0; i < NumEls; i++) {
//    //            if (meshele[i].lbl >= 0)
//    //                if (labellist[meshele[i].lbl].InCircuit != -1) {
//    //                    El = &meshele[i];
//    //                    // get element area;
//    //                    for (k = 0; k < 3; k++) n[k] = El->p[k];
//    //                    p[0] = meshnode[n[1]].y - meshnode[n[2]].y;
//    //                    p[1] = meshnode[n[2]].y - meshnode[n[0]].y;
//    //                    p[2] = meshnode[n[0]].y - meshnode[n[1]].y;
//    //                    q[0] = meshnode[n[2]].x - meshnode[n[1]].x;
//    //                    q[1] = meshnode[n[0]].x - meshnode[n[2]].x;
//    //                    q[2] = meshnode[n[1]].x - meshnode[n[0]].x;
//    //                    a = (p[0] * q[1] - p[1] * q[0]) / 2.;
//    //                    //	r=(meshnode[n[0]].x+meshnode[n[1]].x+meshnode[n[2]].x)/3.;

//    //                    // if coils are wound, they act like they have
//    //                    // a zero "bulk" conductivity...
//    //                    Cduct = blockproplist[El->blk].Cduct;
//    //                    if (labellist[El->lbl].bIsWound) Cduct = 0;

//    //                    // evaluate integrals;
//    //                    CircInt1[labellist[El->lbl].InCircuit] += a;
//    //                    CircInt2[labellist[El->lbl].InCircuit] +=
//    //                            a*Cduct;
//    //                    CircInt3[labellist[El->lbl].InCircuit] +=
//    //                            blockproplist[El->blk].Jr*a*100.;
//    //                }
//    //        }

//    //        for (i = 0; i < NumCircProps; i++) {
//    //            // Case 0 :: voltage gradient is applied to the region;
//    //            // Case 1 :: flat current density is applied to the region;
//    //            if (circproplist[i].CircType == 0) {
//    //                if (CircInt2[i] == 0) {
//    //                    circproplist[i].Case = 1;
//    //                    if (CircInt1[i] == 0.)
//    //                        circproplist[i].J = 0.;
//    //                    else
//    //                        circproplist[i].J = 0.01*(circproplist[i].Amps_re -
//    //                                                   CircInt3[i]) / CircInt1[i];
//    //                } else {
//    //                    circproplist[i].Case = 0;
//    //                    circproplist[i].dV = -0.01*(circproplist[i].Amps_re -
//    //                                                CircInt3[i]) / CircInt2[i];
//    //                }
//    //            } else {
//    //                circproplist[i].Case = 0;
//    //                circproplist[i].dV = circproplist[i].dVolts_re;
//    //            }
//    //        }
//    //    }

//    do {
//        pctr = 0;
//        if (Iter > 0) L.Wipe();
//        /** 单元计算 **/
//        for (i = 0; i < NumEls; i++) {
//            j = (i * 20) / NumEls + 1;
//            if (j > pctr) {
//                j = pctr * 5;
//                if (j > 100) j = 100;
//                pctr++;
//            }
//            /** 初始化单元矩阵 **/
//            for (j = 0; j < 3; j++) {
//                for (k = 0; k < 3; k++) {
//                    Me[j][k] = 0.;
//                    Mx[j][k] = 0.;
//                    My[j][k] = 0.;
//                    Mn[j][k] = 0.;
//                }
//                be[j] = 0.;
//            }
//            /** 计算形函数 **/
//            El = &meshele[i];
//            for (k = 0; k < 3; k++) n[k] = El->n[k];
//            p[0] = meshnode[n[1]].y - meshnode[n[2]].y;
//            p[1] = meshnode[n[2]].y - meshnode[n[0]].y;
//            p[2] = meshnode[n[0]].y - meshnode[n[1]].y;
//            q[0] = meshnode[n[2]].x - meshnode[n[1]].x;
//            q[1] = meshnode[n[0]].x - meshnode[n[2]].x;
//            q[2] = meshnode[n[1]].x - meshnode[n[0]].x;
//            /** 计算单元棱长 **/
//            for (j = 0, k = 1; j < 3; k++, j++) {
//                if (k == 3) k = 0;
//                l[j] = sqrt(pow(meshnode[n[k]].x - meshnode[n[j]].x, 2.) +
//                        pow(meshnode[n[k]].y - meshnode[n[j]].y, 2.));
//            }
//            a = (p[0] * q[1] - p[1] * q[0]) / 2.;
//            r = (meshnode[n[0]].x + meshnode[n[1]].x + meshnode[n[2]].x) / 3.;

//            /** x方向的贡献 **/
//            K = (-1. / (4.*a));
//            for (j = 0; j < 3; j++)
//                for (k = j; k < 3; k++) {
//                    Mx[j][k] += K*p[j] * p[k];
//                    if (j != k) Mx[k][j] += K*p[j] * p[k];
//                }
//            /** y方向的贡献 **/
//            K = (-1. / (4.*a));
//            for (j = 0; j < 3; j++){
//                for (k = j; k < 3; k++) {
//                    My[j][k] += K*q[j] * q[k];
//                    if (j != k) My[k][j] += K*q[j] * q[k];
//                }
//            }

//            /** 电流密度 **/
//            for (j = 0; j < 3; j++) {
//                K = -(blockproplist[El->blk].Jr)*a / 3.;
//                be[j] += K;
//            }
//            /** 永磁 **/
//            t = labellist[El->lbl].MagDir;
//            if (labellist[El->lbl].MagDirFctn != nullptr) // functional magnetization direction
//            {
//                CString str;
//                CComplex X;
//                int top1, top2, lua_error_code;
//                for (j = 0, X = 0; j < 3; j++) X += (meshnode[n[j]].x + I*meshnode[n[j]].y);
//                X = X / units[LengthUnits] / 3.;
//                str.Format("x=%.17g\ny=%.17g\nr=x\nz=y\ntheta=%.17g\nR=%.17g\nreturn %s",
//                           X.re, X.im, arg(X) * 180 / PI, abs(X), labellist[El->lbl].MagDirFctn);
//                top1 = lua_gettop(lua);
//                if ((lua_error_code = lua_dostring(lua, str)) != 0) {
//                    MsgBox("Lua error evaluating \"%s\"", labellist[El->lbl].MagDirFctn);
//                    exit(7);
//                }
//                top2 = lua_gettop(lua);
//                if (top2 != top1) {
//                    str = lua_tostring(lua, -1);
//                    if (str.GetLength() == 0) {
//                        //                            MsgBox("\"%s\" does not evaluate to a numerical value",
//                        //                                   labellist[El->lbl].MagDirFctn);
//                        exit(7);
//                    } else t = Re(lua_tonumber(lua, -1));
//                    lua_pop(lua, 1);
//                }
//            }
//            for (j = 0; j < 3; j++) {
//                k = j + 1; if (k == 3) k = 0;
//                // need to scale so that everything is in proper units...
//                // conversion is 0.0001
//                K = 0.0001*blockproplist[El->blk].H_c*(
//                            cos(t*PI / 180.)*(meshnode[n[k]].x - meshnode[n[j]].x) +
//                        sin(t*PI / 180.)*(meshnode[n[k]].y - meshnode[n[j]].y)) / 2.;
//                be[j] += K;
//                be[k] += K;
//            }
//            /** 更新非线性单元 **/
//            if (Iter == 0) {
//                k = meshele[i].blk;
//                if (blockproplist[k].BHpoints != 0) LinearFlag = false;
//                if (blockproplist[k].LamType == 0) {
//                    t = blockproplist[k].LamFill;
//                    meshele[i].mu1 = blockproplist[k].mu_x*t + (1. - t);
//                    meshele[i].mu2 = blockproplist[k].mu_y*t + (1. - t);
//                }
//                if (blockproplist[k].LamType == 1) {
//                    t = blockproplist[k].LamFill;
//                    mu = blockproplist[k].mu_x;
//                    meshele[i].mu1 = mu*t + (1. - t);
//                    meshele[i].mu2 = mu / (t + mu*(1. - t));
//                }
//                if (blockproplist[k].LamType == 2) {
//                    t = blockproplist[k].LamFill;
//                    mu = blockproplist[k].mu_y;
//                    meshele[i].mu2 = mu*t + (1. - t);
//                    meshele[i].mu1 = mu / (t + mu*(1. - t));
//                }
//                if (blockproplist[k].LamType > 2) {
//                    meshele[i].mu1 = 1;
//                    meshele[i].mu2 = 1;
//                }
//            } else {
//                k = meshele[i].blk;

//                if ((blockproplist[k].LamType == 0) &&
//                        (meshele[i].mu1 == meshele[i].mu2)
//                        && (blockproplist[k].BHpoints > 0)) {
//                    for (j = 0, B1 = 0., B2 = 0.; j < 3; j++) {
//                        B1 += L.V[n[j]] * q[j];
//                        B2 += L.V[n[j]] * p[j];
//                    }
//                    B = c*sqrt(B1*B1 + B2*B2) / (0.02*a);
//                    // correction for lengths in cm of 1/0.02

//                    // find out new mu from saturation curve;
//                    blockproplist[k].GetBHProps(B, mu, dv);
//                    mu = 1. / (muo*mu);
//                    meshele[i].mu1 = mu;
//                    meshele[i].mu2 = mu;
//                    for (j = 0; j < 3; j++) {
//                        for (w = 0, v[j] = 0; w < 3; w++)
//                            v[j] += (Mx[j][w] + My[j][w])*L.V[n[w]];
//                    }
//                    K = -200.*c*c*c*dv / a;
//                    for (j = 0; j < 3; j++)
//                        for (w = 0; w < 3; w++)
//                            Mn[j][w] = K*v[j] * v[w];
//                }

//                if ((blockproplist[k].LamType == 1) && (blockproplist[k].BHpoints>0)) {
//                    t = blockproplist[k].LamFill;
//                    for (j = 0, B1 = 0., B2 = 0.; j < 3; j++) {
//                        B1 += L.V[n[j]] * q[j];
//                        B2 += L.V[n[j]] * p[j] / t;
//                    }
//                    B = c*sqrt(B1*B1 + B2*B2) / (0.02*a);
//                    blockproplist[k].GetBHProps(B, mu, dv);
//                    mu = 1. / (muo*mu);
//                    meshele[i].mu1 = mu*t;
//                    meshele[i].mu2 = mu / (t + mu*(1. - t));
//                    for (j = 0; j < 3; j++) {
//                        for (w = 0, v[j] = 0, u[j] = 0; w < 3; w++) {
//                            v[j] += (My[j][w] / t + Mx[j][w])*L.V[n[w]];
//                            u[j] += (My[j][w] / t + t*Mx[j][w])*L.V[n[w]];
//                        }
//                    }
//                    K = -100.*c*c*c*dv / (a);
//                    for (j = 0; j < 3; j++)
//                        for (w = 0; w < 3; w++)
//                            Mn[j][w] = K*(v[j] * u[w] + v[w] * u[j]);
//                }
//                if ((blockproplist[k].LamType == 2) && (blockproplist[k].BHpoints>0)) {
//                    t = blockproplist[k].LamFill;
//                    for (j = 0, B1 = 0., B2 = 0.; j < 3; j++) {
//                        B1 += (L.V[n[j]] * q[j]) / t;
//                        B2 += L.V[n[j]] * p[j];
//                    }
//                    B = c*sqrt(B1*B1 + B2*B2) / (0.02*a);
//                    blockproplist[k].GetBHProps(B, mu, dv);
//                    mu = 1. / (muo*mu);
//                    meshele[i].mu2 = mu*t;
//                    meshele[i].mu1 = mu / (t + mu*(1. - t));
//                    for (j = 0; j < 3; j++) {
//                        for (w = 0, v[j] = 0, u[j] = 0; w < 3; w++) {
//                            v[j] += (Mx[j][w] / t + My[j][w])*L.V[n[w]];
//                            u[j] += (Mx[j][w] / t + t*My[j][w])*L.V[n[w]];
//                        }
//                    }
//                    K = -100.*c*c*c*dv / (a);
//                    for (j = 0; j < 3; j++)
//                        for (w = 0; w < 3; w++)
//                            Mn[j][w] = K*(v[j] * u[w] + v[w] * u[j]);
//                }
//            }
//            /** 装配大矩阵 **/
//            for (j = 0; j < 3; j++)
//                for (k = 0; k < 3; k++) {
//                    Me[j][k] += (Mx[j][k] / Re(El->mu2) + My[j][k] / Re(El->mu1) + Mn[j][k]);
//                    be[j] += Mn[j][k] * L.V[n[k]];
//                }
//            for (j = 0; j < 3; j++) {
//                for (k = j; k < 3; k++)
//                    L.Put(L.Get(n[j], n[k]) - Me[j][k], n[j], n[k]);
//                L.b[n[j]] -= be[j];
//            }
//        }//end Elments iteration
//        // add in contribution from point currents;
//        //            for (i = 0; i < NumNodes; i++)
//        //                if (meshnode[i].bc >= 0)
//        //                    L.b[i] += (0.01*nodeproplist[meshnode[i].bc].Jr);

//        /** 设置固定边界 **/
//        for (i = 0; i < NumNodes; i++)
//            if (meshnode[i].bc >= 0)
//                if ((nodeproplist[meshnode[i].bc].Jr == 0) &&
//                        (nodeproplist[meshnode[i].bc].Ji == 0) && (sdi_iter == 0))
//                    L.SetValue(i, nodeproplist[meshnode[i].bc].Ar / c);

//        /** 施加边界条件 **/
//        for (i = 0; i < NumEls; i++)
//            for (j = 0; j < 3; j++) {
//                k = j + 1; if (k == 3) k = 0;
//                if (meshele[i].e[j] >= 0)
//                    if (lineproplist[meshele[i].e[j]].BdryFormat == 0) {
//                        if (Coords == 0) {
//                            // first point on the side;
//                            x = meshnode[meshele[i].p[j]].x;
//                            y = meshnode[meshele[i].p[j]].y;
//                            x /= units[LengthUnits]; y /= units[LengthUnits];
//                            s = meshele[i].e[j];
//                            a = lineproplist[s].A0 + x*lineproplist[s].A1 +
//                                    y*lineproplist[s].A2;
//                            // just take ``real'' component.
//                            a *= cos(lineproplist[s].phi*DEG);
//                            L.SetValue(meshele[i].p[j], a / c);

//                            // second point on the side;
//                            x = meshnode[meshele[i].p[k]].x;
//                            y = meshnode[meshele[i].p[k]].y;
//                            x /= units[LengthUnits]; y /= units[LengthUnits];
//                            s = meshele[i].e[j];
//                            a = lineproplist[s].A0 + x*lineproplist[s].A1 +
//                                    y*lineproplist[s].A2;
//                            // just take``real'' component.
//                            a *= cos(lineproplist[s].phi*DEG);
//                            L.SetValue(meshele[i].p[k], a / c);
//                        } else {
//                            // first point on the side;
//                            x = meshnode[meshele[i].p[j]].x;
//                            y = meshnode[meshele[i].p[j]].y;
//                            r = sqrt(x*x + y*y);
//                            if ((x == 0) && (y == 0)) t = 0;
//                            else t = atan2(y, x) / DEG;
//                            r /= units[LengthUnits];
//                            s = meshele[i].e[j];
//                            a = lineproplist[s].A0 + r*lineproplist[s].A1 +
//                                    t*lineproplist[s].A2;
//                            a *= cos(lineproplist[s].phi*DEG); // just take ``real'' component.
//                            L.SetValue(meshele[i].p[j], a / c);

//                            // second point on the side;
//                            x = meshnode[meshele[i].p[k]].x;
//                            y = meshnode[meshele[i].p[k]].y;
//                            r = sqrt(x*x + y*y);
//                            if ((x == 0) && (y == 0)) t = 0;
//                            else t = atan2(y, x) / DEG;
//                            r /= units[LengthUnits];
//                            s = meshele[i].e[j];
//                            a = lineproplist[s].A0 + r*lineproplist[s].A1 +
//                                    t*lineproplist[s].A2;
//                            a *= cos(lineproplist[s].phi*DEG); // just take ``real'' component.
//                            L.SetValue(meshele[i].p[k], a / c);
//                        }

//                    }
//            }
//        // Apply SDI boundary condition;
////        if ((SDIflag == true) && (sdi_iter == 1)) for (i = 0; i < NumEls; i++)
////            for (j = 0; j < 3; j++) {
////                k = j + 1; if (k == 3) k = 0;
////                if (meshele[i].e[j] >= 0)
////                    if (lineproplist[meshele[i].e[j]].BdryFormat == 3) {
////                        L.SetValue(meshele[i].p[j], 0.);
////                        L.SetValue(meshele[i].p[k], 0.);
////                    }
////            }
//        // Apply any periodicity/antiperiodicity boundary conditions that we have
//        //            for (k = 0; k < NumPBCs; k++) {
//        //                if (pbclist[k].t == 0) L.Periodicity(pbclist[k].x, pbclist[k].y);
//        //                if (pbclist[k].t == 1) L.AntiPeriodicity(pbclist[k].x, pbclist[k].y);
//        //            }
//        /** 求解 **/
//        if (SDIflag == false) for (j = 0; j < NumNodes; j++)
//            V_old[j] = L.V[j];
//        else {
//            if (sdi_iter == 0)
//                for (j = 0; j < NumNodes; j++) V_sdi[j] = L.V[j];
//            else
//                for (j = 0; j < NumNodes; j++) {
//                    V_old[j] = V_sdi[j];
//                    V_sdi[j] = L.V[j];
//                }
//        }
//        if (L.PCGSolve(Iter + sdi_iter) == false) return false;

//        if (sdi_iter == 1)
//            for (j = 0; j < NumNodes; j++)
//                L.V[j] = (V_sdi[j] + L.V[j]) / 2.;

//        if (LinearFlag == false) {
//            for (j = 0, x = 0, y = 0; j < NumNodes; j++) {
//                x += (L.V[j] - V_old[j])*(L.V[j] - V_old[j]);
//                y += (L.V[j] * L.V[j]);
//            }

//            if (y == 0) LinearFlag = true;
//            else {
//                lastres = res;
//                res = sqrt(x / y);
//            }
//            // relaxation if we need it
//            if (Iter > 5) {
//                if ((res > lastres) && (Relax > 0.125)) Relax /= 2.;
//                else Relax += 0.1 * (1. - Relax);

//                for (j = 0; j < NumNodes; j++) L.V[j] = Relax*L.V[j] + (1.0 - Relax)*V_old[j];
//            }
//            // report some results
//            char outstr[256];
//            sprintf(outstr, "Newton Iteration(%i) Relax=%.4g", Iter, Relax);
//            //            TheView->SetDlgItemText(IDC_FRAME2, outstr);
//            j = (int)(100.*log10(res) / (log10(Precision) + 2.));
//            if (j > 100) j = 100;
//            //            TheView->m_prog2.SetPos(j);
//        }
//        // nonlinear iteration has to have a looser tolerance
//        // than the linear solver--otherwise, things can't ever
//        // converge.  Arbitrarily choose 100*tolerance.
//        if ((res < 100.*Precision) && (Iter>0)) LinearFlag = true;
//        Iter++;
//    } while (LinearFlag == false);

//    for (i = 0; i < NumNodes; i++) L.b[i] = L.V[i] * c; // convert answer to Amps
//    free(V_old);
//    if (SDIflag == true) free(V_sdi);
//    //    if (NumCircProps > 0) {
//    //        free(CircInt1);
//    //        free(CircInt2);
//    //        free(CircInt3);
//    //    }
    return true;
}

bool PF_Mag2DSProject::WriteStatic2D(CBigLinProb &L)
{
    //    // write solution to disk;

    //    char c[1024];
    //    FILE *fp, *fz;
    //    int i, k;
    //    double cf;
    //    double unitconv[] = { 2.54, 0.1, 1., 100., 0.00254, 1.e-04 };

    //    // first, echo input .fem file to the .ans file;
    //    sprintf(c, "%s.fem", PathName);
    //    if ((fz = fopen(c, "rt")) == nullptr) {
    //        //        MsgBox("Couldn't open %s.fem\n", PathName);
    //        return false;
    //    }

    //    sprintf(c, "%s.ans", PathName);
    //    if ((fp = fopen(c, "wt")) == nullptr) {
    //        //        MsgBox("Couldn't write to %s.ans\n", PathName);
    //        return false;
    //    }

    //    while (fgets(c, 1024, fz) != nullptr) fputs(c, fp);
    //    fclose(fz);

    //    // then print out node, line, and element information
    //    fprintf(fp, "[Solution]\n");
    //    cf = unitconv[LengthUnits];
    //    fprintf(fp, "%i\n", NumNodes);
    //    for (i = 0; i < NumNodes; i++)
    //        fprintf(fp, "%.17g	%.17g	%.17g\n", meshnode[i].x / cf,
    //                meshnode[i].y / cf, L.b[i]);
    //    fprintf(fp, "%i\n", NumEls);
    //    for (i = 0; i < NumEls; i++)
    //        fprintf(fp, "%i	%i	%i	%i\n",
    //                meshele[i].p[0], meshele[i].p[1], meshele[i].p[2], meshele[i].lbl);
    //    /*
    //            // print out circuit info
    //            fprintf(fp,"%i\n",NumCircPropsOrig);
    //            for(i=0;i<NumCircPropsOrig;i++){
    //            if (circproplist[i].Case==0)
    //            fprintf(fp,"0	%.17g\n",circproplist[i].dV.Re());
    //            if (circproplist[i].Case==1)
    //            fprintf(fp,"1	%.17g\n",circproplist[i].J.Re());
    //            }
    //            */

    //    // print out circuit info on a blocklabel by blocklabel basis;
    //    fprintf(fp, "%i\n", NumBlockLabels);
    //    for (k = 0; k < NumBlockLabels; k++) {
    //        i = labellist[k].InCircuit;
    //        if (i < 0) // if block not associated with any particular circuit
    //        {
    //            // print out some "dummy" propeties that say that
    //            // there is a fixed additional current density,
    //            // but that that additional current density is zero.
    //            fprintf(fp, "1	0\n");
    //        } else {
    //            if (circproplist[i].Case == 0)
    //                fprintf(fp, "0	%.17g\n", circproplist[i].dV.Re());
    //            if (circproplist[i].Case == 1)
    //                fprintf(fp, "1	%.17g\n", circproplist[i].J.Re());
    //        }
    //    }

    //    fclose(fp);
    return true;
}

bool PF_Mag2DSProject::StaticAxisymmetric(CBigLinProb &L)
{
    //    auto meshele = m_mesh->eles;
    //    auto meshnode = m_mesh->nodes;
    //    auto NumNodes = m_mesh->numNode;

    //    int i, j, k, s, w, sdi_iter, sdin;
    //    double Me[3][3], Mx[3][3], My[3][3], Mn[3][3];
    //    double l[3], p[3], q[3], g[3], be[3], u[3], v[3], res, lastres, dv, vol;
    //    int n[3];					// numbers of nodes for a particular element;
    //    double a, K, r, t, x, y, B, mu, R, rn[3], a_hat, R_hat, Cduct;
    //    double c = PI*4.e-05;
    //    double units[] = { 2.54, 0.1, 1., 100., 0.00254, 1.e-04 };
    //    double *V_old, *V_sdi, *CircInt1, *CircInt2, *CircInt3;;
    //    int flag, Iter = 0, pctr;
    //    bool LinearFlag = true;
    //    bool SDIflag = false;
    //    res = 0;

    //    CElement *El;
    //    V_old = (double *)calloc(NumNodes, sizeof(double));

    //    for (i = 0; i < NumBlockLabels; i++) GetFillFactor(i);

    //    extRo *= units[LengthUnits];
    //    extRi *= units[LengthUnits];
    //    extZo *= units[LengthUnits];

    //    // check to see if any circuits have been defined and process them;
    //    if (NumCircProps > 0) {
    //        CircInt1 = (double *)calloc(NumCircProps, sizeof(double));
    //        CircInt2 = (double *)calloc(NumCircProps, sizeof(double));
    //        CircInt3 = (double *)calloc(NumCircProps, sizeof(double));
    //        for (i = 0; i < NumEls; i++) {
    //            if (meshele[i].lbl >= 0)
    //                if (labellist[meshele[i].lbl].InCircuit != -1) {
    //                    El = &meshele[i];

    //                    // get element area;
    //                    for (k = 0; k < 3; k++) n[k] = El->p[k];
    //                    p[0] = meshnode[n[1]].y - meshnode[n[2]].y;
    //                    p[1] = meshnode[n[2]].y - meshnode[n[0]].y;
    //                    p[2] = meshnode[n[0]].y - meshnode[n[1]].y;
    //                    q[0] = meshnode[n[2]].x - meshnode[n[1]].x;
    //                    q[1] = meshnode[n[0]].x - meshnode[n[2]].x;
    //                    q[2] = meshnode[n[1]].x - meshnode[n[0]].x;
    //                    a = (p[0] * q[1] - p[1] * q[0]) / 2.;
    //                    r = (meshnode[n[0]].x + meshnode[n[1]].x + meshnode[n[2]].x) / 3.;

    //                    // if coils are wound, they act like they have
    //                    // a zero "bulk" conductivity...
    //                    Cduct = blockproplist[El->blk].Cduct;
    //                    if (labellist[El->lbl].bIsWound) Cduct = 0;

    //                    // evaluate integrals;
    //                    CircInt1[labellist[El->lbl].InCircuit] += a;

    //                    CircInt2[labellist[El->lbl].InCircuit] +=
    //                            100.*a*Cduct / r;

    //                    CircInt3[labellist[El->lbl].InCircuit] +=
    //                            blockproplist[El->blk].Jr*a*100.;
    //                }
    //        }

    //        for (i = 0; i < NumCircProps; i++) {
    //            if (circproplist[i].CircType == 0) {
    //                if (CircInt2[i] == 0) {
    //                    circproplist[i].Case = 1;
    //                    if (CircInt1[i] == 0.) circproplist[i].J = 0.;
    //                    else circproplist[i].J = 0.01*(circproplist[i].Amps_re -
    //                                                   CircInt3[i]) / CircInt1[i];
    //                } else {
    //                    circproplist[i].Case = 0;
    //                    circproplist[i].dV = -0.01*(circproplist[i].Amps_re -
    //                                                CircInt3[i]) / CircInt2[i];
    //                }
    //            } else {
    //                circproplist[i].Case = 0;
    //                circproplist[i].dV = circproplist[i].dVolts_re;
    //            }
    //        }
    //    }

    //    // check to see if there are any SDI boundaries...
    //    // lineproplist[ meshele[i].e[j] ].BdryFormat==0
    //    for (i = 0; i < NumLineProps; i++)
    //        if (lineproplist[i].BdryFormat == 3) SDIflag = true;

    //    if (SDIflag == true) {
    //        // there is an SDI boundary defined; check to see if it is in use
    //        SDIflag = false;
    //        for (i = 0; i < NumEls; i++)
    //            for (j = 0; j < 3; j++)
    //                if (lineproplist[meshele[i].e[j]].BdryFormat == 3) {
    //                    SDIflag = true;
    //                    printf("Problem has SDI boundaries\n");
    //                    i = NumEls;
    //                    j = 3;
    //                }
    //    }

    //    if (SDIflag == true) {
    //        V_sdi = (double *)calloc(NumNodes, sizeof(double));
    //        sdin = 2;
    //    } else sdin = 1;

    //    // first, need to define permeability in each block.  In nonlinear
    //    // case, this is sort of a hassle.  Linear permeability is simply
    //    // copied from the associated block definition, but nonlinear
    //    // permeability must be updated from iteration to iteration...

    //    // build element matrices using the matrices derived in Allaire's book.

    //    do {
    //        for (sdi_iter = 0; sdi_iter < sdin; sdi_iter++) {
    //            //            TheView->SetDlgItemText(IDC_FRAME1, "Matrix Construction");
    //            //            TheView->m_prog1.SetPos(0);
    //            pctr = 0;

    //            if (Iter > 0) L.Wipe();

    //            for (i = 0; i < NumEls; i++) {

    //                // update ''building matrix'' progress bar...
    //                j = (i * 20) / NumEls + 1;
    //                if (j > pctr) {
    //                    j = pctr * 5; if (j > 100) j = 100;
    //                    TheView->m_prog1.SetPos(j);
    //                    pctr++;
    //                }

    //                // zero out Me, be;
    //                for (j = 0; j < 3; j++) {
    //                    for (k = 0; k < 3; k++) {
    //                        Me[j][k] = 0.;
    //                        Mx[j][k] = 0;
    //                        My[j][k] = 0;
    //                        Mn[j][k] = 0;
    //                    }
    //                    be[j] = 0.;
    //                }

    //                // Determine shape parameters.
    //                // l == element side lengths;
    //                // p corresponds to the `b' parameter in Allaire
    //                // q corresponds to the `c' parameter in Allaire
    //                El = &meshele[i];	//the i-th element

    //                for (k = 0; k < 3; k++) {
    //                    n[k] = El->p[k];//the points of the i-th element
    //                    rn[k] = meshnode[n[k]].x;//for axisymmtric
    //                }

    //                p[0] = meshnode[n[1]].y - meshnode[n[2]].y;
    //                p[1] = meshnode[n[2]].y - meshnode[n[0]].y;
    //                p[2] = meshnode[n[0]].y - meshnode[n[1]].y;
    //                q[0] = meshnode[n[2]].x - meshnode[n[1]].x;
    //                q[1] = meshnode[n[0]].x - meshnode[n[2]].x;
    //                q[2] = meshnode[n[1]].x - meshnode[n[0]].x;
    //                g[0] = (meshnode[n[2]].x + meshnode[n[1]].x) / 2.;
    //                g[1] = (meshnode[n[0]].x + meshnode[n[2]].x) / 2.;
    //                g[2] = (meshnode[n[1]].x + meshnode[n[0]].x) / 2.;

    //                for (j = 0, k = 1; j < 3; k++, j++) {//the length of the line
    //                    if (k == 3) k = 0;
    //                    l[j] = sqrt(pow(meshnode[n[k]].x - meshnode[n[j]].x, 2.) +
    //                            pow(meshnode[n[k]].y - meshnode[n[j]].y, 2.));
    //                }

    //                a = (p[0] * q[1] - p[1] * q[0]) / 2.;//the area
    //                R = (meshnode[n[0]].x + meshnode[n[1]].x + meshnode[n[2]].x) / 3.;//the points x

    //                for (j = 0, a_hat = 0; j < 3; j++) a_hat += (rn[j] * rn[j] * p[j] / (4.*R));
    //                vol = 2.*R*a_hat;//volume?

    //                for (j = 0, flag = 0; j < 3; j++) if (rn[j] < 1.e-06) flag++;//the number of  points
    //                switch (flag) {
    //                case 2:
    //                    R_hat = R;

    //                    break;

    //                case 1:

    //                    if (rn[0] < 1.e-06) {
    //                        if (fabs(rn[1] - rn[2]) < 1.e-06) R_hat = rn[2] / 2.;
    //                        else R_hat = (rn[1] - rn[2]) / (2.*log(rn[1]) - 2.*log(rn[2]));
    //                    }
    //                    if (rn[1] < 1.e-06) {
    //                        if (fabs(rn[2] - rn[0]) < 1.e-06) R_hat = rn[0] / 2.;
    //                        else R_hat = (rn[2] - rn[0]) / (2.*log(rn[2]) - 2.*log(rn[0]));
    //                    }
    //                    if (rn[2] < 1.e-06) {
    //                        if (fabs(rn[0] - rn[1]) < 1.e-06) R_hat = rn[1] / 2.;
    //                        else R_hat = (rn[0] - rn[1]) / (2.*log(rn[0]) - 2.*log(rn[1]));
    //                    }

    //                    break;

    //                default:

    //                    if (fabs(q[0]) < 1.e-06)
    //                        R_hat = (q[1] * q[1]) / (2.*(-q[1] + rn[0] * log(rn[0] / rn[2])));
    //                    else if (fabs(q[1]) < 1.e-06)
    //                        R_hat = (q[2] * q[2]) / (2.*(-q[2] + rn[1] * log(rn[1] / rn[0])));
    //                    else if (fabs(q[2]) < 1.e-06)
    //                        R_hat = (q[0] * q[0]) / (2.*(-q[0] + rn[2] * log(rn[2] / rn[1])));
    //                    else
    //                        R_hat = -(q[0] * q[1] * q[2]) /
    //                                (2.*(q[0] * rn[0] * log(rn[0]) +
    //                                q[1] * rn[1] * log(rn[1]) +
    //                                q[2] * rn[2] * log(rn[2])));

    //                    break;
    //                }

    //                // Mr Contribution
    //                // Derived from flux formulation with c0 + c1 r^2 + c2 z
    //                // interpolation in the element.
    //                K = (-1. / (2.*a_hat*R));
    //                for (j = 0; j < 3; j++)
    //                    for (k = j; k < 3; k++)
    //                        Mx[j][k] += K*p[j] * rn[j] * p[k] * rn[k];

    //                // need this loop to avoid singularities.  This just puts something
    //                // on the main diagonal of nodes that are on the r=0 line.
    //                // The program later sets these nodes to zero, but it's good to
    //                // for scaling reasons to grab entries from the neighboring diagonals
    //                // rather than just setting these entries to 1 or something....
    //                for (j = 0; j < 3; j++)
    //                    if (rn[j] < 1.e-06) Mx[j][j] += Mx[0][0] + Mx[1][1] + Mx[2][2];

    //                // Mz Contribution;
    //                // Derived from flux formulation with c0 + c1 r^2 + c2 z
    //                // interpolation in the element.
    //                K = (-1. / (2.*a_hat*R_hat));
    //                for (j = 0; j < 3; j++)
    //                    for (k = j; k < 3; k++)
    //                        My[j][k] += K*(q[j] * rn[j])*(q[k] * rn[k])*
    //                                (g[j] / R)*(g[k] / R);

    //                // Fill out rest of entries of Mx and My;
    //                Mx[1][0] = Mx[0][1]; Mx[2][0] = Mx[0][2]; Mx[2][1] = Mx[1][2];
    //                My[1][0] = My[0][1]; My[2][0] = My[0][2]; My[2][1] = My[1][2];

    //                // contributions to Me, be from derivative boundary conditions;
    //                for (j = 0; j < 3; j++) {
    //                    if (El->e[j] >= 0)
    //                        if (lineproplist[El->e[j]].BdryFormat == 2) {
    //                            // conversion factor is 10^(-4) (I think...)
    //                            k = j + 1; if (k == 3) k = 0;
    //                            r = (meshnode[n[j]].x + meshnode[n[k]].x) / 2.;
    //                            K = -0.0001*c*2.*r*lineproplist[El->e[j]].c0.re*l[j] / 6.;
    //                            k = j + 1; if (k == 3) k = 0;
    //                            Me[j][j] += K*2.;
    //                            Me[k][k] += K*2.;
    //                            Me[j][k] += K;
    //                            Me[k][j] += K;

    //                            K = (lineproplist[El->e[j]].c1.re*l[j] / 2.)*0.0001 * 2 * r;
    //                            be[j] += K;
    //                            be[k] += K;
    //                        }
    //                }


    //                // contribution to be from current density in the block
    //                for (j = 0; j < 3; j++) {
    //                    if (labellist[El->lbl].InCircuit >= 0) {
    //                        k = labellist[El->lbl].InCircuit;
    //                        if (circproplist[k].Case == 1) t = circproplist[k].J.Re();
    //                        if (circproplist[k].Case == 0)
    //                            t = -100.*circproplist[k].dV.Re()*blockproplist[El->blk].Cduct / R;
    //                    } else t = 0;
    //                    K = -2.*R*(blockproplist[El->blk].Jr + t)*a / 3.;
    //                    be[j] += K;
    //                }

    //                // contribution to be from magnetization in the block;
    //                t = labellist[El->lbl].MagDir;
    //                if (labellist[El->lbl].MagDirFctn != nullptr) // functional magnetization direction
    //                {
    //                    CString str;
    //                    CComplex X;
    //                    int top1, top2;
    //                    for (j = 0, X = 0; j < 3; j++) X += (meshnode[n[j]].x + I*meshnode[n[j]].y);
    //                    X = X / units[LengthUnits] / 3.;
    //                    str.Format("r=%.17g\nz=%.17g\nx=r\ny=z\ntheta=%.17g\nR=%.17g\nreturn %s",
    //                               X.re, X.im, arg(X) * 180 / PI, abs(X), labellist[El->lbl].MagDirFctn);
    //                    top1 = lua_gettop(lua);
    //                    if (lua_dostring(lua, str) != 0) {
    //                        //                        MsgBox("Lua error evaluating \"%s\"", labellist[El->lbl].MagDirFctn);
    //                        exit(7);
    //                    }
    //                    top2 = lua_gettop(lua);
    //                    if (top2 != top1) {
    //                        str = lua_tostring(lua, -1);
    //                        if (str.GetLength() == 0) {
    //                            //                            MsgBox("\"%s\" does not evaluate to a numerical value",
    //                            //                                   labellist[El->lbl].MagDirFctn);
    //                            exit(7);
    //                        } else t = Re(lua_tonumber(lua, -1));
    //                    }
    //                }
    //                for (j = 0; j < 3; j++) {
    //                    k = j + 1; if (k == 3) k = 0;
    //                    r = (meshnode[n[j]].x + meshnode[n[k]].x) / 2.;
    //                    // need to scale so that everything is in proper units...
    //                    // conversion is 0.0001
    //                    K = -0.0001*r*blockproplist[El->blk].H_c*(
    //                                cos(t*PI / 180.)*(meshnode[n[k]].x - meshnode[n[j]].x) +
    //                            sin(t*PI / 180.)*(meshnode[n[k]].y - meshnode[n[j]].y));
    //                    be[j] += K;
    //                    be[k] += K;
    //                }

    //                // update permeability for the element;
    //                if (Iter == 0) {
    //                    k = meshele[i].blk;

    //                    if (blockproplist[k].BHpoints != 0) LinearFlag = false;

    //                    if (blockproplist[k].LamType == 0) {
    //                        mu = blockproplist[k].LamFill;
    //                        meshele[i].mu1 = blockproplist[k].mu_x*mu;
    //                        meshele[i].mu2 = blockproplist[k].mu_y*mu;
    //                    }
    //                    if (blockproplist[k].LamType == 1) {
    //                        mu = blockproplist[k].LamFill;
    //                        K = blockproplist[k].mu_x;
    //                        meshele[i].mu1 = K*mu + (1. - mu);
    //                        meshele[i].mu2 = K / (mu + K*(1. - mu));
    //                    }
    //                    if (blockproplist[k].LamType == 2) {
    //                        mu = blockproplist[k].LamFill;
    //                        K = blockproplist[k].mu_y;
    //                        meshele[i].mu1 = K*mu + (1. - mu);
    //                        meshele[i].mu2 = K / (mu + K*(1. - mu));
    //                    }
    //                    if (blockproplist[k].LamType > 2) {
    //                        meshele[i].mu1 = 1;
    //                        meshele[i].mu2 = 1;
    //                    }
    //                } else {
    //                    k = meshele[i].blk;

    //                    if ((blockproplist[k].LamType == 0) &&
    //                            (meshele[i].mu1 == meshele[i].mu2)
    //                            && (blockproplist[k].BHpoints > 0)) {
    //                        //	Derive B directly from energy;
    //                        v[0] = 0; v[1] = 0; v[2] = 0;
    //                        for (j = 0; j < 3; j++)
    //                            for (w = 0; w < 3; w++)
    //                                v[j] += (Mx[j][w] + My[j][w])*L.V[n[w]];
    //                        for (j = 0, dv = 0; j < 3; j++) dv += L.V[n[j]] * v[j];
    //                        dv *= (10000.*c*c / vol);
    //                        B = sqrt(fabs(dv));

    //                        // find out new mu from saturation curve;
    //                        blockproplist[k].GetBHProps(B, mu, dv);
    //                        mu = 1. / (muo*mu);
    //                        meshele[i].mu1 = mu;
    //                        meshele[i].mu2 = mu;
    //                        for (j = 0; j < 3; j++) {
    //                            for (w = 0, v[j] = 0; w < 3; w++)
    //                                v[j] += (Mx[j][w] + My[j][w])*L.V[n[w]];
    //                        }

    //                        K = -200.*c*c*c*dv / vol;
    //                        for (j = 0; j < 3; j++)
    //                            for (w = 0; w < 3; w++)
    //                                Mn[j][w] = K*v[j] * v[w];
    //                    }

    //                    if ((blockproplist[k].LamType == 1) && (blockproplist[k].BHpoints>0)) {

    //                        //	Derive B directly from energy;
    //                        t = blockproplist[k].LamFill;
    //                        v[0] = 0; v[1] = 0; v[2] = 0;
    //                        for (j = 0; j < 3; j++)
    //                            for (w = 0; w < 3; w++)
    //                                v[j] += (Mx[j][w] + My[j][w] / (t*t))*L.V[n[w]];
    //                        for (j = 0, dv = 0; j < 3; j++) dv += L.V[n[j]] * v[j];
    //                        dv *= (10000.*c*c / vol);
    //                        B = sqrt(fabs(dv));

    //                        // Evaluate BH curve
    //                        blockproplist[k].GetBHProps(B, mu, dv);
    //                        mu = 1. / (muo*mu);
    //                        meshele[i].mu1 = mu*t;
    //                        meshele[i].mu2 = mu / (t + mu*(1. - t));
    //                        for (j = 0; j < 3; j++) {
    //                            for (w = 0, v[j] = 0, u[j] = 0; w < 3; w++) {
    //                                v[j] += (My[j][w] / t + Mx[j][w])*L.V[n[w]];
    //                                u[j] += (My[j][w] / t + t*Mx[j][w])*L.V[n[w]];
    //                            }
    //                        }
    //                        K = -100.*c*c*c*dv / (vol);
    //                        for (j = 0; j < 3; j++)
    //                            for (w = 0; w < 3; w++)
    //                                Mn[j][w] = K*(v[j] * u[w] + v[w] * u[j]);
    //                    }
    //                    if ((blockproplist[k].LamType == 2) && (blockproplist[k].BHpoints>0)) {

    //                        //	Derive B directly from energy;
    //                        t = blockproplist[k].LamFill;
    //                        v[0] = 0; v[1] = 0; v[2] = 0;
    //                        for (j = 0; j < 3; j++)
    //                            for (w = 0; w < 3; w++)
    //                                v[j] += (Mx[j][w] / (t*t) + My[j][w])*L.V[n[w]];
    //                        for (j = 0, dv = 0; j < 3; j++) dv += L.V[n[j]] * v[j];
    //                        dv *= (10000.*c*c / vol);
    //                        B = sqrt(fabs(dv));

    //                        // Evaluate BH curve
    //                        blockproplist[k].GetBHProps(B, mu, dv);
    //                        mu = 1. / (muo*mu);
    //                        meshele[i].mu2 = mu*t;
    //                        meshele[i].mu1 = mu / (t + mu*(1. - t));

    //                        for (j = 0; j < 3; j++) {
    //                            for (w = 0, v[j] = 0, u[j] = 0; w < 3; w++) {
    //                                v[j] += (Mx[j][w] / t + My[j][w])*L.V[n[w]];
    //                                u[j] += (Mx[j][w] / t + t*My[j][w])*L.V[n[w]];
    //                            }
    //                        }
    //                        K = -100.*c*c*c*dv / (vol);
    //                        for (j = 0; j < 3; j++)
    //                            for (w = 0; w < 3; w++)
    //                                Mn[j][w] = K*(v[j] * u[w] + v[w] * u[j]);

    //                    }
    //                }

    //                // "Warp" the permeability of this element if part of
    //                // the conformally mapped external region
    //                if ((labellist[meshele[i].lbl].IsExternal) && (Iter == 0) && (sdi_iter == 0)) {
    //                    double Z = (meshnode[n[0]].y + meshnode[n[1]].y + meshnode[n[2]].y) / 3. - extZo;
    //                    double kludge = (R*R + Z*Z)*extRi / (extRo*extRo*extRo);
    //                    meshele[i].mu1 /= kludge;
    //                    meshele[i].mu2 /= kludge;
    //                }

    //                // combine block matrices into global matrices;
    //                for (j = 0; j < 3; j++)
    //                    for (k = 0; k < 3; k++) {
    //                        Me[j][k] += (Mx[j][k] / Re(El->mu2) + My[j][k] / Re(El->mu1) + Mn[j][k]);
    //                        be[j] += Mn[j][k] * L.V[n[k]];
    //                    }

    //                for (j = 0; j < 3; j++) {
    //                    for (k = j; k < 3; k++)
    //                        L.Put(L.Get(n[j], n[k]) - Me[j][k], n[j], n[k]);
    //                    L.b[n[j]] -= be[j];
    //                }
    //            }

    //            // add in contribution from point currents;
    //            for (i = 0; i < NumNodes; i++)
    //                if (meshnode[i].bc >= 0) {
    //                    r = meshnode[i].x;
    //                    L.b[i] += (0.01*nodeproplist[meshnode[i].bc].Jr*2.*r);
    //                }

    //            // apply fixed boundary conditions at points;
    //            for (i = 0; i < NumNodes; i++) {
    //                if (fabs(meshnode[i].x) < (units[LengthUnits] * 1.e-06)) L.SetValue(i, 0.);
    //                else
    //                    if (meshnode[i].bc >= 0)
    //                        if ((nodeproplist[meshnode[i].bc].Jr == 0) &&
    //                                (nodeproplist[meshnode[i].bc].Ji == 0) && (sdi_iter == 0))
    //                            L.SetValue(i, nodeproplist[meshnode[i].bc].Ar / c);
    //            }

    //            // apply fixed boundary conditions along segments;
    //            for (i = 0; i < NumEls; i++)
    //                for (j = 0; j < 3; j++) {
    //                    k = j + 1; if (k == 3) k = 0;
    //                    if (meshele[i].e[j] >= 0)
    //                        if (lineproplist[meshele[i].e[j]].BdryFormat == 0) {
    //                            if (Coords == 0) {
    //                                // first point on the side;
    //                                x = meshnode[meshele[i].p[j]].x;
    //                                y = meshnode[meshele[i].p[j]].y;
    //                                x /= units[LengthUnits]; y /= units[LengthUnits];
    //                                s = meshele[i].e[j];
    //                                a = lineproplist[s].A0 + x*lineproplist[s].A1 +
    //                                        y*lineproplist[s].A2;
    //                                // just take ``real'' component.
    //                                a *= cos(lineproplist[s].phi*DEG);
    //                                if (x != 0) L.SetValue(meshele[i].p[j], a / c);

    //                                // second point on the side;
    //                                x = meshnode[meshele[i].p[k]].x;
    //                                y = meshnode[meshele[i].p[k]].y;
    //                                x /= units[LengthUnits]; y /= units[LengthUnits];
    //                                s = meshele[i].e[j];
    //                                a = lineproplist[s].A0 + x*lineproplist[s].A1 +
    //                                        y*lineproplist[s].A2;
    //                                // just take``real'' component.
    //                                a *= cos(lineproplist[s].phi*DEG);
    //                                if (x != 0) L.SetValue(meshele[i].p[k], a / c);
    //                            } else {
    //                                // first point on the side;
    //                                x = meshnode[meshele[i].p[j]].x;
    //                                y = meshnode[meshele[i].p[j]].y;
    //                                r = sqrt(x*x + y*y);
    //                                if ((x == 0) && (y == 0)) t = 0;
    //                                else t = atan2(y, x) / DEG;
    //                                r /= units[LengthUnits];
    //                                s = meshele[i].e[j];
    //                                a = lineproplist[s].A0 + r*lineproplist[s].A1 +
    //                                        t*lineproplist[s].A2;
    //                                a *= cos(lineproplist[s].phi*DEG); // just take ``real'' component.
    //                                if (x != 0) L.SetValue(meshele[i].p[j], a / c);

    //                                // second point on the side;
    //                                x = meshnode[meshele[i].p[k]].x;
    //                                y = meshnode[meshele[i].p[k]].y;
    //                                r = sqrt(x*x + y*y);
    //                                if ((x == 0) && (y == 0)) t = 0;
    //                                else t = atan2(y, x) / DEG;
    //                                r /= units[LengthUnits];
    //                                s = meshele[i].e[j];
    //                                a = lineproplist[s].A0 + r*lineproplist[s].A1 +
    //                                        t*lineproplist[s].A2;
    //                                a *= cos(lineproplist[s].phi*DEG); // just take ``real'' component.
    //                                if (x != 0) L.SetValue(meshele[i].p[k], a / c);
    //                            }

    //                        }
    //                }

    //            if ((SDIflag == true) && (sdi_iter == 1)) for (i = 0; i < NumEls; i++)
    //                for (j = 0; j < 3; j++) {
    //                    k = j + 1; if (k == 3) k = 0;
    //                    if (meshele[i].e[j] >= 0)
    //                        if (lineproplist[meshele[i].e[j]].BdryFormat == 3) {
    //                            L.SetValue(meshele[i].p[j], 0.);
    //                            L.SetValue(meshele[i].p[k], 0.);
    //                        }
    //                }

    //            // Apply any periodicity/antiperiodicity boundary conditions that we have
    //            for (k = 0; k < NumPBCs; k++) {
    //                if (pbclist[k].t == 0) L.Periodicity(pbclist[k].x, pbclist[k].y);
    //                if (pbclist[k].t == 1) L.AntiPeriodicity(pbclist[k].x, pbclist[k].y);
    //            }

    //            // solve the problem;
    //            if (SDIflag == false) for (j = 0; j < NumNodes; j++) V_old[j] = L.V[j];
    //            else {
    //                if (sdi_iter == 0)
    //                    for (j = 0; j < NumNodes; j++) V_sdi[j] = L.V[j];
    //                else
    //                    for (j = 0; j < NumNodes; j++) {
    //                        V_old[j] = V_sdi[j];
    //                        V_sdi[j] = L.V[j];
    //                    }
    //            }

    //            if (L.PCGSolve(Iter + sdi_iter) == false) return false;

    //            if (sdi_iter == 1)
    //                for (j = 0; j < NumNodes; j++) L.V[j] = (V_sdi[j] + L.V[j]) / 2.;

    //        } // end of SDI iteration loop;
    //        if (LinearFlag == false) {

    //            for (j = 0, x = 0, y = 0; j < NumNodes; j++) {
    //                x += (L.V[j] - V_old[j])*(L.V[j] - V_old[j]);
    //                y += (L.V[j] * L.V[j]);
    //            }

    //            if (y == 0) LinearFlag = true;
    //            else {
    //                lastres = res;
    //                res = sqrt(x / y);
    //            }


    //            // relaxation if we need it
    //            if (Iter > 5) {
    //                if ((res > lastres) && (Relax > 0.125)) Relax /= 2.;
    //                else Relax += 0.1 * (1. - Relax);

    //                for (j = 0; j < NumNodes; j++) L.V[j] = Relax*L.V[j] + (1.0 - Relax)*V_old[j];
    //            }


    //            // report some results
    //            char outstr[256];
    //            sprintf(outstr, "Newton Iteration(%i) Relax=%.4g", Iter, Relax);
    //            //            TheView->SetDlgItemText(IDC_FRAME2, outstr);
    //            j = (int)(100.*log10(res) / (log10(Precision) + 2.));
    //            if (j > 100) j = 100;
    //            //            TheView->m_prog2.SetPos(j);
    //        }

    //        // nonlinear iteration has to have a looser tolerance
    //        // than the linear solver--otherwise, things can't ever
    //        // converge.  Arbitrarily choose 100*tolerance.
    //        if ((res < 100.*Precision) && Iter>0) LinearFlag = true;

    //        Iter++;

    //    } while (LinearFlag == false);

    //    // convert answer back to Webers for plotting purposes.
    //    for (i = 0; i < NumNodes; i++) {
    //        L.b[i] = L.V[i] * c;
    //        L.b[i] *= (meshnode[i].x*0.01 * 2 * PI);
    //    }

    //    free(V_old);
    //    if (SDIflag == true) free(V_sdi);
    //    if (NumCircProps > 0) {
    //        free(CircInt1);
    //        free(CircInt2);
    //        free(CircInt3);
    //    }

    return true;
}

void PF_Mag2DSProject::GetFillFactor(int lbl)
{
    //    auto meshele = m_mesh->eles;
    //    auto meshnode = m_mesh->nodes;
    //    // Get the fill factor associated with a stranded and
    //    // current-carrying region.  For AC problems, also compute
    //    // the apparent conductivity and permeability for use in
    //    // post-processing the voltage.

    //    CMaterialProp* bp= &blockproplist[labellist[lbl].BlockType];
    //    CBlockLabel* bl= &labellist[lbl];
    //    double atot,awire,d,o,fill,dd,W,R,c1,c2;
    //    int i,wiretype;
    //    CComplex ufd,ofd;

    //    if ((abs(bl->Turns)>1) || (blockproplist[labellist[lbl].BlockType].LamType>2))
    //        bl->bIsWound=true;
    //    else
    //        bl->bIsWound=false;

    //    if ((Frequency==0) || (blockproplist[labellist[lbl].BlockType].LamType<3))
    //    {
    //        bl->ProximityMu=1.;
    //        return;
    //    }

    //    // compute total area of associated block
    //    for(i=0,atot=0;i<NumEls;i++)
    //        if(meshele[i].lbl==lbl) atot+=ElmArea(i);

    //    if (atot==0) return;

    //    // "non-physical" case where the wire has a zero conductivity
    //    if (bp->Cduct==0)
    //    {
    //        bl->ProximityMu=1;
    //        return;
    //    }

    //    wiretype=bp->LamType-3;
    //    // wiretype = 0 for magnet wire
    //    // wiretype = 1 for stranded but non-litz wire
    //    // wiretype = 2 for litz wire
    //    // wiretype = 3 for rectangular wire

    //    if(wiretype==3) // rectangular wire
    //    {
    //        W=2.*PI*Frequency;
    //        d=bp->WireD*0.001;
    //        fill=fabs(d*d*((double) bl->Turns)/atot);
    //        dd=d/sqrt(fill);			// foil pitch
    //        fill=d/dd;					// fill for purposes of equivalent foil analysis
    //        o=bp->Cduct*(d/dd)*1.e6;	// effective foil conductivity in S/m

    //        // effective permeability for the equivalent foil
    //        ufd=muo*tanh(sqrt(I*W*o*muo)*d/2.)/(sqrt(I*W*o*muo)*d/2.);
    //        bl->ProximityMu=(fill*ufd+(1.-fill)*muo)/muo;
    //        return;
    //    }

    //    // procedure for round wires;
    //    switch (wiretype)
    //    {
    //    // wiretype = 0 for magnet wire
    //    case 0:
    //        R=bp->WireD*0.0005;
    //        awire=PI*R*R*((double) bp->NStrands)*((double) bl->Turns);
    //        break;

    //        // wiretype = 1 for stranded but non-litz wire
    //    case 1:
    //        R=bp->WireD*0.0005*sqrt((double) bp->NStrands);
    //        awire=PI*R*R*((double) bl->Turns);
    //        break;

    //        // wiretype = 2 for litz wire
    //    case 2:
    //        R=bp->WireD*0.0005;
    //        awire=PI*R*R*((double) bp->NStrands)*((double) bl->Turns);
    //        break;
    //    }
    //    fill=fabs(awire/atot);

    //    // preliminary definitions
    //    o=bp->Cduct*1.e6;						// conductivity in S/m
    //    W=2.*PI*Frequency*o*muo*R*R/2.;			// non-dimensionalized frequency

    //    // fit for frequency-dependent permeability...
    //    c1=0.7756067409818643 + fill*(0.6873854335408803 + fill*(0.06841584481674128 -0.07143732702512284*fill));
    //    c2=1.5*fill/c1;
    //    ufd=c2*(tanh(sqrt(c1*I*W))/sqrt(c1*I*W))+(1.-c2); // relative frequency-dependent permeability
    //    bl->ProximityMu=ufd;
}

double PF_Mag2DSProject::ElmArea(int i)
{
    // returns element cross-section area in meter^2
    int j,n[3];
    double b0,b1,c0,c1;
    auto meshele = m_mesh->eles;
    auto meshnode = m_mesh->nodes;

    for(j=0;j<3;j++) n[j]=meshele[i].n[j];

    b0=meshnode[n[1]].y - meshnode[n[2]].y;
    b1=meshnode[n[2]].y - meshnode[n[0]].y;
    c0=meshnode[n[2]].x - meshnode[n[1]].x;
    c1=meshnode[n[0]].x - meshnode[n[2]].x;
    return 0.0001*(b0*c1-b1*c0)/2.;
}

void PF_Mag2DSProject::CleanUp()
{
    //    int k;

    //    if (meshnode!=nullptr)		free(meshnode);
    //    if (meshele!=nullptr)		free(meshele);
    //    if (blockproplist!=nullptr){
    //        for(k=0;k<NumBlockProps;k++)
    //        {
    //            if(blockproplist[k].Bdata!=nullptr) free(blockproplist[k].Bdata);
    //            if(blockproplist[k].Hdata!=nullptr) free(blockproplist[k].Hdata);
    //            if(blockproplist[k].slope!=nullptr) free(blockproplist[k].slope);
    //        }
    //        free(blockproplist);
    //    }
    //    if (lineproplist!=nullptr)	 free(lineproplist);
    //    if (nodeproplist!=nullptr)	 free(nodeproplist);
    //    if (circproplist!=nullptr)	 free(circproplist);
    //    if (labellist!=nullptr){
    //        for(k=0;k<NumBlockLabels;k++)
    //            if(labellist[k].MagDirFctn!=nullptr) free(labellist[k].MagDirFctn);
    //        free(labellist);
    //    }
    //    if (pbclist!=nullptr)		 free(pbclist);
}
/**
 * @brief
 *
 * @param pro 数据源
 * @param node 要更新的节点
 */
static void createTree(PF_Mag2DSProject* pro,PF_MagFEMNode* node)
{
    if(!pro) return;
    if(!node) return;

    /** 设置root节点的显示 **/

    /** 根据pro中的数据生成node **/
    node->setDisplayName(pro->displayName()+QString(".f2d"));

    /** 添加变量 **/
    auto def_node = std::make_unique<FolderNode>(QString(QObject::tr("Definitions")),NodeType::Variable,QIcon(":/imgs/definitions.png"));

    QHashIterator<QString, double> iter(pro->m_variables.getVariableDict());
    while(iter.hasNext())
    {
        iter.next();
        def_node->addNode(std::make_unique<LeafNode>(iter.key(),LeafType::Unknown));
        //        qDebug() << iter.key() << ": " << iter.value();
    }
    /** 添加材料 **/
    auto material_node = std::make_unique<FolderNode>(QString(QObject::tr("Materials")),NodeType::Material,QIcon(":/imgs/material.png"));
    QMapIterator<QString,CMaterialProp*> it(pro->m_materialList);
    while(it.hasNext())
    {
        it.next();
        material_node->addNode(std::make_unique<LeafNode>(it.value()->BlockName,LeafType::CMaterialProp,NodeType::Leaf,QIcon(":/imgs/material.png")));
    }
    /** 添加几何 **/
    auto geo_node = std::make_unique<FolderNode>(QString(QObject::tr("Geometry")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));
    auto point_node = std::make_unique<FolderNode>(QString(QObject::tr("Point")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));
    auto line_node = std::make_unique<FolderNode>(QString(QObject::tr("Line")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));
    auto face_node = std::make_unique<FolderNode>(QString(QObject::tr("Face")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));

    for(auto e : pro->m_document->getEntityList()){
        switch (e->rtti()) {
        case PF::EntityPoint:
        {
            point_node->addNode(std::make_unique<LeafNode>(QObject::tr("Point")+QString("%1").arg(e->index()),LeafType::Point,NodeType::Leaf,QIcon(":/imgs/material.png")));
            break;
        }
        case PF::EntityLine:
        {
            line_node->addNode(std::make_unique<LeafNode>(QObject::tr("Line")+QString("%1").arg(e->index()),LeafType::Line,NodeType::Leaf,QIcon(":/imgs/material.png")));
            break;
        }
        case PF::EntityFace:
        {
            face_node->addNode(std::make_unique<LeafNode>(QObject::tr("Face")+QString("%1").arg(e->index()),LeafType::Face,NodeType::Leaf,QIcon(":/imgs/material.png")));
            break;
        }
        default:
        {
            qDebug()<<"No such entity.";
            break;
        }
        }
    }
    /** 添加分网 **/
    auto mesh_node = std::make_unique<FolderNode>(QString(QObject::tr("Mesh")),NodeType::Mesh,QIcon(":/imgs/mesh.png"));
    auto mesh_point_node = std::make_unique<FolderNode>(QString(QObject::tr("Mesh Point")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));
    auto mesh_line_node = std::make_unique<FolderNode>(QString(QObject::tr("Mesh Line")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));
    auto mesh_face_node = std::make_unique<FolderNode>(QString(QObject::tr("Mesh Face")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));

    //    auto globaldef_node = std::make_unique<FolderNode>(QString(QObject::tr("Global Definitions")),NodeType::Definition,QIcon(":/imgs/global_branch.png"));

    auto comp_node = std::make_unique<FolderNode>(QString(QObject::tr("Physics")),NodeType::Component,QIcon(":/imgs/model_2d_axi.png"));
    auto domain_node = std::make_unique<FolderNode>(QString(QObject::tr("Domains")),NodeType::Domain,QIcon(":/imgs/model_2d_axi.png"));

    auto solver_node = std::make_unique<FolderNode>(QString(QObject::tr("Solver")),NodeType::Solve,QIcon(":/imgs/model_2d_axi.png"));
    auto solversetting_node = std::make_unique<FolderNode>(QString(QObject::tr("Settings")),NodeType::Component,QIcon(":/imgs/model_2d_axi.png"));

    auto result_node = std::make_unique<FolderNode>(QString(QObject::tr("Result")),NodeType::Component,QIcon(":/imgs/model_2d_axi.png"));
    auto curve2d_node = std::make_unique<FolderNode>(QString(QObject::tr("2D curve")),NodeType::Plot2D,QIcon(":/imgs/model_2d_axi.png"));
    auto surface2d_node = std::make_unique<FolderNode>(QString(QObject::tr("2D surface")),NodeType::Surface2D,QIcon(":/imgs/model_2d_axi.png"));

    geo_node->addNode(std::move(def_node));
    geo_node->addNode(std::move(point_node));
    geo_node->addNode(std::move(line_node));
    geo_node->addNode(std::move(face_node));

    mesh_node->addNode(std::move(mesh_point_node));
    mesh_node->addNode(std::move(mesh_line_node));
    mesh_node->addNode(std::move(mesh_face_node));

    comp_node->addNode(std::move(material_node));
    comp_node->addNode(std::move(domain_node));

    solver_node->addNode(std::move(solversetting_node));

    result_node->addNode(std::move(curve2d_node));
    result_node->addNode(std::move(surface2d_node));

    node->addNode(std::move(geo_node));
    node->addNode(std::move(mesh_node));
    node->addNode(std::move(comp_node));
    node->addNode(std::move(solver_node));
    node->addNode(std::move(result_node));
}

/**
 * @brief 针对pro生成一个node，每一次数据发生更新时，需要调用，
 * 重新生成，并对tree控件进行更新。
 *
 * @param pro
 * @return std::unique_ptr<PF_MagFEMNode>
 */
std::unique_ptr<PF_MagFEMNode> PF_Mag2DSNodeTreeBuilder::buildTree(PF_Mag2DSProject *pro)
{
    /** 先创建一个root节点，这里应该有一点问题，
        后面tree变化的时候，检测的是subtree，
        而subtree又是要找特定的node来改变，每一次都重新生成projectnode
        就不对了**/

    auto   root = std::make_unique<PF_MagFEMNode>(pro);

    /** 生成root的子节点 **/
    createTree(pro,root.get());

    return root;
}

}// namespace MagFEMProjectManagerPlugin
