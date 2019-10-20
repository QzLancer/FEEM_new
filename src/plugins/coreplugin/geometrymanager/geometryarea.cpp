#include "geometryarea.h"

namespace Core {

GeometryArea::GeometryArea(QWidget *parent)
{

}

GeometryArea::~GeometryArea()
{

}

void GeometryArea::setCurrentView(GeometryView *view)
{
    if(view == m_currentView)
        return;
}

}//namespace Core
