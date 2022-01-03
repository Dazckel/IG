#include "dogocopter.h"

_dogocopter::_dogocopter()
{
    rot  = 0;
    tr = 0;
    dog = new _dog;
    gorrocopter = new _gorrocopter;
}

void _dogocopter::Draw_xxx(_draw_modes_model dm)
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslated(0, 0.05 * tr + 7, 0);

    dog->Draw_xxx(dm);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 0.05 * tr + 8.75, 0);
    glRotated(rot, 0, 0, 1); //Cuando el perro se inclina, el gorrocoptero tmbn
    gorrocopter->Draw_xxx(dm);
    glPopMatrix();
}

void _dogocopter::setD1(float v)
{
    tr = v;
}

void _dogocopter::setD2(float v)
{
    rot = v;
}