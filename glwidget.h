/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>

#include <QOpenGLWidget>
#include <QKeyEvent>
#include <iostream>
#include "vertex.h"
#include "colors.h"
#include "axis.h"
#include "tetrahedron.h"
#include "cube.h"
#include <QTimer>

//
#include "dogocopter.h"
#include "draw_modes.h"
#include "model_param.h"

#include <tablero.h>
#include "object_rev.h"
#include "cone.h"

#ifndef CYLINDER_H
#include "cylinder.h"
#endif
#include "sphere.h"
#include "object_ply.h"
#include "object_types.h"

namespace _gl_widget_ne
{

  const float X_MIN = -.1;
  const float X_MAX = .1;
  const float Y_MIN = -.1;
  const float Y_MAX = .1;
  const float FRONT_PLANE_PERSPECTIVE = (X_MAX - X_MIN) / 2;
  const float BACK_PLANE_PERSPECTIVE = 1000;
  const float DEFAULT_DISTANCE = 2;
  const float ANGLE_STEP = 1;



  //

  typedef enum
  {
    F1,
    F2,
    F3,
    F4
  } _fases;
}

class _window;

/*****************************************************************************/ /**
 *
 *
 *
 *****************************************************************************/

class _gl_widget : public QOpenGLWidget
{
  Q_OBJECT
public:
  //Funciones de la Interfaz

  void tetrahedron();
  void cube();
  void cone();
  void cylinder();
  void sphere();
  void ply();
  void model();
  void map();
  void various();
  void plyS();

  void choose_ply(_opciones op);
  void choose_texture(_opciones op);
  //Draw modes

  void Modes(_draw_modes dm);
  void ObjectType(_object ot);

  //Modelo
  void Forearm(_opciones opcion);
  void ArmBody(_opciones opcion);
  void Fly(_opciones opcion);
  void Ratios(_opciones opcion);
  void Animacion();
  void Luces_Materiales(_opciones opcion);
  void Perspectiva(_opciones opcion);
  void Ejes(_opciones opcion);

  _gl_widget(_window *Window1);

  void clear_window();
  void change_projection();
  void change_observer();
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);
  void pick();

  void draw_axis();
  void draw_objects();
  void lights_options();

protected:
  void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;

public slots:
  void idle();

private:
  _window *Window;
  _axis Axis;
  _tetrahedron* Tetrahedron;
  _cube* Cube;
  _cone* Cone;
  _cylinder* Cylinder;
  _sphere* Sphere;
  _tablero Tablero;
  _ply* Ply;

  //Model
  _dogocopter *dogocopter;

  //Draw_modes
  const int N_drawmodes = 9;
  vector<bool> DrawModes;

  //Objeto a dibujar
  _object Object;

  //Vector de objetos
  int objetos_size = 5;
  vector<_object3D*> objetos;
  int the_one_object;

  // Vector de plys
  int size_ply = 7;
  int separacion = 13;
  vector<_object3D> vector_plys;
  int the_one_ply;

  bool projection;

  float OldX;
  float OldY;

  _gl_widget_ne::_fases F;
  QTimer *timer;

  float Observer_angle_x;
  float Observer_angle_y;

  float Selection_position_x;
  float Selection_position_y;

  bool Change_position;
  float Observer_distance;
  float ObserverX;
  float ObserverY;


  float X_MIN_O = -.9;
  float X_MAX_O = .9;
  float Y_MIN_O = -.9;
  float Y_MAX_O = .9;

  int flx;
  int fly;
  int flz;

  //lv3
  int gr1;
  int gr2;

  //lv4
  int gr3;
  int gr4;

  //lv5
  int gr5;
  int gr6;

  int material;

  _opciones opcion;
  bool animacion;

  bool first_light;
  bool second_light;

  eje e = eje::EJE_Y;

  //Vector de objetos del modelo.

  vector<_object3D *> model_objects;
};

#endif
