#ifndef MULTIOBJWIZARD_H
#define MULTIOBJWIZARD_H
#include "typepage.h"
#include "multiobjectpage.h"
#include "multipsopage.h"
#include "pso.h"

#include <QWizard>

class MultiObjWizard : public QWizard
{
    Q_OBJECT
public:
    explicit MultiObjWizard(QWidget *parent = nullptr);
    void appendInputList(const QString &input);
    TypePage *page1;
    MultiObjectPage *page2;
    MultiPSOPage *page3;
signals:

public slots:
    void slotCurrentIdChange(int id);
    void slotSolve();

private:
    /**求解器**/
    static void objectiveFunction (Particle *Particle);
};

#endif // MULTIOBJWIZARD_H
