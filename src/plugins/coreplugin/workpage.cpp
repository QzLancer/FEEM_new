#include "workpage.h"
#include "constants.h"

#include <coreplugin/geometrymanager/geometrymanager.h>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QSplitter>
#include <QDebug>
#include <QToolButton>
#include <QLabel>
#include <QDockWidget>

namespace Core {

/**
 * @brief 正常使用时的页面布局，包括左侧的项目树，中间的几何显示，下面的
 * 信息输出，还有右面的材料库等，只要就是采用QSplitter控件来进行管理。
 *
 */
WorkPage::WorkPage()
    :m_splitter(new QSplitter)
{
    setPriority(Constants::P_PAGE_WORK);
    setId(Constants::PAGE_WORK);

    /** 先添加中间的几何控件 **/
    QVBoxLayout *m_rightSplitWidgetLayout = new QVBoxLayout;
    m_rightSplitWidgetLayout->setSpacing(0);
    m_rightSplitWidgetLayout->setMargin(0);
    QWidget *rightSplitWidget = new QWidget;
    rightSplitWidget->setLayout(m_rightSplitWidgetLayout);
    auto geoPlaceHolder = new GeometryManagerPlaceHolder;
    m_rightSplitWidgetLayout->insertWidget(0, geoPlaceHolder);

    /** 下面的输出窗口 **/
    auto splitter = new QSplitter;
    splitter->setHandleWidth(1);
    splitter->setOrientation(Qt::Vertical);
    splitter->insertWidget(0, rightSplitWidget);
    QWidget *outputPane = new QWidget;
    auto emptyLayout = new QGridLayout(outputPane);
//    QPalette pe;
//    pe.setColor(QPalette::WindowText, Qt::gray);
    QLabel* l1 = new QLabel(outputPane);
    l1->setText("FEEM");
    l1->setStyleSheet("font-size:60px;color:gray");
//    l1->setPalette(pe);
    emptyLayout->addWidget(l1);
    outputPane->setLayout(emptyLayout);
    splitter->insertWidget(1, outputPane);
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 0);

    m_splitter->setHandleWidth(1);

    /** 添加其他的布局，左侧的项目树，右侧的材料树 **/
    m_splitter->insertWidget(0,new QWidget);
    m_splitter->insertWidget(1,splitter);
    m_splitter->insertWidget(2,new QWidget);
    m_splitter->setStretchFactor(0, 0);
    m_splitter->setStretchFactor(1, 1);
    m_splitter->setStretchFactor(2, 0);
    setWidget(m_splitter);
}

WorkPage::~WorkPage()
{
    delete m_splitter;
}

}//namespace Core
