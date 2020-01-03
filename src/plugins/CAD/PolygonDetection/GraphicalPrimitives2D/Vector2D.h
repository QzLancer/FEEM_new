/*
+--------------------------------------------------------------------+
| Vector2D.h: interface for the Vector2D class.                      |
+--------------------------------------------------------------------+
|                                                                    |
| Author : Alfredo Ferreira Jr.                                      |
| E-mail : alfredo.ferreira.jr@inesc-id.pt                           |
| Website: http://immi.inesc-id.pt/~afj                              |
|                                                                    |
| Version: 1.00                                                      |
| Created: Jan 2003                                                  |
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
| Copyright (c) 2003 INESC-ID                                        |
|                                                                    |
|   The copyright to the computer program(s) herein is the property  |
| of INESC-ID, Portugal. The program(s) may be used and/or copied    |
| only with the written permission of INESC-ID or in accordance with |
| the terms and conditions stipulated in the agreement/contract      |
| under which the program(s) have been supplied.                     |
|                                                                    |
+--------------------------------------------------------------------+
*/

#pragma once

#if !defined(VECTOR2D_H_INCLUDED)
#define VECTOR2D_H_INCLUDED

#include "Point2D.h"

namespace GraphicalPrimitives2D {
	class Vector2D : public Entity2D
	{
	public:
		virtual void Rotate(double theta);
		static double dot(Vector2D *u,  Vector2D *v);

		bool IsAxisAligned();
		virtual void Scale(double sx, double sy);
		virtual void Translate( double dx, double dy);
		Vector2D();
		Vector2D(const Point2D& point, double dx, double dy);
		Vector2D(Point2D& start_point, Point2D& point);
		virtual ~Vector2D();
	  
		Vector2D & operator+=(const Vector2D &v);
		Vector2D operator+(const Vector2D &v);
		Vector2D operator*(const double &c);


		inline double GetDX() { return _dx; };
		inline double GetDY() { return _dy; };

	private:
	Point2D _point;
	double _dx;
	double _dy;
	};
}

#endif // !defined(VECTOR2D_H_INCLUDED)
