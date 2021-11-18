#ifndef FEMUR_H
#define FEMUR_H

#include "aux2.h"
#include "sphere.h"


class _femur
{
public:
  _femur();
  _aux2 aux2;
  _sphere esfera;
  void Draw_xxx(_draw_modes dm);
};

#endif // FEMUR_H
