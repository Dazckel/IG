#ifndef PERRO_H
#define PERRO_H

#include "pata.h"
#include "aux3.h"

class _perro
{
public:
    _perro();
    _pata pata;
    _aux3 aux3;
    void Draw_xxx(float l3_1d,float l3_2d,float l4_1d,float l4_2d,float l4t_1d,float l4t_2d,_draw_modes dm);

};

#endif // aux_H
