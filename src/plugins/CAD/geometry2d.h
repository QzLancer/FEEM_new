#ifndef GEOMETRY2D_H
#define GEOMETRY2D_H

#include "CAD_global.h"

#include <coreplugin/geometrymanager/igeometry.h>

class PF_Document;
class PF_GraphicView;
class PF_CADWidget;
/**
 * @brief 二维的几何编辑器
 *
 */
class FEEM_CAD_EXPORT Geometry2D : public Core::IGeometry
{
    Q_OBJECT
public:
    Geometry2D(PF_Document* doc);
    ~Geometry2D();

    PF_Document* document()  const;
    PF_GraphicView* view() const;
private:
    PF_Document* m_document;
    PF_CADWidget* w;
};

#endif // GEOMETRY2D_H
