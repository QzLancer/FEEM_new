#include "magfemprojectmanagerpluginplugin.h"
#include "magfemprojectmanagerpluginconstants.h"
#include "magfieldwizard.h"
#include "magfield2dtransientwizard.h"
#include "magfield3dstaticwizard.h"
#include "magfield3dtransintwizard.h"
#include "pf_mag2dsproject.h"

#include <coreplugin/icore.h>
#include <coreplugin/context.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/constants.h>

#include <project/pf_projectmanager.h>

using namespace Core;

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
    qDebug()<<Q_FUNC_INFO;
    //create and register objects
    ProjectExplorer::PF_ProjectManager::registerProjectType<PF_Mag2DSProject>(MagFEMProjectManagerPlugin::Constants::FEEMFILE_MIMETYPE);
    /** 添加wizards **/
    IWizardFactory::registerFactoryCreator([] {
        return QList<IWizardFactory *> {
            new MagfieldWizard,
            new MagField2DTransientWizard,
            new MagField3DStaticWizard,
            new MagField3DTransintWizard
        };
    });
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
