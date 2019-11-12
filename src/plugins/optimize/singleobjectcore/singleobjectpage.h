#ifndef SINGLEOBJECTPAGE_H
#define SINGLEOBJECTPAGE_H
#include "singleobjectcore/spso.h"
#include "inputparamwidget.h"

#include <QDialog>
#include <QGroupBox>
#include <QString>
#include <QComboBox>
#include <QStandardItemModel>
#include <QList>
#include <QItemSelectionModel>
#include <QLabel>
#include <QWizardPage>

//class SingleObjWizard;

class SingleObjectPage : public QWizardPage
{
    Q_OBJECT

public:
    SingleObjectPage(QWizard *parent = nullptr);
    ~SingleObjectPage();
    void initialize();
    void initialize(QStringList inputlist, QStringList targetlist);
    void setPicture(QPixmap pic);

    //set
    void setInputList(QStringList inputlist);
    void appendInputList(const QString inputstr);
    void setTargetList(QStringList targetlist);
    void appendTargetList(const QString targetstr);

    //get
    QStringList InputList();
    QStringList TargetList();

public slots:
    void resizeEvent(QResizeEvent *event) override;

private:
    QGroupBox *mGroup1;
    QGroupBox *mGroup2;
    void initializeGroup1();
    void initializeGroup2();
    void refreshTable();

    /**Combobox中的参数**/
    QStringList mTargetList;
    QStringList mInputList;

    /**控件**/
    QComboBox *mTargetBox;
    QComboBox *mModeBox;

    InputParamWidget *mInputWidget;
    QStringList mInputName;

    /**父窗口**/
//    SingleObjWizard *mWizard;

    /**求解器**/
    static void objectiveFunction (SParticle *Particle);

    /**测试用Pixmap**/
    QPixmap mCurrentPic;
    QLabel *mPicLabel;
};

#endif // SINGLEOBJECTPAGE_H
