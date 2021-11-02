
#include "jauria.h"


_jauria::_jauria(){

}

void _jauria::Draw_xxx(float delanteras,float traseras,float cuerpo_rot,float fact_traslacionX,float fact_traslacionY,float fact_rotacion){

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslated(-5-fact_traslacionX,fact_traslacionY,0);
    glRotated(fact_rotacion,0,1,0);
    perro.Draw_xxx(delanteras,traseras,cuerpo_rot);
    glPopMatrix();


    glPushMatrix();
    glTranslated(5+fact_traslacionX,fact_traslacionY,0);
    glRotated(fact_rotacion,0,1,0);
    perro.Draw_xxx(delanteras,traseras,cuerpo_rot);
    glPopMatrix();
}