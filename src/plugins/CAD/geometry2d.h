#ifndef GEOMETRY2D_H
#define GEOMETRY2D_H

#include "CAD_global.h"

#include <coreplugin/geometrymanager/igeometry.h>

class PF_Document;
/**
 * @brief 二维的几何编辑器
 *
 */
class FEEM_CAD_EXPORT Geometry2D : public Core::IGeometry
{
public:
    Geometry2D(PF_Document* doc);
    ~Geometry2D();
private:
    PF_Document* m_document;
    QWidget* w;
};

#endif // GEOMETRY2D_H
