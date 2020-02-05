#include "./polygon.h"

using namespace PolygonDetection;

Polygon::Polygon(void) : GraphicalPrimitives2D::Polygon2D()
{
}

Polygon::~Polygon(void)
{
    GraphicalPrimitives2D::Polygon2D::~Polygon2D();
}
