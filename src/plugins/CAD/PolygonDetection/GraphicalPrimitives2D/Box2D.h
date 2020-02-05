#if !defined(BOX2D_H)
#define BOX2D_H

#include "Point2D.h"
#include "Vector2D.h"

//#define BOX2D_LIMITS_COORDINATES(b) b->GetMinX(),b->GetMaxX(),b->GetMinY(),b->GetMaxY()

namespace GraphicalPrimitives2D {
	class Box2D : public Entity2D
	{
	public:
		virtual void Rotate(double theta);
		bool Contains(Point2D * p);
		bool Contains(Box2D *box);
		
		double GetHeigth();
		double GetWidth();
		Point2D * GetCenter();
		
		virtual void Scale(double sx, double sy);
		virtual void Translate(double dx, double dy);

		double GetMaxX();
		double GetMaxY();
		double GetMinX();
		double GetMinY();

		inline Point2D * GetPoint() { return &m_point; };  
		inline Vector2D * GetVi() { return &m_vi; };  
		inline Vector2D * GetVj() { return &m_vj; };  

		Box2D * GetBoundingBox();
		static Box2D * GetBoundingBox( Box2D *box2d_a, Box2D *box2d_b);

		Box2D(Box2D& box2D);
		Box2D(const Point2D& point, const Vector2D&  vi, const Vector2D& vj);
		Box2D(double x_min, double y_min, double x_max, double y_max);

		virtual ~Box2D();

	private:
		void CalculateAlignment();
		Point2D m_point;
		Vector2D m_vi;
		Vector2D m_vj;

		Point2D m_center; 

		bool m_is_axes_aligned;

	};
}
#endif // !defined(BOX2D_H)
