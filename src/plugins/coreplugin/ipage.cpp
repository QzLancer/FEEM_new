#include "ipage.h"

#include <coreplugin/pagemanager.h>

using namespace Core;
/*!
 \brief 不同页面的父类。

 \param parent
*/
IPage::IPage(QObject *parent)
    :IContext (parent)
{
    /** 每创建一个新的，都加入到列表当中 **/
    PageManager::instance()->addPage(this);
}

IPage::~IPage()
{
    /** 将该页面移除 **/
    PageManager::instance()->removePage(this);
}

void IPage::setEnabled(bool enabled)
{
    if(m_isEnabled == enabled)
        return;
    m_isEnabled = enabled;
}
