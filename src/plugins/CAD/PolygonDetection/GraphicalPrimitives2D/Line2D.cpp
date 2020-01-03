#include "Line2D.h"
#include "Box2D.h"

#include "./GPMacros.h"
#include "Polygon2D.h"

using namespace GraphicalPrimitives2D;

#include <math.h>

#define CREATE_POINTS_FOR_INTERSECTION_ALGORITHMS()  \
	Point2D * a = &_start_point; \
	Point2D * b = &_end_point; \
	Point2D * c = line->GetStartPoint(); \
	Point2D * d = line->GetEndPoint(); 

/***
* @desc constructor
*/
Line2D::Line2D() : Entity2D(Entity2D::et_line)
{	
}

/***
* @desc constructor
* @param pointer to start point
* @param pointer to end point
* @note Points passed by reference are not stored, so they must be
*       instances of point deleted by the caller method
*/
Line2D::Line2D(Point2D * start_point, Point2D * end_point) : Entity2D(Entity2D::et_line)
{
  _start_point.Set(start_point);
  _end_point.Set(end_point);
  CalculateFirstAndLastPoint();
}

/***
* @desc constructor
* @param other line
* @note Line passed by reference are not stored, so it must be
*       instances of line deleted by the caller method
*/
Line2D::Line2D(Line2D * line) : Entity2D(Entity2D::et_line)
{
  _start_point.Set(line->GetStartPoint());
  _end_point.Set(line->GetEndPoint());
  CalculateFirstAndLastPoint();
}

/***
* @desc constructor
* @param endpoints coordinates
*/
Line2D::Line2D(double x1, double y1, double x2, double y2) : Entity2D(Entity2D::et_line)
{
	_start_point.SetX(x1);
	_start_point.SetY(y1);

	_end_point.SetX(x2);
	_end_point.SetY(y2);

	CalculateFirstAndLastPoint();
}

 
/***
* @desc destructor
*/
Line2D::~Line2D()
{
//	WX_CLEAR_ARRAY(_intersections);	
}

/***
* @desc selectors that set the attributes of this line
* @param attribute value to be set
*/
//void Line2D::SetStartX(double x) { _start_point.SetX(x); }
//void Line2D::SetStartY(double y) { _start_point.SetY(y); }
//void Line2D::SetEndX(double x) { _end_point.SetX(x); }
//void Line2D::SetEndY(double y) { _end_point.SetY(y); }


// /***
// * @desc calculate the bounding box of this line
// */
// void Line2D::CalculateBoundingBox()
// {
// 	// if bounding box already exists it will not calculate
// 	if (_p_bounding_box)
// 	  return;
//     
// 	// deleted when above lines added (25-Jun-2003)
//     // DELETE_OBJECT(_p_bounding_box );
//       
//     double dx = (_end_point.GetX() - _start_point.GetX());
//     double dy = (_end_point.GetY() - _start_point.GetY());
//   
//     _p_bounding_box= new Box2D(
//         &_start_point, 
//         Vector2D(&_start_point, dx, 0), 
//         Vector2D(&_start_point, 0, dy));     
//}

/***
* @desc calculate the first and Last point of this line
*/
void Line2D::CalculateFirstAndLastPoint()
{	
	if (Point2D::Ordered(&_start_point, &_end_point)) {
		SetFirstPoint( &_start_point );
		SetLastPoint( &_end_point );		
	} else {
		SetFirstPoint( &_end_point );
		SetLastPoint( &_start_point );	
	}
}


/***
* @param pointer to point
* @return pointer to the opposite point of the one passed 
*         or nullptr if point passed don't belong to line
*/
Point2D * Line2D::GetOtherPoint(Point2D *p)
{
	if ((*p)==_start_point)
		return &_end_point;
	
	if ((*p)==_end_point)
		return &_start_point;

	return nullptr;
}

/***
* @return a pointer to the point on passed coordinates
*/
Point2D * Line2D::PointAt(double x, double y)
{
	if (x == _start_point.GetX() && y == _start_point.GetY()) {
		return &_start_point;
	}
	
	if (x == _end_point.GetX() && y == _end_point.GetY()) {
		return &_end_point;
	}

	return nullptr;
}

