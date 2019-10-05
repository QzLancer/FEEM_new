#include "cad.h"

#include <coreplugin/actionmanager/actionmanager.h>

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

namespace CAD {
static CADPlugin *m_instance = nullptr;

CADPlugin::CADPlugin()
{
//    qRegisterMetaType<Core::Id>();
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
}//namespace CAD
