#include "geometrymanager.h"
#include "geometrymanager_p.h"
#include "igeometry.h"
#include "icore.h"

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

/**
 * @brief 激活view
 *
 * @param view
 */
void GeometryManagerPrivate::activateView(GeometryView *view)
{
    if(!view) return;
    QWidget* focusWidget;
    if(IGeometry* cad = view->currentCAD()){
        setCurrentCAD(cad);
        focusWidget = cad->widget();
    }else{
        setCurrentView(view);
        focusWidget = view;
    }
    focusWidget->setFocus();
    ICore::raiseWindow(focusWidget);
}

GeometryView *GeometryManagerPrivate::viewForCAD(IGeometry *cad)
{
    QWidget* w = cad->widget();
    while(w){
        w = w->parentWidget();
        if(auto view = qobject_cast<GeometryView*>(w)){
            return view;
        }
    }
    return nullptr;
}

/**
 * @brief
 *
 * @param cad
 */
void GeometryManagerPrivate::setCurrentCAD(IGeometry *cad)
{
    /** 可能要重置view **/
    if(cad)
        setCurrentView(nullptr);
    if(d->m_currentCAD == cad)
        return;

    d->m_currentCAD = cad;
    if(cad){
        if(GeometryView* view = viewForCAD(cad)){
            view->setCurrentCAD(cad);
        }
    }
    emit m_instance->currentCADChanged(cad);
}

/**
 * @brief 需要在view上打开一个cad，打开的时候，应该知道是什么模型吧？
 * 二维还是三维？
 *
 * @param view
 * @param fileName
 * @param cadId
 * @param newCAD
 * @return IGeometry
 */
IGeometry *GeometryManagerPrivate::openCAD(GeometryView *view, IGeometry* cad, Id cadId/*, bool *newCAD*/)
{
    cad = activateCAD(view,cad);

    return cad;
}

/**
 * @brief
 *
 * @param view
 * @param cad
 * @return IGeometry
 */
IGeometry *GeometryManagerPrivate::activateCAD(GeometryView *view, IGeometry *cad)
{
    if(!cad) return nullptr;
    /** 将cad放置到view上 **/
    cad = placeCAD(view,cad);

    view->setCurrentCAD(cad);
    return cad;
}

void GeometryManagerPrivate::closeCAD(IGeometry *cad)
{

}

void GeometryManagerPrivate::closeCADs(const QList<IGeometry *> &cads)
{

}

/**
 * @brief
 *
 * @param view
 * @param cad
 * @return IGeometry
 */
IGeometry *GeometryManagerPrivate::placeCAD(GeometryView *view, IGeometry *cad)
{
    /** 查找是不是已经有了 **/
    if(view->hasCAD(cad))
        return cad;
    /** cad是不是在另外的view **/
    if(GeometryView* sourceView = viewForCAD(cad)){
        if(cad != sourceView->currentCAD()){
            sourceView->removeCAD(cad);
            view->addCAD(cad);
            view->setCurrentCAD(cad);
            /** sourceView是否关闭了所有？ **/
            if(!sourceView->currentCAD()){

            }
        }
        return  cad;
    }
    view->addCAD(cad);
    return cad;
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

GeometryManager *GeometryManager::instance()
{
    return m_instance;
}

/**
 * @brief 按照那种根据文件类型判断cad的方式，似乎有点复杂，
 * 还不如，直接在用的时候，创建，然后再显示。也就是，每个project
 * 自己去选择哪个cad，文件本身就有，直接自己搞定就可以了。
 *
 * @param cad
 * @param editorId
 * @param newGeoEditor
 * @return IGeometry
 */
IGeometry *GeometryManager::openCAD(IGeometry* cad, Id editorId/*, bool *newGeoEditor*/)
{
    return GeometryManagerPrivate::openCAD(GeometryManagerPrivate::currentGeoView(),
                                           cad,editorId/*,newGeoEditor*/);
}

}//namespace Core
