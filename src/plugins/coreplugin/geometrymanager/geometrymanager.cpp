#include "geometrymanager.h"
#include "geometrymanager_p.h"

#include "geometryview.h"

#include <QVBoxLayout>

namespace Core {

/*!
 \brief 绘图区域的时候所出现的一个占位控件。由几何管理器保存着一系列的
 控件，哪一个应该显示就显示哪个，如果没有需要显示的，就是空白，就是这个
 逻辑。

 \param parent
*/
GeometryManagerPlaceHolder::GeometryManagerPlaceHolder(QWidget *parent)
    : QWidget(parent)
{
    setLayout(new QVBoxLayout);
    layout()->setMargin(0);
}

GeometryManagerPlaceHolder::~GeometryManagerPlaceHolder()
{

}

/**
 * @brief
 *
 * @param event
 */
void GeometryManagerPlaceHolder::showEvent(QShowEvent *event)
{
    QWidget *previousFocus = nullptr;
    QWidget *em = GeometryManagerPrivate::currentGeoView();
    if(!em) return;
    if (em->focusWidget() && em->focusWidget()->hasFocus())
        previousFocus = em->focusWidget();
    layout()->addWidget(em);
    em->show();
    if (previousFocus)
        previousFocus->setFocus();
}

static GeometryManager *m_instance = nullptr;
static GeometryManagerPrivate *d;

GeometryManagerPrivate *GeometryManagerPrivate::instance()
{
    return d;
}

/**
 * @brief 返回当前的geoview，如果没有的话，返回一个占位。
 *
 * @return QWidget
 */
GeometryView *GeometryManagerPrivate::currentGeoView()
{
    GeometryView* view = d->m_currentView;
    /** 可能没有打开文件 **/
    if(!view){
        return nullptr;
    }
    return view;
}

void GeometryManagerPrivate::setCurrentView(GeometryView *view)
{
    if (view == d->m_currentView)
        return;

    GeometryView *old = d->m_currentView;
    d->m_currentView = view;

    if (old)
        old->update();
    if (view)
        view->update();
}

GeometryManagerPrivate::GeometryManagerPrivate(QObject *parent)
    :QObject (parent)
{
    d = this;
}

GeometryManagerPrivate::~GeometryManagerPrivate()
{
    d = nullptr;
}

void GeometryManagerPrivate::init()
{

}

/**
 * @brief 几何管理器，可以切换不同的模型。
 *
 * @param parent
 */
GeometryManager::GeometryManager(QObject *parent)
    :QObject (parent)
{
    m_instance = this;
    /** 因为构造函数是私有的，所以只能在这里构造 **/
    d = new GeometryManagerPrivate(this);
    d->init();
}

GeometryManager::~GeometryManager()
{
    delete d;
    d = nullptr;
    m_instance = nullptr;
}

}//namespace Core
