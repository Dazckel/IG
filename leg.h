#ifndef LEG_H
#define LEG_H

#include "forearm.h"


class _leg{
    
public:
    _leg();
    _sphere* shoulder;
    _cube* femur;
    _forearm* forearm;
    void Draw_xxx(_draw_modes_model dm);

  void setD1(float v);
  void setD2(float v);
  float getD1();
  float getD2();


private:
  float tr_forearm = -4;
  float tr_femur = -2;
  float fact_Sy = 4;  
  float fact_Sx = 0.5;  

  float fac_lv3_1d;
  float fac_lv3_2d;

};

#endif