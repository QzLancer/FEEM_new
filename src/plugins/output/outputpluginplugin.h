#pragma once

#include "outputplugin_global.h"
#include "messageoutputpane.h"

#include <extensionsystem/iplugin.h>

#define PoofeeSay *OutputPlugin::OutputPluginPlugin::MessagePane()

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
    static MessageOutputPane *MessagePane();
private:
//    MessageOutputPane* m_messagePane;
};

} // namespace OutputPlugin
