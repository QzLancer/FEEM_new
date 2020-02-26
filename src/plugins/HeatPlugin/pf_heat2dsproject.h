#ifndef PF_HEAT2DSPROJECT_H
#define PF_HEAT2DSPROJECT_H

#include "magfemprojectmanagerplugin/pf_commonfemproject.h"
#include "boundaryprop.h"

#define muo 1.2566370614359173e-6
#define Golden 0.3819660112501051517954131656
#define PI 3.141592653589793238462643383
#define DEG 0.01745329251994329576923690768
#define SmallNo 1.e-14

namespace HeatFEMProjectManagerPlugin {
class PF_HeatFEMNode;
class PF_Heat2DSProject : public MagFEMProjectManagerPlugin::PF_CommonFEMProject
{
    Q_OBJECT
public:
    PF_Heat2DSProject(const FileName& feemFile);
    ~PF_Heat2DSProject();

    void updateData();

    bool Cuthill();
    bool SortElements();
    bool Static2D();
    bool WriteStatic2D(CBigLinProb &L);
    bool StaticAxisymmetric(CBigLinProb &L);
    void GetFillFactor(int lbl);
    double ElmArea(int i);
    void CleanUp();

    bool onSegment(double x1, double y1, double x2, double y2, double x, double y);

    virtual void entitySelected(bool selected, ProjectExplorer::Node *node = nullptr) override;

    virtual QVariantMap toMap() const;
    virtual RestoreResult fromMap(const QVariantMap &map, QString *errorMessage);

    CBigLinProb* L;
    QMap<QString, CHBoundaryProp*> m_boundaryList;/** 边界名称，边界值**/

public slots:
    void addBoundary(CHBoundaryProp* boundary);

signals:
    void nodeSelected(ProjectExplorer::Node *);
};

class PF_Heat2DSNodeTreeBuilder
{
public:
    static std::unique_ptr<PF_HeatFEMNode> buildTree(PF_Heat2DSProject* pro);
};
}// namespace HeatFEMProjectManagerPlugin

#endif // PF_HEAT2DSPROJECT_H
