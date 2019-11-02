#ifndef SINGLEOBJECTPAGE_H
#define SINGLEOBJECTPAGE_H
#include <QDialog>
#include <QGroupBox>
#include <QString>
#include <QComboBox>
#include <QStandardItemModel>
#include <QList>
#include <QItemSelectionModel>
#include <QLabel>
#include "singleobjectcore/spso.h"
#include "inputparamwidget.h"

class SingleObjectPage : public QDialog
{
    Q_OBJECT

public:
    SingleObjectPage(QWidget *parent = nullptr);
    ~SingleObjectPage();
    void initialize();
    void initialize(QStringList inputlist, QStringList targetlist);

    //set
    void setInputList(QStringList inputlist);
    void appendInputList(const QString inputstr);
    void setTargetList(QStringList targetlist);
    void appendTargetList(const QString targetstr);

    //get
    QStringList InputList();
    QStringList TargetList();

public slots:

private:
    QGroupBox *mGroup1;
    QGroupBox *mGroup2;
    void initializeGroup1();
    void initializeGroup2();
    void refreshTable();

    //Combobox中的参数
    QStringList mTargetList;
    QStringList mInputList;

    //控件
    QComboBox *mTargetBox;
    QComboBox *mModeBox;

    InputParamWidget *mInputWidget;
    QStringList mInputName;
    //求解器
    static void objectiveFunction (SParticle *Particle);
};

#endif // SINGLEOBJECTPAGE_H
