#pragma once

#include "heatplugin_global.h"
#include "heatboundarydialog.h"
#include "boundaryprop.h"

#include <extensionsystem/iplugin.h>
#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>


namespace HeatFEMProjectManagerPlugin {
class Heat2DStaticWizard;

namespace Internal {

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
    void registerDefaultContainers();
    void registerDefaultActions();
    void updateContextActions();

signals:
    void boundaryAdded(CHBoundaryProp*);

public slots:
    void slotaddBoundary();
//    void slotSolve();
private:
    QAction* m_addBoundary = nullptr;
};
}   //namespace Internal
}   //namespace HeatFEMProjectManagerPlugin

