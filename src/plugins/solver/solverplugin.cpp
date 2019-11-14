#include "solverplugin.h"
#include "solverconstants.h"

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
    /**  **/
    ActionContainer* group = ActionManager::createRibbonGroup(Constants::G_SOLVE_SETTING);
    group->ribbonGroup()->setTitle(tr("Solver Setting"));
    page->appendGroup(Constants::G_SOLVE_SETTING);
    page->addRibbonGroup(group,Constants::G_SOLVE_SETTING);

    auto action = new QAction(tr("Solver Setting"));
    action->setIcon(QIcon(":/imgs/setting.png"));
    group->ribbonGroup()->addAction(action,Qt::ToolButtonTextUnderIcon);

    group = ActionManager::createRibbonGroup(Constants::G_SOLVE_SOLVE);
    group->ribbonGroup()->setTitle(tr("Solve"));
    page->appendGroup(Constants::G_SOLVE_SOLVE);
    page->addRibbonGroup(group,Constants::G_SOLVE_SOLVE);

    action = new QAction(tr("Solve"));
    action->setIcon(QIcon(":/imgs/solve.png"));
    group->ribbonGroup()->addAction(action,Qt::ToolButtonTextUnderIcon);

    group = ActionManager::createRibbonGroup(Constants::G_SOLVE_CLEAR);
    group->ribbonGroup()->setTitle(tr("Clear Solution"));
    page->appendGroup(Constants::G_SOLVE_CLEAR);
    page->addRibbonGroup(group,Constants::G_SOLVE_CLEAR);

    action = new QAction(tr("Clear Solution"));
    action->setIcon(QIcon(":/imgs/clearsolution.png"));
    group->ribbonGroup()->addAction(action,Qt::ToolButtonTextUnderIcon);
}

void SolverPlugin::registerDefaultActions()
{

}

}//namespace Solver

