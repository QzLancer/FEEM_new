#ifndef HEATBOUNDARYDIALOG_H
#define HEATBOUNDARYDIALOG_H

#include "boundaryprop.h"

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QStackedLayout>

namespace ProjectExplorer{
    class PF_ProjectTree;
    class PF_Project;
    class Node;
    class LeafNode;
}
namespace HeatFEMProjectManagerPlugin{
    class PF_Heat2DSProject;
}


class HeatBoundaryDialog : public QDialog
{
    Q_OBJECT
public:
    HeatBoundaryDialog(CHBoundaryProp* boundary, QWidget* parent = nullptr);
    ~HeatBoundaryDialog();

    void initialization();

    void updateDialog();

    void setBoundary(CHBoundaryProp* boundary);
    CHBoundaryProp *getBoundary();

signals:
    void boundaryAdded(CHBoundaryProp*);

public slots:
    void TreeNodetoLineBox(ProjectExplorer::Node *node);
    void LineBoxtoEntity(int index);
    void slotChangeType(int type);
    void slotAddBoundary();


private:
    CHBoundaryProp* m_boundary;
    ProjectExplorer::PF_ProjectTree *m_projecttree;
    HeatFEMProjectManagerPlugin::PF_Heat2DSProject *m_project;
    BoundaryType mCurrentType = FIRST;

    /** 控件 **/
    QComboBox *mLineBox;
    QComboBox *mTypeBox;
    QLineEdit *mParamTEdit;  //第一类边界条件，温度
    QLineEdit *mParamqEdit; //第二类边界条件，热流密度
    QLineEdit *mParamhEdit; //第三类边界条件，对流传热系数
    QLineEdit *mParamT0Edit;    //第三类边界条件，介质温度
    QStackedLayout *mParamLayout;
    QList <ProjectExplorer::LeafNode*> mLineNodes;
};


#endif // HEATBOUNDARYDIALOG_H
