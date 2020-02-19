#include "heatboundarydialog.h"
#include "pf_heat2dsproject.h"

#include <project/pf_projecttree.h>
#include <project/pf_node.h>

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>


using namespace ProjectExplorer;
using namespace HeatFEMProjectManagerPlugin;

HeatBoundaryDialog::HeatBoundaryDialog(QWidget *parent)
    : QDialog(parent),
      m_projecttree(ProjectExplorer::PF_ProjectTree::instance()),
      m_project(dynamic_cast<PF_Heat2DSProject*>(m_projecttree->currentProject())),
      mLineBox(new QComboBox(this)),
      mTypeBox(new QComboBox(this)),
      mParamTEdit(new QLineEdit(this)),
      mParamqEdit(new QLineEdit(this)),
      mParamhEdit(new QLineEdit(this)),
      mParamT0Edit(new QLineEdit(this)),
      mParamLayout(new QStackedLayout),
      mErrorLabel(new QLabel(this))
{
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::red);
    mErrorLabel->setPalette(pe);
    mErrorLabel->setText(" ");

    initialization();
    resize(300,200);
    updateDialog();
    connect(m_project, &PF_Heat2DSProject::nodeSelected, this, &HeatBoundaryDialog::TreeNodetoLineBox);
    connect(this, &HeatBoundaryDialog::boundaryAdded, m_project, &PF_Heat2DSProject::addBoundary);
}

HeatBoundaryDialog::~HeatBoundaryDialog()
{

}

void HeatBoundaryDialog::initialization()
{
    QLabel *linelabel = new QLabel(tr("Select Line"), this);
    QLabel *typelabel = new QLabel(tr("Select Boundary Type"), this);
    QPushButton *AddButton = new QPushButton(tr("Add"), this);
    QPushButton *CancelButton = new QPushButton(tr("Cancel"), this);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(linelabel);
    vlayout->addWidget(mLineBox);
    vlayout->addWidget(typelabel);
    vlayout->addWidget(mTypeBox);

    mTypeBox->addItem(tr("First-Type Boundary"));
    mTypeBox->addItem(tr("Second-Type Boundary"));
    mTypeBox->addItem(tr("Third-Type Boundary"));

    /** 设置参数的Widget **/
    QWidget *type1widget = new QWidget(this);
    QVBoxLayout *vlayout1 = new QVBoxLayout(type1widget);
    QLabel *paramTlabel = new QLabel(tr("Temperature(K)"), this);
    vlayout1->addWidget(paramTlabel);
    vlayout1->addWidget(mParamTEdit);
    vlayout1->addStretch();
    vlayout1->setMargin(0);

    QWidget *type2widget = new QWidget(this);
    QVBoxLayout *vlayout2 = new QVBoxLayout(type2widget);
    QLabel *paramqlabel = new QLabel(tr("Heat Flux(W/m^2)"), this);
    vlayout2->addWidget(paramqlabel);
    vlayout2->addWidget(mParamqEdit);
    vlayout2->addStretch();
    vlayout2->setMargin(0);

    QWidget *type3widget = new QWidget(this);
    QVBoxLayout *vlayout3 = new QVBoxLayout(type3widget);
    QLabel *paramhlabel = new QLabel(tr("Heat Transfer Cofficient(W/(m^2*K))"));
    QLabel *paramT0label = new QLabel(tr("Medium Temperature(K)"));
    vlayout3->addWidget(paramhlabel);
    vlayout3->addWidget(mParamhEdit);
    vlayout3->addWidget(paramT0label);
    vlayout3->addWidget(mParamT0Edit);
    vlayout3->addStretch();
    vlayout3->setMargin(0);

    mParamLayout->addWidget(type1widget);
    mParamLayout->addWidget(type2widget);
    mParamLayout->addWidget(type3widget);
    vlayout->addLayout(mParamLayout);
    vlayout->addWidget(mErrorLabel);
    vlayout->addStretch();

    /** 两个Button **/
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addStretch();
    hlayout->addWidget(AddButton);
    hlayout->addWidget(CancelButton);
    vlayout->addLayout(hlayout);

    /** 将线节点和mLineBox相关联 **/
    QList <ProjectExplorer::LeafNode*> mLineNodes = findLineNodes();
    for(auto a : mLineNodes){
        mLineBox->addItem(a->displayName());
    }

    connect(mTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeType(int)));
    connect(mLineBox, SIGNAL(currentIndexChanged(int)), this, SLOT(LineBoxtoEntity(int)));
    connect(AddButton, &QPushButton::clicked, this, &HeatBoundaryDialog::slotAddBoundary);
    connect(CancelButton, &QPushButton::clicked, this, &HeatBoundaryDialog::close);

}

