#pragma once

#include "outputplugin_global.h"

#include <extensionsystem/iplugin.h>

namespace OutputPlugin {

class MessageOutputPane;

class OutputPluginPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "OutputPlugin.json")

public:
    OutputPluginPlugin();
    ~OutputPluginPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private:
    MessageOutputPane* m_messagePane;
};

} // namespace OutputPlugin
