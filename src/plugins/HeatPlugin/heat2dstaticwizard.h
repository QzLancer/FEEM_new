#ifndef HEAT2DSTATICWIZARD_H
#define HEAT2DSTATICWIZARD_H

#include <coreplugin/basefilewizard.h>
#include <coreplugin/basefilewizardfactory.h>

namespace HeatFEMProjectManagerPlugin{
class Heat2DStaticWizard : public Core::BaseFileWizardFactory
{
    Q_OBJECT
public:
    Heat2DStaticWizard();

private:
    Core::BaseFileWizard *create(QWidget *parent, const Core::WizardDialogParameters &parameters) const override;

    Core::GeneratedFiles generateFiles(const QWizard *w, QString *errorMessage) const override;
};
}   // namespace HeatFEMProjectManagerPlugin
#endif // HEAT2DSTATICWIZARD_H
