
#include "sphere.h"   


_sphere::_sphere()
{
    
    vector<_vertex3f> v;
    v.resize(1);
    eje e = eje::EJE_Z;

    switch (e)
    {
    case eje::EJE_X:
        v[0] = _vertex3f(0,1,0);
        break;
    case eje::EJE_Y:
        v[0] = _vertex3f(0,0,1);
        break;
    case eje::EJE_Z:
        v[0] = _vertex3f(0,1,0);
        break;
    }
    crear_OR(v,10,e,objeto::SPHERE_P);
}
