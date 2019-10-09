#ifndef PF_PROJECTTREEWIDGET_H
#define PF_PROJECTTREEWIDGET_H

#include <coreplugin/inavigationwidgetfactory.h>

#include <QWidget>

class QTreeView;

namespace ProjectExplorer {
class Node;
class PF_ProjectModel;

class PF_ProjectTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PF_ProjectTreeWidget(QWidget *parent = nullptr);
    ~PF_ProjectTreeWidget() override;

    Node *currentNode();
    void sync(Node *node);

    void collapseAll();
    void expandAll();

private:
    void handleCurrentItemChange(const QModelIndex &current);
    void showContextMenu(const QPoint &pos);
    void openItem(const QModelIndex &mainIndex);

    void setCurrentItem(Node *node);

    QTreeView *m_view = nullptr;
    PF_ProjectModel *m_model = nullptr;

    QString m_modelId;
    bool m_autoSync = true;

signals:

public slots:
};

class ProjectTreeWidgetFactory : public Core::INavigationWidgetFactory
{
    Q_OBJECT
public:
    ProjectTreeWidgetFactory();

    Core::NavigationView createWidget();
};
}//namespace ProjectExplorer
#endif // PF_PROJECTTREEWIDGET_H
