/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/gl.h>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <iostream>
#include "vertex.h"
#include "colors.h"
#include "axis.h"
#include "tetrahedron.h"
#include "cube.h"

//
#include "object_rev.h"
#include "cone.h"
#include "cylinder.h"
#include "sphere.h"
#include "object_ply.h"
#include "perro.h"
#include "jauria.h"


namespace _gl_widget_ne {

  const float X_MIN=-.1;
  const float X_MAX=.1;
  const float Y_MIN=-.1;
  const float Y_MAX=.1;
  const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
  const float BACK_PLANE_PERSPECTIVE=1000;
  const float DEFAULT_DISTANCE=2;
  const float ANGLE_STEP=1;

  typedef enum {MODE_DRAW_POINT,MODE_DRAW_LINE,MODE_DRAW_FILL,MODE_DRAW_CHESS} _mode_draw;
  typedef enum {OBJECT_TETRAHEDRON,OBJECT_CUBE,OBJECT_CONE,OBJECT_CYLINDER,OBJECT_SPHERE,OBJECT_PLY,OBJECT_PERRO} _object;

  //
  typedef enum {O1,O2,O3,O4,O5,O6,IDLE} _motion;

  typedef enum {QUIETO,MOVIMIENTO,PARAMETROS,POSICION,ANIMACION} _opciones;

  typedef enum {F1,F2,F3,F4,F5} _fases;
}

class _window;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _gl_widget : public QOpenGLWidget
{
Q_OBJECT
public:
  _gl_widget(_window *Window1);

  void clear_window();
  void change_projection();
  void change_observer();

  void draw_axis();
  void draw_objects();


  _gl_widget_ne::_motion motion;
  _gl_widget_ne::_opciones opcion;
    bool Draw_model;


protected:
  void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *Keyevent) Q_DECL_OVERRIDE;

public slots:
  void idle();

private:
  _window *Window;
  _axis Axis;
  _tetrahedron Tetrahedron;
  _cube Cube;
  _cone Cone;
  _cylinder Cylinder;
  _sphere Sphere;
  _ply Ply;
  _jauria jauria;

  _gl_widget_ne::_object Object;
  _gl_widget_ne::_opciones TMP;
  bool Draw_point;
  bool Draw_line;
  bool Draw_fill;
  bool Draw_chess;

  float delanteras;
  float traseras;
  float cuerpo_rot;
  _gl_widget_ne::_fases F;






  float Observer_angle_x;
  float Observer_angle_y;
  float Observer_distance;
  int factor_delanteras;
  int factor_traseras;

  int factor_rot;
  float factor_trasX;
  float factor_trasY;
};

#endif
