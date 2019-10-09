#ifndef PF_PROJECTEXPLORER_H
#define PF_PROJECTEXPLORER_H

#include <extensionsystem/iplugin.h>

namespace Core {
class Id;
}

namespace ProjectExplorer {
class Node;
class PF_Project;
/*!
 \brief 主要实现关于project的

*/
class PF_ProjectExplorerPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "Project.json")

public:
    explicit PF_ProjectExplorerPlugin();
    ~PF_ProjectExplorerPlugin() override;

    static PF_ProjectExplorerPlugin *instance();

    /** 插件接口 **/
    bool initialize(const QStringList &arguments, QString *errorMessage = nullptr) override;
    void extensionsInitialized() override;
    bool delayedInitialize() override;
    ShutdownFlag aboutToShutdown() override;

    class OpenProjectResult
    {
    public:
        OpenProjectResult(const QList<PF_Project *> &projects, const QList<PF_Project *> &alreadyOpen,
                          const QString &errorMessage)
            : m_projects(projects), m_alreadyOpen(alreadyOpen),
              m_errorMessage(errorMessage)
        { }

        explicit operator bool() const
        {
            return m_errorMessage.isEmpty() && m_alreadyOpen.isEmpty();
        }

        PF_Project *project() const
        {
            return m_projects.isEmpty() ? nullptr : m_projects.first();
        }

        QList<PF_Project *> projects() const
        {
            return m_projects;
        }

        QString errorMessage() const
        {
            return m_errorMessage;
        }

        QList<PF_Project *> alreadyOpen() const
        {
            return m_alreadyOpen;
        }
    private:
        QList<PF_Project *> m_projects;
        QList<PF_Project *> m_alreadyOpen;
        QString m_errorMessage;
    };

    static OpenProjectResult openProject(const QString &fileName);
    static OpenProjectResult openProjects(const QStringList &fileNames);

    static void showContextMenu(QWidget *view, const QPoint &globalPos, Node *node);

    static QList<QPair<QString, QString> > recentProjects();

    static bool canRunStartupProject(Core::Id runMode, QString *whyNot = nullptr);
    static void runProject(PF_Project *pro, Core::Id, const bool forceSkipDeploy = false);
    static void runStartupProject(Core::Id runMode, bool forceSkipDeploy = false);

    static void buildProject(PF_Project *p);

    static void updateContextMenuActions();

    static void openNewProjectDialog();
    static void openOpenProjectDialog();

signals:
    void finishedInitialization();

    // Is emitted when a project has been added/removed,
    // or the file list of a specific project has changed.
    void fileListChanged();

    void recentProjectsChanged();

//    void settingsChanged();

    void updateRunActions();

private:
    static bool coreAboutToClose();
};
}//namespace ProjectExplorer

#endif // PF_PROJECTEXPLORER_H
