#pragma once

#include "material_global.h"

#include <extensionsystem/iplugin.h>

#include <QAction>

class CMaterialProp;

namespace Material {

class FEEM_MATERIAL_EXPORT MaterialPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "Material.json")

public:
    MaterialPlugin();
    ~MaterialPlugin() override;

    static MaterialPlugin *instance();

    void addBlankMaterial();

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

signals:
    void materialAdded(CMaterialProp*);
private:
    QAction* m_addBlankMaterial = nullptr;
    QAction* m_addMaterial = nullptr;
    QAction* m_help = nullptr;
};

} // namespace Material
