//#ifndef MAGSOLVER_H
//#define MAGSOLVER_H

//#include "solver_global.h"
//#include "sparsefemm.h"

//#include <mesh/meshfemm.h>

//#include <material/pf_material.h>

//#define muo 1.2566370614359173e-6
//#define Golden 0.3819660112501051517954131656
//#define PI 3.141592653589793238462643383
//#define DEG 0.01745329251994329576923690768
//#define SmallNo 1.e-14

//class FEEM_SOLVER_EXPORT MagSolver
//{
//public:
//    MagSolver();
//    ~MagSolver();
//    // Operations
//public:

//    bool LoadMesh();
////    bool OnOpenDocument();
//    bool Cuthill();
//    bool SortElements();
//    bool Static2D(CBigLinProb &L);
//    bool WriteStatic2D(CBigLinProb &L);
//    //	bool Harmonic2D(CBigComplexLinProb &L);
//    //	bool WriteHarmonic2D(CBigComplexLinProb &L);
//    bool StaticAxisymmetric(CBigLinProb &L);
//    //	bool HarmonicAxisymmetric(CBigComplexLinProb &L);
//    void GetFillFactor(int lbl);
//    double ElmArea(int i);
//    void CleanUp();
//public:
//    // General problem attributes
//    double  Frequency;
//    double  Precision;
//    double  Relax;
//    int		LengthUnits;
//    int		ACSolver;
//    bool    ProblemType;
//    bool	Coords;

//    // axisymmetric external region parameters
//    double  extRo,extRi,extZo;

//    //	CFknDlg *TheView;

//    // CArrays containing the mesh information
//    int	BandWidth;
//    CNode *meshnode;
//    CElement	*meshele;

//    int NumNodes;
//    int NumEls;

//    // lists of properties
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
//    // stuff usually kept track of by CDocument
//    char *PathName;
//};

//#endif // MAGSOLVER_H
