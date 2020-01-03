#pragma once

#if !defined(POINT2D_H_INCLUDED)
#define POINT2D_H_INCLUDED

#include "Entity2D.h"

#define SCALE_2D(obj,s) { (obj)->Scale(s,s); }
#define POINT2D_AS_XY(p) ((GraphicalPrimitives2D::Point2D *)p)->GetX(), ((GraphicalPrimitives2D::Point2D *)p)->GetY()

#include <QVector>

namespace GraphicalPrimitives2D {
class Point2D : public Entity2D
{
public:
    static int CompareOrderUsingDistanceToOwner(Point2D ***p1, Point2D ***p2);
    virtual void Rotate(double theta);
    double SquareDistanceTo(Point2D *p);
    virtual void PerformRounding(double gamma);

    bool Between(Point2D *a, Point2D *b);
    bool StrictBetween(Point2D *a, Point2D *b);
    bool Left(Point2D * a, Point2D * b);
    bool Collinear(Point2D *a, Point2D *b);

    static bool Ordered(Point2D * p1, Point2D * p2);
    static bool CompareOrder(Point2D * p2, Point2D * p1);

    // the next two methods are used to sort arrays
//    static int CompareOrder(Point2D *** p_p1, Point2D *** p_p2);
//    static int CompareOrder(Entity2D *** p_p1, Entity2D *** p_p2);

    inline Entity2D * GetOwnerEntity() { return _owner_entity;}
    inline void SetOwnerEntity(Entity2D * owner_entity) { _owner_entity = owner_entity;}

    virtual void CalculateFirstAndLastPoint();

    void Set(Point2D * p);

    double DistanceTo(Point2D * p);
    virtual void Translate(double dx,double dy);
    virtual void Scale(double sx, double sy);

    inline double GetX() { return _x; }
    inline double GetY() { return _y; }

    inline void SetX(double x) { _x=x; }
    inline void SetY(double y) { _y=y; }

    //inline int GetCoincidentPointsCount() { return _coincident_points_counter;};
    //inline int IncrementCoincidentPointsCount() { return (_coincident_points_counter++);};

    inline void SetIndex(int index) { _index=index; }
    inline int GetIndex() { return _index; }

    bool operator==(const Point2D &p);
    bool operator!=(const Point2D &p);

    void operator=(const Point2D &p);

    Point2D(void);
    Point2D(Point2D * p);
    Point2D(double x, double y);
    virtual ~Point2D();

private:
    void Initialize(double x, double y);
    static void Round(double *value, double * gamma);
    Entity2D * _owner_entity;
    double _x;
    double _y;
    int _index;
    int _coincident_points_counter;
};

typedef QVector<Point2D*> PointArray;
}

#endif // !defined(POINT2D_H_INCLUDED)
