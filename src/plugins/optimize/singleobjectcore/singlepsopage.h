#ifndef SINGLEPSOPAGE_H
#define SINGLEPSOPAGE_H

#include <QWizardPage>
#include <QLineEdit>
#include <QLabel>

class SinglePSOPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit SinglePSOPage(QWizard *parent = nullptr);

    //所有LineEdit
    QLineEdit *mSizeEdit;
    QLineEdit *mTimeEdit;
    QLineEdit *mRateEdit;
    QLineEdit *mWLowerEdit;
    QLineEdit *mWUpperEdit;
    QLineEdit *mC1Edit;
    QLineEdit *mC2Edit;
    QLabel *mWarningLabel;

signals:

public slots:
    void isParamError();

private:

};

#endif // SINGLEPSOPAGE_H
