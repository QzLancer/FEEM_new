#include "bouncedialog.h"
#include "bouncecore.h"

#include <postoperation/plot/plotwidget.h>

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
    double opendistance = mParamWidget->mOpenDistanceEdit->text().toDouble();
    double stroke = mParamWidget->mStrokeEdit->text().toDouble();
    double movingcontactmass = mParamWidget->mMovingMassEdit->text().toDouble();
    double concentratedmass = mParamWidget->mConcentratedMassEdit->text().toDouble();
    double contactspringstiffness = mParamWidget->mContactSpringStiffnessEdit->text().toDouble();
    double returnspringstiffness = mParamWidget->mReturnSpringStiffnessEdit->text().toDouble();
    double contactspringpreloads = mParamWidget->mContactSpringPreloadsEdit->text().toDouble();
    double returnspringpreloads = mParamWidget->mReturnSpringPreloadsEdit->text().toDouble();
    double contactstiffness = mParamWidget->mContactStiffnessEdit->text().toDouble();
    double contactpenetration = mParamWidget->mContactPenetrationEdit->text().toDouble();
    double contactdamping = mParamWidget->mContactDampingEdit->text().toDouble();
    double contactcoefficient = mParamWidget->mContactCoefficientEdit->text().toDouble();
    double starttime = mSolverWidget->mStartTimeEdit->text().toDouble();
    double stoptime = mSolverWidget->mStopTimeEdit->text().toDouble();
    double fixedstepsize = mSolverWidget->mFixedStepSizeEdit->text().toDouble();

    BounceCore *core = new BounceCore(opendistance,
                                      stroke,
                                      movingcontactmass,
                                      concentratedmass,
                                      contactspringstiffness,
                                      returnspringstiffness,
                                      contactspringpreloads,
                                      returnspringpreloads,
                                      contactstiffness,
                                      contactpenetration,
                                      contactdamping,
                                      contactcoefficient,
                                      starttime,
                                      stoptime,
                                      fixedstepsize);
    core->bounceCalculate();

    PlotWidget *pw = new PlotWidget;
    pw->addPlot(core->gett(), core->getxd(), tr("Moving Contact Displacement"));
    pw->addPlot(core->gett(), core->getxx(), tr("Armature Displacement"));
    pw->addTableColumn(core->gett(), tr("time"));
    pw->addTableColumn(core->getxd(), tr("Moving Contact Displacement"));
    pw->addTableColumn(core->getxx(), tr("Armature Displacement"));
    pw->show();

    delete core;
}
