#include "pata.h"

_pata::_pata(){}

void _pata::Draw_xxx(float l3_1d,float l3_2d,_draw_modes dm)
{

    //femur
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    femur.Draw_xxx(dm);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,-4,0);
    tibia.Draw_xxx(l3_1d,l3_2d,dm);
    glPopMatrix();

}