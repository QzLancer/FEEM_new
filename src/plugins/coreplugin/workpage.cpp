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

    auto m_DockManager = new ads::CDockManager(m_splitter);
    QLabel* l = new QLabel();
    l->setWordWrap(true);
    l->setAlignment(Qt::AlignCenter);
    l->setText("FEEM");
    l->setStyleSheet("font-size:60px;color:gray");

    // Create a dock widget with the title Label 1 and set the created label
    // as the dock widget content
    ads::CDockWidget* DockWidget = new ads::CDockWidget("Geometry builder");
    DockWidget->setWidget(l);
    // Add the dock widget to the top dock widget area
    m_DockManager->addDockWidget(ads::TopDockWidgetArea, DockWidget);

    /** 先添加中间的几何控件 **/
    QVBoxLayout *m_rightSplitWidgetLayout = new QVBoxLayout;
    m_rightSplitWidgetLayout->setSpacing(0);
    m_rightSplitWidgetLayout->setMargin(0);
    QWidget *rightSplitWidget = new QWidget;
    rightSplitWidget->setLayout(m_rightSplitWidgetLayout);
    auto geoPlaceHolder = new GeometryManagerPlaceHolder;
    m_rightSplitWidgetLayout->insertWidget(0, geoPlaceHolder);

    /** 下面的输出窗口 **/
    QWidget *outputPane = new QWidget;
    auto emptyLayout = new QGridLayout(outputPane);
//    QPalette pe;
//    pe.setColor(QPalette::WindowText, Qt::gray);
    QLabel* l1 = new QLabel(outputPane);
    l1->setText("FEEM");
    l1->setAlignment(Qt::AlignCenter);
    l1->setStyleSheet("font-size:60px;color:gray");
//    l1->setPalette(pe);
    emptyLayout->addWidget(l1);
    outputPane->setLayout(emptyLayout);

    ads::CDockWidget* DockWidget1 = new ads::CDockWidget("Message outputpane");
    DockWidget1->setWidget(outputPane);
    // Add the dock widget to the top dock widget area
    m_DockManager->addDockWidget(ads::BottomDockWidgetArea, DockWidget1);

    QLabel* l2 = new QLabel();
    l2->setWordWrap(true);
    l2->setAlignment(Qt::AlignCenter);
    l2->setText("FEEM");
    l2->setStyleSheet("font-size:60px;color:gray");

    // Create a dock widget with the title Label 1 and set the created label
    // as the dock widget content
    ads::CDockWidget* DockWidget2 = new ads::CDockWidget("Model tree");
    DockWidget2->setWidget(l2);
    // Add the dock widget to the top dock widget area
    m_DockManager->addDockWidget(ads::LeftDockWidgetArea, DockWidget2);

    QLabel* l3 = new QLabel();
    l3->setWordWrap(true);
    l3->setAlignment(Qt::AlignCenter);
    l3->setText("FEEM");
    l3->setStyleSheet("font-size:60px;color:gray");

    // Create a dock widget with the title Label 1 and set the created label
    // as the dock widget content
    ads::CDockWidget* DockWidget3 = new ads::CDockWidget("Material library");
    DockWidget3->setWidget(l3);
    // Add the dock widget to the top dock widget area
    m_DockManager->addDockWidget(ads::RightDockWidgetArea, DockWidget3);
    setWidget(m_splitter);
}

WorkPage::~WorkPage()
{
    delete m_splitter;
}

}//namespace Core
