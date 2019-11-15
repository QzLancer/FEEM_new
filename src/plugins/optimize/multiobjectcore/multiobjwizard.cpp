#include "multiobjwizard.h"

#include <QDebug>
#include <postoperation/plot/plotwidget.h>
MultiObjWizard::MultiObjWizard(QWidget *parent)
    : QWizard(parent),
      page1(new TypePage(this)),
      page2(new MultiObjectPage(this)),
      page3(new MultiPSOPage(this))
{
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setFixedSize(1200, 700);
    addPage(page1);
    addPage(page2);
    addPage(page3);
    connect(this, &MultiObjWizard::currentIdChanged, this, &MultiObjWizard::slotCurrentIdChange);
    connect(this, &MultiObjWizard::accepted, this, &MultiObjWizard::slotSolve);
}

void MultiObjWizard::appendInputList(const QString &input)
{
    page2->appendInputList(input);
}

void MultiObjWizard::slotCurrentIdChange(int id)
{
    qDebug() << Q_FUNC_INFO << id;
    if(id == 1){
        QPixmap pic = page1->getCurrentPic();
        page2->setPicture(pic);
        page2->slotButtonEnable();
    }
}

void MultiObjWizard::slotSolve()
{
    //optimize mode
    QStringList objectname;
    QStringList modename;
    QStringList inputname;
    QMap<QString, QString> objectmodemap = page2->getObjectModeMap();
    for(auto iter = objectmodemap.begin(); iter != objectmodemap.end(); ++iter){
        qDebug() << iter.key() << iter.value();
        objectname.append(iter.key());
        modename.append(iter.value());
    }
    inputname = page2->getInputName();
    //将input parameter转换成可以传递的形式
    QList<QList<double>> inputvalue = page2->getInputValue();
    double *lower = new double[static_cast<unsigned long long>(inputvalue.size())];
    double *upper = new double[static_cast<unsigned long long>(inputvalue.size())];
    double *vmax = new double[static_cast<unsigned long long>(inputvalue.size())]; //粒子最大速度
    for(int i = 0; i < inputvalue.size(); ++i){
        lower[i] = inputvalue[i][0];
        upper[i] = inputvalue[i][1];
        vmax[i] = 0.5;
    }
    //读取各个lineedit中的数据，目前变异概率不使用
    int numberOfParticles = page3->mSizeEdit->text().toInt();
    int numberOfExtraParticles = page3->mEliteEdit->text().toInt();
    int numberOfVariables = inputvalue.size();
    int numberOfObjectives = modename.size();
    int maxIteration = page3->mTimeEdit->text().toInt();
    double lowerWeight = page3->mWLowerEdit->text().toDouble();
    double upperWeight = page3->mWUpperEdit->text().toDouble();
    double c1 = page3->mC1Edit->text().toDouble();
    double c2 = page3->mC2Edit->text().toDouble();
    QString stoppingCriteria = "none";
    QString psoType = "Classic";
    double vari = 0.05;

    //观察输入参数
    qDebug() << "lower: " << lower[0] << lower[1];
    qDebug() << "upper: " << upper[0] << upper[1];
    qDebug() << "vmax: " << vmax[0] << vmax[1];
    qDebug() << "numberOfParticles: " << numberOfParticles;
    qDebug() << "numberOfExtraParticles: " << numberOfExtraParticles;
    qDebug() << "numberOfVariables: " << numberOfVariables;
    qDebug() << "numberOfobjectives: " << numberOfObjectives;
    qDebug() << "maxIteration: " << maxIteration;
    qDebug() << "lowerWeight: " << lowerWeight;
    qDebug() << "upperWeight: " << upperWeight;
    qDebug() << "c1: " << c1;
    qDebug() << "c2: " << c2;

    PSO pso(numberOfParticles, numberOfVariables, numberOfObjectives, numberOfExtraParticles, lower, upper, vmax, MultiObjWizard::objectiveFunction, lowerWeight, upperWeight, maxIteration, c1, c2, vari, modename, stoppingCriteria, psoType);
    pso.optimize();
    pso.printBest();

    //绘图窗口输出,it is not necessary, as not all results are 2D
    QVector<QVector<double>> position = pso.getBestPosition();
    QVector<QVector<double>> value = pso.getBestValue();

    PlotWidget *pw = new PlotWidget;
    pw->addScatter(position[0], position[1], tr("Input"));
    pw->addScatter(value[0], value[1], tr("Optimization"));
    for(int i = 0; i < inputname.size(); ++i){
        pw->addTableColumn(position[i], inputname[i]);
    }
    for(int i = 0; i < objectname.size(); ++i){
        pw->addTableColumn(value[i], objectname[i]);
    }
    pw->show();

}

void MultiObjWizard::objectiveFunction(Particle *Particle)
{
    const double *_position = Particle->getPosition();
    int numberOfObjectives = Particle->getNumberOfObjective();
    double *Objective;
    Objective = new double [numberOfObjectives];
    int _constraits;

    Objective[0] = _position[0] * _position[0] + _position[1] * _position[1];
    Objective[1] = (1 - _position[0]) * (1 - _position[0]) + (1 - _position[1]) * (1 - _position[1]);

    Particle->setValue(Objective);
    _constraits = 0;
    Particle->setConstraits(_constraits);
    Particle->setFeasible(_constraits ? false : true);
    delete[] Objective;
    return;
}

