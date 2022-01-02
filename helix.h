#ifndef HELIX_H
#define HELIX_H

#include "tetrahedron.h"
#ifndef OBJECT_T
#include "object_types.h"
#endif

class _helix
{
public:
  _helix();
  _tetrahedron* helix;
  void Draw_xxx(_draw_modes_model dm);
};

#endif // aux_H
