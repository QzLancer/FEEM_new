#include "workpage.h"

#include <QHBoxLayout>
#include <QWidget>
#include <QSplitter>
#include <QDebug>
#include <QToolButton>
#include <QLabel>

namespace Core {

/**
 * @brief 正常使用时的页面布局
 *
 */
WorkPage::WorkPage()
    :m_splitter(new QSplitter)
{
    m_splitter->insertWidget(0,new QLabel("Add"));
    m_splitter->setHandleWidth(1);
    m_splitter->insertWidget(1,new QLabel("Add"));
    m_splitter->setStretchFactor(0, 0);
    m_splitter->setStretchFactor(1, 1);
    setWidget(m_splitter);
}

WorkPage::~WorkPage()
{
    delete m_splitter;
}

}//namespace Core
