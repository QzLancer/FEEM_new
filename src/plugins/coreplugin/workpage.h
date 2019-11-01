#ifndef WORKPAGE_H
#define WORKPAGE_H

#include <coreplugin/ipage.h>
#include <QSplitter>
namespace ads {
class CDockManager;
class CDockWidget;
}


namespace Core {

class WorkPage : public IPage
{
    Q_OBJECT
public:
    WorkPage();
    ~WorkPage() override;
    static ads::CDockManager* DockManager();
public:
    static ads::CDockManager* m_DockManager;
    /** 定义几个默认的应该有的页面 **/
    ads::CDockWidget* projectDockWidget = nullptr;
    ads::CDockWidget* CADDockWidget = nullptr;
    ads::CDockWidget* messageDockWidget = nullptr;
    ads::CDockWidget* materialDockWidget = nullptr;
private:
    QSplitter *m_splitter;
};
}//namespace Core

#endif // WORKPAGE_H
