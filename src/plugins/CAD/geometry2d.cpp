#include "geometry2d.h"
#include "pf_cadwidget.h"
#include "pf_document.h"
#include "pf_graphicview.h"


Geometry2D::Geometry2D(PF_Document* doc)
    :Core::IGeometry()
    ,m_document(doc)
    ,w(new PF_CADWidget(doc))
{
    this->setWidget(w);
}

Geometry2D::~Geometry2D()
{

}

PF_Document* Geometry2D::document() const
{
    return m_document;
}

PF_GraphicView* Geometry2D::view() const
{
    return w->getGraphicView();
}
