#ifndef PF_COMMONFEMPROJECT_H
#define PF_COMMONFEMPROJECT_H

#include "sparsefemm.h"
#include "magfemprojectmanagerplugin_global.h"

#include <utils/pf_variabledict.h>
#include <material/pf_material.h>

#include <mesh/meshfemm.h>

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

class MAGPLUGINSHARED_EXPORT PF_CommonFEMProject : public ProjectExplorer::PF_Project
{
    Q_OBJECT
public:
    PF_CommonFEMProject(const QString &mimeType, const Utils::FileName &feemFile);
    ~PF_CommonFEMProject();

    Core::IGeometry* CAD() const override;
    void editMaterial(ProjectExplorer::Node* node) override;
    void doMesh() override;
    void entitySelected(bool selected,ProjectExplorer::Node* node=nullptr) override;
    void setFaceMaterial(ProjectExplorer::Node* node) override;

    PF_Entity* findEntity(const QString &displayName);

    QMap<QString,CMaterialProp*> m_materialList;/** 材料名称，材料值 **/
    QMap<int,CMaterialProp*> m_domains;/** 域编号，材料 **/
    Utils::PF_VariableDict m_variables;//
    PF_Document* m_document;
    CMesh* m_mesh;
    double  Precision;
private:
    Geometry2D* cad2d;
};

}//MagFEMProjectManagerPlugin
#endif // PF_COMMONFEMPROJECT_H
