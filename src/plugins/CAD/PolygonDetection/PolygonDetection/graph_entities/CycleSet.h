#if !defined(AFX_CYCLESET_H_INCLUDED)
#define AFX_CYCLESET_H_INCLUDED

#include "Cycle.h"

//#include <wx/arrimpl.cpp>

namespace PolygonDetection {
typedef QVector<Cycle *> CyclesArray;

class CycleSet
{
public:
    void Sort();
    void SelectCycles();
    Cycle * GetCycle(int number);
    int size();

    void AddCycle(Cycle * c);
    CycleSet();
    virtual ~CycleSet();


private:
    CyclesArray * _p_cycles_array;
};
}
#endif // !defined(AFX_CYCLESET_H_INCLUDED)
