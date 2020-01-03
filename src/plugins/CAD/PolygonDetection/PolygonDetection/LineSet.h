#pragma once

#include "Line.h"
//#include <wx/dynarray.h>

namespace PolygonDetection {

typedef QVector<Line*> LinesArray;

class LineSet
{
public:
    LineSet(void);
    ~LineSet(void);

    void Add(Line * line);
    inline int size() { return _lines_array.size();}
    inline Line * Item(int i) {return _lines_array.at(i);}

    bool RemoveIntersections(void);

    void Clear(void);
    bool Normalize(void);
    void Sort(void);

private:
    void RemoveZeroLengthLines(void);
    void RemoveOverlappings(void);
    void CalculateLinesFirstAndLastPoint(void);
    unsigned int DetectIntersections(void);

    LinesArray _lines_array;

    // Performs a scale transformation on lines of this set
    void Scale(double sx, double sy);

    // Performs a translation transformation on lines of this set
    void Translate(double dx, double dy);
};
}
