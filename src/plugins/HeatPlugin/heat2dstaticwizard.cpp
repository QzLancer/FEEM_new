#include "heat2dstaticwizard.h"
#include "pf_heat2dsproject.h"

#include <utils/fileutils.h>

#include <project/pf_project.h>
#include <project/pf_projectexplorer.h>
#include <project/pf_sessionmanager.h>
#include <project/pf_projecttree.h>

#include <coreplugin/constants.h>
#include <coreplugin/context.h>
#include <coreplugin/icore.h>
#include <coreplugin/iwizardfactory.h>
#include <coreplugin/pagemanager.h>

#include <QDir>
#include <QTextStream>
#include <QSharedPointer>
namespace HeatFEMProjectManagerPlugin{
Heat2DStaticWizard::Heat2DStaticWizard()
{
    setId("FEM.HEAT2DS");
    setIcon(QIcon(":/imgs/model_2d_axi_32.png"));
    setCategoryIcon(QIcon(":/icon/imgs/heat_transfer_32.png"));
    setCategory(tr("Heat field"));
    setDisplayCategory(tr("Heat field"));
    setDisplayName(tr("2D Axis Heat Static field simulation"));
}

Core::BaseFileWizard *Heat2DStaticWizard::create(QWidget *parent, const Core::WizardDialogParameters &parameters) const
{
    /** 新建一个项目 **/
    auto pro = new PF_Heat2DSProject(Utils::FileName());
    ProjectExplorer::PF_SessionManager::instance()->addProject(pro);
    /** 切换到工作页面 **/
    Core::PageManager::activatePage(Core::Constants::PAGE_WORK);
    return nullptr;
}

Core::GeneratedFiles Heat2DStaticWizard::generateFiles(const QWizard *w, QString *errorMessage) const
{
    Core::GeneratedFiles rc;
    return rc;
}
}   // namespace HeatFEMProjectManagerPlugin
