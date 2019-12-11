#ifndef PF_MAG2DSPROJECT_H
#define PF_MAG2DSPROJECT_H

#include <utils/pf_variabledict.h>
#include <material/pf_material.h>

#include <project/pf_project.h>

#include <QVector>

class PF_Document;
class Geometry2D;
namespace ProjectExplorer {
class Node;
}

namespace MagFEMProjectManagerPlugin {
class PF_MagFEMNode;
class PF_Mag2DSProject : public ProjectExplorer::PF_Project
{
public:
    PF_Mag2DSProject();
    ~PF_Mag2DSProject();

    void updateData();

    Core::IGeometry* CAD() const override;
    void editMaterial(ProjectExplorer::Node* node) override;

    QVector<CMaterialProp> m_materialList;//
    Utils::PF_VariableDict m_variables;//
    PF_Document* m_document;
public:

private:
    Geometry2D* cad2d;
};

class PF_Mag2DSNodeTreeBuilder
{
public:
    static std::unique_ptr<PF_MagFEMNode> buildTree(PF_Mag2DSProject* pro);
};
}// namespace MagFEMProjectManagerPlugin


#endif // PF_MAG2DSPROJECT_H
