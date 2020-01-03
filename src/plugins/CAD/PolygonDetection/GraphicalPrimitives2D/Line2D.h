#pragma once

#if !defined(LINE2D_H_DEFINED)
#define LINE2D_H_DEFINED

#include "Point2D.h"	// Added by ClassView

//#include <wx/image.h>
//#include <wx/colour.h>

namespace GraphicalPrimitives2D {
class Polygon2D; // forward declaration because of 'Minkowsky Sum'

class Line2D : public Entity2D
{
public:
    //		bool WriteImage(wxImage *dest, const wxColour &colour=*wxBLACK, double factor=1.0, double dx=0.0, double dy=0.);
    Line2D(double x1, double y1, double x2, double y2);

    virtual void Rotate(double theta);
    virtual void Translate(double dx, double dy);
    virtual void Scale(double sx, double sy);

    static bool Equal(Line2D * line_1, Line2D * line_2);
    static double Distance(Point2D *endpoint_1, Point2D *endpoint_2, Point2D * p, Point2D * nearest_point = nullptr);
    inline double Distance(Point2D * p, Point2D * nearest_point=nullptr);

    inline bool Contains(Point2D *point) { return Contains(this, point); }
    static bool Contains(Line2D * line, Point2D *point);
    inline bool Contains(Line2D * line) { return Contains(this, line); }
    static bool Contains(Line2D *line_1, Line2D * line_2);

    inline bool StrictContains(Point2D *point) { return StrictContains(this, point); }
    static bool StrictContains(Line2D * line, Point2D *point);
    inline bool StrictContains(Line2D * line) { return StrictContains(this, line); }
    static bool StrictContains(Line2D *line_1, Line2D * line_2);

    static Line2D * SimplifiedLine( Line2D * line_1, Line2D * line_2);
    static bool Overlapping(Line2D * line_1, Line2D * line_2);
    static bool StrictOverlapping(Line2D * line_1, Line2D * line_2);

    virtual void PerformRounding(double gamma);

    static inline bool CompareOrder(Entity2D *p_e1, Entity2D *p_e2) { return CompareOrder((Line2D*)p_e2, (Line2D*)p_e1); }
    static bool CompareOrder(Line2D* p_line2, Line2D* p_line1);

    Point2D * IntersectionPoint(Line2D * line);
    bool Intersects( Line2D * line);
    bool IntersectsProper(Line2D * line);

    Point2D * PointAt(double x, double y);
    Point2D * GetOtherPoint( Point2D * p);
    virtual void CalculateFirstAndLastPoint();
    virtual inline Point2D * GetStartPoint() { return &_start_point; }
    virtual inline Point2D * GetEndPoint() { return &_end_point; }

    //		void SetStartX(double x);
    //		void SetStartY(double y);
    //		void SetEndX(double x);
    //		void SetEndY(double y);

    Line2D();
    Line2D(Line2D * line);
    Line2D(Point2D * start_point, Point2D * end_point);
    virtual ~Line2D();

    double GetMaxX(void);
    double GetMaxY(void);
    double GetMinX(void);
    double GetMinY(void);

private:
    //		static bool Bresenham(wxImage *dest, int x1, int y1, int x2, int y2, const wxColour &colour);
    Point2D _start_point;
    Point2D _end_point;
};
}

#endif 
