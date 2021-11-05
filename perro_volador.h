#ifndef PERROVOLADOR_H
#define PERROVOLADOR_H

#include "gorrocoptero.h"
#include "perro.h"
class _perro_volador{
    public:
        _perro_volador();
        void Draw_xxx(float l3_1d,float l3_2d,float l4d_1d,float l4d_2d,float l4t_1d,float l4t_2d,float l5_1d,float l5_2d);
        _perro perro;
        _gorrocoptero gorrocoptero;
};


#endif //PERROVOLADOR_H