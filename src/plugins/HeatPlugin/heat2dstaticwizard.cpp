#include "heat2dstaticwizard.h"

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
    return nullptr;
}

Core::GeneratedFiles Heat2DStaticWizard::generateFiles(const QWizard *w, QString *errorMessage) const
{
    Core::GeneratedFiles rc;
    return rc;
}
