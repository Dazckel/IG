
#include "cylinder.h"   


_cylinder::_cylinder(eje e,bool textura)
{
    text = textura;
    vector<_vertex3f> v;
    v.resize(4);
    
    switch (e)
    {
    case eje::EJE_X:

    v[3] = _vertex3f(0.5,0,0);
    v[2] = _vertex3f(0.5,0.5,0);
    v[1] = _vertex3f(-0.5,0.5,0);
    v[0] = _vertex3f(-0.5,0,0);
        break;

    case eje::EJE_Y:
    v[3] = _vertex3f(0,0.5,0);
    v[2] = _vertex3f(0.5,0.5,0);
    v[1] = _vertex3f(0.5,-0.5,0);
    v[0] = _vertex3f(0,-0.5,0);
        break;

    case eje::EJE_Z:
    v[3] = _vertex3f(0,0,0.5);
    v[2] = _vertex3f(0,0.5,0.5);
    v[1] = _vertex3f(0,0.5,-0.5);
    v[0] = _vertex3f(0,0,-0.5);
        break;
    }


    crear_OR(v,20,e,objeto::CYLINDER);
}


/*
    switch (e)
    {
    case eje::EJE_X:

    //v[5] = _vertex3f(0.5,0,0);
    v[3] = _vertex3f(0.5,0.5,0);
    v[2] = _vertex3f(0.25,0.25,0);
    v[1] = _vertex3f(-0.25,0.25,0);
    v[0] = _vertex3f(-0.5,0.5,0);
    //v[0] = _vertex3f(-0.5,0,0);
        break;

    case eje::EJE_Y:
    //v[5] = _vertex3f(0,0.5,0);
    v[3] = _vertex3f(0.5,0.5,0);
    v[2] = _vertex3f(0.25,0.25,0);
    v[1] = _vertex3f(0.25,-0.25,0);
    v[0] = _vertex3f(0.5,-0.5,0);
    //v[0] = _vertex3f(0,-0.5,0);
        break;

    case eje::EJE_Z:
    //v[5] = _vertex3f(0,0,0.5);
    v[3] = _vertex3f(0,0.5,0.5);
    v[2] = _vertex3f(0,0.25,0.25);
    v[1] = _vertex3f(0,0.25,-0.25);
    v[0] = _vertex3f(0,0.5,-0.5);
    //v[0] = _vertex3f(0,0,-0.5);
        break;
    }

*/
