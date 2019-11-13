#include "optimizeplugin.h"
#include "optimizeconstants.h"
#include "singleobjwizard.h"

#include "qtribbon/include/QtnRibbonPage.h"
#include "qtribbon/include/QtnRibbonGroup.h"

#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/constants.h>
#include <coreplugin/icore.h>

#include <extensionsystem/pluginerroroverview.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>
#include <utils/algorithm.h>
#include <utils/mimetypes/mimedatabase.h>
#include <utils/stringutils.h>

#include <postoperation/postoperationconstants.h>

#include <QtPlugin>

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QMenu>
#include <QUuid>

#include <cstdlib>

using namespace Core;

namespace Optimize {
static OptimizePlugin * m_instance = nullptr;

OptimizePlugin::OptimizePlugin()
    : mMultiObjectDialog(new MultiObjectDialog)
{
    m_instance = this;
}

OptimizePlugin::~OptimizePlugin()
{
    delete mMultiObjectDialog;
}

OptimizePlugin *OptimizePlugin::instance()
{
    return m_instance;
}

bool OptimizePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    registerDefaultContainers();
    registerDefaultActions();

    return true;
}

void OptimizePlugin::extensionsInitialized()
{

}

bool OptimizePlugin::delayedInitialize()
{
    return true;
}

void OptimizePlugin::registerDefaultContainers()
{
    auto page = ActionManager::actionContainer(Core::Constants::P_RESULT);
    page->insertGroup(Postoperation::Constants::G_RESULT_PLOT, Constants::G_RESULT_OPTIMIZE);
    auto ribbongroup = Core::ActionManager::createRibbonGroup(Constants::G_RESULT_OPTIMIZE);
    ribbongroup->ribbonGroup()->setTitle(tr("Optimization"));
    page->addRibbonGroup(ribbongroup, Constants::G_RESULT_OPTIMIZE);
}

void OptimizePlugin::registerDefaultActions()
{
    auto ribbongroup = ActionManager::actionContainer(Constants::G_RESULT_OPTIMIZE);

    QAction *sooaction = new QAction(tr("Single-Objective Optimization"));
    sooaction->setIcon(QIcon(":/icon/imgs/SOO32x32(1).png"));
    ribbongroup->ribbonGroup()->addAction(sooaction, Qt::ToolButtonTextUnderIcon);
    connect(sooaction, &QAction::triggered, this, &OptimizePlugin::slotActionSOO);

    QAction *mooaction = new QAction(tr("Multi-Objective Optimization"));
    mooaction->setIcon(QIcon(":/icon/imgs/MOO32x32(1).png"));
    ribbongroup->ribbonGroup()->addAction(mooaction, Qt::ToolButtonTextUnderIcon);
    connect(mooaction, &QAction::triggered, this, &OptimizePlugin::slotActionMOO);
}

void OptimizePlugin::slotActionSOO()
{
    SingleObjWizard *sow = new SingleObjWizard();
    sow->page1->appendListPicMap("relay1", QPixmap(":./pic/imgs/relay1.jpg"));
    sow->page1->appendListPicMap("son1", QPixmap(":./pic/imgs/son1.jpg"));
    sow->page1->appendListPicMap("son2", QPixmap(":./pic/imgs/son2.jpg"));
    sow->appendInputList("Input1");
    sow->appendInputList("Input2");
    sow->appendInputList("Input3");
    sow->exec();
}

void OptimizePlugin::slotActionMOO()
{
    /**添加部分参数，后续进行修改**/
    QStringList InputList;
    QStringList TargetList;
    InputList << "Input1" << "Input2" << "Input3";
    TargetList << "Target1" << "Target2" << "Target3" << "Target4";
    mMultiObjectDialog->setInputList(InputList);
    mMultiObjectDialog->setTargetList(TargetList);
    mMultiObjectDialog->show();
}

}//namespace Optimize

