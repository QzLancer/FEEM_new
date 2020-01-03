/*
+--------------------------------------------------------------------+
| Point2D.cpp: implementation of the Point2D class.                  |
+--------------------------------------------------------------------+
|                                                                    |
| Author : Alfredo Ferreira Jr.                                      |
| E-mail : alfredo.ferreira.jr@inesc-id.pt                           |
| Website: http://immi.inesc-id.pt/~afj                              |
|                                                                    |
| Version: 2.00                                                      |
| Created: Jan 2003                                                  |
| Updated: May-Jul-Sep 2003                                          |
| Updated: Feb 2008 (Peeled to basic functionalities)                |
|                                                                    |
+--------------------------------------------------------------------+
| Intelligent Multimodal Interfaces Group at INESC-ID                |
| Department of Information Systems and Computer Science             |
| IST/Technical University of Lisbon                                 |
| Rua Alves Redol 9                                                  |
| 100-029 Lisboa, Portugal                                           |
+--------------------------------------------------------------------+
|                                                                    |
| Copyright (c) 2003-2008 INESC-ID                                   |
|                                                                    |
|   The copyright to the computer program(s) herein is the property  |
| of INESC-ID, Portugal. The program(s) may be used and/or copied    |
| only with the written permission of INESC-ID or in accordance with |
| the terms and conditions stipulated in the agreement/contract      |
| under which the program(s) have been supplied.                     |
|                                                                    |
+--------------------------------------------------------------------+
*/

#include "Point2D.h"

#include "./GPMacros.h"

#include <math.h>
//#include <wx/arrimpl.cpp>

using namespace GraphicalPrimitives2D;

//WX_DEFINE_OBJARRAY(PointArray);

/***
* @desc constructor
* @param entity name
*/
Point2D::Point2D(void) : Entity2D(Entity2D::et_point)
{
    Initialize(0,0);
}

/***
* @desc constructor
* @param x coordinate
* @param y coordinate
*/
Point2D::Point2D(double x, double y) : Entity2D(Entity2D::et_point)
{
    Initialize(x,y);
}

/***
* @desc constructor
* @param other point
*/
Point2D::Point2D(Point2D * p_point) : Entity2D( Entity2D::et_point)
{
    // initializes the attributes, just in case of a invalid point
    Initialize(0,0);

    // sets the attributes with the other point value
    this->Set(p_point);
}

/***
* @desc initializes the variables
*/
void Point2D::Initialize(double x, double y)
{
    _x = x;
    _y = y;

    _owner_entity = nullptr;

    _index = 0;

}

/***
* @desc destructor
*/
Point2D::~Point2D()
{
    // there are no need to delete the owner entity because
    // it is just a pointer to a entity that will be deleted
    // elsewhere
}

/***
* @desc performs a scale transformation on this point
* @param x component of the scale
* @param y component of the scale
*/
void Point2D::Scale(double sx, double sy)
{
    SetX(GetX()*sx);
    SetY(GetY()*sy);
}

/***
* @desc performs a translation transformation on this point
* @param x component of the translation
* @param y component of the translation
*/
void Point2D::Translate(double dx, double dy)
{
    SetX(GetX()+dx);
    SetY(GetY()+dy);
}

/***
* @desc performs a rotation transformation on this point
* @param theta component of the translation
* @see J. D. Foley, A. van Dam, S. K. Feiner, J. F. Hughes, 
*      Computer Graphics: Principles and Practice, Addison-Wesley, 2nd ed in C, 1990, chaper 5.
*/
void Point2D::Rotate(double theta)
{
    double rotated_x = GetX()*cos(theta)-GetY()*sin(theta);
    double rotated_y = GetX()*sin(theta)+GetY()*cos(theta);

    SetX(rotated_x);
    SetY(rotated_y);
}

/***
* @desc calculates the distance between this point and another
* @param other point 
* @return distance
*/
double Point2D::DistanceTo(Point2D *p)
{
    if (!p)
        return 0;

    return sqrt(SquareDistanceTo(p));
}


/***
* @desc calculates the square of the distance between this point 
*     and another
* @param other point 
* @return distance
*/
double Point2D::SquareDistanceTo(Point2D *p)
{
    return SQR(fabs(GetX()-p->GetX()))+SQR(fabs(GetY()-p->GetY()));
}

/***
* @desc set this point cordinates with the coordinates of another point
* @param other point 
*/
void Point2D::Set(Point2D *p)
{
    if (p) {
        _x = p->GetX();
        _y = p->GetY();
    }
}


/***
* @desc fills the first and last point attribute
*/
void Point2D::CalculateFirstAndLastPoint()
{
    SetFirstPoint(this);
    SetLastPoint(this);
}

/***
* @desc operator == override 
*/
bool Point2D::operator ==(const Point2D &p)
{    
    return (_x == p._x) && (_y == p._y);
}


/***
* @desc operator != override 
*/
bool Point2D::operator !=(const Point2D &p)
{    
    return !((_x == p._x) && (_y == p._y));
}

/***
* @desc operator = override 
*/
void Point2D::operator =(const Point2D &p)
{    
    _x = p._x;
    _y = p._y;
}


