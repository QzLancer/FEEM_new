#include "commonfemplugin.h"

#include <coreplugin/icore.h>
#include <coreplugin/context.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/constants.h>

#include <project/pf_projectmanager.h>

using namespace Core;

namespace CommonFEM {
namespace Internal {

CommonFEMPlugin::CommonFEMPlugin()
{
    // Create your members
}

CommonFEMPlugin::~CommonFEMPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool CommonFEMPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    qDebug()<<Q_FUNC_INFO;
    return true;
}

void CommonFEMPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag CommonFEMPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}


} // namespace Internal
} // namespace CommonFEM
