#include "pf_mag2dsproject.h"
#include "pf_magfemnode.h"
#include "pf_facesettingdialog.h"

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
    :ProjectExplorer::PF_Project()
    ,m_document(new PF_Document())
    ,m_mesh(new CMesh())
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
        this->updateData();
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

/*!
 \brief 主要是通过名字查找entity

 \param displayName
 \return PF_Entity
*/
PF_Entity *PF_Mag2DSProject::findEntity(const QString &displayName)
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

Core::IGeometry *PF_Mag2DSProject::CAD() const
{
    return cad2d;
}

/*!
 \brief 打开材料对话框并进行编辑。

 \param node
*/
void PF_Mag2DSProject::editMaterial(Node *node)
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
            int result = dialog->exec();
            break;
        }
    }

}

/*!
 \brief 项目树右键菜单进行分网

 \param node
*/
void PF_Mag2DSProject::doMesh()
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
void PF_Mag2DSProject::entitySelected(bool selected, Node *node)
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
void PF_Mag2DSProject::setFaceMaterial(Node *node)
{
    auto e = findEntity(node->displayName());
    int index = -1;
    if(e) index = e->index();
    auto dialog = new PF_FaceSettingDialog(Core::ICore::dialogParent(),this,index);
    QString title = QObject::tr("Set ")+node->displayName()+QObject::tr(" properties");
    dialog->setWindowTitle(title);
    dialog->exec();
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
    for(auto m : pro->m_materialList)
    {
        material_node->addNode(std::make_unique<LeafNode>(m.BlockName,LeafType::CMaterialProp,NodeType::Leaf,QIcon(":/imgs/material.png")));
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
