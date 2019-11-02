#include "singleobjwizard.h"
#include "singleobjectcore/singleobjectpage.h"
#include "singleobjectcore/singlepsopage.h"

#include <QWizardPage>
#include <QVBoxLayout>
#include <QListWidget>
SingleObjWizard::SingleObjWizard(QWizard *parent)
    : QWizard(parent),
      page1(new TypePage)
{
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    QWizardPage *page = new QWizardPage;
    QListWidget *list = new QListWidget;
    list->addItem("item1");
    list->addItem("item2");
    list->addItem("item3");
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->addWidget(new SingleObjectPage);
    page->setTitle(tr("Select the type of relay to optimize"));
    addPage(page1);
    addPage(page);
    addPage(new SinglePSOPage(this));
//    addPage(new SinglePSOPage);
}
