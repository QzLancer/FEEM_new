#ifndef PF_MODELWIDGET_H
#define PF_MODELWIDGET_H

#include <QWidget>

class QPushButton;
namespace ProjectExplorer {
class PF_ProjectTreeWidget;

class PF_ModelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PF_ModelWidget(QWidget *parent = nullptr);
    ~PF_ModelWidget();

    void init();
private:
    QWidget* m_toolbar;
    QPushButton* tb_previousNode;
    QPushButton* tb_nextNode;
    QPushButton* tb_moveup;
    QPushButton* tb_movedown;
    QPushButton* tb_show;
    QPushButton* tb_collapseAll;
    QPushButton* tb_expandAll;
    PF_ProjectTreeWidget* m_modelTreeWidget;
signals:

public slots:
};
}//namespace ProjectExplorer
#endif // PF_MODELWIDGET_H
