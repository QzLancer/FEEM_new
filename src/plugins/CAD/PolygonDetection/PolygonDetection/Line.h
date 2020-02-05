#pragma once
#include "..\GraphicalPrimitives2D\Line2D.h"

namespace PolygonDetection {
class Line : public GraphicalPrimitives2D::Line2D
{
public:
    Line(void);
    Line(GraphicalPrimitives2D::Line2D * line);
    Line(GraphicalPrimitives2D::Point2D * p1, GraphicalPrimitives2D::Point2D * p2);
    Line(double x1, double y1, double x2, double y2);
    virtual ~Line(void);

    void SortIntersectionsList();
    inline bool HaveIntersections() { return (_intersections.size()>0); }
    inline GraphicalPrimitives2D::PointArray * GetIntersectionsList() { return &_intersections; }
    void AddIntersectionPoint(GraphicalPrimitives2D::Point2D * p);

    static Line * SimplifiedLine(Line * line_1, Line * line_2);

    static bool CompareOrder(PolygonDetection::Line* p_line1, PolygonDetection::Line* p_line2);

private:
    GraphicalPrimitives2D::PointArray _intersections;
};
}
