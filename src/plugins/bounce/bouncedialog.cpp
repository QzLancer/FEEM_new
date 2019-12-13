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
    bool opendistanceok;
    bool strokeok;
    bool movingcontactmassok;
    bool concentratedmassok;
    bool contactspringstiffnessok;
    bool returnspringstiffnessok;
    bool contactspringpreloadsok;
    bool returnspringpreloadsok;
    bool contactstiffnessok;
    bool contactpenetrationok;
    bool contactdampingok;
    bool contactcoefficientok;
    bool starttimeok;
    bool stoptimeok;
    bool fixedstepsizeok;

    BounceParam param;
    param.opendistance = mParamWidget->mOpenDistanceEdit->text().toDouble(&opendistanceok);
    param.stroke = mParamWidget->mStrokeEdit->text().toDouble(&strokeok);
    param.movingcontactmass = mParamWidget->mMovingMassEdit->text().toDouble(&movingcontactmassok);
    param.concentratedmass = mParamWidget->mConcentratedMassEdit->text().toDouble(&concentratedmassok);
    param.contactspringstiffness = mParamWidget->mContactSpringStiffnessEdit->text().toDouble(&contactspringstiffnessok);
    param.returnspringstiffness = mParamWidget->mReturnSpringStiffnessEdit->text().toDouble(&returnspringstiffnessok);
    param.contactspringpreloads = mParamWidget->mContactSpringPreloadsEdit->text().toDouble(&contactspringpreloadsok);
    param.returnspringpreloads = mParamWidget->mReturnSpringPreloadsEdit->text().toDouble(&returnspringpreloadsok);
    param.contactstiffness = mParamWidget->mContactStiffnessEdit->text().toDouble(&contactstiffnessok);
    param.contactpenetration = mParamWidget->mContactPenetrationEdit->text().toDouble(&contactpenetrationok);
    param.contactdamping = mParamWidget->mContactDampingEdit->text().toDouble(&contactdampingok);
    param.contactcoefficient = mParamWidget->mContactCoefficientEdit->text().toDouble(&contactcoefficientok);
    param.starttime = mSolverWidget->mStartTimeEdit->text().toDouble(&starttimeok);
    param.endtime = mSolverWidget->mStopTimeEdit->text().toDouble(&stoptimeok);
    param.fixedstepsize = mSolverWidget->mFixedStepSizeEdit->text().toDouble(&fixedstepsizeok);

    BounceCore *core = new BounceCore(param);
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
