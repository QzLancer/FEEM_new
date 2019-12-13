#include "singleobjwizard.h"
#include "singleobjectpage.h"
#include "singlepsopage.h"

#include <QWizardPage>
#include <QVBoxLayout>
#include <QListWidget>
#include <QDebug>

SingleObjWizard::SingleObjWizard(QWidget *parent)
    : QWizard(parent),
      page1(new TypePage(this)),
      page2(new SingleObjectPage(this)),
      page3(new SinglePSOPage(this))
{
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setFixedSize(900, 900);
    addPage(page1);
    addPage(page2);
    addPage(page3);
    connect(this, &SingleObjWizard::currentIdChanged, this, &SingleObjWizard::slotCurrentIdChange);
    connect(this, &SingleObjWizard::accepted, this, &SingleObjWizard::slotSolve);
}

void SingleObjWizard::appendInputList(const QString &input)
{
    page2->appendInputList(input);
}

void SingleObjWizard::slotCurrentIdChange(int id)
{
    if(id == 1){
        QPixmap pic = page1->getCurrentPic();
        page2->setPicture(pic);
        page2->slotButtonEnable();
    }
}

void SingleObjWizard::slotSolve()
{
    //将input parameter转换成可以传递的形式
    QStringList inputname = page2->getInputName();
    QList<QList<double>> inputvalue = page2->getInputValue();
    double *lower = new double[static_cast<unsigned long long>(inputvalue.size())];
    double *upper = new double[static_cast<unsigned long long>(inputvalue.size())];
    double *vmax = new double[static_cast<unsigned long long>(inputvalue.size())]; //粒子最大速度
    qDebug() << inputvalue;
    for(int i = 0; i < inputvalue.size(); ++i){
        lower[i] = inputvalue[i][0];
        upper[i] = inputvalue[i][1];
        vmax[i] = 0.1;
    }
    //读取各个lineedit中的数据，目前变异概率不使用
    int numberOfParticles = page3->mSizeEdit->text().toInt();
    int numberOfVariables = inputvalue.size();
    int maxIteration = page3->mTimeEdit->text().toInt();
    double lowerWeight = page3->mWLowerEdit->text().toDouble();
    double upperWeight = page3->mWUpperEdit->text().toDouble();
    double c1 = page3->mC1Edit->text().toDouble();
    double c2 = page3->mC2Edit->text().toDouble();
    QString stoppingCriteria = "none";
    QString psoType = "Classic";
    double threshold = 0.0001;

    //观察输入参数
    qDebug() << "lower: " << lower[0] << lower[1];
    qDebug() << "upper: " << upper[0] << upper[1];
    qDebug() << "vmax: " << vmax[0] << vmax[1];
    qDebug() << "numberOfParticles: " << numberOfParticles;
    qDebug() << "numberOfVariables: " << numberOfVariables;
    qDebug() << "maxIteration: " << maxIteration;
    qDebug() << "lowerWeight: " << lowerWeight;
    qDebug() << "upperWeight: " << upperWeight;
    qDebug() << "c1: " << c1;
    qDebug() << "c2: " << c2;
    qDebug() << page2->getCurrentMode();

    SParticle::OptimizeMode optimizeMode;
    if(page2->getCurrentMode() == tr("Maximize")){
        optimizeMode = SParticle::MAXIMIZE;
    }else{
        optimizeMode = SParticle::MINIMIZE;
    }
    SPSO spso(numberOfParticles, numberOfVariables, lower, upper, vmax, SingleObjWizard::objectiveFunction, lowerWeight, upperWeight, maxIteration, c1, c2, threshold, optimizeMode, stoppingCriteria, psoType);

    spso.optimize();

    spso.printBest();

    double *position = spso.getBestPosition();
    double value = spso.getBestValue();
    bool feasible = spso.getBestFeasible();

    //优化后结果Dialog
    QDialog *dialog = new QDialog;
    dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    QVBoxLayout *vlayout = new QVBoxLayout(dialog);
    QLabel *positionlabel = new QLabel;
    QLabel *valuelabel = new QLabel;
    QLabel *feasiblelabel = new QLabel;
    vlayout->addWidget(positionlabel);
    vlayout->addWidget(valuelabel);
    vlayout->addWidget(feasiblelabel);

    QString positionstr;
    for(int i = 0; i < numberOfVariables; ++i){
        positionstr += inputname[i];
        positionstr += ": ";
        positionstr += QString::number(position[i]);
        positionstr += " ";
    }
    QString valuestr(tr("Value: "));
    valuestr += QString::number(value);
    QString feasiblestr(tr("Feasible: "));
    feasiblestr += feasible ? "true" : "false";

    positionlabel->setText(positionstr);
    valuelabel->setText(valuestr);
    feasiblelabel->setText(feasiblestr);

    dialog->show();

    delete[] vmax;
    delete[] upper;
    delete[] lower;
}

void SingleObjWizard::objectiveFunction(SParticle *Particle)
{
    const double *_position = Particle->getPosition ();
    double _constraits;

    Particle->setValue(100 * pow((_position[1] - pow(_position[0], 2)), 2) + pow((1 - _position[0]), 2));
    _constraits = _position[1] + _position[0] > 1 ? 10000000 * (_position[1] + _position[0] - 1) : 0;
    //_constraits = 0;
    Particle->setConstraits(_constraits);
    Particle->setFeasible(_constraits ? false : true);
    return;
}
