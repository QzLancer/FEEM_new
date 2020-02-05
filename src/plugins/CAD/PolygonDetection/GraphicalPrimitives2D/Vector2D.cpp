#include "Vector2D.h"

#include ".\GPMacros.h"

using namespace GraphicalPrimitives2D;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/***
* @desc constructor 
*/
Vector2D::Vector2D() : Entity2D( Entity2D::et_vector)
{
  _dx = 0;
  _dy = 0;
}

/***
* @desc constructor 
* @param origin point
* @param x component
* @param y component
*/
Vector2D::Vector2D(const Point2D& point, double dx, double dy) : Entity2D(Entity2D::et_vector)
{
  _point = point;
  _dx = dx;
  _dy = dy;
}

/***
* @desc constructor 
* @param origin point
* @param end point
*/
Vector2D::Vector2D(Point2D& start_point, Point2D& end_point) : Entity2D(Entity2D::et_vector)
{
  _point = start_point;

  _dx=end_point.GetX()-start_point.GetX();
  _dy=end_point.GetY()-start_point.GetY();
}

/***
* @desc destructor
*/
Vector2D::~Vector2D()
{

}

/***
* @desc operator += override 
*/
Vector2D & Vector2D::operator +=(const Vector2D & v)
{
  /* TODO: Nao se podem somar vectores que nao tenham mesma origem */
  _dx += v._dx;
  _dy += v._dy;

  return *this;
}

/***
* @desc operator + override 
*/
Vector2D Vector2D::operator +(const Vector2D & v)
{
  Vector2D result = *this;
  result += v;
  return result;
}


/***
* @desc operator * override 
*/
Vector2D Vector2D::operator *(const double & c)
{
  Vector2D result = *this;
  
  result._dx*=c;
  result._dy*=c;

  return result;
}

/***
* @desc execute a translation of (dx,dy) on this vector
*/
void Vector2D::Translate(double dx, double dy)
{
  _point.Translate(dx,dy);
}


/***
* @desc execute a scale of (sx,sy) on this vector
*/
void Vector2D::Scale(double sx, double sy)
{
  _point.Scale(sx,sy);
  _dx*=sx;
  _dy*=sy;
}

/***
* @desc execute a rotation of theta on this vector
*/
void Vector2D::Rotate(double theta)
{	
	Point2D * p = new Point2D(_point.GetX()+GetDX(), _point.GetY()+GetDY());
	_point.Rotate(theta);
	p->Rotate(theta);

	_dx = p->GetX()-GetDX();
	_dy = p->GetY()-GetDY();

	DELETE_OBJECT(p);
}

/***
* @return true if vector is aligned with one axis, false otherwise
*/
bool Vector2D::IsAxisAligned()
{
	return (GetDX()==0 || GetDY()==0);
}

/***
* @return the dot product of vectors u and v
*/
double Vector2D::dot(Vector2D *u, Vector2D *v)
{
	return (u->_dx*v->_dx+u->_dy*v->_dy);
}


