#include "singleobjectpage.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtDebug>
#include <QPushButton>
#include <QTableView>
#include <QLineEdit>
#include <QFormLayout>

SingleObjectPage::SingleObjectPage(QWidget *parent)
    : QDialog(parent),
      mGroup1(new QGroupBox(this)),
      mGroup2(new QGroupBox(this)),
      mTargetBox(new QComboBox(mGroup1)),
      mModeBox(new QComboBox(mGroup1)),
//      mSizeEdit(new QLineEdit("50", mGroup2)),
//      mTimeEdit(new QLineEdit("500", mGroup2)),
//      mRateEdit(new QLineEdit("0.1", mGroup2)),
//      mWLowerEdit(new QLineEdit("0.4", mGroup2)),
//      mWUpperEdit(new QLineEdit("0.9", mGroup2)),
//      mC1Edit(new QLineEdit("2", mGroup2)),
//      mC2Edit(new QLineEdit("2", mGroup2)),
//      mWarningLabel1(new QLabel(mGroup2)),
      mInputWidget(new InputParamWidget(mGroup1))
{
    initialize();
}

SingleObjectPage::~SingleObjectPage()
{
    delete mInputWidget;
//    delete mWarningLabel1;
//    delete mC2Edit;
//    delete mC1Edit;
//    delete mWLowerEdit;
//    delete mWUpperEdit;
//    delete mRateEdit;
//    delete mTimeEdit;
//    delete mSizeEdit;
    delete mModeBox;
    delete mTargetBox;
    delete mGroup2;
    delete mGroup1;
}

void SingleObjectPage::initialize()
{
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    initializeGroup1();
    initializeGroup2();

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(mGroup1);
    hlayout->addWidget(mGroup2);
    hlayout->setStretch(0,1);
    hlayout->setStretch(1,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
}

void SingleObjectPage::initialize(QStringList inputlist, QStringList targetlist)
{
    initialize();
    setInputList(inputlist);
    setTargetList(targetlist);
}

void SingleObjectPage::setInputList(QStringList inputlist)
{
    mInputList = inputlist;
    mInputWidget->setInputList(mInputList);
}

void SingleObjectPage::appendInputList(const QString inputstr)
{
    mInputList.append(inputstr);
}

void SingleObjectPage::setTargetList(QStringList targetlist)
{
    mTargetList = targetlist;
    mTargetBox->clear();
    mTargetBox->addItems(targetlist);
}

void SingleObjectPage::appendTargetList(const QString targetstr)
{
    mTargetList.append(targetstr);
}

QStringList SingleObjectPage::InputList()
{
    if(mInputList.empty()){
        qDebug() << "InputList is empty!";
    }
    return mInputList;
}

QStringList SingleObjectPage::TargetList()
{
    if(mTargetList.empty()){
        qDebug() << "TargetList is empty!";
    }
    return mTargetList;
}

void SingleObjectPage::initializeGroup1()
{
    mGroup1->setTitle(tr("Object to be optimized && input parameters"));

    //优化目标
    QLabel *targetlabel = new QLabel(tr("Target to be optimized"), mGroup1);
    QLabel *modelabel = new QLabel(tr("Optimize Mode"), mGroup1);
    QComboBox *targetbox = mTargetBox;
    QComboBox *modebox = mModeBox;
    modebox->addItem(tr("Maximize"));
    modebox->addItem(tr("Minimize"));

    //layout
    QGridLayout *gridlayout = new QGridLayout;
    gridlayout->addWidget(targetlabel, 0, 0);
    gridlayout->addWidget(targetbox, 0, 1);
    gridlayout->addWidget(modelabel, 1 ,0);
    gridlayout->addWidget(modebox, 1, 1);

    QVBoxLayout *vlayout = new QVBoxLayout(mGroup1);
    vlayout->addLayout(gridlayout);
    vlayout->addWidget(mInputWidget);
}

void SingleObjectPage::initializeGroup2()
{


}


void SingleObjectPage::objectiveFunction(SParticle *Particle)
{
    const double *_position = Particle->getPosition ();
    double _constraits;

    Particle->setValue(100 * pow((_position[1] - pow(_position[0], 2)), 2) + pow((1 - _position[0]), 2));
    _constraits = _position[1] + _position[0] > 1 ? 10000000 * (_position[1] + _position[0] - 1) : 0;
    //_constraits = 0;
    Particle->setConstraits(_constraits);
    Particle->setFeasible(_constraits ? false : true);
    return;
}