/**
* @param a pointer to a line
* @return true if line intersects with this, false otherwise
*/
bool Line2D::Intersects(Line2D *line)
{

	if (IntersectsProper(line))
		return true;

	CREATE_POINTS_FOR_INTERSECTION_ALGORITHMS();
	
	return (c->Between(a,b) ||
		d->Between(a,b) ||
		a->Between(c,d) ||
		b->Between(c,d));
}

/***
* @param a pointer to a line
* @return true is line have a proper intersection with this, false otherwise
* @note a proper intersection occurs when two segments intersects at a point 
*      interior to both
* @see O'Rourke, Joseph, "Computational Geometry in C, 2nd Ed.", pp.30 
*/
bool Line2D::IntersectsProper(Line2D *line)
{
	CREATE_POINTS_FOR_INTERSECTION_ALGORITHMS();

	// Eliminate improper cases
	if (c->Collinear(a, b) || d->Collinear(a,b) || a->Collinear(c,d) || b->Collinear(c,d))
		return false;

	return ( c->Left(a,b) ^ d->Left(a,b) ) &&
		( a->Left(c,d) ^ b->Left(c,d) );
}

/**
* @param a pointer to a line
* @return a pointer to the intersection point between this line and the line passed
* @note do not forget to delete the returned point elsewhere
* @see O'Rourke, Joseph, "Computational Geometry in C, 2nd Ed.", pp.220-226
*/
Point2D * Line2D::IntersectionPoint(Line2D *line)
{

	// in case two lines share just vertices it was no intersection
	if (line->_start_point == _start_point ||
		line->_start_point == _end_point ||
		line->_end_point == _start_point ||
		line->_end_point == _end_point)
		return nullptr;
	
	double s, num, denom;

	CREATE_POINTS_FOR_INTERSECTION_ALGORITHMS();

	// first we calculate the denominator of equation
	denom = a->GetX() * (d->GetY() - c->GetY()) +
		b->GetX() * (c->GetY() - d->GetY()) +
		d->GetX() * (b->GetY() - a->GetY()) +
		c->GetX() * (a->GetY() - b->GetY());

	// see if segments are parallel
	if (denom == 0.0)
		return nullptr;

	num = a->GetX() * (d->GetY() - c->GetY()) +
		c->GetX() * (a->GetY() - d->GetY()) +
		d->GetX() * (c->GetY() - a->GetY());

	s = num/denom;
/*
	num = c->GetX() * ( c->GetY() - b->GetY()) +
		b->GetX() * ( a->GetY() - c->GetY()) +
		c->GetX() * ( b->GetY() - a->GetY());

	t = num / denom;
*/
	
	return new Point2D(a->GetX()+s*(b->GetX()-a->GetX()), a->GetY()+s*(b->GetY() - a->GetY()));
}

/***
* @desc adds an intersection point to the intersection points list
* @param pointer to point2D entity
* @note the point will be deleted by the line destructor
*/
//void Line2D::AddIntersectionPoint(Point2D *p)
//{
//    if (p)
//        _intersections.Add(p);
//}

/***
 * @desc sort the intersections list
 */
//void Line2D::SortIntersectionsList()
//{
//    _intersections.Sort(Point2D::CompareOrder);
//}

