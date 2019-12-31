#include "pf_project.h"
#include "pf_node.h"
#include "pf_femprojectaccessor.h"

#include <coreplugin/idocument.h>
#include "pf_nodetreebuilder.h"
#include "pf_projecttree.h"

#include <coreplugin/geometrymanager/igeometry.h>
#include <coreplugin/icore.h>

#include <memory>
#include <QDebug>

#include <QDir>
#include <QFileDialog>

using namespace Utils;
namespace ProjectExplorer {
// --------------------------------------------------------------------
// ProjectDocument:
// --------------------------------------------------------------------

ProjectDocument::ProjectDocument(const QString& mimeType, const FileName &fileName)
{
    setFilePath(fileName);
    setMimeType(mimeType);
//    if (m_callback)
//        DocumentManager::addDocument(this);
}

Core::IDocument::ReloadBehavior
ProjectDocument::reloadBehavior(IDocument::ChangeTrigger state,
                                IDocument::ChangeType type) const
{
    Q_UNUSED(state);
    Q_UNUSED(type);
    return BehaviorSilent;
}

bool ProjectDocument::reload(QString *errorString, IDocument::ReloadFlag flag,
                             IDocument::ChangeType type)
{
    Q_UNUSED(errorString);
    Q_UNUSED(flag);
    Q_UNUSED(type);

//    if (m_callback)
//        m_callback();
    return true;
}
/*!
 \brief Project的具体实现。

*/
class PF_ProjectPrivate{
public:
    PF_ProjectPrivate(const QString &mimeType, const FileName &fileName)
    {
        m_document = std::make_unique<ProjectDocument>(mimeType, fileName);
    }
    ~PF_ProjectPrivate();

    /** 保存真实的文件 **/
    std::unique_ptr<Core::IDocument> m_document;
    std::unique_ptr<ProjectNode> m_rootProjectNode;
    std::unique_ptr<ProjectNode> m_containerNode;
    std::unique_ptr<PF_FEMProjectAccessor> m_accessor;

