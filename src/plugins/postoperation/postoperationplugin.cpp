#include "postoperationplugin.h"
#include "postoperationconstants.h"

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
    registerDefaultContainers();
    registerDefaultActions();
    return true;
}

void PostoperationPlugin::extensionsInitialized()
{

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
}

void PostoperationPlugin::registerDefaultActions()
{

}

}//namespace Postoperation

