#ifndef PERRO_H
#define PERRO_H

#include "cube.h"
#include "pata.h"
#include "aux3.h"
#include "cabeza.h"


class _perro
{
public:
    _perro();
    _pata pata;
    _aux3 aux3;
    _cabeza cabeza;
    void Draw_xxx(float l3_1d,float l3_2d,float l4_1d,float l4_2d,float l4t_1d,float l4t_2d,float l5_1d,float l5_2d);

    //void idle(int d, int t, int c);
};

#endif // aux_H
