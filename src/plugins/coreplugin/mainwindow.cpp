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

    ribbonBar()->setFrameThemeEnabled();//不显示一条白带

//    setCentralWidget(cad);

    /** Qribbon更新主题 **/
    Qtitan::OfficeStyle* st = (Qtitan::OfficeStyle*)qApp->style();
    Qtitan::OfficeStyle::Theme theme = Qtitan::OfficeStyle::Office2010Silver;

    QWidget* w = new QWidget(this);
    setCentralWidget(w);

    st->setTheme(theme);

    updateActionsTheme();
}

/**
 * @brief
 *
 */
void MainWindow::registerDefaultContainers()
{

}

/**
 * @brief
 *
 */
void MainWindow::registerDefaultActions()
{

}
