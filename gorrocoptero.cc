#include "gorrocoptero.h"

_gorrocoptero::_gorrocoptero(){}

void _gorrocoptero::Draw_xxx(float l5_d1, float l5_d2,_draw_modes dm){


    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glRotated(l5_d1*50,0,1,0);
    glTranslated(-2.75,0.75,0);
    glScaled(l5_d2*0.2+1,1,1);
    helices.Draw_xxx(dm);
    glPopMatrix();

    glPushMatrix();
    glRotated(l5_d1*50,0,1,0);
    glTranslated(2.75,0.75,0);
    glScaled(l5_d2*0.2+1,1,1);
    helices.Draw_xxx(dm);
    glPopMatrix();

    glPushMatrix();
    glScaled(0.3,1,0.3);
    switch (dm)
    {
    case _draw_modes::CHESS:
        base.draw_chess();
        break;

    case _draw_modes::FILL:
        base.draw_fill();
        break;

    case _draw_modes::POINTS:
        base.draw_point();
        break;

    case _draw_modes::LINES:
        base.draw_line();
        break;
    }
    glPopMatrix();





}