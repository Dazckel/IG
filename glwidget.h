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
#include "draw_modes.h"

#include <tablero.h>
#include "object_rev.h"
#include "cone.h"
#include "cylinder.h"
#include "sphere.h"
#include "object_ply.h"
#include "perro_volador.h"
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

  typedef enum
  {
    MODE_DRAW_POINT,
    MODE_DRAW_LINE,
    MODE_DRAW_FILL,
    MODE_DRAW_CHESS
  } _mode_draw;

  //
  typedef enum
  {
    LEVEL_3,
    LEVEL_4,
    LEVEL_5,
    ESTATICO,
    ANIMACION,
    PARAR_ANIMACION,
    GRADOS
  } _motion;

  typedef enum
  {
    OP1,
    OP2,
    OP3,
    OP4,
    IDLE,
    OP5,
    OP6,
    OP7,
    OP8,
    OP9,
    OP10,
    OP11,
    OP12
  } _opciones;

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

  //Draw modes

void Modes(_draw_modes dm);
void ObjectType(_object ot);





  _gl_widget(_window *Window1);

  void clear_window();
  void change_projection();
  void change_observer();
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void pick();

  void draw_axis();
  void draw_objects();
  void draw_model(_draw_modes_model dm);
  void lights_options();

  _gl_widget_ne::_motion motion;
  _gl_widget_ne::_opciones opcion;
  bool animacion;

  bool first_light;
  bool second_light;

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
  _tablero Tablero;
  _ply Ply;
  _perro_volador perro;


  //Draw_modes
  const int N_drawmodes = 9;
  vector<bool> DrawModes;

  //Objeto a dibujar
  _object Object;

  //Vector de objetos
  int objetos_size = 5;
  vector<_object3D> objetos;
  int the_one_object;
  vector<pair<int, int>> rangos_id;

  // Vector de plys
  int size_ply = 7;
  int separacion = 13;
  vector<_object3D> vector_plys;
  vector<pair<int, int>> rangos_id_ply;
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

  float fac_lv3_1d;
  float fac_lv3_2d;
  float fac_lv4d_1d;
  float fac_lv4d_2d;
  float fac_lv4t_1d;
  float fac_lv4t_2d;
  float fac_lv5_1d;
  float fac_lv5_2d;

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
};

#endif
