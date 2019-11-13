#ifndef MAGFIELDWIZARD_H
#define MAGFIELDWIZARD_H

#include <coreplugin/basefilewizard.h>
#include <coreplugin/basefilewizardfactory.h>

namespace MagFEMProjectManagerPlugin {
class MagfieldWizard : public Core::BaseFileWizardFactory
{
    Q_OBJECT

public:
    MagfieldWizard();

private:
    Core::BaseFileWizard *create(QWidget *parent, const Core::WizardDialogParameters &parameters) const override;

    Core::GeneratedFiles generateFiles(const QWizard *w, QString *errorMessage) const override;

private:
//    static bool parametrizeTemplate(const QString &templatePath, const QString &templateName,
//                                    const GuiAppParameters &params,
//                                    QString *target, QString *errorMessage);
};
}// namespace MagFEMProjectManagerPlugin


#endif // MAGFIELDWIZARD_H
