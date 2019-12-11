#ifndef MESHPLUGIN_H
#define MESHPLUGIN_H

#include <extensionsystem/iplugin.h>
class QAction;

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

    void automesh();

    void registerDefaultContainers();
    void registerDefaultActions();
public slots:

private:
    QAction* m_autoMesh;
};

}//namespace Mesh

#endif // MESHPLUGIN_H
