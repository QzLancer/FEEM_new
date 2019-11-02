#ifndef SINGLEOBJWIZARD_H
#define SINGLEOBJWIZARD_H
#include "typepage.h"

#include <QWizard>

class SingleObjWizard : public QWizard
{
    Q_OBJECT
public:
    explicit SingleObjWizard(QWizard *parent = nullptr);

signals:

public slots:

private:
    TypePage *page1;
};

#endif // SINGLEOBJWIZARD_H
