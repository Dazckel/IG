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

#ifndef MODEL_PARAM 
#include "model_param.h"
#endif

#include <string>

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
  vector<_vertex2f> texture_coordinate;

  int nv_plantilla;
  int num_rot;

  bool selected;
  bool pick_model; //Para resaltar el objeto cuando es del modelo.

  bool text;
  int n_triangle_selected;


  //para asignar identificadores para el pick del modelo
  int id_ini;
  int id_fin;

  string textura;


  void draw_line();
  void draw_fill();
  void draw_chess();
  _object3D(_opciones op = _opciones::OP1);
  void draw_lighted_smooth(_object obj);
  void draw_lighted_flat();
  void compute_normals_vertex();
  void compute_normals_triangles();
  void compute_normals_vertex_sphere();
  void compute_texture_coordinates();
  void draw_texture_flat();
  void draw_texture_smooth(_object obj);
  void draw_texture();


  int draw_selection(int id = 1);

};

#endif // OBJECT3D_H
