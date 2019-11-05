#pragma once

#include "magfemprojectmanagerplugin_global.h"

#include <extensionsystem/iplugin.h>

namespace MagFEMProjectManagerPlugin {
namespace Internal {

class MagFEMProjectManagerPluginPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "MagFEMProjectManagerPlugin.json")

public:
    MagFEMProjectManagerPluginPlugin();
    ~MagFEMProjectManagerPluginPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private:
};

} // namespace Internal
} // namespace MagFEMProjectManagerPlugin
