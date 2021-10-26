
#include "cylinder.h"   


_cylinder::_cylinder()
{
    
    vector<_vertex3f> v;
    v.resize(4);

    eje e = eje::EJE_Z;
    
    switch (e)
    {
    case eje::EJE_X:

    v[0] = _vertex3f(1,0,0);
    v[1] = _vertex3f(1,1,0);
    v[2] = _vertex3f(-1,1,0); 
    v[3] = _vertex3f(-1,0,0);
        break;

    case eje::EJE_Y:
    v[0] = _vertex3f(0,1,0);
    v[1] = _vertex3f(1,1,0);
    v[2] = _vertex3f(1,-1,0); 
    v[3] = _vertex3f(0,-1,0);
        break;

    case eje::EJE_Z:
    v[0] = _vertex3f(0,0,1);
    v[1] = _vertex3f(0,1,1);
    v[2] = _vertex3f(0,1,-1); 
    v[3] = _vertex3f(0,0,-1);
        break;
    }


    crear_OR(v,100,e,objeto::CYLINDER);
}