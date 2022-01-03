
#include "sphere.h"   


_sphere::_sphere(eje e,bool textura)
{
    
    vector<_vertex3f> v;
    v.resize(1);
    text = textura;

    switch (e)
    {
    case eje::EJE_X:
        v[0] = _vertex3f(-0.5,0,0);
        e = eje::EJE_Z;
        break;
    case eje::EJE_Y:
        v[0] = _vertex3f(0,-0.5,0);
        e = eje::EJE_X;
        break;
    case eje::EJE_Z:
        v[0] = _vertex3f(0,0,-0.5);
        e = eje::EJE_Y;
        break;
    }
    crear_OR(v,20,e,objeto::SPHERE_P);
}
