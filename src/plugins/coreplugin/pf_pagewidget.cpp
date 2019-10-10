#include "pf_pagewidget.h"

#include <QStatusBar>
#include <QVBoxLayout>
#include <QStackedLayout>

namespace Core {

/*!
 \brief 实际的多页面的控件。主要是QStackedLayout

 \param parent
*/
PF_PageWidget::PF_PageWidget(QWidget *parent)
    :QWidget (parent)
{
    m_pageIndex = new PF_PageIndex(this);

    m_pagesStack = new QStackedLayout;
    m_statusBar = new QStatusBar;
    m_statusBar->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    /** 主要的显示 **/
    auto vlayout = new QVBoxLayout;
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addLayout(m_pagesStack);
    vlayout->addWidget(m_statusBar);
    /** 主布局 **/
    auto mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(1);
    mainLayout->addLayout(vlayout);
    setLayout(mainLayout);
}

/*!
 \brief 插入一个page

 \param index
 \param page
 \param label
*/
void PF_PageWidget::insertPage(int index, QWidget *page, const QString &label)
{
    m_pagesStack->insertWidget(index, page);
}

/*!
 \brief 移除一个page

 \param index
*/
void PF_PageWidget::removePage(int index)
{
    m_pagesStack->removeWidget(m_pagesStack->widget(index));
}

int PF_PageWidget::currentIndex() const
{
    return m_pageIndex->currentIndex();
}

QStatusBar *PF_PageWidget::statusBar() const
{
    return m_statusBar;
}

void PF_PageWidget::setPageEnabled(int index, bool enable)
{
    m_pageIndex->setPageEnabled(index, enable);
}

bool PF_PageWidget::isPageEnabled(int index) const
{
    return m_pageIndex->isPageEnabled(index);
}

void PF_PageWidget::setCurrentIndex(int index)
{
    m_pageIndex->setCurrentIndex(index);
}

/*!
 \brief 显示index处的widget

 \param index
*/
void PF_PageWidget::showWidget(int index)
{
    emit currentAboutToShow(index);
    m_pagesStack->setCurrentIndex(index);
    QWidget *w = m_pagesStack->currentWidget();

    if (QWidget *focusWidget = w->focusWidget())
        w = focusWidget;
    w->setFocus();

    emit currentChanged(index);
}

PF_PageIndex::PF_PageIndex(QObject *parent)
    :QObject (parent)
{

}

void PF_PageIndex::setPageEnabled(int index, bool enable)
{
    if(index > m_inds.size()) return;
    if(index < 0) return;

    if (index < m_inds.size() && index >= 0) {
        m_inds[index]->enabled = enable;
    }
}

bool PF_PageIndex::isPageEnabled(int index) const
{
    if(index > m_inds.size()) return false;
    if(index < 0) return false;

    if (index < m_inds.size() && index >= 0)
        return m_inds[index]->enabled;

    return false;
}

void PF_PageIndex::setEnabled(int index, bool enabled)
{

}

void PF_PageIndex::setCurrentIndex(int index)
{
    if (isPageEnabled(index) && index != m_currentIndex) {
        m_currentIndex = index;
        emit currentChanged(m_currentIndex);
    }
}

}//namespace Core
