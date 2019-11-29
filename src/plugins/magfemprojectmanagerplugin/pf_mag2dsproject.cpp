#include "pf_mag2dsproject.h"
#include "pf_magfemnode.h"

#include <project/pf_node.h>
#include <project/pf_projecttree.h>

#include <material/materialplugin.h>
#include <output/outputpluginplugin.h>

#include <QString>
#include <QHash>
#include <QDebug>

using namespace ProjectExplorer;

namespace MagFEMProjectManagerPlugin {

PF_Mag2DSProject::PF_Mag2DSProject()
    :ProjectExplorer::PF_Project ()
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
                OutputPlugin::OutputPluginPlugin::write(s);
                return;
            }
        }
        m_materialList.push_back(*material);
        /** 更新tree **/
        /** 这里有问题，如果不是从tree操作进来的，那么node就不对了 **/
        Node *node = PF_ProjectTree::findCurrentNode();
        FolderNode *folderNode = node ? node->asFolderNode() : nullptr;
        /** 需要判断为文件夹，不清楚需不需要判断是材料类型
            感觉不需要，因为右键菜单就是根据材料进来的   **/
        if(!folderNode) return;
        folderNode->addNode(std::make_unique<LeafNode>(material->BlockName,LeafType::CMaterialProp));
        PF_ProjectTree::emitSubtreeChanged(folderNode);
        OutputPlugin::OutputPluginPlugin::write("Material "+material->BlockName+" Added.");
    });
}

PF_Mag2DSProject::~PF_Mag2DSProject()
{

}

void PF_Mag2DSProject::updateData()
{
    setRootProjectNode(PF_Mag2DSNodeTreeBuilder::buildTree(this));
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
        material_node->addNode(std::make_unique<LeafNode>(m.BlockName,LeafType::CMaterialProp));
    }
    /** 添加几何 **/
    auto geo_node = std::make_unique<FolderNode>(QString(QObject::tr("Geometry")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));
    auto point_node = std::make_unique<FolderNode>(QString(QObject::tr("Point")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));
    auto line_node = std::make_unique<FolderNode>(QString(QObject::tr("Line")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));
    auto face_node = std::make_unique<FolderNode>(QString(QObject::tr("Face")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));
    /** 添加分网 **/
    auto mesh_node = std::make_unique<FolderNode>(QString(QObject::tr("Mesh")),NodeType::Mesh,QIcon(":/imgs/mesh.png"));
    auto mesh_point_node = std::make_unique<FolderNode>(QString(QObject::tr("Mesh Point")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));
    auto mesh_line_node = std::make_unique<FolderNode>(QString(QObject::tr("Mesh Line")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));
    auto mesh_face_node = std::make_unique<FolderNode>(QString(QObject::tr("Mesh Face")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));

//    auto globaldef_node = std::make_unique<FolderNode>(QString(QObject::tr("Global Definitions")),NodeType::Definition,QIcon(":/imgs/global_branch.png"));

    auto comp_node = std::make_unique<FolderNode>(QString(QObject::tr("Physics")),NodeType::Component,QIcon(":/imgs/model_2d_axi.png"));

    auto solver_node = std::make_unique<FolderNode>(QString(QObject::tr("Solver")),NodeType::Component,QIcon(":/imgs/model_2d_axi.png"));

    auto result_node = std::make_unique<FolderNode>(QString(QObject::tr("Result")),NodeType::Component,QIcon(":/imgs/model_2d_axi.png"));

    geo_node->addNode(std::move(def_node));
    geo_node->addNode(std::move(point_node));
    geo_node->addNode(std::move(line_node));
    geo_node->addNode(std::move(face_node));

    mesh_node->addNode(std::move(mesh_point_node));
    mesh_node->addNode(std::move(mesh_line_node));
    mesh_node->addNode(std::move(mesh_face_node));

    comp_node->addNode(std::move(material_node));

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
    /** 先创建一个root节点 **/
    auto root = std::make_unique<PF_MagFEMNode>(pro);

    /** 生成root的子节点 **/
    createTree(pro,root.get());

    return root;
}

}// namespace MagFEMProjectManagerPlugin
