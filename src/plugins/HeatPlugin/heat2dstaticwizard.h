#ifndef HEAT2DSTATICWIZARD_H
#define HEAT2DSTATICWIZARD_H

#include <coreplugin/basefilewizard.h>
#include <coreplugin/basefilewizardfactory.h>

class Heat2DStaticWizard : public Core::BaseFileWizardFactory
{
public:
    Heat2DStaticWizard();

private:
    Core::BaseFileWizard *create(QWidget *parent, const Core::WizardDialogParameters &parameters) const override;

    Core::GeneratedFiles generateFiles(const QWizard *w, QString *errorMessage) const override;
};

#endif // HEAT2DSTATICWIZARD_H
