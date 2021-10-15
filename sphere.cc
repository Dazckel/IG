
#include "sphere.h"   


_sphere::_sphere()
{
    
    vector<_vertex3f> v;
    v.resize(1);

    v[0] = _vertex3f(1,0,0);

    eje e = eje::EJE_Y;
    crear_OR(v,3,e);
}