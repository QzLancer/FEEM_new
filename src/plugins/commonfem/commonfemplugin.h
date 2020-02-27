#pragma once

#include "commonfem_global.h"

#include <extensionsystem/iplugin.h>

namespace CommonFEM {
namespace Internal {

class CommonFEMPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "CommonFEM.json")

public:
    CommonFEMPlugin();
    ~CommonFEMPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private:
};

} // namespace Internal
} // namespace CommonFEM
