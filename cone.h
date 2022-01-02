/*! \file
 * Copyright Jose Heredia Muñoz
 * email: dazckel@correo.ugr.es
 * 2021
 * GPL 3
 */

#ifndef CONE_H
#define CONE_H


#include "object_rev.h"
class _cone: public _revolution
{
    public:
    _cone(eje e = eje::EJE_Y,bool textura = false);
};

#endif