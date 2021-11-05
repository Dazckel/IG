#include "pata.h"

_pata::_pata(){}

void _pata::Draw_xxx(float l3_1d,float l3_2d)
{

    //femur
    glMatrixMode(GL_MODELVIEW);

    femur.Draw_xxx(0,0);

    //tibia
    glPushMatrix();
    femur.Draw_xxx(0,0);
    glTranslated(0,-3,0);
    tibia.Draw_xxx(l3_1d,l3_2d);
    glPopMatrix();

}