/*
* Practicas de IG
* Jose Heredia Muñoz© 2021-2022
*
* GPL 3
*/

#ifndef PLY
#define PLY

#include "object3d.h"
#include "file_ply_stl.h"

#ifndef MODEL_PARAM
#include "model_param.h"
#endif

#include <string>


class _ply : public _object3D
{
    public:
        _ply(_opciones op  =_opciones::OP1);

    private:
        string fichero;
};

#endif