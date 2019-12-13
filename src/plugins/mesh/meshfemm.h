#ifndef MESHFEMM_H
#define MESHFEMM_H

#include "mesh_global.h"

#include <material/pf_material.h>
/////////////////////////////////////////////////////////////////////////////
// CNode -- structure that holds information about each mesh point.
enum GmshElementType{
    LINE_NODE2=1,
    TRIANGLE_NODE3,
    QUAD_NODE4
};

class FEEM_MESH_EXPORT CElement
{
public:
    int n[3];// ni, nj, nk;//
    int ele_type;
    int physic_tag;
    int geometry_tag;/** 与face的编号对应 **/

    CComplex mu1,mu2;
    int blk;
    int lbl;
};

class FEEM_MESH_EXPORT CNode
{
public:

    double x,y,z;
    int bc;

private:

};
class FEEM_MESH_EXPORT CMesh{
public:
    CMesh();
    ~CMesh();

    int numNode;
    int numEle;
    CNode* nodes;
    CElement* eles;

    void loadGsh22(const char fn[]);
private:

};
class CMeshline
{
public:

    int n0,n1;

private:
};

class FEEM_MESH_EXPORT CBlockLabel
{
public:

    double x,y;
    double MaxArea;
    double MagDir;
    int BlockType;
    int InCircuit;
    int InMask;
    int InGroup;
    int Turns;
    bool IsExternal;
    char *MagDirFctn;

    // used for proximity effect regions only.
    CComplex ProximityMu;
    bool bIsWound;

private:

};

class FEEM_MESH_EXPORT CCommonPoint
{
public:
    int x,y,t;

private:
};

class FEEM_MESH_EXPORT CBoundaryProp
{
public:

    int BdryFormat;			// type of boundary condition we are applying
    // 0 = constant value of A
    // 1 = Small skin depth eddy current BC
    // 2 = Mixed BC

    double A0,A1,A2,phi;	// set value of A for BdryFormat=0;

    double Mu,Sig;			// material properties necessary to apply
    // eddy current BC

    CComplex c0,c1;			// coefficients for mixed BC

    // TO DO:  ``flux pipe?'' and ''line currents''
    // Line currents might be redundant, since we already have magnetization.

private:
};

class FEEM_MESH_EXPORT CPointProp
{
public:

    double Jr,Ji;			// applied point current, A
    double Ar,Ai;				// prescribed nodal value;

private:
};

class FEEM_MESH_EXPORT CCircuit
{
public:
    double dVolts_re, dVolts_im;
    double Amps_re, Amps_im;
    int CircType;
    int OrigCirc;

    // some member variables used to store some results
    CComplex J;
    CComplex dV;
    int Case;

private:
};


#endif // MESHFEMM_H
