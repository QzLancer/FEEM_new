#include "workpage.h"
#include "constants.h"

#include <coreplugin/geometrymanager/geometrymanager.h>

#include <QtAdvancedDock/DockManager.h>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QSplitter>
#include <QDebug>
#include <QToolButton>
#include <QLabel>
#include <QPainter>

namespace Core {

ads::CDockManager* WorkPage::m_DockManager = nullptr;
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

    /** static的变量似乎不能在初始化列表初始化 **/
    m_DockManager = new ads::CDockManager(m_splitter);
//    m_DockManager->setStyleSheet("");
//    QLabel* l = new QLabel();
//    l->setWordWrap(true);
//    l->setAlignment(Qt::AlignCenter);
//    l->setText("FEEM");
//    l->setStyleSheet("font-size:60px;color:gray");

    // Create a dock widget with the title Label 1 and set the created label
    // as the dock widget content
    ads::CDockWidget* DockWidget = new ads::CDockWidget(tr("Geometry builder"));
//    DockWidget->setWidget(l);
    // Add the dock widget to the top dock widget area
    m_DockManager->addDockWidget(ads::TopDockWidgetArea, DockWidget);

    /** 先添加中间的几何控件 **/
//    QVBoxLayout *m_rightSplitWidgetLayout = new QVBoxLayout;
//    m_rightSplitWidgetLayout->setSpacing(0);
//    m_rightSplitWidgetLayout->setMargin(0);
//    QWidget *rightSplitWidget = new QWidget;
//    rightSplitWidget->setLayout(m_rightSplitWidgetLayout);
//    auto geoPlaceHolder = new GeometryManagerPlaceHolder;
//    m_rightSplitWidgetLayout->insertWidget(0, geoPlaceHolder);

    /** 下面的输出窗口 **/
//    QWidget *outputPane = new QWidget;
//    auto emptyLayout = new QGridLayout(outputPane);
//    QLabel* l1 = new QLabel(outputPane);
//    l1->setText("FEEM");
//    l1->setAlignment(Qt::AlignCenter);
//    l1->setStyleSheet("font-size:60px;color:gray");
//    emptyLayout->addWidget(l1);
//    outputPane->setLayout(emptyLayout);

    setWidget(m_splitter);
}

WorkPage::~WorkPage()
{
    delete m_splitter;
}

/*!
 \brief 返回一个dock的管理器，那么其他人就可以通过这个
 在这个界面当中添加窗口了。

 \return ads::CDockManager
*/
ads::CDockManager *WorkPage::DockManager()
{
    return m_DockManager;
}


}//namespace Core
