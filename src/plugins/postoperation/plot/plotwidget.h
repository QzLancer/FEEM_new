#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include "../postoperation_global.h"

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QToolBar>

namespace Postoperation{
    class QCustomPlot;
    class QCPItemTracer;
    class QCPItemText;
    class QCPGraph;
}

class FEEM_POSTOPERATION_EXPORT PlotWidget : public QWidget
{
    Q_OBJECT
public:
    PlotWidget(QWidget *parent = nullptr);
    void addPlot(QVector<double> x, QVector<double> y);
    void addPlot(QVector<double> x, QVector<double> y, QString graphname);
    void addScatter(QVector<double> x, QVector<double> y);
    void addScatter(QVector<double> x, QVector<double> y, QString graphname);
    void addTableColumn(QVector<double> data);
    void addTableColumn(QVector<double> data, QString name);
    void setGraphName(int index, QString name);
    void setTableColumnTitle(int index, QString title);
    Postoperation::QCustomPlot *mCustomPlot;
    QTableView *mTable;
    enum Action{
        ZOOMIN,
        ZOOMOUT,
        TRANSLATION,
        TRACER,
    };

public slots:
    void slotZoomIn();
    void slotZoomOut();
    void slotTranslation();
    void slotTracer();
    void slotReset();
    void slotMousePress(QMouseEvent *event);
    void slotMouseMove(QMouseEvent *event);
    void slotMouseRelease(QMouseEvent *event);

private:
    void setToolBar();
    void uncheckAllToolBar();

    QStandardItemModel *mModel;
    QList<Postoperation::QCPItemTracer*> mTracerList;
    QList<Postoperation::QCPItemText*> mTextList;
    QToolBar *mToolBar;
    QAction *mActionZoomIn;
    QAction *mActionZoomOut;
    QAction *mActionTranslation;
    QAction *mActionTracer;
    QAction *mActionReset;
    Action mCurrentAction;
    bool mMousePressed;
};

#endif // PLOTWIDGET_H
