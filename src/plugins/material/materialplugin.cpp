#include "materialplugin.h"
#include "materialconstants.h"

#include "pf_materiallibrary.h"

#include "qtribbon/include/QtnRibbonGroup.h"

#include <QtAdvancedDock/DockManager.h>

#include <coreplugin/constants.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/workpage.h>

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

namespace Material {
static MaterialPlugin *m_instance = nullptr;

MaterialPlugin::MaterialPlugin()
{
    m_instance = this;
}

MaterialPlugin::~MaterialPlugin()
{

}

MaterialPlugin *MaterialPlugin::instance()
{
    return m_instance;
}

bool MaterialPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    registerDefaultContainers();
    registerDefaultActions();

    QWidget* materialLibraryTree = new PF_MaterialLibraryWidget();
    ads::CDockWidget* DockWidget3 = new ads::CDockWidget(tr("Material library"));
    DockWidget3->setWidget(materialLibraryTree);
    // Add the dock widget to the top dock widget area
    Core::WorkPage::DockManager()->addDockWidget(ads::RightDockWidgetArea, DockWidget3);

    return true;
}

void MaterialPlugin::extensionsInitialized()
{

}

bool MaterialPlugin::delayedInitialize()
{
	return true;
}

ExtensionSystem::IPlugin::ShutdownFlag MaterialPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}

QObject *MaterialPlugin::remoteCommand(const QStringList &, const QString &workingDirectory, const QStringList &args)
{
    return nullptr;
}

void MaterialPlugin::registerDefaultContainers()
{
    /** 添加P_MATERIAL group **/
    ActionContainer* page = ActionManager::actionContainer(Core::Constants::P_MATERIAL);
    /** 材料 **/
    ActionContainer* group = ActionManager::createRibbonGroup(Constants::G_MATERIAL_LIBRARY);
    group->ribbonGroup()->setTitle(tr("Material"));
    page->appendGroup(Constants::G_MATERIAL_LIBRARY);
    page->addRibbonGroup(group,Constants::G_MATERIAL_LIBRARY);
}

void MaterialPlugin::registerDefaultActions()
{
    auto group = ActionManager::actionContainer(Constants::G_MATERIAL_LIBRARY);
    group->ribbonGroup()->addAction(QIcon(":/material/imgs/addmaterial.png"), tr("Add material"), Qt::ToolButtonTextUnderIcon);
    group->ribbonGroup()->addAction(QIcon(":/material/imgs/materiallibrary.png"), tr("Material library"), Qt::ToolButtonTextUnderIcon);
}
}//namespace Material
