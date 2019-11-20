#include "bouncestack.h"
#include "bouncedialog.h"

BounceStack::BounceStack(BounceDialog *parent, QString title, QWidget *mainwidget)
    : QWidget(parent),
      mTitleLabel(new QLabel(title, this)),
      mMainWidget(mainwidget),
      mMainLayout(new QVBoxLayout(this))
{
    QFont font;
    font.setPointSize(15);
    font.setBold(true);
    mTitleLabel->setFont(font);

    mMainLayout->addWidget(mTitleLabel);
    mMainLayout->addWidget(mMainWidget);
    mMainLayout->setMargin(0);
    mTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    parent->mListWidget->addItem(title);
    parent->mStackedWidget->addWidget(this);
}
