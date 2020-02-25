#pragma once

#include "commonfem_global.h"

#include <extensionsystem/iplugin.h>

namespace CommonFEM {
namespace Internal {

class CommonFEMProjectManagerPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "CommonFEMProjectManagerPlugin.json")

public:
    CommonFEMProjectManagerPlugin();
    ~CommonFEMProjectManagerPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private:
};

} // namespace Internal
} // namespace CommonFEM
