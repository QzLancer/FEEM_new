#include "Entity2D.h"

#include "Point2D.h"
#include "Box2D.h"

#include "./GPMacros.h"

//#include <wx/arrimpl.cpp>

using namespace GraphicalPrimitives2D;

//WX_DEFINE_OBJARRAY(EntityArray);

/***
* @desc constructor
* @param entity name
*/
Entity2D::Entity2D(entity_type type)
{    
    _p_bounding_box = nullptr;
    _first_point = nullptr;	
	_last_point = nullptr;	
//	_selected = nullptr;
	_type = type;
	_id = 0;
}

/***
* @desc destructor
*/
Entity2D::~Entity2D()
{
    DELETE_OBJECT(_p_bounding_box);	
}

/**
* @desc returns the bounding box of the entity.Calculates it if does nort exist
* @return Box2D entity representing the bounding box
*/
Box2D * Entity2D::GetBoundingBox()
{
	// if bounding box already exists do not calculate bounding box 
    if (!_p_bounding_box)
		CalculateBoundingBox();

    return _p_bounding_box;
}

/**
* @desc compares two entities in term of order
* @return negative, zero or positive value 
*         according to whether the first element 
*         passed to it is less than, equal to or 
*         greater than the second one. 
*/
// int Entity2D::CompareOrder(Entity2D ***p_e1, Entity2D ***p_e2)
// {
//	return Point2D::CompareOrder((**p_e1)->_first_point, (**p_e2)->_first_point);
// }

/***
* @desc Auxiliary method for calculation of areas
* @see O'Rourke, Joseph, "Computational Geometry in C, 2nd Ed.", pp.27
* @return area of triangle defined by points a, b, c 
*/
double Entity2D::Area(Point2D *a, Point2D *b, Point2D *c)
{
	if (a==nullptr || b==nullptr || c==nullptr)
        return 0;

	return (b->GetX() - a->GetX())*(c->GetY()-a->GetY())-
		(c->GetX()-a->GetX())*(b->GetY()-a->GetY());
}

// inline bool Entity2D::IsFirstPoint(Point2D *p)
// {
// 	return (*_first_point)==(*p); 
// }
// 
// inline bool Entity2D::IsLastPoint(Point2D *p)
// {
// 	return (*_last_point)==(*p); 
// }
// 
// /***
// * @return a string containing the text with the type name of the entity
// */
// QString Entity2D::Name(entity_type et)
// {
//     static QString name[] = {
//         "Point",
//         "Line",
//         "Polyline",
//         "Polygon",
//         "Vector",
//         "Unknown"
//     };
// 
//     return name[et];
// }

/***
* @desc forces the axis aligned bounding box to be calculated
*/
void Entity2D::RecalculateBoundingBox()
{
	DELETE_OBJECT(_p_bounding_box); 
	CalculateBoundingBox();
}

