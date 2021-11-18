#ifndef TIBIA_H
#define TIBIA_H

#include "aux.h"
#include "sphere.h"


class _tibia
{
public:
  _tibia();
  _aux aux;
  _sphere esfera;
  void Draw_xxx(float l3_1d,float l3_2d,_draw_modes dm);
};

#endif // TIBIA_H
