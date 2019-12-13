#ifndef BOUNCEDIALOG_H
#define BOUNCEDIALOG_H

#include "bouncestack.h"
#include "subwidget/inputwidget.h"
#include "subwidget/paramwidget.h"
#include "subwidget/solverwidget.h"

#include <QDialog>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPushButton>

class BounceDialog : public QDialog
{
    Q_OBJECT

public:
    BounceDialog(QWidget *parent = nullptr);
    ~BounceDialog();
    QListWidget *mListWidget;
    QStackedWidget *mStackedWidget;

public slots:
    void slotRun();

private:

    QHBoxLayout *mHBoxLayout;
    QVBoxLayout *mVBoxLayout;
    QHBoxLayout *mButtonLayout;
    QPushButton *mRunButton;
    QPushButton *mCancelButton;

    /**动态特性输入窗口**/
    InputWidget *mInputWidget;
    /**参数设置窗口**/
    ParamWidget *mParamWidget;
    /**求解器窗口**/
    SolverWidget *mSolverWidget;
};

#endif // BOUNCEDIALOG_H
