#include "inputwidget.h"

InputWidget::InputWidget(QWidget *parent)
    : QWidget(parent),
      mCurveSelectBox(new QComboBox(this)),
      mGroupBox(new QGroupBox(this)),
      mVLayout1(new QVBoxLayout(this)),
      mVLayout2(new QVBoxLayout(mGroupBox)),
      mInput(FORCE_TIME_CURVE)
{
    mGroupBox->setTitle(tr("Select the Dynamic Characteristics Input"));
    mCurveSelectBox->addItem(tr("The Electromagnetic Force-Time Curve"));
    mCurveSelectBox->setParent(mGroupBox);

//    mVLayout1->setMargin(0);
    mVLayout1->addWidget(mGroupBox);
    mVLayout1->addStretch();
    mVLayout2->addWidget(mCurveSelectBox);

    connect(mCurveSelectBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeInput(int)));
}

void InputWidget::slotChangeInput(int index)
{
    mInput = static_cast<Input>(index);
}
