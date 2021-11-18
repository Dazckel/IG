#include "perro.h"



_perro::_perro()
{
}
void _perro::Draw_xxx(float l3_1d,float l3_2d,float l4d_1d,float l4d_2d,float l4t_1d,float l4t_2d,_draw_modes dm){

  glMatrixMode(GL_MODELVIEW);

    
    float fact_trY = (sin(45)*2.8)/45;
    float fact_trX = (sin(45)*0.3)/45;
    glPushMatrix();

    //PATA DELANTERA +
    glTranslated(2+l4d_2d*fact_trX,l4d_2d*fact_trY,2);
    glRotated(l4d_1d,0,0,1);
    pata.Draw_xxx(l3_1d,l3_2d,dm);

    glPopMatrix();


    glPushMatrix();

    //PATA DELANTERA -
    glTranslated(2+l4d_2d*fact_trX,l4d_2d*fact_trY,-2);
    glRotated(l4d_1d,0,0,1);
    pata.Draw_xxx(l3_1d,l3_2d,dm);

    glPopMatrix();


    glPushMatrix();


    //PATA TRASERA +
    glTranslated(-2+l4t_2d*fact_trX,l4t_2d*fact_trY,2);
    glRotated(l4t_1d,0,0,1);
    pata.Draw_xxx(l3_1d,l3_2d,dm);
    glPopMatrix();




    glPushMatrix();

    //PATA TRASERA -
    glTranslated(-2+l4t_2d*fact_trX,l4t_2d*fact_trY,-2);
    glRotated(l4t_1d,0,0,1);
    pata.Draw_xxx(l3_1d,l3_2d,dm);
    glPopMatrix();




    //Cuerpo
    glPushMatrix();

    glTranslated(0,l4d_2d/45+l4t_2d/45,0);
    glRotated(l4d_2d-l4t_2d,0,0,1);
    aux3.Draw_xxx(dm);
    glPopMatrix();


}
