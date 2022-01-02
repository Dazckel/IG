#include "leg.h"

_leg::_leg()
{
    forearm = new _forearm;
    shoulder = new _sphere;
    femur = new _cube;
    fac_lv3_1d = 0;
    fac_lv3_2d = 0;
}

void _leg::Draw_xxx(_draw_modes_model dm)
{
    //Factores para hacer que el movimiento parezca real
    // y no se descuadre al -> al mover las patas el cuerpo
    //no se descuadrará
    float fact_trY = (sin(45) * 2.8) / 45;
    float fact_trX = (sin(45) * 0.3) / 45;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslated(fac_lv3_2d * fact_trX, fac_lv3_2d * fact_trY,0 );
    glRotated(fac_lv3_1d, 0, 0, 1);



    glPushMatrix();
    glTranslated(0, tr_femur, 0);
    glScaled(fact_Sx, fact_Sy, fact_Sx);
    switch (dm)
    {
    case _draw_modes_model::CHESS:
        femur->draw_chess();
        break;

    case _draw_modes_model::FILL:
        if (femur->pick_model)
            femur->draw_line();
        femur->draw_fill();
        break;

    case _draw_modes_model::POINTS:
        femur->draw_point();
        break;

    case _draw_modes_model::LINES:
        femur->draw_line();
        break;
    case _draw_modes_model::SMOOTH:
        femur->draw_lighted_smooth(_object::OBJECT_SPHERE);
        break;
    case _draw_modes_model::FLAT:
        femur->draw_lighted_flat();
        break;
    case _draw_modes_model::TEXTURE:
        femur->draw_texture();
        break;
    case _draw_modes_model::SELECTION:
        femur->draw_selection(femur->id_ini);
        break;
    }
    glPopMatrix();

    //Rodilla
    glPushMatrix();
    switch (dm)
    {
    case _draw_modes_model::CHESS:
        shoulder->draw_chess();
        break;

    case _draw_modes_model::FILL:
        if (shoulder->pick_model)
            shoulder->draw_line();
        shoulder->draw_fill();
        break;

    case _draw_modes_model::POINTS:
        shoulder->draw_point();
        break;

    case _draw_modes_model::LINES:
        shoulder->draw_line();
        break;
    case _draw_modes_model::SMOOTH:
        shoulder->draw_lighted_smooth(_object::OBJECT_SPHERE);
        break;
    case _draw_modes_model::FLAT:
        shoulder->draw_lighted_flat();
        break;
    case _draw_modes_model::TEXTURE:
        shoulder->draw_texture();
        break;
    case _draw_modes_model::SELECTION:
        shoulder->draw_selection(shoulder->id_ini);
        break;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, tr_forearm, 0);
    forearm->Draw_xxx(dm);
    glPopMatrix();

    glPopMatrix();
}

void _leg::setD1(float v)
{
    fac_lv3_1d += v;
}
void _leg::setD2(float v)
{
    fac_lv3_2d += v;
}

float _leg::getD1()
{
    return fac_lv3_1d;
}
float _leg::getD2()
{
    return fac_lv3_2d;
}