#include "typepage.h"

#include <QDebug>

TypePage::TypePage(QWizard *parent)
    : QWizardPage(parent),
      mList(new QListWidget(this)),
      mPicLabel(new QLabel(this)),
      mHLayout(new QHBoxLayout(this))
{
    setTitle(tr("Select the type of relay"));
    mHLayout->addWidget(mList);
    mHLayout->addWidget(mPicLabel);
    mList->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    connect(mList, &QListWidget::currentItemChanged, this, &TypePage::slotChangePic);
//    mPicLabel->setAutoFillBackground(true);
}

void TypePage::appendListPicMap(const QString name, const QPixmap pic)
{
    mListPicMap.insert(name, pic);
    mList->addItem(name);
}

QPixmap TypePage::getCurrentMap() const
{
    QString name = mList->currentItem()->text();
    return mListPicMap[name];
}

void TypePage::slotChangePic(QListWidgetItem *item)
{
    qDebug() << Q_FUNC_INFO;
    mCurrentPic = mListPicMap[item->text()];
    mScaledPic = mCurrentPic.scaled(mPicLabel->width(), mPicLabel->height(),
                                    Qt::KeepAspectRatio, Qt::SmoothTransformation);
    mPicLabel->setPixmap(mScaledPic);
}

void TypePage::resizeEvent(QResizeEvent *event)
{
    QWizardPage::resizeEvent(event);
    if(!mCurrentPic.isNull()){
        qDebug() << Q_FUNC_INFO << mPicLabel->size();
        mScaledPic = mCurrentPic.scaled(mPicLabel->width(), mPicLabel->height(),
                         Qt::KeepAspectRatio, Qt::SmoothTransformation);
        mPicLabel->setPixmap(mScaledPic);
    }
}

QPixmap TypePage::getCurrentPic() const
{
    return mCurrentPic;
}

void TypePage::setCurrentPic(const QPixmap &currentPic)
{
    mCurrentPic = currentPic;
}
