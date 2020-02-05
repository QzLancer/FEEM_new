#pragma once

#include "./polygon.h"
#include "./graph_entities/Graph.h"
#include "LineSet.h"

namespace PolygonDetection {

typedef QVector<Polygon*> PolygonsArray;

class PolygonSet
{
public:
    PolygonSet(void);
    ~PolygonSet(void);
    // Constructs a polygon set from given line set
    bool Construct(LineSet * line_set);

    // Simplifies the polygon set
    void Simplify(double smaller_polygon_length);

    inline int size() { return _polygons_array.size(); }
    inline Polygon * Item(int i) { return _polygons_array.at(i); }

    void Clear(void);

private:
    void CreatePointsArray(LineSet * line_set);
    Graph * LinesToGraph(LineSet * line_set);
    void CyclesToPolygons(CycleSet * cycle_set);

    int GetPointCount();
    GraphicalPrimitives2D::Point2D * PointByID(int id);

    GraphicalPrimitives2D::PointArray _all_points_array;
    PolygonsArray _polygons_array;

public:
    // Returns a string with the SVG containing the polygon set
    QString AsSVG(bool colorized=false);
};
}
