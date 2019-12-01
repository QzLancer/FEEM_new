#include "geometryview.h"
#include "geometrymanager/geometrymanager.h"
#include "geometrymanager/geometrymanager_p.h"
#include "igeometry.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QStackedWidget>
#include <QToolButton>
#include <QSplitter>
#include <QStackedLayout>

namespace Core {

GeometryView::GeometryView(QWidget *parent)
    :QWidget (parent)
    ,m_container(new QStackedWidget(this))
{
    auto tl = new QVBoxLayout(this);
    tl->setSpacing(0);
    tl->setMargin(0);
    tl->addWidget(m_container);

    /** 空白的时候 **/
    auto empty = new QWidget;
    empty->hide();
    auto emptyLayout = new QGridLayout(empty);
    empty->setLayout(emptyLayout);
    m_emptyViewLabel = new QLabel;
//    const QString placeholderText = tr("Hello!");
    m_emptyViewLabel->setText(tr("Please select a file."));
//    connect(GeometryManagerPrivate::instance(), &GeometryManagerPrivate::placeholderTextChanged,
//            m_emptyViewLabel, &QLabel::setText);
//    m_emptyViewLabel->setText(EditorManagerPrivate::placeholderText());
    emptyLayout->addWidget(m_emptyViewLabel);
    m_container->addWidget(empty);
    m_widgetCADMap.insert(empty,nullptr);
}

GeometryView::~GeometryView()
{

}

int GeometryView::CADCount() const
{
    return m_CADs.size();
}

void GeometryView::addCAD(IGeometry *cad)
{
    if(m_CADs.contains(cad))
        return;
    m_CADs.append(cad);

    /** 将CAD的控件添加进来 **/
    m_container->addWidget(cad->widget());
    m_widgetCADMap.insert(cad->widget(),cad);

    if(cad == currentCAD())
        setCurrentCAD(cad);
}

void GeometryView::removeCAD(IGeometry *cad)
{
    if(!cad) return;
    if(!m_CADs.contains(cad)) return;

    const int index = m_container->indexOf(cad->widget());
    if(index == -1) return;
    bool wasCurrent = (index == m_container->currentIndex());
    m_CADs.removeAll(cad);

    m_container->removeWidget(cad->widget());
    m_widgetCADMap.remove(cad->widget());
    cad->widget()->setParent(nullptr);

    if(wasCurrent)
        setCurrentCAD(m_CADs.count() ? m_CADs.last() : nullptr);
}

IGeometry *GeometryView::currentCAD() const
{
    if(m_CADs.count() > 0)
        return m_widgetCADMap.value(m_container->currentWidget());
    return nullptr;
}

void GeometryView::setCurrentCAD(IGeometry *cad)
{
    /** 应该要把控件显示出来 **/
    if(!cad || m_container->indexOf(cad->widget()) == -1){
        /** 显示空白 **/
        m_container->setCurrentIndex(0);
        emit currentCADChanged(nullptr);
        return;
    }
    m_CADs.removeAll(cad);
    m_CADs.append(cad);

    const int idx = m_container->indexOf(cad->widget());
    if(idx < 0) return;

    m_container->setCurrentIndex(idx);

    emit currentCADChanged(cad);
}

bool GeometryView::hasCAD(IGeometry *cad) const
{
    return m_CADs.contains(cad);
}

QList<IGeometry *> GeometryView::CADs() const
{
    return m_CADs;
}

//GeometryView *GeometryView::findNextView()
//{
//    return nullptr;
//}

//GeometryView *GeometryView::findPreviousView()
//{
//    return nullptr;
//}

void GeometryView::paintEvent(QPaintEvent *)
{

}

void GeometryView::mousePressEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton)
        return;
    setFocus(Qt::MouseFocusReason);
}

void GeometryView::focusInEvent(QFocusEvent *)
{
    GeometryManagerPrivate::setCurrentView(this);
}

}//namespace Core
