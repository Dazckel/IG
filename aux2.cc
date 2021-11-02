#include "aux2.h"
#include "sphere.h"

_aux2::_aux2()
{
}
void _aux2::Draw_xxx(float factor){

    double ang = 90;


    float fact_x = 1.5/ang;
    float fact_y = 1.5/ang;
    float fact_x_knee = 3/ang;
    float fact_y_knee = 3/ang;
    float fact_y_elbow = 5.5/ang;

    float fr_abajo = 1;
    float fr_arriba = 3;
    float fr_y = 1;


    if(factor >0){
        fact_x*=-1;
        fact_y =(3+sin(45)*3)/ang;
        fact_y_elbow=(2+sin(45)*3)/ang;
        fact_x_knee = -(cos(45)*5)/ang;;
        fact_y_knee =(4.5+sin(45)*3)/ang;
        fr_abajo = -1;
        fr_arriba = 1;
        fr_y = 1.5;
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //Pata arriba
    //1.5 para que esté 3u por encima
    glTranslated(-factor*fact_x,1.5+factor*fact_y*fr_arriba,0);
    glRotated(abs(factor),0,0,1);
    aux.Draw_xxx();
    glPopMatrix();

    //Pata abajo
    glPushMatrix();
    //1.5 para que esté 3u por debajo
    glTranslated(-factor*fact_x,-1.5+factor*fact_y*fr_y,0);
    glRotated(fr_abajo *factor,0,0,1);
    aux.Draw_xxx();
    glPopMatrix();

    //Rodilla
    glPushMatrix();
    glTranslated(-factor*fact_x_knee,factor*fact_y_knee,0);
    glScaled(0.45,0.45,0.45);
    esfera.draw_fill();
    glPopMatrix();


    //Hombro
    glPushMatrix();
    glTranslated(0,2.5 +factor*fact_y_elbow,0);
    glScaled(0.45,0.45,0.45);
    esfera.draw_fill();
    glPopMatrix();





}