/**
* @desc compares two points in term of order
* @return negative, zero or positive value 
*         according to whether the first element 
*         passed to it is less than, equal to or 
*         greater than the second one. 
*/
//int Point2D::CompareOrder(Point2D ***p_p1, Point2D ***p_p2)
//{
//    return CompareOrder(**p_p1, **p_p2);
//}

/**
* @desc compares two points in term of order
* @return negative, zero or positive value 
*         according to whether the first element 
*         passed to it is less than, equal to or 
*         greater than the second one. 
*/
//int Point2D::CompareOrder(Entity2D ***p_p1, Entity2D ***p_p2)
//{
//    return CompareOrder((Point2D *) **p_p1, (Point2D *) **p_p2);
//}

/**
* @desc compares two points in term of order
* @return negative, zero or positive value 
*         according to whether the first element 
*         passed to it is less than, equal to or 
*         greater than the second one. 
*/
bool Point2D::CompareOrder(Point2D *p2, Point2D *p1)
{

    if (p1->GetY() < p2->GetY())
        return false;
    else if (p1->GetY() == p2->GetY()) {
        if (p1->GetX() < p2->GetX())
            return false;
        else if (p1->GetX() == p2->GetX())
            return false;
    }

    // p1 is greater than p2
    return true;

}


/**
* @desc compares two points in term of order
* @return negative, zero or positive value 
*         according to whether the distance of <p1> to its owner is less than, equal to or 
*         greater than the distance of <p2> to its owner. 
*/
int Point2D::CompareOrderUsingDistanceToOwner(Point2D ***p1, Point2D ***p2)
{
    // if any of the points have no owner entity they cannot be compared
    if ((!(**p1)->_owner_entity) || (!(**p2)->_owner_entity)) return 0;

    Point2D *first_point_owner_p1 = (**p1)->_owner_entity->GetFirstPoint();
    Point2D *first_point_owner_p2 = (**p2)->_owner_entity->GetFirstPoint();
    
    // if any of the points owner entity have no first point computed
    // then the points cannot be compared
    if (!first_point_owner_p1 || !first_point_owner_p2) return 0;

    double sqr_distance_p1 = (**p1)->SquareDistanceTo(first_point_owner_p1);
    double sqr_distance_p2 = (**p2)->SquareDistanceTo(first_point_owner_p2);

    if (sqr_distance_p1<sqr_distance_p2)
        return -1;
    
    if (sqr_distance_p1 > sqr_distance_p2)
        return 1;

    return 0;
}

/*** 
* @return true if points p1 and p2 are ordered, false otherwise
*/
bool Point2D::Ordered(Point2D *p1, Point2D *p2)
{
    if (CompareOrder(p1, p2))
        return false;
    else
        return true;
}

/***
* @desc indicates if this point is collinear with a and b
* @return true if is collinear, false otherwise
* @see O'Rourke, Joseph, "Computational Geometry in C, 2nd Ed.", pp.29
*/
bool Point2D::Collinear(Point2D *a, Point2D *b)
{
    return Area(a, b, this) == 0;
}


/***
* @desc indicates if this point is at left of the directed line from a to b
* @return true if is at left, false otherwise
* @see O'Rourke, Joseph, "Computational Geometry in C, 2nd Ed.", pp.29
*/
bool Point2D::Left(Point2D *a, Point2D *b)
{
    return Area(a,b, this) > 0;
}

/***
* @return true is this point is betwen a and b
* @note c must be collinear with a and b
* @see O'Rourke, Joseph, "Computational Geometry in C, 2nd Ed.", pp.32
*/
bool Point2D::Between(Point2D *a, Point2D *b)
{
    // if this point is not collinear with a and b
    // then it cannot be between this two points
    if (! Collinear(a,b))
        return false;

    if (a->GetX() != b->GetX())
        return ((a->GetX()<=_x) && (_x<=b->GetX())) ||
                ((a->GetX()>=_x) && (_x >= b->GetX()));
    else
        return ((a->GetY()<=_y) && (_y<=b->GetY())) ||
                ((a->GetY()>=_y) && (_y >=b->GetY()));
}

/***
* @return true is this point is betwen a and b,
*        but is different from a and b
* @note c must be collinear with a and b
* @see O'Rourke, Joseph, "Computational Geometry in C, 2nd Ed.", pp.32
*/
bool Point2D::StrictBetween(Point2D *a, Point2D *b)
{
    // first check if this point is between a and b
    if (! Between(a,b))
        return false;

    // if is between, lets check if it is not coincident with
    // one of them
    return (((*a)!=(*this) && (*b)!=(*this)));
}

/***
* @desc performs the rounding of coordinates according with gamma
*/
void Point2D::PerformRounding(double gamma)
{
    Point2D::Round(&_x, &gamma);
    Point2D::Round(&_y, &gamma);
}

/***
* @desc performs the rounding of value pointed by <value> according with 
*       value pointed by <gamma>
*/
void Point2D::Round(double *value, double *gamma)
{
    double v = (*value) / (*gamma);

    double v_ceil = ceil(v);

    if (fabs(v-v_ceil)<=0.5)
        (*value) = v_ceil * (*gamma);
    else
        (*value) = floor(v) * (*gamma);
}