/**
* @desc compares two lines in term of order
* @return negative, zero or positive value 
*         according to whether the first element 
*         passed to it is less than, equal to or 
*         greater than the second one. 
*/
bool Line2D::CompareOrder(Line2D *p_line2, Line2D *p_line1)
{
    bool result = Point2D::CompareOrder((p_line1)->GetFirstPoint(), (p_line2)->GetFirstPoint());

    if (result==false) {
		// in case lines share first point
		// we must order the lines by its slope

        double dx1 = (p_line1)->GetLastPoint()->GetX() - (p_line1)->GetFirstPoint()->GetX();
        double dy1 = (p_line1)->GetLastPoint()->GetY() - (p_line1)->GetFirstPoint()->GetY();
        double dx2 = (p_line2)->GetLastPoint()->GetX() - (p_line2)->GetFirstPoint()->GetX();
        double dy2 = (p_line2)->GetLastPoint()->GetY() - (p_line2)->GetFirstPoint()->GetY();

		// by definition of first and last point we are sure that dy > 0

		if (dx1>0 && dx2<0)
			// line 1 in 1st quadrant, line 2 in 2nd quadrant
			// this means line 2 cames first
            return true;

		if (dx1<0 && dx2>0)
			// line 1 in 2nd quadrant, line 2 in 1st quadrant
			// this means line 1 cames first
            return false;

		if (dx1==0) {
			// first line is vertical
			if (dx2>0)
				// second line in 1st quadrant
				// first line is previous
                return false;

			if (dx2<0)
				// second line in 2nd quadrant
				// second line is previous
                return true;
			// this should no happen
            return false;
		}

		if (dx2==0) {
			// second line is vertical
			if (dx1>0)
				// first line in 1st quadrant
				// second line is previous
                return true;

			if (dx1<0)
				// first line in 2nd quadrant
				// first line is previous
                return false;

			// this should not happen
            return false;
		}


		// calculate the slopes
		double m1 = dy1/dx1;
		double m2 = dy2/dx2;
		// line 1 and line 2 in 2nd quadrant
		if (m1>m2)
            return false;
		if (m1<m2)
            return true;
		
		// in this case we have the same slope in both lines, 
		// which means that both lines are coincident.
        return false;
	}

	return result;
}	

/***
* @desc perform rounding in entities coordinates
*/
void Line2D::PerformRounding(double gamma)
{
	_end_point.PerformRounding(gamma);
	_start_point.PerformRounding(gamma);
}

/***
* @return true if lines overlap, false otherwise
*/
bool Line2D::Overlapping(Line2D *line_1, Line2D *line_2)
{
	Point2D *p1, *p2, *p3, *p4;

	p1 = line_1->GetStartPoint();
	p2 = line_1->GetEndPoint();
	p3 = line_2->GetStartPoint();
	p4 = line_2->GetEndPoint();
	
	// first see of all endpoints are collinear,
	// then see if any endpoint of one line lies on the other line
	return (p1->Collinear(p3,p4) && p2->Collinear(p3,p4)) &&
		((line_1->Contains(p3) || line_1->Contains(p4)) ||
		 (line_2->Contains(p1) || line_2->Contains(p2)));
}

/***
* @return true if lines are strictly overlapping, false otherwise
*/
bool Line2D::StrictOverlapping(Line2D *line_1, Line2D *line_2)
{
	Point2D *p1, *p2, *p3, *p4;

	p1 = line_1->GetStartPoint();
	p2 = line_1->GetEndPoint();
	p3 = line_2->GetStartPoint();
	p4 = line_2->GetEndPoint();

	// check the case the lines are coincident
	if ((((*p1)==(*p3)) && ((*p2)==(*p4))) || (((*p2)==(*p3)) && ((*p1)==(*p4))))
		return true;

	// first see of all endpoints are collinear,
	// then see if any endpoint of one line lies on the other line
	return (p1->Collinear(p3,p4) && p2->Collinear(p3,p4)) &&
		((line_1->StrictContains(p3) || line_1->StrictContains(p4)) ||
		 (line_2->StrictContains(p1) || line_2->StrictContains(p2)));
}

/***
* @return a new simplified line if line_1 and line_2 overlaps, nullptr otherwise
*/
Line2D * Line2D::SimplifiedLine(Line2D *line_1, Line2D *line_2)
{
	if (Overlapping(line_1, line_2)){		
		if (line_1->Contains(line_2))
			return line_1;
		if (line_2->Contains(line_1))
			return line_2;

		Point2D *new_line_start_point;
		Point2D *new_line_end_point;

		// detects which point of <line_1> must be removed
		if (line_1->GetStartPoint()->Between(line_2->GetStartPoint(), line_2->GetEndPoint())) {
			new_line_start_point = line_1->GetEndPoint();
		} else {
			new_line_start_point = line_1->GetStartPoint();
		}
		// detects which point of <line_2> must be removed
		if (line_2->GetStartPoint()->Between(line_1->GetStartPoint(), line_1->GetEndPoint())) {
			new_line_end_point = line_2->GetEndPoint();
		} else {
			new_line_end_point = line_2->GetStartPoint();
		}

		// create a new line
		return new Line2D(new_line_start_point, new_line_end_point);
	}

	return nullptr;

}

