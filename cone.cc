
#include "cone.h"   


_cone::_cone(eje e,bool textura)
{
    text = textura;
    vector<_vertex3f> v;
    v.resize(3);

    switch (e)
    {
    case eje::EJE_X:
        v[2] = _vertex3f(0.5,0,0);
        v[1] = _vertex3f(0.5,0.5,0);
        v[0] = _vertex3f(-0.5,0,0);
        
        break;
    case eje::EJE_Y:
        v[2] = _vertex3f(0,0.5,0);
        v[1] = _vertex3f(0.5,-0.5,0); 
        v[0] = _vertex3f(0,-0.5,0);
        break;
    case eje::EJE_Z:
        v[2] = _vertex3f(0,0,0.5);
        v[1] = _vertex3f(0,0.5,-0.5); 
        v[0] = _vertex3f(0,0,-0.5);
        break;
    }
    crear_OR(v,20,e,objeto::CONE);
}
