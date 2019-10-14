#include "bounceplugin.h"
#include "bounceconstants.h"

#include "qtribbon/include/QtnRibbonPage.h"
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

#include "plot/plotwidget.h"

using namespace Core;

namespace Bounce {
static BouncePlugin * m_instance = nullptr;

BouncePlugin::BouncePlugin()
    : dialog(new BounceDialog)
{
    m_instance = this;
}

BouncePlugin::~BouncePlugin()
{
    delete dialog;
}

BouncePlugin *BouncePlugin::instance()
{
    return m_instance;
}

bool BouncePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    registerDefaultContainers();
    registerDefaultActions();
    return true;
}

void BouncePlugin::extensionsInitialized()
{

}

bool BouncePlugin::delayedInitialize()
{
    return true;
}

void BouncePlugin::registerDefaultContainers()
{
    ActionContainer *ribbonbar = ActionManager::actionContainer(Core::Constants::RIBBONBAR);
    ribbonbar->insertGroup(Core::Constants::G_RESULT,Constants::G_MECHANIC);
    ActionContainer* page = ActionManager::createRibbonPage(Constants::P_MECHANIC);
    page->ribbonPage()->setTitle(tr("&Mechanic"));
    ribbonbar->addRibbonPage(page, Constants::G_MECHANIC);
    auto ribbongroup = ActionManager::createRibbonGroup(Constants::G_MECHANIC_BOUNCE);;
    ribbongroup->ribbonGroup()->setTitle(tr("Bounce"));
    page->appendGroup(Constants::G_MECHANIC_BOUNCE);
    page->addRibbonGroup(ribbongroup, Constants::G_MECHANIC_BOUNCE);
}

void BouncePlugin::registerDefaultActions()
{
    auto group = ActionManager::actionContainer(Constants::G_MECHANIC_BOUNCE);
    QAction *action = new QAction(tr("Bounce Calculate"));
    action->setIcon(QIcon(":/icon/imgs/bounce32x32.png"));
    connect(action, &QAction::triggered, this, &BouncePlugin::slotCalculate);
    group->ribbonGroup()->addAction(action, Qt::ToolButtonTextUnderIcon);
}

void BouncePlugin::slotCalculate()
{
    dialog->show();
}

}//namespace Bounce

