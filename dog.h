#ifndef DOG_H
#define DOG_H

#include "leg.h"
#include "cylinder.h"

class _dog
{
public:
    _dog();
    vector<_leg *> legs;
    _cylinder *body;
    void Draw_xxx(_draw_modes_model dm);
  void setD1(float v);
  void setD2(float v);

private:
//Factores de las patas delanteras y traseras
//No se modifican a voluntad, sino que su valor se saca a partir 
//del movimiento de las patas, para dar realismo -> el cuerpo sigue a las patas.
    float facD_2d;
    float facT_2d;
};

#endif // DOG_H
