#include "plotwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include "postoperation/qcustomplot/qcustomplot.h"

using namespace Postoperation;

PlotWidget::PlotWidget(QWidget *parent)
    : QWidget (parent),
      mCustomPlot(new QCustomPlot(this)),
      mTable(new QTableView(this)),
      mModel(new QStandardItemModel(this)),
      mToolBar(new QToolBar(this)),
      mActionZoomIn(new QAction(mToolBar)),
      mActionZoomOut(new QAction(mToolBar)),
      mActionTranslation(new QAction(mToolBar)),
      mActionTracer(new QAction(mToolBar)),
      mActionReset(new QAction(mToolBar)),
      mMousePressed(false)
{
    //ToolBar配置
    setToolBar();

    //layout
    QHBoxLayout *DataLayout = new QHBoxLayout;
    DataLayout->addWidget(mCustomPlot);
    DataLayout->addWidget(mTable);
    DataLayout->setStretch(0, 2);
    DataLayout->setStretch(1, 1);
    QVBoxLayout *MainLayout = new QVBoxLayout(this);
    MainLayout->addWidget(mToolBar);
    MainLayout->addLayout(DataLayout);

    //CustomPlot设置
    mCustomPlot->legend->setVisible(true);

    //table和Model设置
    mTable->setModel(mModel);
    mTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //connect
    connect(mCustomPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(slotMousePress(QMouseEvent*)));
    connect(mCustomPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(slotMouseMove(QMouseEvent*)));
    connect(mCustomPlot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(slotMouseRelease(QMouseEvent*)));
}

void PlotWidget::slotZoomIn()
{
    qDebug() << Q_FUNC_INFO;
    mCurrentAction = ZOOMIN;
    uncheckAllToolBar();
    mActionZoomIn->setChecked(true);
    mCustomPlot->setSelectionRectMode(srmZoom);
    mCustomPlot->setInteraction(iRangeDrag, false);
}

void PlotWidget::slotZoomOut()
{
    mCurrentAction = ZOOMOUT;
    uncheckAllToolBar();
    mActionZoomOut->setChecked(true);
    mCustomPlot->setSelectionRectMode(srmNone);
    mCustomPlot->setInteraction(iRangeDrag, false);
}

void PlotWidget::slotTranslation()
{
    mCurrentAction = TRANSLATION;
    uncheckAllToolBar();
    mActionTranslation->setChecked(true);
    mCustomPlot->setSelectionRectMode(srmNone);
    mCustomPlot->setInteraction(iRangeDrag, true);
}

void PlotWidget::slotTracer()
{
    mCurrentAction = TRACER;
    uncheckAllToolBar();
    mActionTracer->setChecked(true);
    mCustomPlot->setSelectionRectMode(srmNone);
    mCustomPlot->setInteraction(iRangeDrag, false);
}

void PlotWidget::slotReset()
{
    for(int i = 0; i < mCustomPlot->graphCount(); ++i){
        mCustomPlot->graph(i)->rescaleAxes(true);
    }
    mCustomPlot->replot();
}

void PlotWidget::slotMousePress(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton || !mCustomPlot->viewport().contains(event->pos())) return;
    if(mCurrentAction == TRACER){
        double x = mCustomPlot->xAxis->pixelToCoord(event->pos().x());
        for(int i = 0; i < mTracerList.size(); ++i){
            mTracerList[i]->setGraphKey(x);
            double traceX = mTracerList[i]->position->key();
            double traceY = mTracerList[i]->position->value();
            QString text;
            text = QString::number(traceX) + ", " + QString::number(traceY);
            mTextList[i]->setText(text);
        }
        mCustomPlot->replot();
        mMousePressed = true;
    }
}

