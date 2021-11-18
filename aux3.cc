#include "aux3.h"

_aux3::_aux3()
{
}
void _aux3::Draw_xxx(_draw_modes dm)
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //
    glScaled(9, 1.5, 4);

    switch (dm)
    {
    case _draw_modes::CHESS:
        Cube.draw_chess();
        break;

    case _draw_modes::FILL:
        Cube.draw_fill();
        break;

    case _draw_modes::POINTS:
        Cube.draw_point();
        break;

    case _draw_modes::LINES:
        Cube.draw_line();
        break;
    }

    glPopMatrix();
}
