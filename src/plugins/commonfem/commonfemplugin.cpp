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

CommonFEMProjectManagerPlugin::CommonFEMProjectManagerPlugin()
{
    // Create your members
}

CommonFEMProjectManagerPlugin::~CommonFEMProjectManagerPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool CommonFEMProjectManagerPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    return true;
}

void CommonFEMProjectManagerPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag CommonFEMProjectManagerPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}


} // namespace Internal
} // namespace CommonFEM
