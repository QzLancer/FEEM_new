#pragma once

#if !defined(POLYLINE2D_H)
#define POLYLINE2D_H

#include "Box2D.h"	
#include "Point2D.h"
#include "Line2D.h"

#include "./GPConsts.h"

namespace GraphicalPrimitives2D {
class Polygon2D; // to allow returning polygons inside polyline class

class Polyline2D : public Entity2D
{
public:
    bool Intersects(Polyline2D * polyline);
    bool Intersects(Entity2D * entity);

    PointArray * IntersectionPoints(Line2D *line, wxArrayInt * indexes = nullptr);
    bool Intersects(Line2D * line, bool proper = false);
    Point2D * Extension(double length, short flag = AT_END);
    double DistanceTo(Point2D * point, Point2D * nearest_point = nullptr, int * pred=nullptr, int * succ=nullptr);
    int Intersections();
    QString AsString(bool svg_format=false, const QString & stroke_color=DEFAULT_POLYLINE_COLOR, const QString & fill_color=DEFAULT_POLYLINE_FILL);
    virtual void Rotate(double theta);
    virtual void Translate(double dx, double dy);
    virtual void Scale(double sx, double sy);

    bool HaveVertex(Point2D *p, int *index=nullptr);
    void Simplify(double tolerance);
    void VertexReduction(double tolerance);
    inline Point2D * GetVertexAt(int n) { return (n<_vertex_array.size())?_vertex_array[n]:nullptr; }
    Point2D * GetVertexAt(int index, short offset);
    void Simplify();
    virtual void PerformRounding(double gamma);
    static Polyline2D * Join(Polyline2D *polyline1, Polyline2D *polyline2);
    void AddPolyline( Polyline2D * pl);
    Point2D * PointAt(double x, double y);
    Point2D * GetOtherPoint( Point2D *p );
    //		static bool CoincidentExtremities(Polyline2D * polyline1, Polyline2D * polyline2);
    Point2D * GetLastVertex() { return _vertex_array.last(); }
    Point2D * GetFirstVertex() { return _vertex_array[0]; }
    inline int GetVertexCount() { return _vertex_array.size(); }
    inline PointArray * GetVertexArray() { return &_vertex_array; }
    virtual void CalculateFirstAndLastPoint();

    inline bool IsClosed() { return _closed; }
    inline double GetLength() { return _length; }
    virtual bool AddVertex(Point2D *vertex, short flag = AT_END, int pos = 0u);
    inline void SetClosed(bool closed) { _closed = closed; }

    inline virtual Point2D * GetStartPoint() { return (Point2D::Ordered(_vertex_array[0], _vertex_array.last())?_vertex_array[0]:_vertex_array.last()); }
    inline virtual Point2D * GetEndPoint() { return (Point2D::Ordered(_vertex_array[0], _vertex_array.last())?_vertex_array.last():_vertex_array[0]); }

    Polyline2D();
    Polyline2D(Line2D * line);
    Polyline2D(Polyline2D * polyline);
    virtual ~Polyline2D();

protected:
    Polyline2D(entity_type type );

    void RecalculateLength();
    static bool HaveCommonVertex(Polyline2D *p1, Polyline2D *p2, int *i, int *j);
    virtual void CalculateBoundingBox();
    bool _closed;
    PointArray _vertex_array;

private:
    void DouglasPeucker(double tolerance, int start_index, int end_index);
    void ExecuteJoin(Polyline2D * pl, short flags = (NORMAL_ORDER | AT_END));
    double _length;
};
}


#endif // !defined(POLYLINE2D_H)
