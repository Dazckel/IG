/*! \file
 * Copyright Jose Heredia Muñoz
 * email: dazckel@correo.ugr.es
 * 2021
 * GPL 3
 */

#ifndef CUBE_H
#define CUBE_H

#include "object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _cube:public _object3D
{
    public:
    _cube(float Size=1.0);
};

#endif