/***
* @return true if <line_1> contains <line_2>, false otherwise
*/
inline
bool Line2D::Contains(Line2D *line_1, Line2D *line_2)
{
	return ( line_1->Contains(line_2->GetStartPoint()) && line_1->Contains(line_2->GetEndPoint()));
}

/***
* @return true if <line_1> contains strictly <line_2>, false otherwise
*/
inline
bool Line2D::StrictContains(Line2D *line_1, Line2D *line_2)
{
	return ( line_1->StrictContains(line_2->GetStartPoint()) && line_1->StrictContains(line_2->GetEndPoint()));
}

/***
* @return true if <line> contains <point>, false otherwise
*/
inline
bool Line2D::Contains(Line2D * line, Point2D *point)
{
	return point && line && point->Between(line->GetStartPoint(), line->GetEndPoint());
}

/***
* @return true if <line> contains strictly <point>, false otherwise
*/
inline
bool Line2D::StrictContains(Line2D * line, Point2D *point)
{
	return point && line && point->StrictBetween(line->GetStartPoint(), line->GetEndPoint());
}

/***
* @return distance from point p to this line
*/
inline double Line2D::Distance(Point2D *p, Point2D *nearest_point)
{
	return Distance(GetStartPoint(), GetEndPoint(), p, nearest_point);
}

/***
* @desc macro to set the neares point
* @note used only in distance method, undefined a few lines below
*/
#define SET_NEAREST_POINT(p) if (nearest_point) nearest_point->Set(p);

/***
* @desc distance between point p and line segment defined 
*    by <endpoint_1> and <endpoint_2>
*/
double Line2D::Distance(Point2D *endpoint_1, Point2D *endpoint_2, Point2D * p, Point2D * nearest_point)
{
	Vector2D u(*endpoint_1, *endpoint_2);
	Vector2D v(*endpoint_1, *p);

	double c1 = Vector2D::dot(&v, &u);
	if (c1<=0) {
		SET_NEAREST_POINT(endpoint_1);
		return p->DistanceTo(endpoint_1);
	}

	double c2 = Vector2D::dot(&u, &u);
	if (c2<=c1) {
		SET_NEAREST_POINT(endpoint_2);
		return p->DistanceTo(endpoint_2);
	}

	Vector2D w = u*(c1/c2);

	Point2D q(Point2D(endpoint_1->GetX()+w.GetDX(), endpoint_1->GetY()+w.GetDY())); 
	SET_NEAREST_POINT(&q);
	return p->DistanceTo(&q);
}

#undef SET_NEAREST_POINT


/***
* @return true if lines are equal, false otherwise
*/
bool Line2D::Equal(Line2D *line_1, Line2D *line_2)
{
	Point2D *p1, *p2, *p3, *p4;

	p1 = line_1->GetStartPoint();
	p2 = line_1->GetEndPoint();
	p3 = line_2->GetStartPoint();
	p4 = line_2->GetEndPoint();

	return ((*p1)==(*p3) && (*p2)==(*p4)) || ((*p1)==(*p4) && (*p2)==(*p3));
}

/***
* @desc performs a scale transformation on this line
* @param x component of the translation
* @param y component of the translation
*/
void Line2D::Scale(double sx, double sy)
{
	_start_point.Scale(sx,sy);
	_end_point.Scale(sx,sy);
}

/***
* @desc performs a translation transformation on this line
* @param x component of the translation
* @param y component of the translation
*/
void Line2D::Translate(double dx, double dy)
{
	_start_point.Translate(dx,dy);
	_end_point.Translate(dx,dy);
}


