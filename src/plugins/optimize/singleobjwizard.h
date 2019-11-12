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
    explicit SingleObjWizard(QWizard *parent = nullptr);
    TypePage *page1;
    SingleObjectPage *page2;
    SinglePSOPage *page3;

signals:

public slots:
    void slotCurrentIdChange(int id);

private:
    QVariantMap mMap;
};

#endif // SINGLEOBJWIZARD_H