    QString m_displayName;
};

PF_Project::PF_Project(const QString& mimeType, const FileName &fileName)
    : d(new PF_ProjectPrivate(mimeType, fileName))
{
    d->m_containerNode = std::make_unique<ProjectNode>(this);
//    setRootProjectNode(PF_NodeTreeBuilder::buildTree(this));
}

PF_Project::~PF_Project()
{

}

QString PF_Project::displayName() const
{
    if(d->m_displayName.isEmpty()){
        d->m_displayName = QString(tr("untitled"));
    }

    return d->m_displayName;
}

void PF_Project::setDisplayName(const QString &displayName)
{
    d->m_displayName = displayName;
}

Core::IDocument*PF_Project::document() const
{
    return d->m_document.get();
}

FileName PF_Project::projectFilePath() const
{
    return document()->filePath();
}

FileName PF_Project::projectDirectory() const
{
    auto filePath = document()->filePath();
    if(filePath.isEmpty())
        return FileName();
    return Utils::FileName::fromString(filePath.toFileInfo().absoluteDir().path());
}

/**
 * @brief 简单的测试tree
 *
 */
void PF_Project::creatTree()
{
    std::unique_ptr<ProjectNode> root = std::make_unique<ProjectNode>(this);
    std::vector<std::unique_ptr<FolderNode>> nodes;
    nodes.emplace_back(std::make_unique<FolderNode>(QString(tr("Global Definitions")),NodeType::Definition,QIcon(":/imgs/global_branch.png")));
    nodes.emplace_back(std::make_unique<FolderNode>(QString(tr("Materials: Materials")),NodeType::Material,QIcon(":/imgs/material.png")));
    nodes.emplace_back(std::make_unique<FolderNode>(QString(tr("Component: Component1")),NodeType::Component,QIcon(":/imgs/model_2d_axi.png")));
    nodes.emplace_back(std::make_unique<FolderNode>(QString(tr("Definitions")),NodeType::Variable,QIcon(":/imgs/definitions.png")));
    nodes.emplace_back(std::make_unique<FolderNode>(QString(tr("Geometry1")),NodeType::Geometry,QIcon(":/imgs/geometry.png")));
    nodes.emplace_back(std::make_unique<FolderNode>(QString(tr("Mesh1")),NodeType::Mesh,QIcon(":/imgs/mesh.png")));

    nodes.at(0)->addNode(std::move(nodes.at(3)));
    nodes.at(0)->addNode(std::move(nodes.at(1)));
    root->addNode(std::move(nodes.at(0)));

    nodes.at(2)->addNode(std::move(nodes.at(4)));
    nodes.at(2)->addNode(std::move(nodes.at(5)));
    root->addNode(std::move(nodes.at(2)));

    setRootProjectNode(std::move(root));
}

/*!
 \brief 将root设置为项目的节点，在此之前，应该已经对project进行了处理，
 并得到projectnode。

 \param root
*/
void PF_Project::setRootProjectNode(std::unique_ptr<ProjectNode> &&root)
{
//    qDebug()<<Q_FUNC_INFO;
    if(d->m_rootProjectNode.get() == root.get() && root)
        return;

    if (root && root->isEmpty()) {
        // Something went wrong with parsing: At least the project file needs to be
        // shown so that the user can fix the breakage.
        // Do not leak root and use default project tree in this case.
        root.reset();
    }

    if (root) {
//        ProjectTree::applyTreeManager(root.get());
        root->setParentFolderNode(d->m_containerNode.get());
        /** 感觉要更新一下container的显示 **/
        d->m_containerNode.get()->setDisplayName(root.get()->displayName());
    }

    std::unique_ptr<ProjectNode> oldNode = std::move(d->m_rootProjectNode);

    d->m_rootProjectNode = std::move(root);
    if (oldNode || d->m_rootProjectNode)
        handleSubTreeChanged(d->m_containerNode.get());
}

/*!
 \brief 应该是让tree控件生效，让model重新生成一下tree数据，应该有
 两层的关系，一层是node，一层是treeitem，

 \param node
*/
void PF_Project::handleSubTreeChanged(FolderNode* node)
{
//    qDebug()<<Q_FUNC_INFO;

    PF_ProjectTree::emitSubtreeChanged(node);
//    emit fileListChanged();
}

/*!
 \brief 返回根部的节点

 \return ProjectNode
*/
ProjectNode* PF_Project::rootProjectNode() const
{
    return d->m_rootProjectNode.get();
}

ProjectNode *PF_Project::containerNode() const
{
    return d->m_containerNode.get();
}

/*!
 \brief 将Project当中的数据保存到map当中。子类如果要重写该函数，那么
 可能需要先调用父类的该函数。

 \return QVariantMap
*/
QVariantMap PF_Project::toMap() const
{
    QVariantMap map;
    return map;
}

/*!
 \brief 将数据从map中恢复出来。

 \param map
 \param errorMessage
 \return PF_Project::RestoreResult
*/
PF_Project::RestoreResult PF_Project::fromMap(const QVariantMap &map, QString *errorMessage)
{
    return RestoreResult::Ok;
}

/**
 * @brief 保存project，一般来说，保存的数据都在toMap里存储，这样，子类不需要重写该函数。
 *
 * @param fileName
 */
void PF_Project::saveProject()
{
//    emit aboutToSaveProject();
    /** 判断当前项目文件存在不存在，否则打开保存对话框 **/
    QString f;
    if(document()->filePath().isEmpty()){
        f = QFileDialog::getSaveFileName(
            Core::ICore::dialogParent(), tr("Save project file to..."),
                    QString("."), QString("FEEM project file(*.feem)"));
        if(f.isEmpty()) return;
        auto fileinfo = QFileInfo(f);
        QString fileSuffix = fileinfo.suffix();
        if(fileSuffix.compare("feem",Qt::CaseInsensitive) != 0)
            f += ".feem";
        document()->setFilePath(FileName::fromString(f));
        /** 修改项目的显示名称 **/
        setDisplayName(fileinfo.baseName());
        emit displayNameChanged();
        emit dataChanged();
//        if (QFile::exists(fileName)) {
//            if (QMessageBox::warning(Core::ICore::dialogParent(), tr("Overwrite?"),
//                tr("An item named \"%1\" already exists at this location. "
//                   "Do you want to overwrite it?").arg(QDir::toNativeSeparators(fileName)),
//                QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
//                repeat = true;
//            }
//        }
    }
    if (!d->m_accessor)
        d->m_accessor = std::make_unique<PF_FEMProjectAccessor>(this);
    /** 保存数据 **/
    d->m_accessor->saveProject(toMap(), Core::ICore::mainWindow());
}

/**
 * @brief 从项目文件中恢复文件。
 *
 * @param errorMessage
 * @return PF_Project::RestoreResult
 */
PF_Project::RestoreResult PF_Project::restoreProject(QString* errorMessage)
{
    if (!d->m_accessor)
        d->m_accessor = std::make_unique<PF_FEMProjectAccessor>(this);
    QVariantMap map(d->m_accessor->restoreProject(Core::ICore::mainWindow()));
    RestoreResult result = fromMap(map, errorMessage);
//    if (result == RestoreResult::Ok)
//        emit settingsLoaded();
    return result;
}

Core::IGeometry *PF_Project::CAD() const
{
    return nullptr;
}

void PF_Project::editMaterial(Node *node)
{

}

void PF_Project::doMesh()
{

}

void PF_Project::entitySelected(bool selected, Node *node)
{

}

void PF_Project::setFaceMaterial(Node *node)
{

}



PF_ProjectPrivate::~PF_ProjectPrivate()
{
    // Make sure our root node is null when deleting the actual node
    std::unique_ptr<ProjectNode> oldNode = std::move(m_rootProjectNode);
}
}//namespace ProjectExplorer
