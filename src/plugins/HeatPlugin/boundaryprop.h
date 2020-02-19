#ifndef BOUNDARYPROP_H
#define BOUNDARYPROP_H

#include <QString>
#include <project/pf_node.h>

enum BoundaryType{
    EMPTY = 0,
    FIRST = 1,
    SECOND = 2,
    THIRD = 3
};

class CHBoundaryProp
{
public:
    QString name = "";
    BoundaryType type = BoundaryType::EMPTY;
    double Tg = 0;
    double q = 0;
    double h = 0;
    double T0 = 0;
    void reset();
};


#endif // BOUNDARYPROP_H
