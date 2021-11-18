#include "femur.h"
#include "sphere.h"

_femur::_femur()
{
}
void _femur::Draw_xxx(_draw_modes dm)
{

    glMatrixMode(GL_MODELVIEW);
    //Pata abajo
    glPushMatrix();

    glTranslated(0, -2, 0);
    aux2.Draw_xxx(dm);
    glPopMatrix();

    //Rodilla
    glPushMatrix();
    glScaled(0.45, 0.45, 0.45);
    switch (dm)
    {
    case _draw_modes::CHESS:
        esfera.draw_chess();
        break;

    case _draw_modes::FILL:
        esfera.draw_fill();
        break;

    case _draw_modes::POINTS:
        esfera.draw_point();
        break;

    case _draw_modes::LINES:
        esfera.draw_line();
        break;
    }
    glPopMatrix();
}
