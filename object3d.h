/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "basic_object3d.h"
#include "draw_types.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _object3D:public _basic_object3D
{
  public:
  vector<_vertex3ui> Triangles;
  vector<_vertex2i> Edges;
  vector<_vertex3f> NormalsT;
  vector<_vertex3f> NormalsV;

  void draw_line();
  void draw_fill();
  void draw_chess();


  void draw_lighted_flat_smooth();
  void compute_triangles_normals();
  void compute_vertex_normals();

};

#endif // OBJECT3D_H
