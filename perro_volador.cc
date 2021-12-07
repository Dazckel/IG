#include "perro_volador.h"

_perro_volador::_perro_volador() {}

void _perro_volador::Draw_xxx(float l3_1d, float l3_2d, float l4d_1d, float l4d_2d, float l4t_1d, float l4t_2d, float l5_1d, float l5_2d, _draw_modes dm)
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslated(0, 0.05 * l5_1d + 7, 0);

    perro.Draw_xxx(l3_1d, l3_2d, l4d_1d, l4d_2d, l4t_1d, l4t_2d, dm);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 0.05 * l5_1d + 8.25, 0);
    glTranslated(0,l4d_2d / 45 + l4t_2d / 45, 0);
    glRotated(l4d_2d - l4t_2d, 0, 0, 1);
    gorrocoptero.Draw_xxx(l5_1d, l5_2d, dm);
    glPopMatrix();



}