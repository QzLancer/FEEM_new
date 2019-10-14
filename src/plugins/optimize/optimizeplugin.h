#pragma once

#include <extensionsystem/iplugin.h>
#include "singleobjectdialog.h"
#include "multiobjectdialog.h"

namespace Optimize {

class OptimizePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "Optimize.json")

public:
    OptimizePlugin();
    ~OptimizePlugin() override;

    static OptimizePlugin *instance();

    bool initialize(const QStringList &arguments, QString *errorMessage = nullptr) override;
    void extensionsInitialized() override;
    bool delayedInitialize() override;

    void registerDefaultContainers();
    void registerDefaultActions();

public slots:
    void slotActionSOO();
    void slotActionMOO();

private:
    SingleObjectDialog *mSingleObjectDialog;
    MultiObjectDialog *mMultiObjectDialog;
};

}//namespace Optimize
