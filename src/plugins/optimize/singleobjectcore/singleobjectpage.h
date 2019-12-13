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
    ~SingleObjectPage() override;
    void initialize();
    void initialize(QStringList inputlist);
    void setPicture(QPixmap pic);

    //set
    void setInputList(QStringList inputlist);
    void appendInputList(const QString inputstr);
    void setOptimizeHintMap(const QMap<QString, QString> optimizeHintMap);
    void appendOptimizeHintMap (QString objective, QString hint);

    //get
    QStringList getInputList();
    QMap<QString, QString> optimizeHintMap() const;
    QStringList getInputName() const;
    QList<QList<double>> getInputValue() const;
    QString getCurrentObject() const;
    QString getCurrentMode() const;

public slots:
    void resizeEvent(QResizeEvent *event) override;
    void slotObjectChange(const QString &text);
    void slotButtonEnable();

private:
    QGroupBox *mGroup1;
    QGroupBox *mGroup2;
    void initializeGroup1();
    void initializeGroup2();
    void refreshTable();

    /**控件**/
    QComboBox *mObjectBox;
    QComboBox *mModeBox;

    InputParamWidget *mInputWidget;

    /**测试用Pixmap**/
    QPixmap mCurrentPic;
    QLabel *mPicLabel;
    QLabel *mTipLabel;

    /**优化目标与注释配对**/
    QMap<QString, QString> mOptimizeHintMap;

    QWizard *mWizard;
};

#endif // SINGLEOBJECTPAGE_H
