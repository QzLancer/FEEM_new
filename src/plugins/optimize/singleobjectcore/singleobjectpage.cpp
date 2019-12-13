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
    : mGroup1(new QGroupBox(this)),
      mGroup2(new QGroupBox(this)),
      mObjectBox(new QComboBox(mGroup1)),
      mModeBox(new QComboBox(mGroup1)),
      mInputWidget(new InputParamWidget(mGroup1)),
//      mWizard(parent),
      mPicLabel(new QLabel(mGroup2)),
      mTipLabel(new QLabel(mGroup2)),
      mWizard(parent)
{
    initialize();
}

SingleObjectPage::~SingleObjectPage()
{

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

    QString str1("电磁力（保持力）：一般望大，保证继电器可靠吸合。主要影响因素包括：气隙及永磁附近的尺寸因素(如衔铁尺寸，轭铁尺寸，铁芯尺寸，永磁体尺寸等)，线圈匝数，线圈电阻，电源电压，软磁材料的磁化特性，永磁材料的磁化特性等");
    QString str2("吸合时间：一般望小。主要影响因素包括：气隙及永磁附近的尺寸因素(如衔铁尺寸，轭铁尺寸，铁芯尺寸，永磁体尺寸等)，衔铁质量，衔铁行程，反力特性（超程弹簧、反力弹簧），线圈匝数，线圈电阻，电源电压，软磁材料的磁化特性，永磁材料的磁化特性等");
    QString str3("释放时间：一般望小。主要影响因素包括：气隙及永磁附近的尺寸因素(如衔铁尺寸，轭铁尺寸，铁芯尺寸，永磁体尺寸等)，衔铁质量，衔铁行程，反力特性（超程弹簧、反力弹簧），线圈匝数，线圈电阻，电源电压，软磁材料的磁化特性，永磁材料的磁化特性等");

//    appendOptimizeHintMap(tr("Electromagnetic force"), tr("Electromagnetic force: Expect a large value."));
    appendOptimizeHintMap(tr("Electromagnetic force"), str1);
//    appendOptimizeHintMap(tr("Pick-up time"), tr("Pick-up time: Expect a small value."));
    appendOptimizeHintMap(tr("Pick-up time"), str2);
//    appendOptimizeHintMap(tr("Release time"), tr("Release time: Expect a large value."));
    appendOptimizeHintMap(tr("Release time"), str3);
    emit(SingleObjectPage::slotObjectChange(tr("Electromagnetic force")));

    connect(mInputWidget, &InputParamWidget::inputParamChanged, this, &SingleObjectPage::slotButtonEnable);
}

void SingleObjectPage::initialize(QStringList inputlist)
{
    initialize();
    setInputList(inputlist);
}

void SingleObjectPage::setPicture(QPixmap pic)
{
    mCurrentPic = pic;
    QPixmap scaledpic = mCurrentPic.scaled(mPicLabel->width(), mPicLabel->height(),
                     Qt::KeepAspectRatio, Qt::SmoothTransformation);
    mPicLabel->setPixmap(scaledpic);
}

void SingleObjectPage::setInputList(QStringList inputlist)
{
    mInputWidget->setInputList(inputlist);
}

void SingleObjectPage::appendInputList(const QString inputstr)
{
    mInputWidget->appendInputList(inputstr);
}

QStringList SingleObjectPage::getInputList()
{
    if(mInputWidget->getInputName().empty()){
        qDebug() << "InputList is empty!";
    }
    return mInputWidget->getInputName();
}

void SingleObjectPage::resizeEvent(QResizeEvent *event)
{
    if(!mCurrentPic.isNull()){
        QPixmap scaledpic = mCurrentPic.scaled(mPicLabel->width(), mPicLabel->height(),
                         Qt::KeepAspectRatio, Qt::SmoothTransformation);
        mPicLabel->setPixmap(scaledpic);
    }
}

void SingleObjectPage::slotObjectChange(const QString &text)
{
    mTipLabel->setText(mOptimizeHintMap[text]);
}

void SingleObjectPage::slotButtonEnable()
{
    if(mInputWidget->getInputName().isEmpty()){
        mWizard->button(QWizard::NextButton)->setEnabled(false);
        mWizard->button(QWizard::FinishButton)->setEnabled(false);
    }else{
        mWizard->button(QWizard::NextButton)->setEnabled(true);
        mWizard->button(QWizard::FinishButton)->setEnabled(true);
    }
}

void SingleObjectPage::initializeGroup1()
{
    //优化目标
    QLabel *targetlabel = new QLabel(tr("Object to be optimized"), mGroup1);
    QLabel *modelabel = new QLabel(tr("Optimize Mode"), mGroup1);
    QComboBox *targetbox = mObjectBox;
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

    connect(mObjectBox, SIGNAL(activated(const QString &)), this, SLOT(slotObjectChange(const QString &)));
}

void SingleObjectPage::initializeGroup2()
{
    QVBoxLayout *vlayout = new QVBoxLayout(mGroup2);
//    mPicLabel->setScaledContents(true);
    mTipLabel->setWordWrap(true);
//    mTipLabel->setText("电磁力（保持力）：一般望大，保证继电器可靠吸合。主要影响因素包括：气隙及永磁附近的尺寸因素(如衔铁尺寸，轭铁尺寸，铁芯尺寸，永磁体尺寸等)，线圈匝数，线圈电阻，电源电压，软磁材料的磁化特性，永磁材料的磁化特性等");
    vlayout->addWidget(mPicLabel);
    vlayout->addWidget(mTipLabel);
    vlayout->setStretch(0, 1);
    vlayout->setStretch(1, 1);
}

QMap<QString, QString> SingleObjectPage::optimizeHintMap() const
{
    return mOptimizeHintMap;
}

QStringList SingleObjectPage::getInputName() const
{
    return mInputWidget->getInputName();
}

QList<QList<double>> SingleObjectPage::getInputValue() const
{
    return mInputWidget->getInputValue();
}

QString SingleObjectPage::getCurrentObject() const
{
    return mObjectBox->currentText();
}

QString SingleObjectPage::getCurrentMode() const
{
    return mModeBox->currentText();
}

void SingleObjectPage::setOptimizeHintMap(const QMap<QString, QString> optimizeHintMap)
{
    mOptimizeHintMap = optimizeHintMap;
    mObjectBox->clear();
    for(auto i = mOptimizeHintMap.begin(); i != mOptimizeHintMap.end(); ++i){
        mObjectBox->addItem(i.key());
    }
}

void SingleObjectPage::appendOptimizeHintMap(QString objective, QString hint)
{
    mOptimizeHintMap.insert(objective, hint);
    mObjectBox->addItem(objective);
}

