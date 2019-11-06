#include "magfemprojectmanagerpluginplugin.h"
#include "magfemprojectmanagerpluginconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/context.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/constants.h>


namespace MagFEMProjectManagerPlugin {
namespace Internal {

MagFEMProjectManagerPluginPlugin::MagFEMProjectManagerPluginPlugin()
{
    // Create your members
}

MagFEMProjectManagerPluginPlugin::~MagFEMProjectManagerPluginPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool MagFEMProjectManagerPluginPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

//    Q_UNUSED(arguments)
//    Q_UNUSED(errorString)

    return true;
}

void MagFEMProjectManagerPluginPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag MagFEMProjectManagerPluginPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}


} // namespace Internal
} // namespace MagFEMProjectManagerPlugin
