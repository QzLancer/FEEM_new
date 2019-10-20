#include "geometrymanager.h"

#include <QVBoxLayout>

namespace Core {

/*!
 \brief 不显示绘图区域的时候所出现的一个占位控件。

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

void GeometryManagerPlaceHolder::showEvent(QShowEvent *event)
{

}
}//namespace Core
