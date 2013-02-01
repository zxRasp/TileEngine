#include "Collisions.h"

bool isRectIntersect(RECT rc1, RECT rc2)
{
    int rc1right  = rc1.x + rc1.w;
    int rc1bottom = rc1.y + rc1.h;
    int rc2right  = rc2.x + rc2.w;
    int rc2bottom = rc2.y + rc2.h;

    return  rc1.x < rc2right  &&
            rc1right > rc2.x  &&
            rc1.y < rc2bottom &&
            rc1bottom > rc2.y;
}
