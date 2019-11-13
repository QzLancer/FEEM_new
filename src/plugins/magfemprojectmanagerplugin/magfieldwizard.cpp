#include "magfieldwizard.h"

#include <utils/fileutils.h>

#include <QCoreApplication>
#include <QDir>
#include <QTextStream>
#include <QSharedPointer>

namespace MagFEMProjectManagerPlugin {

/*!
 \brief 电磁场仿真的一个向导，需要将内容添加到Project页面供用户选择。

*/
MagfieldWizard::MagfieldWizard()
{
    setId("FEM.MAG");
    setCategory(tr("Magnetic field"));
    setDisplayCategory(tr("Magnetic field"));
    setDisplayName(tr("2D Magnetic Static field simulation"));
    setDescription(tr("Create a project to simulate the distribution of magnetic field."));
//    setRequiredFeatures({QtSupport::Constants::FEATURE_QWIDGETS});
}

Core::BaseFileWizard *MagfieldWizard::create(QWidget *parent, const Core::WizardDialogParameters &parameters) const
{
    return nullptr;
}

Core::GeneratedFiles MagfieldWizard::generateFiles(const QWizard *w, QString *errorMessage) const
{
    Core::GeneratedFiles rc;
    return rc;
}

}// namespace MagFEMProjectManagerPlugin
