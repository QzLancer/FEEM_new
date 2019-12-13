#pragma once

#include "heatplugin_global.h"

#include <extensionsystem/iplugin.h>

class HeatPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "HeatPlugin.json")

public:
    HeatPlugin();
    ~HeatPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private:

};

