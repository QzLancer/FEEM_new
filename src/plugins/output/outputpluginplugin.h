#pragma once

#include "outputplugin_global.h"

#include <extensionsystem/iplugin.h>

namespace OutputPlugin {

class MessageOutputPane;

class OUTPUTPLUGINSHARED_EXPORT OutputPluginPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "OutputPlugin.json")

public:
    OutputPluginPlugin();
    ~OutputPluginPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

    static void write(const QString &text);
private:
//    MessageOutputPane* m_messagePane;
};

} // namespace OutputPlugin
