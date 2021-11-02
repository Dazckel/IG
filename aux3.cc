#include "aux3.h"

_aux3::_aux3()
{
}
void _aux3::Draw_xxx(){

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //
    glScaled(9,0.7,4);
    Cube.draw_chess();
    
    
    glPopMatrix();

}
