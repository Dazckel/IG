#include "perro.h"


_perro::_perro()
{
}
void _perro::Draw_xxx(float delanteras,float traseras,float cuerpo_rot){

    double ang = 90;
    float fac_y = 2.5/ang;



   glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //PATA DELANTERA +
    glTranslated(2,0,2);
    
    aux2.Draw_xxx(delanteras);


    glPopMatrix();


    glPushMatrix();

    //PATA DELANTERA -
    glTranslated(2,0,-2);
    aux2.Draw_xxx(delanteras);

    glPopMatrix();


    glPushMatrix();


    //PATA TRASERA +
    glTranslated(-2,0,2);
    aux2.Draw_xxx(traseras);
    glPopMatrix();




    glPushMatrix();

    //PATA TRASERA -
    glTranslated(-2,0,-2);
    aux2.Draw_xxx(traseras);
    glPopMatrix();




    //Cuerpo
    glPushMatrix();

    int c = traseras+delanteras;
    if(traseras == delanteras && c == 0)
        c = 0;
    glTranslated(0,2.5 +c*fac_y,0);
    glRotated(cuerpo_rot/2,0,0,1);
    aux3.Draw_xxx();
    glPopMatrix();

}
