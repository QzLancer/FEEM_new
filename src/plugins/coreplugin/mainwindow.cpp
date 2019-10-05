#include "mainwindow.h"

#include <QApplication>
#include <QStatusBar>
#include <QMenuBar>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QMdiArea>
#include <QTextEdit>
#include <QHBoxLayout>

#include <QTreeWidget>
#include <QTableWidget>
#include <QTabWidget>

#include "actionmanager/actioncontainer.h"
#include "actionmanager/actioncontainer_p.h"
#include "actionmanager/actionmanager.h"
#include "actionmanager/actionmanager_p.h"
#include "actionmanager/command.h"
#include "ouptput/messagemanager.h"

namespace Core {

MainWindow::MainWindow(QWidget *parent)
    : RibbonWindow(parent)
    , m_coreImpl(new ICore(this))
{
    init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    m_ribbonStyle->setAccentColor(OfficeStyle::AccentColorBlue);

    registerDefaultContainers();
    registerDefaultActions();    

//    setCentralWidget(cad);

    /** Qribbon更新主题 **/
    Qtitan::OfficeStyle* st = (Qtitan::OfficeStyle*)qApp->style();
    Qtitan::OfficeStyle::Theme theme = Qtitan::OfficeStyle::Office2010Silver;
//    setFixedSize(500,500);
    QWidget* w = new QWidget(this);
    setCentralWidget(w);

    st->setTheme(theme);

    updateActionsTheme();
}

/**
 * @brief 创建默认的顶部菜单
 *
 */
void MainWindow::registerDefaultContainers()
{
    /** 创建ribbonbar，这里不用创建，因为已经有了 **/
    auto ribbonbar = new RibbonBarActionContainer(Constants::RIBBONBAR);
    ribbonbar->setRibbonBar(ribbonBar());

    ribbonBar()->setFrameThemeEnabled();//不显示一条白带
    /** 添加一些默认的group用来保存Page类型的container **/
    ribbonbar->appendGroup(Constants::G_HOME);
    ribbonbar->appendGroup(Constants::G_DEFINITION);
    ribbonbar->appendGroup(Constants::G_GEOMETRY);
    ribbonbar->appendGroup(Constants::G_MATERIAL);
    ribbonbar->appendGroup(Constants::G_MESH);
    ribbonbar->appendGroup(Constants::G_SOLVER);
    ribbonbar->appendGroup(Constants::G_RESULT);

    /** 添加不同的page **/
    ActionContainer* page = ActionManager::createRibbonPage(Constants::P_HOME);
    page->ribbonPage()->setTitle(tr("&Home"));
    ribbonbar->addPage(page,Constants::G_HOME);

    page = ActionManager::createRibbonPage(Constants::P_SOLVER);
    page->ribbonPage()->setTitle(tr("&Solve"));
    ribbonbar->addPage(page,Constants::G_SOLVER);

    page = ActionManager::createRibbonPage(Constants::P_DEFINITION);
    page->ribbonPage()->setTitle(tr("&Definitions"));
    ribbonbar->addPage(page,Constants::G_DEFINITION);

    page = ActionManager::createRibbonPage(Constants::P_MATERIAL);
    page->ribbonPage()->setTitle(tr("&Materials"));
    ribbonbar->addPage(page,Constants::G_MATERIAL);

    page = ActionManager::createRibbonPage(Constants::P_MESH);
    page->ribbonPage()->setTitle(tr("&Mesh"));
    ribbonbar->addPage(page,Constants::G_MESH);

    page = ActionManager::createRibbonPage(Constants::P_GEOMETRY);
    page->ribbonPage()->setTitle(tr("&Geometry"));
    ribbonbar->addPage(page,Constants::G_GEOMETRY);

    page = ActionManager::createRibbonPage(Constants::P_RESULT);
    page->ribbonPage()->setTitle(tr("&Results"));
    ribbonbar->addPage(page,Constants::G_RESULT);






}

/**
 * @brief 添加默认的动作
 *
 */
void MainWindow::registerDefaultActions()
{

}

} // namespace Core
