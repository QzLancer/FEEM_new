#include ".\line.h"

#include <QtAlgorithms>

using namespace PolygonDetection;
Line::Line(void) : 
GraphicalPrimitives2D::Line2D()
{}

Line::Line(GraphicalPrimitives2D::Line2D * line) :
GraphicalPrimitives2D::Line2D(line)
{}

Line::Line(GraphicalPrimitives2D::Point2D * p1, GraphicalPrimitives2D::Point2D * p2) :
GraphicalPrimitives2D::Line2D(p1,p2)
{}

Line::Line(double x1, double y1, double x2, double y2) :
GraphicalPrimitives2D::Line2D(x1,y1,x2,y2) 
{}

Line::~Line(void)
{
	WX_CLEAR_ARRAY(_intersections);
	GraphicalPrimitives2D::Line2D::~Line2D();
}

/***
* @desc adds an intersection point to the intersection points list
* @param pointer to point2D entity
* @note the point will be deleted by the line destructor
*/
void Line::AddIntersectionPoint(GraphicalPrimitives2D::Point2D *p)
{
    if (p) _intersections.append(p);
}

/***
* @desc sort the intersections list
*/
void Line::SortIntersectionsList()
{
//	_intersections.Sort(GraphicalPrimitives2D::Point2D::CompareOrder);
    qSort(_intersections.begin(),_intersections.end(),GraphicalPrimitives2D::Point2D::CompareOrder);
}

Line * PolygonDetection::Line::SimplifiedLine(Line * line_1, Line * line_2)
{
	if (!line_1 || !line_2)
        return nullptr;

	GraphicalPrimitives2D:: Line2D * line = 
		GraphicalPrimitives2D::Line2D::SimplifiedLine(line_1, line_2);

	if (line != line_1 && line != line_2) {
		Line * new_line = new Line(line);
		wxDELETE(line);
		line = new_line;
	}

	return (Line*) line;
}

bool PolygonDetection::Line::CompareOrder(Line * p_line1, Line * p_line2) {
	return GraphicalPrimitives2D::Line2D::CompareOrder(
        (GraphicalPrimitives2D::Line2D *) p_line1,
        (GraphicalPrimitives2D::Line2D *) p_line2);
}
