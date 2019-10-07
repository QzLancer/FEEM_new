#ifndef MESHPLUGIN_H
#define MESHPLUGIN_H

#include <extensionsystem/iplugin.h>

namespace Mesh {

class MeshPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "Mesh.json")

public:
    MeshPlugin();
    ~MeshPlugin() override;

    static MeshPlugin *instance();

    bool initialize(const QStringList &arguments, QString *errorMessage = nullptr) override;
    void extensionsInitialized() override;
    bool delayedInitialize() override;
    ShutdownFlag aboutToShutdown() override;
    QObject *remoteCommand(const QStringList & /* options */,
                           const QString &workingDirectory,
                           const QStringList &args) override;

    void registerDefaultContainers();
    void registerDefaultActions();
public slots:

private:
};

}//namespace Mesh

#endif // MESHPLUGIN_H
