#ifndef PATA_H
#define PATA_H

#include "tibia.h"
#include "femur.h"


class _pata{
    
public:
    _pata();
    _femur femur;
    _tibia tibia;
    void Draw_xxx(float l3_1d,float l3_2d,_draw_modes dm);

};

#endif