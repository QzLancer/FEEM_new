#include "pf_mag2dsproject.h"
#include "pf_magfemnode.h"

#include <project/pf_node.h>

#include <QString>
#include <QHash>
#include <QDebug>

using namespace ProjectExplorer;

namespace MagFEMProjectManagerPlugin {

PF_Mag2DSProject::PF_Mag2DSProject()
    :ProjectExplorer::PF_Project ()
{
    m_materialList.push_back(CMaterialProp());
    m_materialList.push_back(CMaterialProp());
    m_materialList.push_back(CMaterialProp());
    m_materialList.push_back(CMaterialProp());

    m_variables.add("length",1);
    m_variables.add("length1",1);
    m_variables.add("length2",1);
    m_variables.add("length3",1);
    setRootProjectNode(PF_Mag2DSNodeTreeBuilder::buildTree(this));
}

PF_Mag2DSProject::~PF_Mag2DSProject()
{

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
    auto material_node = std::make_unique<FolderNode>(QString(QObject::tr("Materials: Materials")),NodeType::Material,QIcon(":/imgs/material.png"));
    for(auto m : pro->m_materialList)
    {
        material_node->addNode(std::make_unique<LeafNode>(m.BlockName,LeafType::CMaterialProp));
    }
    /** 添加几何 **/
    auto geo_node = std::make_unique<FolderNode>(QString(QObject::tr("Geometry1")),NodeType::Geometry,QIcon(":/imgs/geometry.png"));

    /** 添加分网 **/
    auto mesh_node = std::make_unique<FolderNode>(QString(QObject::tr("Mesh1")),NodeType::Mesh,QIcon(":/imgs/mesh.png"));

    auto globaldef_node = std::make_unique<FolderNode>(QString(QObject::tr("Global Definitions")),NodeType::Definition,QIcon(":/imgs/global_branch.png"));

    auto comp_node = std::make_unique<FolderNode>(QString(QObject::tr("Component: Component1")),NodeType::Component,QIcon(":/imgs/model_2d_axi.png"));

    globaldef_node->addNode(std::move(def_node));
    globaldef_node->addNode(std::move(material_node));

    comp_node->addNode(std::move(geo_node));
    comp_node->addNode(std::move(mesh_node));

    node->addNode(std::move(globaldef_node));
    node->addNode(std::move(comp_node));
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
