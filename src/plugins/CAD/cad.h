#ifndef CAD_H
#define CAD_H

#include <extensionsystem/iplugin.h>

namespace CAD {

class CADPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "CAD.json")

public:
    CADPlugin();
    ~CADPlugin() override;

    static CADPlugin *instance();

    bool initialize(const QStringList &arguments, QString *errorMessage = nullptr) override;
    void extensionsInitialized() override;
    bool delayedInitialize() override;
    ShutdownFlag aboutToShutdown() override;
    QObject *remoteCommand(const QStringList & /* options */,
                           const QString &workingDirectory,
                           const QStringList &args) override;

public slots:

private:
};

}//namespace CAD
#endif // CAD_H
