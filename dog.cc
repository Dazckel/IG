#include "dog.h"

_dog::_dog()
{
    facD_2d = 0;
    facT_2d = 0;
    legs.resize(4);

    for (int i = 0; i < 4; i++)
        legs[i] = new _leg;
    body = new _cylinder;
}
void _dog::Draw_xxx(_draw_modes_model dm)
{

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glTranslated(2, 0, 2);

    legs[0]->Draw_xxx(dm);

    glPopMatrix();

    glPushMatrix();

    glTranslated(2, 0, -2);

    legs[1]->Draw_xxx(dm);

    glPopMatrix();

    glPushMatrix();

    glTranslated(-2, 0, 2);
    legs[2]->Draw_xxx(dm);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2, 0, -2);
    legs[3]->Draw_xxx(dm);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,facD_2d/45+facT_2d/45,0);
    glRotated(facD_2d-facT_2d,0,0,1);

    glScaled(9, 1.5, 4);
    switch (dm)
    {
    case _draw_modes_model::CHESS:
        body->draw_chess();
        break;

    case _draw_modes_model::FILL:
        if (body->pick_model)
            body->draw_line();
        body->draw_fill();
        break;

    case _draw_modes_model::POINTS:
        body->draw_point();
        break;

    case _draw_modes_model::LINES:
        body->draw_line();
        break;
    case _draw_modes_model::SMOOTH:
        body->draw_lighted_smooth(_object::OBJECT_SPHERE);
        break;
    case _draw_modes_model::FLAT:
        body->draw_lighted_flat();
        break;
    case _draw_modes_model::TEXTURE:
        body->draw_texture();
        break;
    case _draw_modes_model::SELECTION:
        body->draw_selection(body->id_ini);
        break;
    }
    glPopMatrix();
}

void _dog::setD1(float v)
{
    facD_2d = v;
}
void _dog::setD2(float v)
{
    facT_2d = v;
}
