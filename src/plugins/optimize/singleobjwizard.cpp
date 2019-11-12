#include "singleobjwizard.h"
#include "singleobjectcore/singleobjectpage.h"
#include "singleobjectcore/singlepsopage.h"

#include <QWizardPage>
#include <QVBoxLayout>
#include <QListWidget>
#include <QDebug>

SingleObjWizard::SingleObjWizard(QWizard *parent)
    : QWizard(parent),
      page1(new TypePage(this)),
      page2(new SingleObjectPage(this)),
      page3(new SinglePSOPage(this))
{
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setFixedSize(900, 900);
    addPage(page1);
    addPage(page2);
    addPage(page3);
    connect(this, &SingleObjWizard::currentIdChanged, this, &SingleObjWizard::slotCurrentIdChange);
}

void SingleObjWizard::slotCurrentIdChange(int id)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << id;
    if(id == 1){
        QPixmap pic = page1->getCurrentPic();
        page2->setPicture(pic);
    }
}
