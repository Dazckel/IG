#ifndef PERRO_H
#define PERRO_H

#include "cube.h"
#include "aux2.h"
#include "aux3.h"


class _perro
{
public:
    _perro();
    _aux2 aux2;
    _aux3 aux3;
    _sphere cabeza;
    void Draw_xxx(float delanteras,float traseras,float cuerpo_rot);

    void idle(int d, int t, int c);
};

#endif // aux_H
