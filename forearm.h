#ifndef FOREARM_H
#define FOREARM_H

#ifndef CUBE_H
#include "cube.h"
#endif
#ifndef OBJECT_T
#include "object_types.h"
#endif

#ifndef SPHERE_H
#include "sphere.h"
#endif

class _forearm
{
public:
  _forearm();
  void Draw_xxx(_draw_modes_model dm);
  _cube* forearm;
  _sphere*  knee;

  void setD1(float v);
  void setD2(float v);
  float getD1();
  float getD2();


private:
  float tr_inicial = -1.5;
  float fact_escalado = 0.5;  //Para que no se descuadre la pata.
  float fac_lv2_1d;
  float fac_lv2_2d;
};

#endif // aux_H
