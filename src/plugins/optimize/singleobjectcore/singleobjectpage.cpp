#include "singleobjectpage.h"
#include "singleobjwizard.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtDebug>
#include <QPushButton>
#include <QTableView>
#include <QLineEdit>
#include <QFormLayout>

SingleObjectPage::SingleObjectPage(QWizard *parent)
    : QWizardPage(parent),
      mGroup1(new QGroupBox(this)),
      mGroup2(new QGroupBox(this)),
      mTargetBox(new QComboBox(mGroup1)),
      mModeBox(new QComboBox(mGroup1)),
      mInputWidget(new InputParamWidget(mGroup1)),
//      mWizard(parent),
      mPicLabel(new QLabel(mGroup2))
{
    initialize();
}

SingleObjectPage::~SingleObjectPage()
{
//    delete mWizard;
//    delete mInputWidget;
//    delete mModeBox;
//    delete mTargetBox;
//    delete mGroup2;
//    delete mGroup1;
}

void SingleObjectPage::initialize()
{
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setTitle(tr("Object to be optimized & Input parameters"));

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

void SingleObjectPage::setPicture(QPixmap pic)
{
    mCurrentPic = pic;
    QPixmap scaledpic = mCurrentPic.scaled(mPicLabel->width(), mPicLabel->height(),
                     Qt::KeepAspectRatio, Qt::SmoothTransformation);
    qDebug() << mPicLabel->size();
    mPicLabel->setPixmap(scaledpic);
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

void SingleObjectPage::resizeEvent(QResizeEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    QPixmap scaledpic = mCurrentPic.scaled(mPicLabel->width(), mPicLabel->height(),
                     Qt::KeepAspectRatio, Qt::SmoothTransformation);
    qDebug() << mPicLabel->size();
    mPicLabel->setPixmap(scaledpic);
}

void SingleObjectPage::initializeGroup1()
{
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
    QVBoxLayout *vlayout = new QVBoxLayout(mGroup2);
//    mPicLabel->setScaledContents(true);
    QLabel *tiplabel = new QLabel(mGroup2);
    tiplabel->setWordWrap(true);
    tiplabel->setText("电磁力（保持力）：一般望大，保证继电器可靠吸合。主要影响因素包括：气隙及永磁附近的尺寸因素(如衔铁尺寸，轭铁尺寸，铁芯尺寸，永磁体尺寸等)，线圈匝数，线圈电阻，电源电压，软磁材料的磁化特性，永磁材料的磁化特性等");
    vlayout->addWidget(mPicLabel);
    vlayout->addWidget(tiplabel);
    vlayout->setStretch(0, 1);
    vlayout->setStretch(1, 1);
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

