#include "gorrocopter.h"

_gorrocopter::_gorrocopter()
{
    helixs.resize(2);
    helixs[0] = new _helix;
    helixs[1] = new _helix;
    base = new _cone;

    d1 = 0;
    d2 = 0;
}

void _gorrocopter::Draw_xxx(_draw_modes_model dm)
{

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glRotated(d1 * 50, 0, 1, 0);
    glTranslated(-2, 1, 0.45);
    glScaled(d2 * 0.2 + 1, 1, 1);
    helixs[0]->Draw_xxx(dm);
    glPopMatrix();

    glPushMatrix();
    glRotated(d1 * 50, 0, 1, 0);
    glTranslated(2, 1, 0.45);
    glScaled(d2 * 0.2 + 1, 1, 1);
    helixs[1]->Draw_xxx(dm);
    glPopMatrix();

    glPushMatrix();
    glScaled(0.5, 2, 0.5);
    switch (dm)
    {
    case _draw_modes_model::CHESS:
        base->draw_chess();
        break;

    case _draw_modes_model::FILL:
        if (base->pick_model)
            base->draw_line();
        base->draw_fill();
        break;

    case _draw_modes_model::POINTS:
        base->draw_point();
        break;

    case _draw_modes_model::LINES:
        base->draw_line();
        break;
    case _draw_modes_model::SMOOTH:
        base->draw_lighted_smooth(_object::OBJECT_CYLINDER);
        break;
    case _draw_modes_model::FLAT:
        base->draw_lighted_flat();
        break;
    case _draw_modes_model::TEXTURE:
        base->draw_texture();
        break;
    case _draw_modes_model::SELECTION:
        base->draw_selection(base->id_ini);
        break;
    }
    glPopMatrix();
}

void _gorrocopter::setD1(float v)
{
    d1 += v;
}
void _gorrocopter::setD2(float v)
{
    d2 += v;
}

float _gorrocopter::getD1()
{
    return d1;
}
float _gorrocopter::getD2()
{
    return d2;
}