/***
* @desc performs a rotation transformation on this line
* @param theta component of the translation
*/
void Line2D::Rotate(double theta)
{
	_start_point.Rotate(theta);
	_end_point.Rotate(theta);
}


/***
* @desc writes the line in given image
*/
//bool Line2D::WriteImage(wxImage *dest, const wxColour &colour, double factor, double dx, double dy)
//{
//	if (!dest) return false;

//	int x1 = (int) ((_start_point.GetX()+dx)*factor);
//	int y1 = (int) ((_start_point.GetY()+dy)*factor);

//	int x2 = (int) ((_end_point.GetX()+dx)*factor);
//	int y2 = (int) ((_end_point.GetY()+dy)*factor);

//	return Bresenham(dest, x1, y1, x2, y2, colour);
	
//}

/***
* @desc writes the line using bresenham algorithm
*/
//bool Line2D::Bresenham(wxImage *dest, int x1, int y1, int x2, int y2, const wxColour &colour)
//{
//	if (!dest) return false;
	
//	int xc[2];
//	int yc[2];
	
//	xc[0] = y1<y2?x1:x2;
//	xc[1] = y1<y2?x2:x1;
//	yc[0] = y1<y2?y1:y2;
//	yc[1] = y1<y2?y2:y1;
	
//	int x[2], y[2], xx, yy,
//		d,    dx,   dy,   ince, incne, incy,
//		swap, tmp, i;
	
//	/* computes xx and yy interval*/
//	dx = xc[1] - xc[0];
//	dy = yc[1] - yc[0];
	
//	/* swap x with y if interval in yy is bigger than in xx */
//	if ( abs( dx) >= abs( dy) ) {
//		for( i=0; i<2; i++) {
//			x[i] = xc[i];
//			y[i] = yc[i];
//		}
//		swap = 0;
//	} else {
//		for( i=0; i<2; i++) {
//			x[i] = yc[i];
//			y[i] = xc[i];
//		}
//		swap = 1;
//		tmp = dx;
//		dx  = dy;
//		dy  = tmp;
//	}
	
//	/* Swap segment endpoints to make x variation positive */
//	if ( dx < 0 ) {
//		tmp  = x[0];
//		x[0] = x[1];
//		x[1] = tmp;
//		tmp  = y[0];
//		y[0] = y[1];
//		y[1] = tmp;
//		dx   = -dx;
//		dy   = -dy;
//	}
	
//	/* Prepares y increment according to dy signal and
//	assures that dy is positive */
//	if ( dy < 0 ) {
//		incy = -1;
//		dy   = -dy;
//	} else incy = 1;
	
//	/* Assign initial values for Bresenham algorithm */
//	xx    = x[0];
//	yy    = y[0];
//	d     = 2 * dy - dx;
//	ince  = 2 * dy;
//	incne = 2 * (dy - dx);
	
//	/* Paints inicial point (attention to x and y swaping) */
//	if ( swap )
//		dest->SetRGB( yy, xx, colour.Red(), colour.Green(), colour.Blue());
//    else
//		dest->SetRGB( xx, yy, colour.Red(), colour.Green(), colour.Blue());
	
//	/* Bresenham algorithm main cycle*/
//	while( xx < x[1] ) {
//		if ( d <= 0  ) {
//			d += ince;
//			xx++;
//		} else {
//			d += incne;
//			xx++;
//			yy += incy;
//		}
	
//		/* Paints computed point (attention to x and y swaping) */
//		if ( swap )
//			dest->SetRGB( yy, xx, colour.Red(), colour.Green(), colour.Blue());
//		else
//			dest->SetRGB( xx, yy, colour.Red(), colour.Green(), colour.Blue());
//	}
	
//	return true;
//}

