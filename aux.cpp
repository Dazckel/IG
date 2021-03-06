#include "aux.h"

_aux::_aux()
{
}
void _aux::Draw_xxx(_draw_modes dm){

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //
    glScaled(0.5,3,0.5);
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
