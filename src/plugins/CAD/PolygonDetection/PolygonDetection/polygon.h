#pragma once

#include "../GraphicalPrimitives2D/Polygon2D.h"

namespace PolygonDetection {
class Polygon : public GraphicalPrimitives2D::Polygon2D
{
public:
    Polygon(void);
    virtual ~Polygon(void);
};
}
