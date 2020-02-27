#include "solverplugin.h"
#include "solverconstants.h"
#include "pf_solvernode.h"

#include "qtribbon/include/QtnRibbonGroup.h"

#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/constants.h>

#include <project/pf_node.h>
#include <project/pf_projecttree.h>
#include <project/projectexplorerconstants.h>

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

namespace Solver {
static SolverPlugin * m_instance = nullptr;

SolverPlugin::SolverPlugin()
{
    m_instance = this;
}

SolverPlugin::~SolverPlugin()
{

}

SolverPlugin *SolverPlugin::instance()
{
    return m_instance;
}

bool SolverPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    qDebug()<<Q_FUNC_INFO;
    registerDefaultContainers();
    registerDefaultActions();
    return true;
}

void SolverPlugin::extensionsInitialized()
{

}

bool SolverPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag SolverPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}

QObject *SolverPlugin::remoteCommand(const QStringList &, const QString &workingDirectory, const QStringList &args)
{
    return nullptr;
}

void SolverPlugin::registerDefaultContainers()
{
    /** 添加 group **/
    ActionContainer* page = ActionManager::actionContainer(Core::Constants::P_SOLVER);
    /** 右键菜单 **/
    ActionContainer *msolverContextMenu =
        ActionManager::actionContainer(ProjectExplorer::Constants::M_FOLDERCONTEXT);
    /**  **/
    ActionContainer* group = ActionManager::createRibbonGroup(Constants::G_SOLVE_SETTING);
    group->ribbonGroup()->setTitle(tr("Solver Setting"));
    page->appendGroup(Constants::G_SOLVE_SETTING);
    page->addRibbonGroup(group,Constants::G_SOLVE_SETTING);

    m_solverSetting = new QAction(tr("Solver Setting"));
    m_solverSetting->setIcon(QIcon(":/imgs/setting.png"));
    group->ribbonGroup()->addAction(m_solverSetting,Qt::ToolButtonTextUnderIcon);

    m_solverSettingcontext = new QAction(tr("Solver Setting"));
    m_solverSettingcontext->setIcon(QIcon(":/imgs/setting.png"));

    group = ActionManager::createRibbonGroup(Constants::G_SOLVE_SOLVE);
    group->ribbonGroup()->setTitle(tr("Solve"));
    page->appendGroup(Constants::G_SOLVE_SOLVE);
    page->addRibbonGroup(group,Constants::G_SOLVE_SOLVE);

    m_solve = new QAction(tr("Solve"));
    m_solve->setIcon(QIcon(":/imgs/solve.png"));
    group->ribbonGroup()->addAction(m_solve,Qt::ToolButtonTextUnderIcon);

    m_solvecontext = new QAction(tr("Solve"));
    m_solvecontext->setIcon(QIcon(":/imgs/solve.png"));

    group = ActionManager::createRibbonGroup(Constants::G_SOLVE_CLEAR);
    group->ribbonGroup()->setTitle(tr("Clear Solution"));
    page->appendGroup(Constants::G_SOLVE_CLEAR);
    page->addRibbonGroup(group,Constants::G_SOLVE_CLEAR);

    m_clearSolution = new QAction(tr("Clear Solution"));
    m_clearSolution->setIcon(QIcon(":/imgs/clearsolution.png"));
    group->ribbonGroup()->addAction(m_clearSolution,Qt::ToolButtonTextUnderIcon);

    m_clearSolutioncontext = new QAction(tr("Clear Solution"));
    m_clearSolutioncontext->setIcon(QIcon(":/imgs/clearsolution.png"));

    Command* cmd = ActionManager::registerAction(m_solvecontext, Constants::M_SOLVECONTEXT);
    //    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+N")));
    msolverContextMenu->addAction(cmd,Core::Constants::G_DEFAULT_ONE);

    cmd = ActionManager::registerAction(m_clearSolutioncontext, Constants::M_CLEARSOLUTIONCONTEXT);
        //    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+N")));
    msolverContextMenu->addAction(cmd,Core::Constants::G_DEFAULT_ONE);

    cmd = ActionManager::registerAction(m_solverSettingcontext, Constants::M_SOLVERSETTINGCONTEXT);
        //    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+N")));
    msolverContextMenu->addAction(cmd,Core::Constants::G_DEFAULT_ONE);

    connect(PF_ProjectTree::instance(), &PF_ProjectTree::currentNodeChanged,
            this, &SolverPlugin::updateContextActions);
}

void SolverPlugin::registerDefaultActions()
{

}

void SolverPlugin::updateContextActions()
{
    /** 判断是不是求解节点 **/
    const Node *node = PF_ProjectTree::findCurrentNode();
    const bool isSolverNode = dynamic_cast<const PF_SolverNode *>(node);

    m_solvecontext->setEnabled(isSolverNode);
    m_solvecontext->setVisible(isSolverNode);

    m_clearSolutioncontext->setEnabled(isSolverNode);
    m_clearSolutioncontext->setVisible(isSolverNode);

    m_solverSettingcontext->setEnabled(isSolverNode);
    m_solverSettingcontext->setVisible(isSolverNode);
}

}//namespace Solver

