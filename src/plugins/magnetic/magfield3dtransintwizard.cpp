#include "magfield3dtransintwizard.h"


#include <utils/fileutils.h>

#include <QDir>
#include <QTextStream>
#include <QSharedPointer>
#include <QMessageBox>

namespace MagneticFEM {

/*!
 \brief 电磁场仿真的一个向导，需要将内容添加到Project页面供用户选择。

*/
MagField3DTransintWizard::MagField3DTransintWizard()
{
    setId("FEM.MAG3DTransient");
    setIcon(QIcon(":/imgs/model3d32.png"));
    setCategoryIcon(QIcon(":/imgs/magnetic_fields_32.png"));
    setCategory("0Magnetic field");
    setDisplayCategory(tr("Magnetic field"));
    setDisplayName(tr("3D Magnetic Transient field simulation"));
//    setDescription(tr("Create a project to simulate the distribution of magnetic field."));
//    setRequiredFeatures({QtSupport::Constants::FEATURE_QWIDGETS});
}

Core::BaseFileWizard *MagField3DTransintWizard::create(QWidget *parent, const Core::WizardDialogParameters &parameters) const
{
    QMessageBox::warning(parent,tr("Tips"),tr("This feature is not available."));
    return nullptr;
}

Core::GeneratedFiles MagField3DTransintWizard::generateFiles(const QWizard *w, QString *errorMessage) const
{
    Core::GeneratedFiles rc;
    return rc;
}

}// namespace MagneticFEM
