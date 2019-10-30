#pragma once

#include <extensionsystem/iplugin.h>

#include "bouncedialog.h"
#include "bouncecore.h"

namespace Bounce {

class BouncePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "Bounce.json")

public:
    BouncePlugin();
    ~BouncePlugin() override;

    static BouncePlugin *instance();

    bool initialize(const QStringList &arguments, QString *errorMessage = nullptr) override;
    void extensionsInitialized() override;
    bool delayedInitialize() override;

    void registerDefaultContainers();
    void registerDefaultActions();

public slots:
    void slotCalculate();

private:
//    BounceDialog *dialog;
};

}//namespace Bounce