/***
* @desc computes the Minkowski Sum of this line
* @return convex poligon representing the Minkowski sum 
* @see documents/minkowski.vsd
* @note do not forget to delete the returned polygon
*/
// Polygon2D * Line2D::GetMinkowskiSum(double pixel_size)
// {
//     Polygon2D *result = nullptr;
//     Point2D *p1, *p2;
//     
//     int order = Point2D::CompareOrder(&_start_point,&_end_point);
// 
//     // check if endpoint and startpoint are coincident
//     if (order == 0) return nullptr;
// 
//     if (order < 0) {
//         // start point before end point: dy>0 or (dy=0 and dx>0)
//         p1 = &_start_point;
//         p2 = &_end_point;
//     } else {        
//         p1 = &_end_point;
//         p2 = &_start_point;
//     }
// 
//     double dx = p2->GetX() - p1->GetX();
//     double dy = p2->GetY() - p1->GetY();
//     
//     // compute half pixel size
//     double s = pixel_size/2.0f;
// 
//     result = new Polygon2D();
//     
//     // the Minkowski sum of a line segment is a convex polygon
//     result->SetConvex(true);
// 
//     // case 1: dx = 0
//     if (dx==0) {
//         result->AddVertex(new Point2D(p1->GetX()-s, p1->GetY()-s)); // V1
//         result->AddVertex(new Point2D(p1->GetX()+s, p1->GetY()-s)); // V2
// 
//         result->AddVertex(new Point2D(p2->GetX()+s, p2->GetY()+s)); // V3
//         result->AddVertex(new Point2D(p2->GetX()-s, p2->GetY()+s)); // V4
// 
//         return result;
//     }
// 
//     // case 2: dy = 0
//     if (dy==0){
//         result->AddVertex(new Point2D(p1->GetX()-s, p1->GetY()+s)); // V1
//         result->AddVertex(new Point2D(p1->GetX()-s, p1->GetY()-s)); // V2
// 
//         result->AddVertex(new Point2D(p2->GetX()+s, p2->GetY()-s)); // V3
//         result->AddVertex(new Point2D(p2->GetX()+s, p2->GetY()+s)); // V4
// 
//         return result;
//     }
// 
//     // case 3: dx < 0
//     if (dx<0){
//         result->AddVertex(new Point2D(p1->GetX()-s, p1->GetY()-s)); // V1
//         result->AddVertex(new Point2D(p1->GetX()+s, p1->GetY()-s)); // V2
//         result->AddVertex(new Point2D(p1->GetX()+s, p1->GetY()+s)); // V3
// 
//         result->AddVertex(new Point2D(p2->GetX()+s, p2->GetY()+s)); // V4
//         result->AddVertex(new Point2D(p2->GetX()-s, p2->GetY()+s)); // V5
//         result->AddVertex(new Point2D(p2->GetX()-s, p2->GetY()-s)); // V6
// 
//         return result;
//     }
// 
//     
//     // case 4: dx > 0
//     if (dx>0){
//         result->AddVertex(new Point2D(p1->GetX()-s, p1->GetY()+s)); // V1
//         result->AddVertex(new Point2D(p1->GetX()-s, p1->GetY()-s)); // V2
//         result->AddVertex(new Point2D(p1->GetX()+s, p1->GetY()-s)); // V3
// 
//         result->AddVertex(new Point2D(p2->GetX()+s, p2->GetY()-s)); // V4
//         result->AddVertex(new Point2D(p2->GetX()+s, p2->GetY()+s)); // V5
//         result->AddVertex(new Point2D(p2->GetX()-s, p2->GetY()+s)); // V6
// 
//         return result;
//     }
// 
//     DELETE_OBJECT(result);
//     return nullptr;
// }

#define GET_LIMITS_FUNCTION_MACRO(fn, coord_fn, limit) \
double Line2D::fn(void) { \
	double x1 = _start_point.coord_fn(); \
	double x2 = _end_point.coord_fn(); \
	return limit(x1,x2); \
} 

GET_LIMITS_FUNCTION_MACRO(GetMaxX, GetX, MAX)
GET_LIMITS_FUNCTION_MACRO(GetMaxY, GetY, MAX)
GET_LIMITS_FUNCTION_MACRO(GetMinX, GetX, MIN)
GET_LIMITS_FUNCTION_MACRO(GetMinY, GetY, MIN)

#undef GET_LIMITS_FUNCTION_MACRO
