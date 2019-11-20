#include "bouncedialog.h"

BounceDialog::BounceDialog(QWidget *parent)
    : QDialog(parent),
      mListWidget(new QListWidget(this)),
      mStackedWidget(new QStackedWidget(this)),
      mHBoxLayout(new QHBoxLayout),
      mVBoxLayout(new QVBoxLayout(this)),
      mButtonLayout(new QHBoxLayout),
      mRunButton(new QPushButton(tr("Run"), this)),
      mCancelButton(new QPushButton(tr("Cancel"), this)),
      mInputWidget(new InputWidget(this)),
      mParamWidget(new ParamWidget(this)),
      mSolverWidget(new SolverWidget(this))
{
    setMinimumSize(800, 600);
//    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setWindowTitle(tr("Bounce Calculate"));

    BounceStack *stack1 = new BounceStack(this, tr("Dynamic Characteristics Input"), mInputWidget);
    BounceStack *stack2 = new BounceStack(this, tr("Parameters Settings"), mParamWidget);
    BounceStack *stack3 = new BounceStack(this, tr("Solver"), mSolverWidget);

    mHBoxLayout->addWidget(mListWidget);
    mHBoxLayout->addWidget(mStackedWidget);
    mListWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    mButtonLayout->addStretch();
    mButtonLayout->addWidget(mRunButton);
    mButtonLayout->addWidget(mCancelButton);

    mVBoxLayout->addLayout(mHBoxLayout);
    mVBoxLayout->addLayout(mButtonLayout);
    setLayout(mVBoxLayout);

    connect(mListWidget, &QListWidget::currentRowChanged, mStackedWidget, &QStackedWidget::setCurrentIndex);
    connect(mCancelButton, &QPushButton::clicked, this, &BounceDialog::close);
    connect(mRunButton, &QPushButton::clicked, this, &BounceDialog::slotRun);
}

BounceDialog::~BounceDialog()
{

}

void BounceDialog::slotRun()
{

}
