#ifndef MULTIOBJECTPAGE_H
#define MULTIOBJECTPAGE_H
#include "inputparamwidget.h"
#include "objectwidget.h"

#include <QWizardPage>
#include <QGroupBox>

class MultiObjectPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit MultiObjectPage(QWizard *parent = nullptr);

    //set
    void setInputList(const QStringList &inputList);
    void appendInputList(const QString &input) const;
    void setObjectList(const QStringList &objectList);
    void appendObjectList(const QString &object);
    void setPicture(const QPixmap pic);
    void setOptimizeHintMap(const QMap<QString, QString> &optimizeHintMap);
    void appendOptimizeHintMap(const QString &objective, const QString hint);

    //get
    QStringList getInputList() const;
    QList<QList<double>> getInputValue() const;
    QStringList getObjectList() const;
    QStringList getInputName() const;
    QMap<QString, QString> getObjectModeMap() const;
    QMap<QString, QString> getOptimizeHintMap() const;

public slots:
    void resizeEvent(QResizeEvent *event) override;
    void slotObjectChange(const QString &text);
    void slotButtonEnable();

private:
    void initializeGroup1();
    void initializeGroup2();

    QGroupBox *mGroup1;
    QGroupBox *mGroup2;

    InputParamWidget *mInputWidget;
    ObjectWidget *mObjectWidget;

    /**Pixmap以及Tip**/
    QPixmap mCurrentPic;
    QLabel *mPicLabel;
    QLabel *mTipLabel;

    /**优化目标与注释配对**/
    QMap<QString, QString> mOptimizeHintMap;

    QWizard *mWizard;
};

#endif // MULTIOBJECTPAGE_H
