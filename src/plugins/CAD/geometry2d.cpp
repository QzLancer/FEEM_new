#include "geometry2d.h"
#include "pf_cadwidget.h"

Geometry2D::Geometry2D()
{
    QWidget* w = new PF_CADWidget();
    this->setWidget(w);
}

Geometry2D::~Geometry2D()
{

}
