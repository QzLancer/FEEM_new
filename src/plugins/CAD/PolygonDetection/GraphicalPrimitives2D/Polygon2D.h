/*
+--------------------------------------------------------------------+
| Polygon2D.h: interface for the Polygon2D class.                    |
+--------------------------------------------------------------------+
|                                                                    |
| Author : Alfredo Ferreira Jr.                                      |
| E-mail : alfredo.ferreira.jr@inesc-id.pt                           |
| Website: http://immi.inesc-id.pt/~afj                              |
|                                                                    |
| Version: 2.00                                                      |
| Created: Jun 2003                                                  |
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
| Copyright (c) 2003-2008 INESC-ID                                        |
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

#if !defined(POLYGON2D_H)
#define POLYGON2D_H

#include "Polyline2D.h"

//#include <wx/string.h>

namespace GraphicalPrimitives2D {
class Polygon2D : public Polyline2D
{
public:
    Polygon2D(Polygon2D * polygon);
    Polygon2D();
    virtual ~Polygon2D();

    //		inline void SetConvex(bool convex) { _is_convex = convex; };
    //		inline bool IsConvex() { return _is_convex; };

    bool Contains(Line2D * line, bool strict=false);
    bool Contains(Entity2D * entity, bool strict=false);
    bool Disjoint(Polygon2D *polygon);
    bool Minus(Polygon2D * p);

    // 		void FindSiblings();
    // 		void FindSons();
    //
    // 		static int CompareDeepness(Polygon2D ***p_p1, Polygon2D ***p_p2);
    //
    // 		inline int GetDeepness() {
    // 			return _container_polygons?_container_polygons->size():0;
    // 		};

    //		QString GetTopologyFileEntry();

    //		inline void AddSibling(Polygon2D *p) { AddPolygonToArray(p, &_sibling_polygons); };
    //		inline void AddSon(Polygon2D * p) { AddPolygonToArray(p, &_son_polygons); };

    //		inline void SetParent(Polygon2D * p) { _parent_polygon = p; };
    //		inline Polygon2D * GetParent() { return _parent_polygon; };

    //		inline void AddAdjacent(Polygon2D *p) { AddPolygonToArray(p, &_adjacent_polygons); };
    //		inline void AddContained(Polygon2D * p) { AddPolygonToArray(p, &_contained_polygons); };
    //		inline void AddContainer(Polygon2D * p) { AddPolygonToArray(p, &_container_polygons); };

    static bool IsAdjacent( Polygon2D *p1, Polygon2D *p2, bool strict=false);
    inline bool IsAdjacent(Polygon2D *p, bool strict=false) { return IsAdjacent(this, p, strict); }
    bool Contains(Polyline2D *polyline, bool strict=false);
    bool Contains(Point2D * point, bool strict=false);
    virtual inline bool IsClosed() { return true; }

private:
    //		bool _is_convex;
    void Initialize();
    bool ConsecutiveVertices(Point2D *v1, Point2D* v2, short * index_increment = nullptr);
    static bool SingleAdjacency(Polygon2D *p1, Polygon2D *p2, int *i, int* j, long *length);
    //		static bool Siblings(Polygon2D* p1, Polygon2D* p2);

    //		void AddPolygonToArray(Polygon2D * p, EntityArray ** a);
    double _area;

    //		Polygon2D * _parent_polygon;

    //		EntityArray * _son_polygons;
    //		EntityArray * _sibling_polygons ;

    //		EntityArray * _container_polygons;
    //		EntityArray * _contained_polygons;
    //		EntityArray * _adjacent_polygons ;
};
}

#endif // !defined(POLYGON2D_H)
