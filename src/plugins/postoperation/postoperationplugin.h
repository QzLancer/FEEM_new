#pragma once

#include <extensionsystem/iplugin.h>

namespace Postoperation {

class PostoperationPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "Postoperation.json")

public:
    PostoperationPlugin();
    ~PostoperationPlugin() override;

    static PostoperationPlugin *instance();

    bool initialize(const QStringList &arguments, QString *errorMessage = nullptr) override;
    void extensionsInitialized() override;
    bool delayedInitialize() override;
    ShutdownFlag aboutToShutdown() override;
    QObject *remoteCommand(const QStringList & /* options */,
                           const QString &workingDirectory,
                           const QStringList &args) override;

    void registerDefaultContainers();
    void registerDefaultActions();

    void new2DCurvePlot();
    void new2DSurfacePlot();
public slots:

private:
};

}//namespace Postoperation
