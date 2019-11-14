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
#include <geometrymanager/geometrymanager.h>

#include <coreplugin/pf_pagewidget.h>
#include <coreplugin/pagemanager.h>

namespace Core {

MainWindow::MainWindow(QWidget *parent)
    : RibbonWindow(parent)
    , m_coreImpl(new ICore(this))
    , m_pagesStack(new PF_PageWidget(this))
{
    init();
}

MainWindow::~MainWindow()
{

}

IContext *MainWindow::contextObject(QWidget *widget)
{
    return m_contextWidgets.value(widget);
}

void MainWindow::addContextObject(IContext *context)
{
    if (!context)
        return;
    QWidget *widget = context->widget();
    if (m_contextWidgets.contains(widget))
        return;

    m_contextWidgets.insert(widget, context);
}

void MainWindow::removeContextObject(IContext *context)
{
    if (!context)
        return;

    QWidget *widget = context->widget();
    if (!m_contextWidgets.contains(widget))
        return;

    m_contextWidgets.remove(widget);
    if (m_activeContext.removeAll(context) > 0)
        updateContextObject(m_activeContext);
}

void MainWindow::init()
{
    m_ribbonStyle->setAccentColor(OfficeStyle::AccentColorBlue);

    setDockNestingEnabled(true);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);

    m_pageManager = new PageManager(this, m_pagesStack);

    registerDefaultContainers();
    registerDefaultActions();    

    /** 几何管理器 **/
    m_geometryManager = new GeometryManager(this);

    setCentralWidget(m_pagesStack);

    /** Qribbon更新主题 **/
    setOptions(Qtitan::OfficeStyle::Office2007Blue);

    updateActionsTheme();
}

void MainWindow::extensionsInitialized()
{
    PageManager::extensionsInitialized();
}

/**
 * @brief 创建默认的顶部菜单
 *
 */
void MainWindow::registerDefaultContainers()
{
    /** 创建ribbonbar，这里不用创建，因为已经有了 **/
    auto ribbonbar = ActionManager::createRibbonBar(Constants::RIBBONBAR);
    static_cast<RibbonBarActionContainer*>(ribbonbar)->setRibbonBar(ribbonBar());

    ribbonBar()->setFrameThemeEnabled();//不显示一条白带
    /** 添加一些默认的group用来保存Page类型的container **/
    ribbonbar->appendGroup(Constants::G_HOME);
    ribbonbar->appendGroup(Constants::G_DEFINITION);
//    ribbonbar->appendGroup(Constants::G_GEOMETRY);
    ribbonbar->appendGroup(Constants::G_MATERIAL);
    ribbonbar->appendGroup(Constants::G_MESH);
    ribbonbar->appendGroup(Constants::G_SOLVER);
    ribbonbar->appendGroup(Constants::G_RESULT);
    ribbonbar->insertGroup(Constants::G_MATERIAL,Constants::G_GEOMETRY);

    /** 添加不同的page **/
    ActionContainer* page = ActionManager::createRibbonPage(Constants::P_HOME);
    page->ribbonPage()->setTitle(tr("&Home"));
    ribbonbar->addRibbonPage(page,Constants::G_HOME);    

    page = ActionManager::createRibbonPage(Constants::P_SOLVER);
    page->ribbonPage()->setTitle(tr("&Solve"));
    ribbonbar->addRibbonPage(page,Constants::G_SOLVER);

    page = ActionManager::createRibbonPage(Constants::P_DEFINITION);
    page->ribbonPage()->setTitle(tr("&Definitions"));
    ribbonbar->addRibbonPage(page,Constants::G_DEFINITION);

    page = ActionManager::createRibbonPage(Constants::P_MATERIAL);
    page->ribbonPage()->setTitle(tr("&Materials"));
    ribbonbar->addRibbonPage(page,Constants::G_MATERIAL);

    page = ActionManager::createRibbonPage(Constants::P_MESH);
    page->ribbonPage()->setTitle(tr("&Mesh"));
    ribbonbar->addRibbonPage(page,Constants::G_MESH);

    page = ActionManager::createRibbonPage(Constants::P_GEOMETRY);
    page->ribbonPage()->setTitle(tr("&Geometry"));
    ribbonbar->addRibbonPage(page,Constants::G_GEOMETRY);

    page = ActionManager::createRibbonPage(Constants::P_RESULT);
    page->ribbonPage()->setTitle(tr("&Results"));
    ribbonbar->addRibbonPage(page,Constants::G_RESULT);

}

/**
 * @brief 添加默认的动作
 *
 */
void MainWindow::registerDefaultActions()
{

}

void MainWindow::updateContextObject(const QList<IContext *> &context)
{
    emit m_coreImpl->contextAboutToChange(context);
    m_activeContext = context;
    updateContext();/*
    if (debugMainWindow) {
        qDebug() << "new context objects =" << context;
        foreach (IContext *c, context)
            qDebug() << (c ? c->widget() : nullptr) << (c ? c->widget()->metaObject()->className() : nullptr);
    }*/
}

void MainWindow::updateContext()
{
    Context contexts;// = m_highPrioAdditionalContexts;

    foreach (IContext *context, m_activeContext)
        contexts.add(context->context());

//    contexts.add(m_lowPrioAdditionalContexts);

    Context uniquecontexts;
    for (const Id &id : qAsConst(contexts)) {
        if (!uniquecontexts.contains(id))
            uniquecontexts.add(id);
    }

    ActionManager::setContext(uniquecontexts);
    emit m_coreImpl->contextChanged(uniquecontexts);
}

} // namespace Core
