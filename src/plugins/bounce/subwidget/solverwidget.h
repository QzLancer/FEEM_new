#ifndef SOLVERWIDGET_H
#define SOLVERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTableWidget>
#include <QComboBox>
#include <QVBoxLayout>

class SolverWidget : public QWidget
{
    Q_OBJECT
public:
    enum Solver{
        ODE4 = 0,
    };

    enum StepType{
        FIXEDSTEP = 0,
    };

    explicit SolverWidget(QWidget *parent = nullptr);
    QLineEdit *mStartTimeEdit;
    QLineEdit *mStopTimeEdit;
    QComboBox *mSolverBox;
    QComboBox *mStepTypeBox;
    QLineEdit *mFixedStepSizeEdit;
signals:

public slots:

private:
    void addSimulationTab();
    void addSolverOptionsTab();
    QTabWidget *mTabWidget;
    QWidget *mStepTypeWidget;
    Solver mSolver;
    StepType mStepType;
};

#endif // SOLVERWIDGET_H
