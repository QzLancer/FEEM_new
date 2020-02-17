#include "postoperationplugin.h"
#include "postoperationconstants.h"
#include "pf_resultnode.h"

#include "contourtest/contourtestwidget.h"

#include "qtribbon/include/QtnRibbonGroup.h"

#include <project/pf_projecttree.h>
#include <project/projectexplorerconstants.h>

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
using namespace ProjectExplorer;

namespace Postoperation {
static PostoperationPlugin * m_instance = nullptr;

PostoperationPlugin::PostoperationPlugin()
{
    m_instance = this;
}

PostoperationPlugin::~PostoperationPlugin()
{

}

PostoperationPlugin *PostoperationPlugin::instance()
{
    return m_instance;
}

bool PostoperationPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    qDebug()<<Q_FUNC_INFO;
    registerDefaultContainers();
    registerDefaultActions();
    return true;
}

void PostoperationPlugin::extensionsInitialized()
{
//    ContourTestWidget* w = new ContourTestWidget;
//    w->show();
}

bool PostoperationPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag PostoperationPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}

QObject *PostoperationPlugin::remoteCommand(const QStringList &, const QString &workingDirectory, const QStringList &args)
{
    return nullptr;
}

void PostoperationPlugin::registerDefaultContainers()
{
    /** 添加 group **/
    ActionContainer* page = ActionManager::actionContainer(Core::Constants::P_RESULT);
    /**  **/
    ActionContainer* group = ActionManager::createRibbonGroup(Constants::G_RESULT_PLOT);
    group->ribbonGroup()->setTitle(tr("Postoperation Setting"));
    page->appendGroup(Constants::G_RESULT_PLOT);
    page->addRibbonGroup(group,Constants::G_RESULT_PLOT);

    /** 添加绘图组的右键菜单 **/
    //2d curve
    ActionContainer *resultContextMenu =
        ActionManager::actionContainer(ProjectExplorer::Constants::M_FOLDERCONTEXT);
    m_new2dPlot = new QAction(tr("New 2D Curve Plot"), this);
    Command* cmd = ActionManager::registerAction(m_new2dPlot, Constants::G_2DCURVE_PLOT);
    //    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+N")));
    resultContextMenu->addAction(cmd,Core::Constants::G_DEFAULT_ONE);
    connect(m_new2dPlot,&QAction::triggered,this,&PostoperationPlugin::new2DCurvePlot);
    //2d surface
    m_new2dsurfacePlot = new QAction(tr("New 2D Surface Plot"), this);
    cmd = ActionManager::registerAction(m_new2dsurfacePlot, Constants::G_2DSURFACE_PLOT);
    //    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+N")));
    resultContextMenu->addAction(cmd,Core::Constants::G_DEFAULT_ONE);
    connect(m_new2dPlot,&QAction::triggered,this,&PostoperationPlugin::new2DSurfacePlot);

    connect(PF_ProjectTree::instance(), &PF_ProjectTree::currentNodeChanged,
            this, &PostoperationPlugin::updateContextActions);
}

void PostoperationPlugin::registerDefaultActions()
{

}

void PostoperationPlugin::updateContextActions()
{
    /** 判断是不是分网节点 **/
    const Node *node = PF_ProjectTree::findCurrentNode();
    const bool isSolverNode = dynamic_cast<const PF_ResultNode *>(node);

    m_new2dPlot->setEnabled(isSolverNode);
    m_new2dPlot->setVisible(isSolverNode);

    m_new2dsurfacePlot->setEnabled(isSolverNode);
    m_new2dsurfacePlot->setVisible(isSolverNode);
}

void PostoperationPlugin::new2DCurvePlot()
{

}

void PostoperationPlugin::new2DSurfacePlot()
{

}

}//namespace Postoperation

