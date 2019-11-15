#ifndef PF_PROJECT_H
#define PF_PROJECT_H

#include "project_export.h"

#include <QObject>
#include <functional>
#include <memory>

#include <coreplugin/idocument.h>

namespace ProjectExplorer {
class FolderNode;
class Node;
class ProjectNode;
class PF_ProjectPrivate;

// Auto-registers with the DocumentManager if a callback is set!
class ProjectDocument : public Core::IDocument
{
public:
    using ProjectCallback = std::function<void()>;

    ProjectDocument(const QString &mimeType, const FileName &fileName,
                    const ProjectCallback &callback = {});

    IDocument::ReloadBehavior reloadBehavior(Core::IDocument::ChangeTrigger state,
                                                   Core::IDocument::ChangeType type) const final;
    bool reload(QString *errorString, Core::IDocument::ReloadFlag flag,
                Core::IDocument::ChangeType type) final;

private:
    ProjectCallback m_callback;
};


class FEEM_PROJECT_EXPORT PF_Project : public QObject
{
    friend class PF_SessionManager; // for setActiveTarget
    friend class PF_ProjectExplorerPlugin; // for projectLoaded
    Q_OBJECT
public:
    explicit PF_Project(QObject *parent = nullptr);
    ~PF_Project();

    QString displayName() const;
    void setDisplayName(const QString& displayName);

    void creatTree();
    void setRootProjectNode(std::unique_ptr<ProjectNode> &&root); // takes ownership!

    void handleSubTreeChanged(FolderNode *node);

    virtual ProjectNode* rootProjectNode() const;

signals:
    void displayNameChanged();
public slots:

private:
    PF_ProjectPrivate* d;
};
}//namespace ProjectExplorer
/** 为了使用 **/
Q_DECLARE_METATYPE(ProjectExplorer::PF_Project*)
#endif // PF_PROJECT_H

