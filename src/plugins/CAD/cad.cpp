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

    ActionContainer* group = ActionManager::createRibbonGroup(Constants::G_GEOMETRY_IMEXPORT);
    group->ribbonGroup()->setTitle(tr("Import/Export"));
    group->ribbonGroup()->setIcon(QIcon(":/cad/imgs/buildgeometry.png"));
    page->appendGroup(Constants::G_GEOMETRY_IMEXPORT);
    page->addRibbonGroup(group,Constants::G_GEOMETRY_IMEXPORT);
}

/**
 * @brief 注册CAD方面的actions
 *
 */
void CADPlugin::registerDefaultActions()
{

}
}//namespace CAD
