#include "pf_modelwidget.h"

#include "pf_projecttreewidget.h"
#include "pf_projecttree.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

PF_ModelWidget::PF_ModelWidget(QWidget* parent)
    : QWidget (parent)
{
    init();
}

PF_ModelWidget::~PF_ModelWidget()
{

}

void PF_ModelWidget::init()
{
    m_toolbar = new QWidget(this);
    tb_previousNode = new QPushButton(this);
    tb_nextNode = new QPushButton(this);
    tb_moveup = new QPushButton(this);
    tb_movedown = new QPushButton(this);
    tb_collapseAll = new QPushButton(this);
    tb_expandAll = new QPushButton(this);
    tb_show = new QPushButton(this);

    m_modelTreeWidget = new PF_ProjectTreeWidget(this);

    QHBoxLayout* toolbarLayout = new QHBoxLayout(this);
    toolbarLayout->setMargin(0);
    toolbarLayout->setSpacing(1);

    /** previous Node QToolbutton **/
    tb_previousNode->setIcon(QIcon(":/tree/report_previous.png"));
    tb_previousNode->setToolTip(tr("Previous Node"));
    tb_previousNode->setFlat(true);
    tb_previousNode->setAttribute(Qt::WA_TranslucentBackground);

    tb_nextNode->setIcon(QIcon(":/tree/report_next.png"));
    tb_nextNode->setToolTip(tr("Next Node"));
    tb_nextNode->setFlat(true);
    tb_nextNode->setAttribute(Qt::WA_TranslucentBackground);

    tb_moveup->setIcon(QIcon(":/tree/report_up.png"));
    tb_moveup->setToolTip(tr("Move Up"));
    tb_moveup->setFlat(true);
    tb_moveup->setAttribute(Qt::WA_TranslucentBackground);

    tb_movedown->setIcon(QIcon(":/tree/report_down.png"));
    tb_movedown->setToolTip(tr("Move Down"));
    tb_movedown->setFlat(true);
    tb_movedown->setAttribute(Qt::WA_TranslucentBackground);

    tb_show->setIcon(QIcon(":/tree/node_labels.png"));
    tb_show->setToolTip(tr("Show"));
    tb_show->setFlat(true);
    tb_show->setAttribute(Qt::WA_TranslucentBackground);

    tb_collapseAll->setIcon(QIcon(":/tree/hide_tree.png"));
    tb_collapseAll->setToolTip(tr("Collapse All"));
    tb_collapseAll->setFlat(true);
    tb_collapseAll->setAttribute(Qt::WA_TranslucentBackground);
    connect(tb_collapseAll,&QPushButton::clicked,[]()
    {
//        qDebug()<<"Collapse All";
        PF_ProjectTree::instance()->collapseAll();
    });

    tb_expandAll->setIcon(QIcon(":/tree/show_tree.png"));
    tb_expandAll->setToolTip(tr("Expand All"));
    tb_expandAll->setFlat(true);
//    tb_expandAll->setAttribute(Qt::WA_TranslucentBackground);
    connect(tb_expandAll,&QPushButton::clicked,[]()
    {
//        qDebug()<<"Expand All";
        PF_ProjectTree::instance()->expandAll();
    });

    toolbarLayout->addWidget(tb_previousNode);
    toolbarLayout->addWidget(tb_nextNode);
    toolbarLayout->addWidget(tb_moveup);
    toolbarLayout->addWidget(tb_movedown);
    toolbarLayout->addWidget(tb_show);
    toolbarLayout->addWidget(tb_collapseAll);
    toolbarLayout->addWidget(tb_expandAll);
    toolbarLayout->addStretch(1);

    m_toolbar->setLayout(toolbarLayout);

    QVBoxLayout* modellayout = new QVBoxLayout(this);
    modellayout->setMargin(5);
    modellayout->setSpacing(5);
    modellayout->addWidget(m_toolbar);
    modellayout->addWidget(m_modelTreeWidget);

    setLayout(modellayout);
}
