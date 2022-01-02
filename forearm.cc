#include "forearm.h"

_forearm::_forearm()
{
    fac_lv2_1d = 0;
    fac_lv2_2d = 0;
    forearm = new _cube();
    knee = new _sphere();
}
void _forearm::Draw_xxx(_draw_modes_model dm)
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotated(fac_lv2_1d, 0, 0, 1);
    glTranslated(0, tr_inicial - fac_lv2_2d * fact_escalado, 0);
    glScaled(fact_escalado, 3 + fac_lv2_2d, fact_escalado);
    //Dibujamos el antebrazo
    switch (dm)
    {
    case _draw_modes_model::CHESS:
        forearm->draw_chess();
        break;

    case _draw_modes_model::FILL:
        if(forearm->pick_model)
            forearm->draw_line();
        forearm->draw_fill();
        break;

    case _draw_modes_model::POINTS:
        forearm->draw_point();
        break;

    case _draw_modes_model::LINES:
        forearm->draw_line();
        break;
    case _draw_modes_model::SMOOTH:
        forearm->draw_lighted_smooth(_object::OBJECT_CYLINDER);
        break;
    case _draw_modes_model::FLAT:
        forearm->draw_lighted_flat();
        break;
    case _draw_modes_model::TEXTURE:
        forearm->draw_texture();
        break;
    case _draw_modes_model::SELECTION:
        forearm->draw_selection(forearm->id_ini);
        break;
    }
    glPopMatrix();

    glPushMatrix();
    //Dibujamos la rodilla
    switch (dm)
    {
    case _draw_modes_model::CHESS:
        knee->draw_chess();
        break;

    case _draw_modes_model::FILL:
        if(knee->pick_model)
            knee->draw_line();
        knee->draw_fill();
        break;

    case _draw_modes_model::POINTS:
        knee->draw_point();
        break;

    case _draw_modes_model::LINES:
        knee->draw_line();
        break;
    case _draw_modes_model::SMOOTH:
        knee->draw_lighted_smooth(_object::OBJECT_CYLINDER);
        break;
    case _draw_modes_model::FLAT:
        knee->draw_lighted_flat();
        break;
    case _draw_modes_model::TEXTURE:
        knee->draw_texture();
        break;
    case _draw_modes_model::SELECTION:
        knee->draw_selection(knee->id_ini);
        break;
    }
    glPopMatrix();
}

void _forearm::setD1(float v)
{
    fac_lv2_1d += v;
}
void _forearm::setD2(float v)
{
    fac_lv2_2d += v;
}

float _forearm::getD1()
{
    return fac_lv2_1d;
}
float _forearm::getD2()
{
    return fac_lv2_2d;
}