void HeatBoundaryDialog::updateDialog()
{

}

void HeatBoundaryDialog::setBoundary(CHBoundaryProp *boundary)
{

}

CHBoundaryProp *HeatBoundaryDialog::getBoundary()
{
    return nullptr;
}

void HeatBoundaryDialog::TreeNodetoLineBox(Node *node)
{
    if(!node) return;
    if(node->asLeafNode()){
        if(dynamic_cast<LeafNode*>(node)->leafType() == LeafType::Line){
            mLineBox->setCurrentText(node->displayName());
        }
    }
    update();
}

/** 这部分取消注释后，出现添加一个边界，再去选择其它边，指针跑飞的bug **/
void HeatBoundaryDialog::LineBoxtoEntity(int index)
{
    QList <ProjectExplorer::LeafNode*> mLineNodes = findLineNodes();
    LeafNode *linenode = mLineNodes.at(index);
//    qDebug() << mLineNodes.at(index)->displayName();
    m_project->entitySelected(true,linenode);

}

void HeatBoundaryDialog::slotChangeType(int type)
{
    mParamLayout->setCurrentIndex(type);
    mCurrentType = (BoundaryType)(type+1);
//    qDebug() << "CurrentType = " << mCurrentType;
}

void HeatBoundaryDialog::slotAddBoundary()
{
    CHBoundaryProp *boundary = new CHBoundaryProp;
    boundary->name = mLineBox->currentText();
    boundary->type = mCurrentType;
    bool isError = false;
    bool isdouble0 = false, isdouble1 = false;

    switch(mCurrentType){
    case BoundaryType::FIRST:
        boundary->Tg = mParamTEdit->text().toDouble(&isdouble0);
        if(!isdouble0) isError = true;
        break;
    case BoundaryType::SECOND:
        boundary->q = mParamqEdit->text().toDouble(&isdouble0);
        if(!isdouble0) isError = true;
        break;
    case BoundaryType::THIRD:
        boundary->h = mParamhEdit->text().toDouble(&isdouble0);
        boundary->T0 = mParamT0Edit->text().toDouble(&isdouble1);
        if((!isdouble0) || (!isdouble1)) isError = true;
        break;
    }
    if(isError){
        mErrorLabel->setText(tr("Error: invalid parameter!"));
        delete boundary;
        return;
    }
    emit boundaryAdded(boundary);
    //    close();
}

QList<LeafNode *> HeatBoundaryDialog::findLineNodes()
{
    ProjectNode *root = m_project->rootProjectNode();   //根节点
    FolderNode *geofolder = nullptr;
    FolderNode *linefolder = nullptr;
    for(auto a : root->nodes()){
        if(a->displayName() == tr("Geometry")){
            geofolder = dynamic_cast<FolderNode*>(a);
            break;
        }
    } //几何Folder节点
//    qDebug() << geofolder->displayName();
    for(auto a : geofolder->nodes()){
        if(a->displayName() == tr("Line")){
            linefolder = dynamic_cast<FolderNode*>(a);
            break;
        }
    }   //线Folder节点
//    qDebug() << linefolder->displayName();
    if(linefolder){
        return linefolder->LeafNodes();
    }else{
        qDebug() << "QList<LeafNode *> HeatBoundaryDialog::findLineNodes() Error!";
        return *new QList<LeafNode *>;
    }
}


