
#include "cylinder.h"   


_cylinder::_cylinder()
{
    
    vector<_vertex3f> v;
    v.resize(4);


    v[3] = _vertex3f(0,1,0);
    v[2] = _vertex3f(1,1,0);
    v[1] = _vertex3f(1,-1,0); 
    v[0] = _vertex3f(0,-1,0);

    eje e = eje::EJE_Y;
    crear_OR(v,10,e);
}