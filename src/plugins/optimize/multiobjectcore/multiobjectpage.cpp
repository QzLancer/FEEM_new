#include "multiobjectpage.h"

#include <QHBoxLayout>
#include <QDebug>

MultiObjectPage::MultiObjectPage(QWizard *parent)
    : mGroup1(new QGroupBox(this)),
      mGroup2(new QGroupBox(this)),
      mInputWidget(new InputParamWidget(mGroup2)),
      mObjectWidget(new ObjectWidget(mGroup1)),
      mPicLabel(new QLabel(mGroup2)),
      mTipLabel(new QLabel(mGroup2)),
      mWizard(parent)
{
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setTitle(tr("Object to be optimized & Input parameters"));
    initializeGroup1();
    initializeGroup2();

    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->addWidget(mGroup1);
    hlayout->addWidget(mGroup2);
    hlayout->setStretch(0, 2);
    hlayout->setStretch(1, 1);

    QString str1("电磁力（保持力）：一般望大，保证继电器可靠吸合。主要影响因素包括：气隙及永磁附近的尺寸因素(如衔铁尺寸，轭铁尺寸，铁芯尺寸，永磁体尺寸等)，线圈匝数，线圈电阻，电源电压，软磁材料的磁化特性，永磁材料的磁化特性等");
    QString str2("吸合时间：一般望小。主要影响因素包括：气隙及永磁附近的尺寸因素(如衔铁尺寸，轭铁尺寸，铁芯尺寸，永磁体尺寸等)，衔铁质量，衔铁行程，反力特性（超程弹簧、反力弹簧），线圈匝数，线圈电阻，电源电压，软磁材料的磁化特性，永磁材料的磁化特性等");
    QString str3("释放时间：一般望小。主要影响因素包括：气隙及永磁附近的尺寸因素(如衔铁尺寸，轭铁尺寸，铁芯尺寸，永磁体尺寸等)，衔铁质量，衔铁行程，反力特性（超程弹簧、反力弹簧），线圈匝数，线圈电阻，电源电压，软磁材料的磁化特性，永磁材料的磁化特性等");

//    appendOptimizeHintMap(tr("Electromagnetic force"), tr("Electromagnetic force: Expect a large value."));
    appendOptimizeHintMap(tr("Electromagnetic force"), str1);
//    appendOptimizeHintMap(tr("Pick-up time"), tr("Pick-up time: Expect a small value."));
    appendOptimizeHintMap(tr("Pick-up time"), str2);
//    appendOptimizeHintMap(tr("Release time"), tr("Release time: Expect a large value."));
    appendOptimizeHintMap(tr("Release time"), str3);

    emit(MultiObjectPage::slotObjectChange(tr("Electromagnetic force")));

    connect(mInputWidget, &InputParamWidget::inputParamChanged, this, &MultiObjectPage::slotButtonEnable);
    connect(mObjectWidget, &ObjectWidget::objectChanged, this, &MultiObjectPage::slotButtonEnable);

}

QStringList MultiObjectPage::getInputList() const
{
    return mInputWidget->getInputName();
}

QList<QList<double>> MultiObjectPage::getInputValue() const
{
    return mInputWidget->getInputValue();
}

void MultiObjectPage::setInputList(const QStringList &inputList)
{
    mInputWidget->setInputList(inputList);
}

void MultiObjectPage::appendInputList(const QString &input) const
{
    mInputWidget->appendInputList(input);
}

QStringList MultiObjectPage::getObjectList() const
{
    return mObjectWidget->getObjectList();
}

void MultiObjectPage::setObjectList(const QStringList &objectList)
{
    mObjectWidget->setObjectList(objectList);
}

void MultiObjectPage::appendObjectList(const QString &object)
{
    mObjectWidget->appendObjectList(object);
}

void MultiObjectPage::setPicture(const QPixmap pic)
{
    mCurrentPic = pic;
    QPixmap scaledpic = mCurrentPic.scaled(mPicLabel->width(), mPicLabel->height(),
                     Qt::KeepAspectRatio, Qt::SmoothTransformation);
    mPicLabel->setPixmap(scaledpic);
}

QMap<QString, QString> MultiObjectPage::getObjectModeMap() const
{
    return mObjectWidget->getObjectModeMap();
}


QStringList MultiObjectPage::getInputName() const
{
    return mInputWidget->getInputName();
}

void MultiObjectPage::resizeEvent(QResizeEvent *event)
{
    if(!mCurrentPic.isNull()){
        QPixmap scaledpic = mCurrentPic.scaled(mPicLabel->width(), mPicLabel->height(),
                         Qt::KeepAspectRatio, Qt::SmoothTransformation);
        mPicLabel->setPixmap(scaledpic);
    }
}

void MultiObjectPage::slotObjectChange(const QString &text)
{
    mTipLabel->setText(mOptimizeHintMap[text]);
}

void MultiObjectPage::slotButtonEnable()
{
    qDebug() << Q_FUNC_INFO;
    if(mInputWidget->getInputName().isEmpty() || mObjectWidget->getObjectModeMap().isEmpty()){
        mWizard->button(QWizard::NextButton)->setEnabled(false);
        mWizard->button(QWizard::FinishButton)->setEnabled(false);
    }else{
        mWizard->button(QWizard::NextButton)->setEnabled(true);
        mWizard->button(QWizard::FinishButton)->setEnabled(true);
    }
}

void MultiObjectPage::initializeGroup1()
{
    QHBoxLayout *hlayout = new QHBoxLayout(mGroup1);
    hlayout->addWidget(mObjectWidget);

    QVBoxLayout *vlayout = new QVBoxLayout;
    mTipLabel->setWordWrap(true);
//    mTipLabel->setText("电磁力（保持力）：一般望大，保证继电器可靠吸合。主要影响因素包括：气隙及永磁附近的尺寸因素(如衔铁尺寸，轭铁尺寸，铁芯尺寸，永磁体尺寸等)，线圈匝数，线圈电阻，电源电压，软磁材料的磁化特性，永磁材料的磁化特性等");
    vlayout->addWidget(mPicLabel);
    vlayout->addWidget(mTipLabel);
    vlayout->setStretch(0, 1);
    vlayout->setStretch(1, 1);

    hlayout->addLayout(vlayout);
    hlayout->setStretch(0, 1);
    hlayout->setStretch(1, 1);

    connect(mObjectWidget->getObjectBox(), SIGNAL(activated(const QString &)), this, SLOT(slotObjectChange(const QString &)));
}

void MultiObjectPage::initializeGroup2()
{
    QHBoxLayout *hlayout = new QHBoxLayout(mGroup2);
    hlayout->addWidget(mInputWidget);
}

QMap<QString, QString> MultiObjectPage::getOptimizeHintMap() const
{
    return mOptimizeHintMap;
}

void MultiObjectPage::setOptimizeHintMap(const QMap<QString, QString> &optimizeHintMap)
{
    mOptimizeHintMap = optimizeHintMap;
    QStringList objectlist;
    for(auto i = mOptimizeHintMap.begin(); i != mOptimizeHintMap.end(); ++i){
        objectlist.append(i.key());
    }
    mObjectWidget->setObjectList(objectlist);
}

void MultiObjectPage::appendOptimizeHintMap(const QString &objective, const QString hint)
{
    mOptimizeHintMap.insert(objective, hint);
    mObjectWidget->appendObjectList(objective);
}
