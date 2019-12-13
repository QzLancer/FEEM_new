#ifndef PF_MAG2DSPROJECT_H
#define PF_MAG2DSPROJECT_H

#include <utils/pf_variabledict.h>
#include <material/pf_material.h>

#include <project/pf_project.h>

#include <QVector>
#include <QMap>

class PF_Document;
class Geometry2D;
class PF_Entity;

class CMesh;
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

    PF_Entity* findEntity(const QString &displayName);

    Core::IGeometry* CAD() const override;
    void editMaterial(ProjectExplorer::Node* node) override;
    void doMesh() override;
    void entitySelected(bool selected,ProjectExplorer::Node* node=nullptr) override;
    void setFaceMaterial(ProjectExplorer::Node* node) override;

    QVector<CMaterialProp> m_materialList;//
    QMap<int,QString> m_domains;
    Utils::PF_VariableDict m_variables;//
    PF_Document* m_document;
    CMesh* m_mesh;
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
