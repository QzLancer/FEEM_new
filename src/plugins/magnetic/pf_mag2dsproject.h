#ifndef PF_MAG2DSPROJECT_H
#define PF_MAG2DSPROJECT_H

#include "sparsefemm.h"

#include <commonfem/pf_commonfemproject.h>

#define muo 1.2566370614359173e-6
#define Golden 0.3819660112501051517954131656
#define PI 3.141592653589793238462643383
#define DEG 0.01745329251994329576923690768
#define SmallNo 1.e-14

namespace MagneticFEM {
class PF_MagFEMNode;
class PF_Mag2DSProject : public CommonFEM::PF_CommonFEMProject
{
    Q_OBJECT
public:
    PF_Mag2DSProject(const FileName& feemFile);
    ~PF_Mag2DSProject();

    void updateData();

    bool Cuthill();
    bool SortElements();
    bool Static2D();
    bool WriteStatic2D(CBigLinProb &L);
    bool StaticAxisymmetric(CBigLinProb &L);
    void GetFillFactor(int lbl);
    double ElmArea(int i);
    void CleanUp();

    virtual QVariantMap toMap() const;
    virtual RestoreResult fromMap(const QVariantMap &map, QString *errorMessage);

public:
    // General problem attributes
//    double  Frequency;
//
//    double  Relax;
//    int		LengthUnits;
//    int		ACSolver;
//    bool    ProblemType;
//    bool	Coords;

    // axisymmetric external region parameters
//    double  extRo,extRi,extZo;

    //	CFknDlg *TheView;

    // CArrays containing the mesh information
//    int	BandWidth;
//    CNode *meshnode;
//    CElement	*meshele;

//    int NumNodes;
//    int NumEls;

    // lists of properties
//    int NumBlockProps;
//    int NumPBCs;
//    int NumLineProps;
//    int NumPointProps;
//    int NumCircProps;
//    int NumBlockLabels;
//    int NumCircPropsOrig;

//    CMaterialProp	*blockproplist;
//    CBoundaryProp	*lineproplist;
//    CPointProp		*nodeproplist;
//    CCircuit		*circproplist;
//    CBlockLabel		*labellist;
//    CCommonPoint	*pbclist;
    CBigLinProb* L;
};

class PF_Mag2DSNodeTreeBuilder
{
public:
    static std::unique_ptr<PF_MagFEMNode> buildTree(PF_Mag2DSProject* pro);
};
}// namespace MagneticFEM


#endif // PF_MAG2DSPROJECT_H
