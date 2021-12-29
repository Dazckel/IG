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
#include "object_types.h"

/*****************************************************************************/ /**
 *
 *
 *
 *****************************************************************************/

class _object3D : public _basic_object3D
{
public:
  vector<_vertex3ui> Triangles;
  vector<_vertex2i> Edges;
  vector<_vertex3f> NormalsT;
  vector<_vertex3f> NormalsV;
  vector<int> Veces_visitado;
  vector<int> identifier;
  vector<_vertex2f> texture_coordinate;
  int nv_plantilla;
  int num_rot;

  bool selected = false;
  int n_triangle_selected;


  void draw_line();
  void draw_fill();
  void draw_chess();

  void draw_lighted_smooth(_object obj);
  void draw_lighted_flat();
  void compute_normals_vertex();
  void compute_normals_triangles();
  void compute_normals_vertex_sphere();
  void compute_texture_coordinates();
  void draw_texture_flat();
  void draw_texture_smooth(_object obj);
  void draw_texture();


void draw_selection();

};

#endif // OBJECT3D_H
