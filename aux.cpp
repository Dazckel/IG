#include "aux.h"

_aux::_aux()
{
}
void _aux::Draw_xxx(){

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //
    glScaled(0.5,3,0.5);
    Cube.draw_chess();
    
    
    glPopMatrix();

}
