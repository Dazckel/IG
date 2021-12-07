#include "tibia.h"
#include "sphere.h"

_tibia::_tibia()
{
}
void _tibia::Draw_xxx(float l3_1d,float l3_2d,_draw_modes dm){


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //Pata abajo
    glPushMatrix();
    //1.5 para que esté 3u por debajo

    glRotated(l3_1d,0,0,1);
    glTranslated(0,-1.5-l3_2d*1.5,0);
    glScaled(1,1+l3_2d,1);
    aux.Draw_xxx(dm);
    glPopMatrix();

    //Rodilla
    glPushMatrix();
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
    case _draw_modes::SMOOTH:
        esfera.draw_lighted_smooth(_object::OBJECT_SPHERE);
        break;
    case _draw_modes::FLAT:
        esfera.draw_lighted_flat();
        break;
    }
    glPopMatrix();





}
