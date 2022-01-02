#ifndef GORROCOPTER_H
#define GORROCOPTER_H

#include "cone.h"
#include "helix.h"
#ifndef OBJECT_T
#include "object_types.h"
#endif

class _gorrocopter
{
public:
    _gorrocopter();
    void Draw_xxx(_draw_modes_model);
    vector<_helix *> helixs;
    _cone *base;

    void setD1(float v);
    void setD2(float v);
    float getD1();
    float getD2();

private:
    float d1;
    float d2;
};

#endif //GORROCOPTER_H