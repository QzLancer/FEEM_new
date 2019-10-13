#pragma once

#include <coreplugin/iwelcomepage.h>

#include <QAbstractListModel>

namespace ProjectExplorer {
//namespace Internal {

//class SessionModel;
class SessionsPage;

//class ProjectModel : public QAbstractListModel
//{
//    Q_OBJECT

//public:
//    enum { FilePathRole = Qt::UserRole+1, PrettyFilePathRole, ShortcutRole };

//    ProjectModel(QObject *parent = nullptr);
//    int rowCount(const QModelIndex &parent) const override;
//    QVariant data(const QModelIndex &index, int role) const override;
//    QHash<int, QByteArray> roleNames() const override;

//public slots:
//    void resetProjects();
//};

class ProjectWelcomePage : public Core::IWelcomePage
{
    Q_OBJECT
public:
    ProjectWelcomePage();

    QString title() const override { return tr("Projects"); }
    int priority() const override { return 20; }
    Core::Id id() const override;
    QWidget *createWidget() const override;

    void reloadWelcomeScreenData() const;

public slots:
    void newProject();
    void openProject();

signals:
    void requestProject(const QString &project);
    void manageSessions();

private:
    void openSessionAt(int index);
    void openProjectAt(int index);

    friend class SessionsPage;
//    SessionModel *m_sessionModel = nullptr;
//    ProjectModel *m_projectModel = nullptr;
};

//} // namespace Internal
} // namespace ProjectExplorer
