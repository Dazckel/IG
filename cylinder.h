/*! \file
 * Copyright Jose Heredia Muñoz
 * email: dazckel@correo.ugr.es
 * 2021
 * GPL 3
 */

#ifndef CILYNDER_H
#define CYLINDER_H

#include "object_rev.h"
class _cylinder: public _revolution
{
    public:
    _cylinder(eje e = eje::EJE_Y,bool textura = false);
};

#endif