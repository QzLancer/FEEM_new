#include "typepage.h"

TypePage::TypePage(QWizardPage *parent)
    : QWizardPage(parent),
      mList(new QListWidget(this)),
      mPicLabel(new QLabel(this)),
      mHLayout(new QHBoxLayout(this))
{
    setTitle(tr("Select the type of relay"));

    mHLayout->addWidget(mList);
    mHLayout->addWidget(mPicLabel);
    mList->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    QPixmap pix1(QPixmap(":./pic/imgs/relay1.jpg"));
    appendListPicMap("relay1", QPixmap(":./pic/imgs/relay1.jpg"));
    appendListPicMap("son1", QPixmap(":./pic/imgs/son1.jpg"));
    appendListPicMap("son2", QPixmap(":./pic/imgs/son2.jpg"));
    mList->setCurrentRow(0);
    mPicLabel->setAutoFillBackground(true);
    mPicLabel->setPixmap(QPixmap(":./pic/imgs/relay1.jpg"));
    connect(mList, &QListWidget::itemClicked, this, &TypePage::slotChangePic);
}

void TypePage::appendListPicMap(const QString name, const QPixmap pic)
{
    mListPicMap.insert(name, pic);
    mList->addItem(name);
}

void TypePage::slotChangePic(QListWidgetItem *item)
{
    mPicLabel->setPixmap(mListPicMap[item->text()]);
}

void TypePage::resizeEvent(QResizeEvent *event)
{
    QWizardPage::resizeEvent(event);
}
