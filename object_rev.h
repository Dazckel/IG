/*! \file
 * Copyright Jose Heredia Muñoz
 * email: dazckel@correo.ugr.es
 * 2021
 * GPL 3
 */

#ifndef REVOLUTION_H
#define REVOLUTION_H

#include "object3d.h"
enum class eje{EJE_X,EJE_Y,EJE_Z};
enum class objeto{CONE,CYLINDER,SPHERE_P,SPHERE};

class _revolution: public _object3D
{

    public:

    //////////////////////////////////////////////////////////////////////////////////////////////
    _revolution();
    bool dentro_eje(_vertex3f p,eje e = eje::EJE_Y);
    void crear_OR(vector<_vertex3f> v, int nr,eje e ,objeto o);
    void GenerarTriangulos(vector<_vertex3f> v,int nr,eje e = eje::EJE_Y);
    int n_tapas(vector<_vertex3f> v,eje e = eje::EJE_Y);
    void RotarVertices(vector<_vertex3f> v,int nr,eje e ,objeto o);
    float Distancia(_vertex3f p1, _vertex3f p2 = _vertex3f(0,0,0));
};

#endif