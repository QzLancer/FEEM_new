#include "heatplugin.h"
#include "heatpluginconstants.h"
#include "heat2dstaticwizard.h"
#include "pf_heat2dsproject.h"
#include "pf_boundarynode.h"

#include "qtribbon/include/QtnRibbonGroup.h"

#include <coreplugin/icore.h>
#include <coreplugin/context.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/constants.h>

#include <project/projectexplorerconstants.h>
#include <project/pf_node.h>
#include <project/pf_projecttree.h>

#include <solver/solverconstants.h>

#include <typeinfo>

using namespace Core;
using namespace ProjectExplorer;

namespace HeatFEMProjectManagerPlugin {
namespace Internal {

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
    qDebug() << Q_FUNC_INFO;
    registerDefaultActions();
    registerDefaultContainers();

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

void HeatPlugin::registerDefaultContainers()
{

}

void HeatPlugin::registerDefaultActions()
{
    /** 边界节点右键菜单栏 **/
    ActionContainer *mboundaryContextMenu = ActionManager::actionContainer(ProjectExplorer::Constants::M_FOLDERCONTEXT);
    mboundaryContextMenu->appendGroup(ProjectExplorer::Constants::G_HELP);

    /** boundary **/
    m_addBoundary = new QAction(QIcon(":/icon/imgs/boundary_32.png"), tr("add Boundary Condition"), this);
    Command* cmd = ActionManager::registerAction(m_addBoundary, Constants::M_ADDBOUNDARY);
    mboundaryContextMenu->addAction(cmd,Core::Constants::G_DEFAULT_ONE);
    connect(m_addBoundary, &QAction::triggered, this, &HeatPlugin::slotaddBoundary);

    ActionContainer *group = ActionManager::actionContainer(Solver::Constants::G_SOLVE_SOLVE);
    QAction *action = new QAction(tr("Heat Field Solve"));
    action->setIcon(QIcon(":/imgs/solve.png"));
    group->ribbonGroup()->addAction(action, Qt::ToolButtonTextUnderIcon);
        connect(action, &QAction::triggered, this, &HeatPlugin::slotSolve);
    connect(PF_ProjectTree::instance(), &PF_ProjectTree::currentNodeChanged,
            this, &HeatPlugin::updateContextActions);
}

void HeatPlugin::updateContextActions()
{
    /** 判断是不是边界节点 **/
    const Node *node = PF_ProjectTree::findCurrentNode();
    const bool isBoundaryNode = dynamic_cast<const PF_BoundaryNode *>(node);

    m_addBoundary->setEnabled(isBoundaryNode);
    m_addBoundary->setVisible(isBoundaryNode);
}

void HeatPlugin::slotaddBoundary()
{
    Node *node = PF_ProjectTree::findCurrentNode();
    FolderNode *folderNode = node ? node->asFolderNode() : nullptr;
    if(!folderNode) return;

    HeatBoundaryDialog *dialog = new HeatBoundaryDialog(Core::ICore::dialogParent());
    dialog->setWindowTitle(tr("Add Boundary Condition"));
    dialog->show();
//    if(result == QDialog::Accepted){
//        emit boundaryAdded(dialog->getBoundary());
//    }else{
//        qDebug() << "addBlankBoundary Cancle.";
    //    }
}

void HeatPlugin::slotSolve()
{
    PF_Heat2DSProject *project = dynamic_cast<PF_Heat2DSProject*>(PF_ProjectTree::currentProject());
    project->Static2D();
}

}   //namespace Internal
}   //namespace HeatFEMProjectManagerPlugin
