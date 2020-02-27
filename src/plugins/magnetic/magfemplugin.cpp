#include "magfemplugin.h"
#include "magfempluginconstants.h"
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

namespace MagneticFEM {
namespace Internal {

MagFEMPlugin::MagFEMPlugin()
{
    // Create your members
}

MagFEMPlugin::~MagFEMPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool MagFEMPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    qDebug()<<Q_FUNC_INFO;
    //create and register objects
    /** 为了能够打开自己定义的project文件，需要将自定义的project注册一下。
        也就是你的mimetype字符串以及你的项目类名。**/
    ProjectExplorer::PF_ProjectManager::registerProjectType<PF_Mag2DSProject>(MagneticFEM::Constants::FEEMMAG2DSTATIC_MIMETYPE);
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

void MagFEMPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag MagFEMPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}


} // namespace Internal
} // namespace MagneticFEM
