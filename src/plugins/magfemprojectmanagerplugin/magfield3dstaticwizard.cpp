#include "magfield3dstaticwizard.h"

#include <utils/fileutils.h>

#include <QDir>
#include <QTextStream>
#include <QSharedPointer>
#include <QMessageBox>

namespace MagFEMProjectManagerPlugin {

/*!
 \brief 电磁场仿真的一个向导，需要将内容添加到Project页面供用户选择。

*/
MagField3DStaticWizard::MagField3DStaticWizard()
{
    setId("FEM.MAG3DStatic");
    setIcon(QIcon(":/imgs/model_3d_32.png"));
    setCategoryIcon(QIcon(":/imgs/magnetic_fields_32.png"));
    setCategory(tr("Magnetic field"));
    setDisplayCategory(tr("Magnetic field"));
    setDisplayName(tr("3D Magnetic Static field simulation"));
//    setDescription(tr("Create a project to simulate the distribution of magnetic field."));
//    setRequiredFeatures({QtSupport::Constants::FEATURE_QWIDGETS});
}

Core::BaseFileWizard *MagField3DStaticWizard::create(QWidget *parent, const Core::WizardDialogParameters &parameters) const
{
    QMessageBox::warning(parent,tr("Warning"),tr("This feature is not available."));
    return nullptr;
}

Core::GeneratedFiles MagField3DStaticWizard::generateFiles(const QWizard *w, QString *errorMessage) const
{
    Core::GeneratedFiles rc;
    return rc;
}

}// namespace MagFEMProjectManagerPlugin
