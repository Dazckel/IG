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
    void Draw_xxx(float factor,bool dp,bool dn,bool tp,bool tn);
};

#endif // aux_H
