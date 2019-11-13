#include "singlepsopage.h"

#include <QFormLayout>
#include <QDebug>
#include <QPalette>
#include <singleobjwizard.h>

SinglePSOPage::SinglePSOPage(QWizard *parent)
    : mSizeEdit(new QLineEdit("50", this)),
      mTimeEdit(new QLineEdit("500", this)),
      mRateEdit(new QLineEdit("0.1", this)),
      mWLowerEdit(new QLineEdit("0.4", this)),
      mWUpperEdit(new QLineEdit("0.9", this)),
      mC1Edit(new QLineEdit("2", this)),
      mC2Edit(new QLineEdit("2", this)),
      mWarningLabel(new QLabel(this)),
      mWizard(parent)
{
    setTitle(tr("Single object PSO parameters"));

    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::red);
    mWarningLabel->setPalette(pe);

    //种群大小
    QLabel *sizelabel = new QLabel(tr("Number of Particles: "), this);
    QLineEdit *sizeedit = mSizeEdit;

    //粒子群循环次数
    QLabel *timelabel = new QLabel(tr("Max iteration: "), this);
    QLineEdit *timeedit = mTimeEdit;

    //变异概率
    QLabel *ratelabel = new QLabel(tr("Mutation rate: "), this);
    QLineEdit *rateedit = mRateEdit;

    //w下界
    QLabel *wlowerlabel = new QLabel(tr("Lower weight: "), this);
    QLineEdit *wloweredit = mWLowerEdit;

    //w上界
    QLabel *wupperlabel = new QLabel(tr("Upper weight: "), this);
    QLineEdit *wupperedit = mWUpperEdit;

    //c1
    QLabel *c1label = new QLabel(tr("c1: "), this);
    QLineEdit *c1edit = mC1Edit;

    //c2
    QLabel *c2label = new QLabel(tr("c2: "), this);
    QLineEdit *c2edit = mC2Edit;

    //layout
    QFormLayout *flayout = new QFormLayout(this);
    qDebug() << layout();
    flayout->addRow(sizelabel, sizeedit);
    flayout->addRow(timelabel, timeedit);
    flayout->addRow(ratelabel, rateedit);
    flayout->addRow(wlowerlabel, wloweredit);
    flayout->addRow(wupperlabel, wupperedit);
    flayout->addRow(c1label, c1edit);
    flayout->addRow(c2label, c2edit);

    connect(parent, &QWizard::accepted, this, &SinglePSOPage::isParamError);
}

void SinglePSOPage::isParamError()
{
    qDebug() << Q_FUNC_INFO;
}
