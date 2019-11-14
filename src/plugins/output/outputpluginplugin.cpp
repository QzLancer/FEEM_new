#include "outputpluginplugin.h"
#include "outputpluginconstants.h"

#include <QtAdvancedDock/DockManager.h>

#include <coreplugin/icore.h>
#include <coreplugin/context.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/constants.h>
#include <coreplugin/workpage.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>

using namespace Core;

namespace OutputPlugin {

OutputPluginPlugin::OutputPluginPlugin()
{
    // Create your members
}

OutputPluginPlugin::~OutputPluginPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool OutputPluginPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

    return true;
}

void OutputPluginPlugin::extensionsInitialized()
{
    qDebug()<<Q_FUNC_INFO;
    ads::CDockWidget* DockWidget1 = new ads::CDockWidget(tr("Message outputpane"));

    Core::WorkPage::DockManager()->addDockWidget(ads::BottomDockWidgetArea, DockWidget1);
}

ExtensionSystem::IPlugin::ShutdownFlag OutputPluginPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

} // namespace OutputPlugin
