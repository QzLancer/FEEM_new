#include "heatplugin.h"
#include "heatpluginconstants.h"
#include "heat2dstaticwizard.h"

#include <coreplugin/icore.h>
#include <coreplugin/context.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/constants.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>

using namespace Core;

HeatPlugin::HeatPlugin()
{
    // Create your members
}

HeatPlugin::~HeatPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool HeatPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    /** 添加wizards **/
    IWizardFactory::registerFactoryCreator([] {
        return QList<IWizardFactory *> {
            new Heat2DStaticWizard
        };
    });
    return true;
}

void HeatPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag HeatPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}
