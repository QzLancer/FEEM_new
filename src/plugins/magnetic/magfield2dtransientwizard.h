#ifndef MAGFIELD2DTRANSIENTWIZARD_H
#define MAGFIELD2DTRANSIENTWIZARD_H


#include <coreplugin/basefilewizard.h>
#include <coreplugin/basefilewizardfactory.h>

namespace MagneticFEM {
class MagField2DTransientWizard : public Core::BaseFileWizardFactory
{
    Q_OBJECT

public:
    MagField2DTransientWizard();

private:
    Core::BaseFileWizard *create(QWidget *parent, const Core::WizardDialogParameters &parameters) const override;

    Core::GeneratedFiles generateFiles(const QWizard *w, QString *errorMessage) const override;

private:
//    static bool parametrizeTemplate(const QString &templatePath, const QString &templateName,
//                                    const GuiAppParameters &params,
//                                    QString *target, QString *errorMessage);
};
}// namespace MagneticFEM
#endif // MAGFIELD2DTRANSIENTWIZARD_H
