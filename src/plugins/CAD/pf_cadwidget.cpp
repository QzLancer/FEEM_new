#include "pf_cadwidget.h"

#include "pf_graphicview.h"

#include <stdio.h>

#include <QToolBar>
#include <QToolButton>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QStatusBar>

QStatusBar* PF_CADWidget::statusbar = nullptr;

PF_CADWidget::PF_CADWidget(PF_Document* doc, QWidget *parent)
    : QWidget(parent)
{
    if(doc == nullptr){

    }else{
        document = doc;
    }
    init();
    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
}

PF_CADWidget::~PF_CADWidget()
{

}

void PF_CADWidget::init()
{
    toolBar = new QWidget(this);
    QPalette p;
    p.setBrush(toolBar->backgroundRole(),QBrush(QColor(251,253,253)));
    toolBar->setPalette(p);
//    toolBar->setBackgroundRole(QPalette::Button);
    toolBar->setAutoFillBackground(true);
//    toolBar->setIconSize(QSize(24,24));
    toolBar->setObjectName("ToolBar");

    QString str;
    zoom = new QToolButton(this);
    zoom->setIcon(QIcon(":/main/zoombox.png"));
    zoom->setCheckable(true);
    zoom->setToolTip(tr("Zoom box"));
    zoom->setAttribute(Qt::WA_TranslucentBackground);
    connect(zoom,&QToolButton::clicked,[this]()
    {
        qDebug()<<"Zoom";
        this->zoom->setChecked(zoom->isChecked());
    });
    str.append("QPushButton{background-color:rgba(0,0,0,0);}");
    zoom->setStyleSheet(str);

    zoomextents = new QToolButton(this);
    zoomextents->setIcon(QIcon(":/main/zoomextents.png"));
    zoomextents->setToolTip(tr("Zoom Extents"));
//    zoomextents->setFlat(true);
//    zoomextents->setAttribute(Qt::WA_TranslucentBackground);
//    zoomextents->setCheckable(true);
    connect(zoomextents,&QToolButton::clicked,[this]()
    {
//        qDebug()<<"ZoomExtents";
        this->view->zoomAuto(true,true);
        //this->zoomextents->setChecked(zoomextents->isChecked());
    });
    zoomin = new QToolButton(this);
    zoomin->setIcon(QIcon(":/main/zoomin.png"));
    zoomin->setToolTip(tr("Zoom In"));
    zoomin->setAttribute(Qt::WA_TranslucentBackground);
//    zoomin->setCheckable(true);
    connect(zoomin,&QToolButton::clicked,[this]()
    {
//        qDebug()<<"Zoom In";
        this->view->zoomIn(1.2);
        //this->zoomin->setChecked(zoomin->isChecked());
    });
    zoomout = new QToolButton(this);
    zoomout->setIcon(QIcon(":/main/zoomout.png"));
    zoomout->setToolTip(tr("Zoom Out"));
    zoomout->setAttribute(Qt::WA_TranslucentBackground);
//    zoomout->setCheckable(true);
    connect(zoomout,&QToolButton::clicked,[this]()
    {
//        qDebug()<<"Zoom Out";
        this->view->zoomOut(1.2);
        //this->zoomout->setChecked(zoomout->isChecked());
    });
    zoomselected = new QToolButton(this);
    zoomselected->setIcon(QIcon(":/main/zoomselected.png"));
    zoomselected->setToolTip(tr("Zoom to Selected"));
    zoomselected->setCheckable(true);
    zoomselected->setAttribute(Qt::WA_TranslucentBackground);
    connect(zoomselected,&QToolButton::clicked,[this]()
    {
        qDebug()<<"Zoom Selected";
        this->zoomselected->setChecked(zoomselected->isChecked());
    });
    QHBoxLayout* toolbarlayout = new QHBoxLayout(this);
    toolbarlayout->setMargin(0);
    toolbarlayout->setSpacing(1);
    toolbarlayout->addWidget(zoomin);
    toolbarlayout->addWidget(zoomout);
    toolbarlayout->addWidget(zoom);
//    toolbarlayout->addSeparator();
    toolbarlayout->addWidget(zoomselected);
    toolbarlayout->addWidget(zoomextents);
    toolbarlayout->addStretch(1);

    toolBar->setLayout(toolbarlayout);
    toolBar->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    view = new PF_GraphicView(document,this);

    QVBoxLayout* cadlayout = new QVBoxLayout(this);
    cadlayout->setMargin(5);
    cadlayout->setSpacing(5);
    /** If the stretch factor is 0 and nothing else
     * in the QBoxLayout has a stretch factor greater
     *  than zero, the space is distributed according
     * to the QWidget:sizePolicy() of each widget
     *  that's involved. **/
    cadlayout->addWidget(toolBar,0);
    cadlayout->addWidget(view,1);

    statusbar = new QStatusBar(this);
    statusbar->setStyleSheet("QStatusBar::item{border: 20 px}");
    cadlayout->addWidget(statusbar,0);

    setLayout(cadlayout);
}

PF_GraphicView* PF_CADWidget::getGraphicView()
{
    return view ? view : nullptr;
}

PF_Document* PF_CADWidget::getDocument()
{
    return document;
}

/*!
 \brief 将当前的绘图导出为gmsh的geo文件

*/
void PF_CADWidget::exportGmshGeo()
{
    FILE* fp = NULL;

}

void PF_CADWidget::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
