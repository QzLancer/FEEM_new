#ifndef MULTIPSOPAGE_H
#define MULTIPSOPAGE_H

#include <QWizardPage>
#include <QLineEdit>
#include <QLabel>

class MultiPSOPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit MultiPSOPage(QWizard *parent = nullptr);

    /**所有LineEdit**/
    QLineEdit *mSizeEdit;
    QLineEdit *mTimeEdit;
    QLineEdit *mEliteEdit;
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
    QWizard *mWizard;
};

#endif // MULTIPSOPAGE_H
