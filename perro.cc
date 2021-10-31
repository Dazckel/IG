#include "perro.h"


_perro::_perro()
{
}
void _perro::Draw_xxx(float factor){

    double ang = 45;

    float fact_y = (1.5*sin(ang)) /ang;
    float fact_x = 1.5*cos(ang) /ang;


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //PATA DELANTERA +
    glTranslated(2,0,2);
    aux2.Draw_xxx(factor);


    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //PATA DELANTERA -
    glTranslated(2,0,-2);
    aux2.Draw_xxx(factor);

    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();


    //PATA TRASERA +
    glTranslated(-2,0,2);
    aux2.Draw_xxx(factor);
    glPopMatrix();



    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //PATA TRASERA -
    glTranslated(-2,0,-2);
    aux2.Draw_xxx(factor);
    glPopMatrix();

    glPushMatrix();
    glTranslated(fact_x*factor,2.25*sin(ang)+fact_y*factor,0);
    aux3.Draw_xxx();
    glPopMatrix();
}