void PlotWidget::slotMouseMove(QMouseEvent *event)
{
    if(!mCustomPlot->viewport().contains(event->pos())) return;
    if(mCurrentAction == TRACER & mMousePressed == true){
        double x = mCustomPlot->xAxis->pixelToCoord(event->pos().x());
        for(int i = 0; i < mTracerList.size(); ++i){
            mTracerList[i]->setGraphKey(x);
            double traceX = mTracerList[i]->position->key();
            double traceY = mTracerList[i]->position->value();
            QString text;
            text = QString::number(traceX) + ", " + QString::number(traceY);
            mTextList[i]->setText(text);
        }
        mCustomPlot->replot();
    }
}

void PlotWidget::slotMouseRelease(QMouseEvent *event)
{
    mMousePressed = false;
}

void PlotWidget::addPlot(QVector<double> x, QVector<double> y)
{
    mCustomPlot->addGraph();
    int index = mCustomPlot->graphCount()-1;

    QColor color;
    switch (index) {
    case 0:
        color = Qt::red;
        break;
    case 1:
        color = Qt::blue;
        break;
    case 2:
        color = Qt::black;
        break;
    case 3:
        color = Qt::green;
        break;
    case 4:
        color = Qt::cyan;
        break;
    }
    mCustomPlot->graph(index)->setData(x, y);
    mCustomPlot->graph(index)->setPen(QPen(color));

    //新建tracer
    QCPItemTracer *tracer = new QCPItemTracer(mCustomPlot);
    tracer->setPen(Qt::DashLine);
    tracer->setInterpolating(false);
    tracer->setGraph(mCustomPlot->graph(index));
    mTracerList.push_back(tracer);

    //新建Text
    QCPItemText *itemtext = new QCPItemText(mCustomPlot);
//    itemtext->setLayer("overlay");
    itemtext->position->setParentAnchor(tracer->position);
    itemtext->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);
    itemtext->setPadding(QMargins(5, 5, 5, 5));
    itemtext->setColor(color);
    itemtext->setText("");
    mTextList.push_back(itemtext);

    mCustomPlot->rescaleAxes(true);
    mCustomPlot->replot();

    //新建model中参数
    QList<QStandardItem*> xlist;
    QList<QStandardItem*> ylist;
    for(int i = 0; i < x.size(); ++i){
        xlist.append(new QStandardItem(QString::number(x[i])));
        ylist.append(new QStandardItem(QString::number(y[i])));
    }
    mModel->appendColumn(xlist);
    mModel->appendColumn(ylist);
}

void PlotWidget::setToolBar()
{
    mActionZoomIn->setIcon(QIcon(":/icon/resource/zoomin_32px.png"));
    mActionZoomOut->setIcon(QIcon(":/icon/resource/zoomout_32px.png"));
    mActionTranslation->setIcon(QIcon(":/icon/resource/translation_32px.png"));
    mActionTracer->setIcon(QIcon(":/icon/resource/tracer_32px.png"));
    mActionReset->setIcon(QIcon(":/icon/resource/reset_32px.png"));

    mActionZoomIn->setCheckable(true);
    mActionZoomOut->setCheckable(true);
    mActionTranslation->setCheckable(true);
    mActionTracer->setCheckable(true);

    mToolBar->addAction(mActionZoomIn);
    mToolBar->addAction(mActionZoomOut);
    mToolBar->addAction(mActionTranslation);
    mToolBar->addAction(mActionTracer);
    mToolBar->addAction(mActionReset);

    connect(mActionZoomIn, &QAction::triggered, this, &PlotWidget::slotZoomIn);
    connect(mActionZoomOut, &QAction::triggered, this, &PlotWidget::slotZoomOut);
    connect(mActionTranslation, &QAction::triggered, this, &PlotWidget::slotTranslation);
    connect(mActionTracer, &QAction::triggered, this, &PlotWidget::slotTracer);
    connect(mActionReset, &QAction::triggered, this, &PlotWidget::slotReset);
}

void PlotWidget::uncheckAllToolBar()
{
    mActionZoomIn->setChecked(false);
    mActionZoomOut->setChecked(false);
    mActionTranslation->setChecked(false);
    mActionTracer->setChecked(false);
}
