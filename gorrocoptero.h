#ifndef GORROCOPTERO
#define GORROCOPTERO



#ifndef CYLINDER_H
#include "cylinder.h"
#endif
#include "helice.h"

class _gorrocoptero{
    public:
        _gorrocoptero();
        void Draw_xxx(float l5_d1, float l5_d2,_draw_modes);
        _helice helices;
        _cylinder base;
};



#endif //GORROCOPTERO