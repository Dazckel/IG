#include "helice.h"

_helice::_helice(){}

void _helice::Draw_xxx(_draw_modes dm)
{

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glScaled(4.5,0,1);
    switch (dm)
    {
    case _draw_modes::CHESS:
        helice.draw_chess();
        break;

    case _draw_modes::FILL:
        helice.draw_fill();
        break;

    case _draw_modes::POINTS:
        helice.draw_point();
        break;

    case _draw_modes::LINES:
        helice.draw_line();
        break;
    }
    glPopMatrix();
}