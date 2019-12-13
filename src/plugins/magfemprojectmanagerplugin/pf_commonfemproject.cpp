#include "pf_commonfemproject.h"
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

namespace MagFEMProjectManagerPlugin{
PF_CommonFEMProject::PF_CommonFEMProject()
    :ProjectExplorer::PF_Project()
    ,m_document(new PF_Document())
    ,m_mesh(new CMesh())
{
    connect(Material::MaterialPlugin::instance(),&Material::MaterialPlugin::materialAdded
            ,[this](CMaterialProp* material)
    {
        /** 因为connect连接的是创建的具体对象，所以不会出现，同样的Project都会打开 **/
        /** 判断材料名是否存在 **/
        for(auto m : m_materialList)
        {
            if(m.BlockName == material->BlockName){
                QString s("Material "+material->BlockName+" exists.");
                PoofeeSay<<s;
                return;
            }
        }
        /** 这个地方为什么会调用两次拷贝构造函数？ **/
        m_materialList.push_back(*material);
        /** 更新项目树 **/
        emit dataChanged();
        PoofeeSay<<"Material "+material->BlockName+" Added.";
        /** 更新tree **/
        /** 这里有问题，如果不是从tree操作进来的，那么node就不对了 **/
        //        Node *node = PF_ProjectTree::findCurrentNode();
        //        FolderNode *folderNode = node ? node->asFolderNode() : nullptr;
        /** 需要判断为文件夹，不清楚需不需要判断是材料类型
            感觉不需要，因为右键菜单就是根据材料进来的   **/
        //        if(!folderNode) return;
        //        folderNode->addNode(std::make_unique<LeafNode>(material->BlockName,LeafType::CMaterialProp));
        //        PF_ProjectTree::emitSubtreeChanged(folderNode);
        //        OutputPlugin::OutputPluginPlugin::write("Material "+material->BlockName+" Added.");
    });
    /** 添加CAD **/
    cad2d = new Geometry2D(m_document);
    Core::GeometryManager::openCAD(cad2d);
}

PF_CommonFEMProject::~PF_CommonFEMProject()
{

}

Core::IGeometry *PF_CommonFEMProject::CAD() const
{
    return cad2d;
}

/*!
 \brief 打开材料对话框并进行编辑。

 \param node
*/
void PF_CommonFEMProject::editMaterial(ProjectExplorer::Node *node)
{
    if(!node) return;
    qDebug()<<Q_FUNC_INFO;
    /** 根据节点名称查询材料 **/
    for(int i = 0; i < m_materialList.size();i++)
    {
        if(m_materialList[i].BlockName == node->displayName()){
            qDebug()<<"found!"<<m_materialList[i].BlockName;
            PF_MagMaterialDialog* dialog = new PF_MagMaterialDialog(Core::ICore::dialogParent());
            dialog->setMaterial(m_materialList[i]);
            dialog->setWindowTitle(m_materialList[i].BlockName);
            dialog->exec();
            break;
        }
    }

}
/*!
 \brief 项目树右键菜单进行分网

 \param node
*/
void PF_CommonFEMProject::doMesh()
{
    qDebug()<<Q_FUNC_INFO;
    m_document->doMesh();
    m_mesh->loadGsh22("D:/model.msh");
}
/*!
 \brief 单个的选择

 \param selected
 \param node
*/
void PF_CommonFEMProject::entitySelected(bool selected, ProjectExplorer::Node *node)
{
    m_document->setSelected(false);
    if(selected){
        auto e = findEntity(node->displayName());
        if(e){
            e->setSelected(true);
        }
    }
    cad2d->replot();
}
/*!
 \brief 应该是弹出一个对话框，然后选择材料

 \param node
*/
void PF_CommonFEMProject::setFaceMaterial(ProjectExplorer::Node *node)
{
    auto e = findEntity(node->displayName());
    int index = -1;
    if(e) index = e->index();
    auto dialog = new PF_FaceSettingDialog(Core::ICore::dialogParent(),this,index);
    QString title = QObject::tr("Set ")+node->displayName()+QObject::tr(" properties");
    dialog->setWindowTitle(title);
    dialog->exec();
}

/*!
 \brief 主要是通过名字查找entity

 \param displayName
 \return PF_Entity
*/
PF_Entity *PF_CommonFEMProject::findEntity(const QString &displayName)
{
    QString entityName;
    for(auto e : m_document->getEntityList()){
        switch (e->rtti()) {
        case PF::EntityPoint:
        {
            entityName = QObject::tr("Point")+QString("%1").arg(e->index());
            break;
        }
        case PF::EntityLine:
        {
            entityName = QObject::tr("Line")+QString("%1").arg(e->index());
            break;
        }
        case PF::EntityFace:
        {
            entityName = QObject::tr("Face")+QString("%1").arg(e->index());
            break;
        }
        default:
        {
            qDebug()<<"No such entity.";
            break;
        }
        }
        if(displayName == entityName){
            return e;
        }
    }
    return nullptr;
}
}//MagFEMProjectManagerPlugin

