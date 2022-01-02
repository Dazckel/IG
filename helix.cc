#include "helix.h"

_helix::_helix()
{
    helix = new _tetrahedron;
}

void _helix::Draw_xxx(_draw_modes_model dm)
{

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glScaled(4.5, 0.25, 1);
    switch (dm)
    {
    case _draw_modes_model::CHESS:
        helix->draw_chess();
        break;

    case _draw_modes_model::FILL:
        if (helix->pick_model)
            helix->draw_line();
        helix->draw_fill();
        break;

    case _draw_modes_model::POINTS:
        helix->draw_point();
        break;

    case _draw_modes_model::LINES:
        helix->draw_line();
        break;
    case _draw_modes_model::SMOOTH:
        helix->draw_lighted_smooth(_object::OBJECT_SPHERE);
        break;
    case _draw_modes_model::FLAT:
        helix->draw_lighted_flat();
        break;
    case _draw_modes_model::TEXTURE:
        helix->draw_texture();
        break;
    case _draw_modes_model::SELECTION:
        helix->draw_selection(helix->id_ini);
        break;
    }
    glPopMatrix();
}