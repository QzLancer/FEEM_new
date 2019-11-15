#ifndef SINGLEOBJWIZARD_H
#define SINGLEOBJWIZARD_H
#include "typepage.h"
#include "singleobjectcore/singleobjectpage.h"
#include "singleobjectcore/singlepsopage.h"

#include <QWizard>

class SingleObjWizard : public QWizard
{
    Q_OBJECT
public:
    explicit SingleObjWizard(QWidget *parent = nullptr);
    void appendInputList(const QString &input);
    TypePage *page1;
    SingleObjectPage *page2;
    SinglePSOPage *page3;

signals:

public slots:
    void slotCurrentIdChange(int id);
    void slotSolve();

private:
    /**求解器**/
    static void objectiveFunction (SParticle *Particle);
};

#endif // SINGLEOBJWIZARD_H
