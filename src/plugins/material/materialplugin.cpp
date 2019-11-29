#include "materialplugin.h"
#include "materialconstants.h"

#include "pf_materiallibrary.h"
#include "pf_magmaterialdialog.h"
#include "pf_material.h"

#include "qtribbon/include/QtnRibbonGroup.h"

#include <QtAdvancedDock/DockManager.h>

#include <coreplugin/constants.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/workpage.h>
#include <coreplugin/icore.h>

#include <project/projectexplorerconstants.h>
#include <project/pf_node.h>
#include <project/pf_projecttree.h>

#include <extensionsystem/pluginerroroverview.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>
#include <utils/algorithm.h>
#include <utils/mimetypes/mimedatabase.h>
#include <utils/stringutils.h>

#include <QtPlugin>

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QMenu>
#include <QUuid>

#include <cstdlib>

using namespace Core;
using namespace ProjectExplorer;

namespace Material {
static MaterialPlugin *m_instance = nullptr;

MaterialPlugin::MaterialPlugin()
{
    m_instance = this;
}

MaterialPlugin::~MaterialPlugin()
{

}

MaterialPlugin *MaterialPlugin::instance()
{
    return m_instance;
}

void MaterialPlugin::addBlankMaterial()
{
    /** 这里有问题，如果不是从tree操作进来的，那么node就不对了 **/
    Node *node = PF_ProjectTree::findCurrentNode();
    FolderNode *folderNode = node ? node->asFolderNode() : nullptr;
    /** 需要判断为文件夹，不清楚需不需要判断是材料类型
        感觉不需要，因为右键菜单就是根据材料进来的   **/
    if(!folderNode) return;

    PF_MagMaterialDialog* dialog = new PF_MagMaterialDialog(Core::ICore::dialogParent());
    dialog->setWindowTitle(tr("Add Blank Material"));
    int result = dialog->exec();
    /** 获取result之后，对话框已经关闭了，变量不存在了，
        解决方法，不设置WA_DeleteOnClose，但是对话框要设置parents，
        不然会内存泄漏**/
    if(result == QDialog::Accepted){
        emit materialAdded(dialog->getMaterial());
        /** 但是这个也不能直接添加吧，如果重名的话，就不能添加，
            主要的问题在于现在的插件依赖关系，是Project依赖material插件，
            所以，material不能反向去包含Project插件。。。。。**/
        /** 如何把这个材料值传到Project当中进行保存？主要问题是，
            不清楚是哪一个Project要这个东西，应该是要传给active的Project。**/
    }else{
        qDebug()<<"addBlankMaterial Cancle";
    }
}

bool MaterialPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    registerDefaultContainers();
    registerDefaultActions();

    QWidget* materialLibraryTree = new PF_MaterialLibraryWidget();
    ads::CDockWidget* DockWidget3 = new ads::CDockWidget(tr("Material library"));
    DockWidget3->setWidget(materialLibraryTree);
    // Add the dock widget to the top dock widget area
    Core::WorkPage::DockManager()->addDockWidget(ads::RightDockWidgetArea, DockWidget3);

    return true;
}

void MaterialPlugin::extensionsInitialized()
{

}

bool MaterialPlugin::delayedInitialize()
{
	return true;
}

ExtensionSystem::IPlugin::ShutdownFlag MaterialPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}

QObject *MaterialPlugin::remoteCommand(const QStringList &, const QString &workingDirectory, const QStringList &args)
{
    return nullptr;
}

void MaterialPlugin::registerDefaultContainers()
{
    /** 添加P_MATERIAL group **/
    ActionContainer* page = ActionManager::actionContainer(Core::Constants::P_MATERIAL);
    /** 材料 **/
    ActionContainer* group = ActionManager::createRibbonGroup(Constants::G_MATERIAL_LIBRARY);
    group->ribbonGroup()->setTitle(tr("Material"));
    page->appendGroup(Constants::G_MATERIAL_LIBRARY);
    page->addRibbonGroup(group,Constants::G_MATERIAL_LIBRARY);
}

void MaterialPlugin::registerDefaultActions()
{
    auto group = ActionManager::actionContainer(Constants::G_MATERIAL_LIBRARY);
    group->ribbonGroup()->addAction(QIcon(":/material/imgs/addmaterial.png"), tr("Add material"), Qt::ToolButtonTextUnderIcon);
    group->ribbonGroup()->addAction(QIcon(":/material/imgs/materiallibrary.png"), tr("Material library"), Qt::ToolButtonTextUnderIcon);

    /** 材料 节点 **/
    ActionContainer *mmaterialContextMenu =
        ActionManager::createMenu(ProjectExplorer::Constants::M_MATERIALCONTEXT);
    mmaterialContextMenu->appendGroup(ProjectExplorer::Constants::G_HELP);

    /************material******************/
    m_addMaterial = new QAction(QIcon(":/material/imgs/material_picker.png"),tr("add Material"), this);
    Command* cmd = ActionManager::registerAction(m_addMaterial, Constants::ADDMATERIAL);
    //    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+N")));
    mmaterialContextMenu->addAction(cmd,Core::Constants::G_DEFAULT_ONE);

    m_addBlankMaterial = new QAction(QIcon(":/material/imgs/more_materials.png"),tr("add Blank Material"), this);
    cmd = ActionManager::registerAction(m_addBlankMaterial, Constants::ADDBLANKMATERIAL);
    //    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+N")));

    mmaterialContextMenu->addAction(cmd,Core::Constants::G_DEFAULT_ONE);
    // help
    m_help = new QAction(QIcon(":/imgs/help_16.png"),tr("Help"), this);
    cmd = ActionManager::command(Constants::HELP);
    mmaterialContextMenu->addSeparator(ProjectExplorer::Constants::G_HELP);
    mmaterialContextMenu->addAction(cmd,ProjectExplorer::Constants::G_HELP);

    connect(m_addBlankMaterial,&QAction::triggered,this,&MaterialPlugin::addBlankMaterial);

}
}//namespace Material
