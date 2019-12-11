#include "meshplugin.h"
#include "meshconstants.h"

#include "qtribbon/include/QtnRibbonGroup.h"

#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/constants.h>

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

namespace Mesh {
static MeshPlugin * m_instance = nullptr;

MeshPlugin::MeshPlugin()
{
    m_instance = this;
}

MeshPlugin::~MeshPlugin()
{

}

MeshPlugin *MeshPlugin::instance()
{
    return m_instance;
}

bool MeshPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    registerDefaultContainers();
    registerDefaultActions();
    return true;
}

void MeshPlugin::extensionsInitialized()
{

}

bool MeshPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag MeshPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}

QObject *MeshPlugin::remoteCommand(const QStringList &, const QString &workingDirectory, const QStringList &args)
{
    return nullptr;
}

void MeshPlugin::registerDefaultContainers()
{
    /** 添加 group **/
    ActionContainer* page = ActionManager::actionContainer(Core::Constants::P_MESH);
    /**  **/
    ActionContainer* group = ActionManager::createRibbonGroup(Constants::G_MESH_BUILD);
    group->ribbonGroup()->setTitle(tr("BuildMesh"));
    page->appendGroup(Constants::G_MESH_BUILD);
    page->addRibbonGroup(group,Constants::G_MESH_BUILD);

    auto action = new QAction(tr("Build mesh"));
    action->setIcon(QIcon(":/imgs/buildmesh.png"));
    group->ribbonGroup()->addAction(action,Qt::ToolButtonTextUnderIcon);

    group = ActionManager::createRibbonGroup(Constants::G_MESH_IMEXPORT);
    group->ribbonGroup()->setTitle(tr("Im/ExportMesh"));
    page->appendGroup(Constants::G_MESH_IMEXPORT);
    page->addRibbonGroup(group,Constants::G_MESH_IMEXPORT);

    action = new QAction(tr("Import mesh"));
    action->setIcon(QIcon(":/imgs/import.png"));
    group->ribbonGroup()->addAction(action,Qt::ToolButtonTextUnderIcon);

    action = new QAction(tr("Export mesh"));
    action->setIcon(QIcon(":/imgs/export.png"));
    group->ribbonGroup()->addAction(action,Qt::ToolButtonTextUnderIcon);

    group = ActionManager::createRibbonGroup(Constants::G_MESH_GENERATOR);
    group->ribbonGroup()->setTitle(tr("Mesh Generator"));
    page->appendGroup(Constants::G_MESH_GENERATOR);
    page->addRibbonGroup(group,Constants::G_MESH_GENERATOR);

    action = new QAction(tr("Mesh generator"));
    action->setIcon(QIcon(":/imgs/meshgenerator.png"));
    group->ribbonGroup()->addAction(action,Qt::ToolButtonTextUnderIcon);

    group = ActionManager::createRibbonGroup(Constants::G_MESH_STATICS);
    group->ribbonGroup()->setTitle(tr("Statics"));
    page->appendGroup(Constants::G_MESH_STATICS);
    page->addRibbonGroup(group,Constants::G_MESH_STATICS);

    action = new QAction(tr("Statics"));
    action->setIcon(QIcon(":/imgs/Statics.png"));
    group->ribbonGroup()->addAction(action,Qt::ToolButtonTextUnderIcon);

    group = ActionManager::createRibbonGroup(Constants::G_MESH_CLEAR);
    group->ribbonGroup()->setTitle(tr("ClearMesh"));
    page->appendGroup(Constants::G_MESH_CLEAR);
    page->addRibbonGroup(group,Constants::G_MESH_CLEAR);

    action = new QAction(tr("Clear mesh"));
    action->setIcon(QIcon(":/imgs/clearmesh.png"));
    group->ribbonGroup()->addAction(action,Qt::ToolButtonTextUnderIcon);

    /** projecttree当中的右键菜单 **/
    ActionContainer *meshContextMenu =
        ActionManager::createMenu(Constants::M_MESHCONTEXT);
    m_autoMesh = new QAction(tr("Auto mesh"), this);
    Command* cmd = ActionManager::registerAction(m_autoMesh, Constants::G_MESH_AUTO);
    //    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+N")));
    meshContextMenu->addAction(cmd,Core::Constants::G_DEFAULT_ONE);

}

void MeshPlugin::registerDefaultActions()
{

}

}//namespace Mesh

