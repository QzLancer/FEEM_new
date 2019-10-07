#include "cad.h"
#include "pf_actionhandler.h"
#include "cadconstants.h"

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

namespace CAD {
static CADPlugin *m_instance = nullptr;

CADPlugin::CADPlugin()
//    :ac_handler(new PF_ActionHandler)
{
    m_instance = this;
}

CADPlugin::~CADPlugin()
{

}

CADPlugin *CADPlugin::instance()
{
    return m_instance;
}

bool CADPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    registerDefaultContainers();
    registerDefaultActions();
    return true;
}

void CADPlugin::extensionsInitialized()
{

}

bool CADPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag CADPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}

QObject *CADPlugin::remoteCommand(const QStringList &, const QString &workingDirectory, const QStringList &args)
{
    return nullptr;
}

/**
 * @brief 添加关于CAD方面的container
 *
 */
void CADPlugin::registerDefaultContainers()
{
    /** 添加geometry group **/
    ActionContainer* page = ActionManager::actionContainer(Core::Constants::P_GEOMETRY);
    /** 导入导出 **/
    ActionContainer* group = ActionManager::createRibbonGroup(Constants::G_GEOMETRY_IMEXPORT);
    group->ribbonGroup()->setTitle(tr("Import/Export"));
    page->appendGroup(Constants::G_GEOMETRY_IMEXPORT);
    page->addRibbonGroup(group,Constants::G_GEOMETRY_IMEXPORT);
    /** 构建 **/
    group = ActionManager::createRibbonGroup(Constants::G_GEOMETRY_BUILD);
    group->ribbonGroup()->setTitle(tr("BuildGeometry"));
    page->appendGroup(Constants::G_GEOMETRY_BUILD);
    page->addRibbonGroup(group,Constants::G_GEOMETRY_BUILD);
    /** 绘图设置 **/
    group = ActionManager::createRibbonGroup(Constants::G_GEOMETRY_SETTING);
    group->ribbonGroup()->setTitle(tr("DrawSetting"));
    page->appendGroup(Constants::G_GEOMETRY_SETTING);
    page->addRibbonGroup(group,Constants::G_GEOMETRY_SETTING);
    /** 绘图 **/
    group = ActionManager::createRibbonGroup(Constants::G_GEOMETRY_DRAW);
    group->ribbonGroup()->setTitle(tr("Draw"));
    page->appendGroup(Constants::G_GEOMETRY_DRAW);
    page->addRibbonGroup(group,Constants::G_GEOMETRY_DRAW);
    /** 绘图操作 **/
    group = ActionManager::createRibbonGroup(Constants::G_GEOMETRY_OPERATION);
    group->ribbonGroup()->setTitle(tr("DrawOperation"));
    page->appendGroup(Constants::G_GEOMETRY_OPERATION);
    page->addRibbonGroup(group,Constants::G_GEOMETRY_OPERATION);
    /** 试图 **/
    group = ActionManager::createRibbonGroup(Constants::G_GEOMETRY_VIEW);
    group->ribbonGroup()->setTitle(tr("View"));
    page->appendGroup(Constants::G_GEOMETRY_VIEW);
    page->addRibbonGroup(group,Constants::G_GEOMETRY_VIEW);
}

/**
 * @brief 注册CAD方面的actions
 *
 */
void CADPlugin::registerDefaultActions()
{
    auto group = ActionManager::actionContainer(Constants::G_GEOMETRY_IMEXPORT);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/import.png"), tr("Import Geometry"), Qt::ToolButtonTextUnderIcon);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/export.png"), tr("Export Geometry"), Qt::ToolButtonTextUnderIcon);
    group = ActionManager::actionContainer(Constants::G_GEOMETRY_BUILD);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/buildgeometry.png"), tr("Build Geometry"), Qt::ToolButtonTextUnderIcon);

    group = ActionManager::actionContainer(Constants::G_GEOMETRY_SETTING);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/snapgrid.png"), tr("Snap to grid"), Qt::ToolButtonTextBesideIcon);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/snapgeometry.png"), tr("Snap to geometry"), Qt::ToolButtonTextBesideIcon);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/solid.png"), tr("Solid"), Qt::ToolButtonTextBesideIcon);

    group = ActionManager::actionContainer(Constants::G_GEOMETRY_SETTING);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/snapgrid.png"), tr("Snap to grid"), Qt::ToolButtonTextBesideIcon);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/snapgeometry.png"), tr("Snap to geometry"), Qt::ToolButtonTextBesideIcon);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/solid.png"), tr("Solid"), Qt::ToolButtonTextBesideIcon);

}
}//namespace CAD
