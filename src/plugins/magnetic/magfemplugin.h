#pragma once

#include "magfemplugin_global.h"

#include <extensionsystem/iplugin.h>

namespace MagneticFEM {
namespace Internal {

class MagFEMPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "Magnetic.json")

public:
    MagFEMPlugin();
    ~MagFEMPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private:
};

} // namespace Internal
} // namespace MagneticFEM
