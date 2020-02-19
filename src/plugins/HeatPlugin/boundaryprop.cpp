#include "boundaryprop.h"

void CHBoundaryProp::reset()
{
    name = "";
    type = BoundaryType::EMPTY;
    Tg = 0;
    q = 0;
    h = 0;
    T0 = 0;
}
