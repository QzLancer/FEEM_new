#include "pagemanager.h"
#include "pf_pagewidget.h"

#include "mainwindow.h"

#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/ipage.h>

#include <QVector>
#include <QDebug>

namespace Core {

/*!
 \brief 保存真实的数据，主要是提供page和主窗口之间
 的接口。

*/
struct PageManagerPrivate
{
    void appendPage(IPage *page);
    void enabledStateChanged(IPage *page);
    void activatePageHelper(Id id);
    void extensionsInitializedHelper();

    MainWindow *m_mainWindow;/** 主窗口 **/
    PF_PageWidget *m_pagesStack;/** stack控件，所有的页面 **/
    QVector<IPage*> m_pages;/** 已有的Page **/
    QVector<Command*> m_pagesCommands;
    Context m_addedContexts;
    int m_oldCurrent;

    bool m_startingUp = true;
    Id m_pendingFirstActivePage; // Valid before extentionsInitialized.
};


static PageManagerPrivate *d;
static PageManager* m_instance = nullptr;

static int indexOf(Id id)
{
    for (int i = 0; i < d->m_pages.count(); ++i) {
        if (d->m_pages.at(i)->id() == id)
            return i;
    }
    qDebug() << "Warning, no such page:" << id.toString();
    return -1;
}
/*!
 \brief 用来管理不同的页面，也就是IPage创建的实例。
 管理整个的页面之间的切换。

 \param mainWindow
*/
PageManager::PageManager(MainWindow *mainWindow, PF_PageWidget *pageStack)
{
    m_instance = this;

    /** 初始化私有变量 **/
    d = new PageManagerPrivate();
    d->m_mainWindow = mainWindow;
    d->m_pagesStack = pageStack;
    d->m_oldCurrent = -1;

    connect(d->m_pagesStack, &PF_PageWidget::currentAboutToShow,
            this, &PageManager::currentIndexAboutToChange);
    connect(d->m_pagesStack, &PF_PageWidget::currentChanged,
            this, &PageManager::currentIndexChanged);
}

PageManager::~PageManager()
{
    delete d;
    d = nullptr;
    m_instance = nullptr;
}

/*!
 \brief 需要收集所有的Page，在extension阶段初始化

*/
void PageManager::extensionsInitialized()
{
    d->extensionsInitializedHelper();
}

/*!
 \brief 这里的添加主要是供构造函数使用，之后会
 进行相应的处理。见 extensionsInitializedHelper

 \param page
*/
void PageManager::addPage(IPage *page)
{
    if(!d->m_startingUp) return;
    d->m_pages.append(page);
}

/*!
 \brief 此时可能在布局当中已经添加了控件，所以要同时删除。

 \param page
*/
void PageManager::removePage(IPage *page)
{
    const int index = d->m_pages.indexOf(page);
    d->m_pages.remove(index);
    d->m_pagesStack->removePage(index);

//    d->m_mainWindow->removeContextObject(page);
}

void PageManager::currentIndexAboutToChange(int index)
{
    if (index >= 0) {
        IPage *page = d->m_pages.at(index);
        if (page)
            emit currentPageAboutToChange(page->id());
    }
}

void PageManager::currentIndexChanged(int index)
{
    // Tab index changes to -1 when there is no tab left.
    if (index < 0)
        return;

    IPage *page = d->m_pages.at(index);
    if (!page)
        return;

    d->m_addedContexts = page->context();

    IPage *oldPage = nullptr;
    if (d->m_oldCurrent >= 0)
        oldPage = d->m_pages.at(d->m_oldCurrent);
    d->m_oldCurrent = index;
    emit currentPageChanged(page->id(), oldPage ? oldPage->id() : Id());
}

PageManager *PageManager::instance()
{
    return m_instance;
}

IPage *PageManager::currentPage()
{
    const int currentIndex = d->m_pagesStack->currentIndex();
    return currentIndex < 0 ? nullptr : d->m_pages.at(currentIndex);
}

Id PageManager::currentPageId()
{
    int currentIndex = d->m_pagesStack->currentIndex();
    if (currentIndex < 0)
        return Id();
    return d->m_pages.at(currentIndex)->id();
}

static IPage *findPage(Id id)
{
    const int index = indexOf(id);
    if (index >= 0)
        return d->m_pages.at(index);
    return nullptr;
}

void PageManager::activatePage(Id id)
{
    d->activatePageHelper(id);
}

void PageManager::setFocusToCurrentPage()
{
    IPage *page = findPage(currentPageId());
    if(!page) return;
    QWidget *widget = page->widget();
    if (widget) {
        QWidget *focusWidget = widget->focusWidget();
        if (!focusWidget)
            focusWidget = widget;
        focusWidget->setFocus();
    }
}

/*!
 \brief 将Page列表当中的控件添加到布局当中。

 \param page
*/
void PageManagerPrivate::appendPage(IPage *page)
{
    const int index = m_pagesCommands.count();
//    m_mainWindow->addContextObject(page);

    m_pagesStack->insertPage(index, page->widget(), page->displayName());
    m_pagesStack->setPageEnabled(index, page->isEnabled());

    // Register mode shortcut
    const Id actionId = page->id().withPrefix("FEEM.Page.");
    QAction *action = new QAction(PageManager::tr("Switch to <b>%1</b> page").arg(page->displayName()), m_instance);
    Command *cmd = ActionManager::registerAction(action, actionId);
    cmd->setDefaultKeySequence(QKeySequence(QString("Ctrl+%1").arg(index + 1)));
    m_pagesCommands.append(cmd);
}

void PageManagerPrivate::enabledStateChanged(IPage *page)
{
    int index = d->m_pages.indexOf(page);
    if(index >= 0){}else return;
    d->m_pagesStack->setPageEnabled(index, page->isEnabled());

    // Make sure we leave any disabled mode to prevent possible crashes:
    if (page->id() == PageManager::currentPageId() && !page->isEnabled()) {
        // This assumes that there is always at least one enabled mode.
        for (int i = 0; i < d->m_pages.count(); ++i) {
            if (d->m_pages.at(i) != page &&
                d->m_pages.at(i)->isEnabled()) {
                PageManager::activatePage(d->m_pages.at(i)->id());
                break;
            }
        }
    }
}

void PageManagerPrivate::activatePageHelper(Id id)
{
    if (m_startingUp) {
        m_pendingFirstActivePage = id;
    } else {
        const int currentIndex = m_pagesStack->currentIndex();
        const int newIndex = indexOf(id);
        if (newIndex != currentIndex && newIndex >= 0)
            m_pagesStack->setCurrentIndex(newIndex);
    }
}

/*!
 \brief 真正处理控件添加的部分。

*/
void PageManagerPrivate::extensionsInitializedHelper()
{
    m_startingUp = false;

//    Utils::sort(m_pages, &IPage::priority);
    std::reverse(m_pages.begin(), m_pages.end());

    for (IPage *page : m_pages)
        appendPage(page);

    if (m_pendingFirstActivePage.isValid())
        activatePageHelper(m_pendingFirstActivePage);
}

}//namespace Core
