#include "cad.h"
#include "pf_actionhandler.h"
#include "cadconstants.h"
#include "pf_cadwidget.h"

#include "qtribbon/include/QtnRibbonGroup.h"

#include <QtAdvancedDock/DockManager.h>

#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/constants.h>
#include <coreplugin/workpage.h>
#include <coreplugin/geometrymanager/geometryview.h>
#include <coreplugin/geometrymanager/geometrymanager_p.h>

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
    :action_handler(new PF_ActionHandler)
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

    /** 如果将CAD看作一个文件编辑器，那么这里应该是创建一个占位的控件，
        当需要打开文件的时候，才会创建相应的控件，并进行激活和切换。**/
    auto* cad = new GeometryView;
    GeometryManagerPrivate::instance()->setCurrentView(cad);
    ads::CDockWidget* DockWidget = new ads::CDockWidget(tr("Geometry builder"));
    DockWidget->setWidget(cad);
    // Add the dock widget to the top dock widget area
    Core::WorkPage::DockManager()->addDockWidget(ads::TopDockWidgetArea, DockWidget);
    qDebug()<<Q_FUNC_INFO;
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
    /** 绘图 **/
    group = ActionManager::createRibbonGroup(Constants::G_GEOMETRY_DRAW);
    group->ribbonGroup()->setTitle(tr("Draw"));
    page->appendGroup(Constants::G_GEOMETRY_DRAW);
    page->addRibbonGroup(group,Constants::G_GEOMETRY_DRAW);
    /** 绘图设置 **/
    group = ActionManager::createRibbonGroup(Constants::G_GEOMETRY_SETTING);
    group->ribbonGroup()->setTitle(tr("DrawSetting"));
    page->appendGroup(Constants::G_GEOMETRY_SETTING);
    page->addRibbonGroup(group,Constants::G_GEOMETRY_SETTING);   
    /** 绘图操作 **/
    group = ActionManager::createRibbonGroup(Constants::G_GEOMETRY_OPERATION);
    group->ribbonGroup()->setTitle(tr("DrawOperation"));
    page->appendGroup(Constants::G_GEOMETRY_OPERATION);
    page->addRibbonGroup(group,Constants::G_GEOMETRY_OPERATION);
    /** 视图 **/
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
    /** 导入导出 **/
    auto group = ActionManager::actionContainer(Constants::G_GEOMETRY_IMEXPORT);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/import.png"), tr("Import Geometry"), Qt::ToolButtonTextUnderIcon);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/export.png"), tr("Export Geometry"), Qt::ToolButtonTextUnderIcon);
    /** 构建 **/
    group = ActionManager::actionContainer(Constants::G_GEOMETRY_BUILD);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/buildgeometry.png"), tr("Build Geometry"), Qt::ToolButtonTextUnderIcon);
    /** 绘图 **/
    /**画点**/
    group = ActionManager::actionContainer(Constants::G_GEOMETRY_DRAW);
    auto action = new QAction(tr("DrawPoint"));
    action->setIcon(QIcon(":/cad/imgs/dot.png"));
    connect(action, SIGNAL(triggered()), action_handler, SLOT(slotDrawPoint()));
    action->setObjectName("DrawPoint");
    group->ribbonGroup()->addAction(action, Qt::ToolButtonTextUnderIcon);

    /**画线段**/
    action = new QAction(tr("DrawLine"));
    action->setIcon(QIcon(":/cad/imgs/line.png"));
    connect(action, SIGNAL(triggered()), action_handler, SLOT(slotDrawLine()));
    action->setObjectName("DrawLine");
    group->ribbonGroup()->addAction(action, Qt::ToolButtonTextUnderIcon);

    /**画闭合面**/
    action = new QAction(tr("DrawFace"));
    connect(action, SIGNAL(triggered()), action_handler, SLOT(slotDrawFace()));
    action->setObjectName("DrawFace");
    action->setIcon(QIcon(":/cad/imgs/square.png"));
    group->ribbonGroup()->addAction(action, Qt::ToolButtonTextUnderIcon);

    /**画圆**/
    action = new QAction(tr("DrawCircle"));
    connect(action, SIGNAL(triggered()), action_handler, SLOT(slotDrawCircle()));
    action->setObjectName("DrawCircle");
    action->setIcon(QIcon(":/cad/imgs/circle.png"));
    group->ribbonGroup()->addAction(action, Qt::ToolButtonTextUnderIcon);

    /** 绘图设置 **/
    group = ActionManager::actionContainer(Constants::G_GEOMETRY_SETTING);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/snapgrid.png"), tr("Snap to grid"), Qt::ToolButtonTextBesideIcon);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/snapgeometry.png"), tr("Snap to geometry"), Qt::ToolButtonTextBesideIcon);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/solid.png"), tr("Solid"), Qt::ToolButtonTextBesideIcon);
    /** 绘图操作 **/
    group = ActionManager::actionContainer(Constants::G_GEOMETRY_OPERATION);
    action = new QAction(tr("SelectSingle"));
    connect(action, SIGNAL(triggered()), action_handler, SLOT(slotSelectSingle()));
    action->setObjectName("SelectSingle");
    action->setIcon(QIcon(":/cad/imgs/select16x16.png"));
    group->ribbonGroup()->addAction(action,Qt::ToolButtonTextBesideIcon);

    action = new QAction(tr("SelectAll"));
    action->setIcon(QIcon(":/cad/imgs/snapgeometry.png"));
    connect(action, SIGNAL(triggered()), action_handler, SLOT(slotSelectAll()));
    action->setObjectName("SelectAll");
    group->ribbonGroup()->addAction(action,Qt::ToolButtonTextBesideIcon);

    action = new QAction(tr("DeSelectAll"));
    action->setIcon(QIcon(":/cad/imgs/solid.png"));
    connect(action, SIGNAL(triggered()), action_handler, SLOT(slotDeSelectAll()));
    action->setObjectName("DeSelectAll");
    group->ribbonGroup()->addAction(action,Qt::ToolButtonTextBesideIcon);

    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/cut32x32.png"), tr("Cut"), Qt::ToolButtonTextUnderIcon);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/copy32x32.png"), tr("Copy"), Qt::ToolButtonTextUnderIcon);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/paste32x32.png"), tr("Paste"), Qt::ToolButtonTextUnderIcon);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/delete32x32.png"), tr("Delete"), Qt::ToolButtonTextUnderIcon);
    /** 视图 **/
    group = ActionManager::actionContainer(Constants::G_GEOMETRY_VIEW);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/zoomin32x32.png"), tr("Zoom In"), Qt::ToolButtonTextUnderIcon);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/zoomout32x32.png"), tr("Zoom Out"), Qt::ToolButtonTextUnderIcon);
    group->ribbonGroup()->addAction(QIcon(":/cad/imgs/zoomauto32x32.png"), tr("Zoom Auto"), Qt::ToolButtonTextUnderIcon);

}
}//namespace CAD
