#pragma once

#include <extensionsystem/iplugin.h>

#include <QAction>

namespace Solver {

class SolverPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "Solver.json")

public:
    SolverPlugin();
    ~SolverPlugin() override;

    static SolverPlugin *instance();

    bool initialize(const QStringList &arguments, QString *errorMessage = nullptr) override;
    void extensionsInitialized() override;
    bool delayedInitialize() override;
    ShutdownFlag aboutToShutdown() override;
    QObject *remoteCommand(const QStringList & /* options */,
                           const QString &workingDirectory,
                           const QStringList &args) override;

    void registerDefaultContainers();
    void registerDefaultActions();

    void updateContextActions();
public slots:

private:
    QAction* m_solve = nullptr;
    QAction* m_clearSolution = nullptr;
    QAction* m_solverSetting = nullptr;

    QAction* m_solvecontext = nullptr;
    QAction* m_clearSolutioncontext = nullptr;
    QAction* m_solverSettingcontext = nullptr;
};

}//namespace Solver
