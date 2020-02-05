#include "Box2D.h"
#include "./GPMacros.h"

using namespace GraphicalPrimitives2D;

/***
* @desc constructor
* @param another box
*/
Box2D::Box2D(Box2D& box2d) : Entity2D( Entity2D::et_box)
{
  m_point = box2d.GetPoint();
  m_vi = *box2d.GetVi();
  m_vj = *box2d.GetVj();

  CalculateAlignment();
}

/***
* @desc constructor
* @param another box
*/
Box2D::Box2D(double x_min, double y_min, double x_max, double y_max) : Entity2D( Entity2D::et_box)
{
	Point2D p(x_min, y_min);

	m_point = p;
	m_vi = Vector2D(p, x_max-x_min, 0);
	m_vj = Vector2D(p, 0, y_max-y_min);
}

/***
* @desc constructor
* @param point 
* @param vector
* @param vector
*/
Box2D::Box2D(const Point2D& point, const Vector2D&  vi, const Vector2D& vj) : Entity2D(Entity2D::et_box)
{
  m_point = point;
  m_vi = vi;
  m_vj = vj;

  CalculateAlignment();
}

/***
* @desc destructor
*/
Box2D::~Box2D() { }


/***
* @return bounding box of this Box2D
*/
Box2D * Box2D::GetBoundingBox()
{
  Point2D p(GetMinX(), GetMinY());

  return new Box2D(
    p, 
    Vector2D(p,GetMaxX()-GetMinX(),0),
    Vector2D(p,0,GetMaxY()-GetMinY()));
}

/***
* @param pointer to Box2D
* @param pointer to Box2D
* @return bounding box of the two Box2D passed 
*/
Box2D * Box2D::GetBoundingBox(Box2D *box2d_a, Box2D *box2d_b)
{
  if (!box2d_a) {
    if (box2d_b)
      return new Box2D(*box2d_b);
    else
      return nullptr;
  }
  
  if (!box2d_b)
    return new Box2D(*box2d_a);

  double a_min_x=box2d_a->GetMinX();
  double b_min_x=box2d_b->GetMinX();
  double minX = MIN(a_min_x,b_min_x);

  double a_min_y=box2d_a->GetMinY();
  double b_min_y=box2d_b->GetMinY();
  double minY = MIN(a_min_y,b_min_y);
  
  double a_max_x=box2d_a->GetMaxX();
  double b_max_x=box2d_b->GetMaxX();
  double maxX = MAX(a_max_x,b_max_x);

  double a_max_y=box2d_a->GetMaxY();
  double b_max_y=box2d_b->GetMaxY();
  double maxY = MAX(a_max_y,b_max_y);

  Point2D p(minX,minY);

  return new Box2D(p, Vector2D(p,maxX-minX,0), Vector2D(p,0,maxY-minY));
}

/***
* @return maximum x coordinate of this box
*/
double Box2D::GetMaxX()
{
  double x = m_point.GetX();
  double i_dx = x+m_vi.GetDX();
  double j_dx = x+m_vj.GetDX();
  double max_i = MAX(x,i_dx);

  return MAX(max_i,j_dx);
}

/***
* @return maximum y coordinate of this box
*/
double Box2D::GetMaxY()
{
  double y = m_point.GetY();
  double i_dy = y+m_vi.GetDY();
  double j_dy = y+m_vj.GetDY();
  double max_i = MAX(y,i_dy);

  return MAX(max_i,j_dy);
}

/***
* @return minimum x coordinate of this box
*/
double Box2D::GetMinX()
{
  double x = m_point.GetX();
  double i_dx = x+m_vi.GetDX();
  double j_dx = x+m_vj.GetDX();
  double min_i = MIN(x,i_dx);

  return MIN(min_i,j_dx);
}

/***
* @return minimum y coordinate of this box
*/
double Box2D::GetMinY()
{
  double y = m_point.GetY();
  double i_dy = y+m_vi.GetDY();
  double j_dy = y+m_vj.GetDY();
  double min_i = MIN(y,i_dy);

  return MIN(min_i,j_dy);
}



/**
* @desc execute a translation of this box
*/
void Box2D::Translate(double dx, double dy)
{
  m_point.Translate(dx,dy);
}


/**
* @desc scale the box by (sx,sy)
* @note: attention to the box center
*/
void Box2D::Scale(double sx, double sy)
{
  m_point.Scale(sx,sy);
  m_vi.Scale(sx,sy);
  m_vj.Scale(sx,sy);
}

/**
* @desc rotate the box by theta
* @note: attention to the box center
*/
void Box2D::Rotate(double theta)
{
	m_point.Rotate(theta);
	m_vi.Rotate(theta);
	m_vj.Rotate(theta);
}



/**
* @return Point2D representing the box center
*/
Point2D * Box2D::GetCenter()
{
  double x = m_point.GetX()+m_vi.GetDX()/2+m_vj.GetDX()/2;
  double y = m_point.GetY()+m_vi.GetDY()/2+m_vj.GetDY()/2;

  return new Point2D(x,y);
}

/**
* @return witdh of the box 
*/
double Box2D::GetWidth()
{
  return GetMaxX()-GetMinX();
}

/**
* @return box height
*/
double Box2D::GetHeigth()
{
  return GetMaxY()-GetMinY();
}


/***
* @desc determines if box is axes-aligned or not
*/
void Box2D::CalculateAlignment()
{
	m_is_axes_aligned = (m_vi.IsAxisAligned() && m_vj.IsAxisAligned());		
}

/***
* @returns true if this box contains <box>, false otherwise
*/
bool Box2D::Contains(Box2D *box)
{
	if (!box) return false;

	if (m_is_axes_aligned) {
		return (GetMinX()<=box->GetMinX()) && (GetMaxX()>=box->GetMaxX()) &&
			(GetMinY()<=box->GetMinY()) && (GetMaxY()>=box->GetMaxY());		
	} else {
		// TODO: determine this case to use not axes-aligned boxes 
		// for now returns always false
		return false;
	}
}

bool Box2D::Contains(Point2D *p)
{
	if (!p) return false;

	if (m_is_axes_aligned) {
		return (GetMinX()<=p->GetX()) && (GetMaxX()>=p->GetX()) &&
			(GetMinY()<=p->GetY()) && (GetMaxY()>=p->GetY());		
	} else {
		// TODO: determine this case to use not axes-aligned boxes 
		// for now returns always false
		return false;
	}
}

