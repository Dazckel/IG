
#include "cone.h"   


_cone::_cone()
{
    
    vector<_vertex3f> v;
    v.resize(3);

    v[0] = _vertex3f(0,1,0);
    v[1] = _vertex3f(1,-1,0); 
    v[2] = _vertex3f(0,-1,0);

    eje e = eje::EJE_Y;
    crear_OR(v,5,e,objeto::CONE);
}