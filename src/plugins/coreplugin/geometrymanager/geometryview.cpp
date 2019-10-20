#include "geometryview.h"
#include "geometrymanager/geometrymanager.h"
#include "geometrymanager/geometrymanager_p.h"

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
    const QString placeholderText = tr("Hello!");
    m_emptyViewLabel->setText("");
//    connect(GeometryManagerPrivate::instance(), &GeometryManagerPrivate::placeholderTextChanged,
//            m_emptyViewLabel, &QLabel::setText);
//    m_emptyViewLabel->setText(EditorManagerPrivate::placeholderText());
    emptyLayout->addWidget(m_emptyViewLabel);
    m_container->addWidget(empty);
}

GeometryView::~GeometryView()
{

}

GeometryView *GeometryView::findNextView()
{
    return nullptr;
}

GeometryView *GeometryView::findPreviousView()
{
    return nullptr;
}

void GeometryView::paintEvent(QPaintEvent *)
{

}

void GeometryView::mousePressEvent(QMouseEvent *e)
{

}

void GeometryView::focusInEvent(QFocusEvent *)
{

}

}//namespace Core
