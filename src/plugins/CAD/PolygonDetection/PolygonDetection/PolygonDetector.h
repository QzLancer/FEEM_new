#pragma once

#include "PolygonSet.h"

namespace PolygonDetection {
class PolygonDetector
{
public:
    PolygonDetector(void);
    ~PolygonDetector(void);

    inline int GetLineCount() {return _line_set.size();}
    inline PolygonSet * GetPolygonSet() {return &_polygon_set;}

    static inline bool Silent() {return _silent; }
    static inline void Silent(bool silent) {_silent = silent;}

    static inline bool WasInterrupted() {return _interrupted;}
    static inline bool TimeWasExceeded() {return _time_exceeded; }
    static inline void Interrupt(bool time_exceeded = true) { _interrupted = true; _time_exceeded = time_exceeded; }
    static inline void SetMaxProcessingTime(unsigned long t) { _max_processing_time = t;}
    static inline unsigned long GetMaxProcessingTime() {return _max_processing_time;}

private:
    static bool _silent;
    static bool _interrupted;
    static bool _time_exceeded;
    static unsigned long _max_processing_time;
    LineSet _line_set;
    PolygonSet _polygon_set;

public:
    bool ReadSVGfile(const char * filename);
    void AddLine(double x1, double y1, double x2, double y2);
    void Reset(void);
    bool DetectPolygons(void);
    inline void SimplifyPolygons(double smaller_polygon_length) {	_polygon_set.Simplify(smaller_polygon_length);}
    //		inline void DetermineTopologicalRelationships() {_polygon_set.DetermineTopologicalRelationships();};
    bool CreateSVGwithPolygons(const char * filename);
};
}
