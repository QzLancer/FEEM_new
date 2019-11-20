#include "solverwidget.h"

#include <QLabel>
#include <QGroupBox>

SolverWidget::SolverWidget(QWidget *parent)
    : QWidget(parent),
      mTabWidget(new QTabWidget(this)),
      mSolver(ODE4),
      mStepType(FIXEDSTEP)
{
    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->addWidget(mTabWidget);

    addSimulationTab();
    addSolverOptionsTab();
}

void SolverWidget::addSimulationTab()
{
    QWidget *simulationtab = new QWidget(this);

    QLabel *starttimeelabel = new QLabel(tr("Start Time(s)"), simulationtab);
    mStartTimeEdit = new QLineEdit(simulationtab);
    QLabel *stoptimelabel = new QLabel(tr("Stop Time(s)"), simulationtab);
    mStopTimeEdit = new QLineEdit(simulationtab);

    QVBoxLayout *vlayout = new QVBoxLayout(simulationtab);
    vlayout->addWidget(starttimeelabel);
    vlayout->addWidget(mStartTimeEdit);
    vlayout->addWidget(stoptimelabel);
    vlayout->addWidget(mStopTimeEdit);
    vlayout->addStretch();

    mTabWidget->addTab(simulationtab, tr("Simulation Time"));
}

void SolverWidget::addSolverOptionsTab()
{
    QWidget *solveroptionstab = new QWidget(this);

    /**求解器**/
    QGroupBox *solverbox = new QGroupBox(tr("Solver"), solveroptionstab);
    mSolverBox = new QComboBox(solverbox);
    mSolverBox->addItem(tr("ode4(Runge-Kutta)"));
    QVBoxLayout *solverlayout = new QVBoxLayout(solverbox);
    solverlayout->addWidget(mSolverBox);

    /**步长类型**/
    QGroupBox *steptypebox = new QGroupBox(tr("Step Type"), solveroptionstab);
    mStepTypeBox = new QComboBox(steptypebox);
    mStepTypeBox->addItem(tr("Fixed-Step"));
    /**StepTypeWidget设置**/
    mStepTypeWidget = new QWidget(steptypebox);
    mFixedStepSizeEdit = new QLineEdit(mStepTypeWidget);
    QVBoxLayout *steptypewidgetlayout = new QVBoxLayout(mStepTypeWidget);
    steptypewidgetlayout->setMargin(0);
    steptypewidgetlayout->addWidget(new QLabel(tr("Fixed-Step Size"), mStepTypeWidget));
    steptypewidgetlayout->addWidget(mFixedStepSizeEdit);
    /**steptypeboxlayout设置**/
    QVBoxLayout *steptypeboxlayout = new QVBoxLayout(steptypebox);
    steptypeboxlayout->addWidget(mStepTypeBox);
    steptypeboxlayout->addWidget(mStepTypeWidget);

    /**mainLayout**/
    mTabWidget->addTab(solveroptionstab, tr("Solver Options"));
    QVBoxLayout *mainlayout = new QVBoxLayout(solveroptionstab);
    mainlayout->addWidget(solverbox);
    mainlayout->addWidget(steptypebox);
    mainlayout->addStretch();
}
