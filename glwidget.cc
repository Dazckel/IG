/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */

#include "glwidget.h"
#include "window.h"
#include <QTimer>

using namespace std;
using namespace _gl_widget_ne;
using namespace _colors_ne;

/*****************************************************************************/ /**
 *
 *
 *
 *****************************************************************************/

_gl_widget::_gl_widget(_window *Window1) : Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);
}

/*****************************************************************************/ /**
 * Evento tecla pulsada
 *
 *
 *
 *****************************************************************************/

void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{
  switch (Keyevent->key())
  {
  case Qt::Key_1:
    Object = OBJECT_TETRAHEDRON;
    break;
  case Qt::Key_2:
    Object = OBJECT_CUBE;
    break;

  //
  case Qt::Key_3:
    Object = OBJECT_CYLINDER;
    break;
  case Qt::Key_4:
    Object = OBJECT_CONE;
    break;
  case Qt::Key_5:
    Object = OBJECT_SPHERE;
    break;
  case Qt::Key_6:
    Object = OBJECT_PLY;
    break;
  case Qt::Key_7:
    Object = OBJECT_PERRO;
    break;

  //
  case Qt::Key_M:
    Draw_model = !Draw_model;
    break;
  case Qt::Key_P:
    Draw_point = !Draw_point;
    break;
  case Qt::Key_L:
    Draw_line = !Draw_line;
    break;
  case Qt::Key_F:
    Draw_fill = !Draw_fill;
    break;
  case Qt::Key_C:
    Draw_chess = !Draw_chess;
    break;

  //
  case Qt::Key_Q:
    opcion = _gl_widget_ne::_opciones::INC_1;
    break;
  case Qt::Key_W:
    opcion = _gl_widget_ne::_opciones::DEC_1;
    break;
  case Qt::Key_E:
    opcion = _gl_widget_ne::_opciones::INC_2;
    break;
  case Qt::Key_R:
    opcion = _gl_widget_ne::_opciones::DEC_2;
    break;
/// traseras
  case Qt::Key_T:
    opcion = _gl_widget_ne::_opciones::INC_1t;
    break;
  case Qt::Key_Y:
    opcion = _gl_widget_ne::_opciones::DEC_1t;
    break;
  case Qt::Key_U:
    opcion = _gl_widget_ne::_opciones::INC_2t;
    break;
  case Qt::Key_I:
    opcion = _gl_widget_ne::_opciones::DEC_2t;
    break;

    //

  case Qt::Key_Left:
    Observer_angle_y -= ANGLE_STEP;
    break;
  case Qt::Key_Right:
    Observer_angle_y += ANGLE_STEP;
    break;
  case Qt::Key_Up:
    Observer_angle_x -= ANGLE_STEP;
    break;
  case Qt::Key_Down:
    Observer_angle_x += ANGLE_STEP;
    break;
  case Qt::Key_PageUp:
    Observer_distance *= 1.2;
    break;
  case Qt::Key_PageDown:
    Observer_distance /= 1.2;
    break;
  }

  update();
}

/*****************************************************************************/ /**
 * Limpiar ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*****************************************************************************/ /**
 * Funcion para definir la transformación de proyeccion
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  // Front_plane>0  Back_plane>PlanoDelantero)
  glFrustum(X_MIN, X_MAX, Y_MIN, Y_MAX, FRONT_PLANE_PERSPECTIVE, BACK_PLANE_PERSPECTIVE);
}

/*****************************************************************************/ /**
 * Funcion para definir la transformación de vista (posicionar la camara)
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -Observer_distance);
  glRotatef(Observer_angle_x, 1, 0, 0);
  glRotatef(Observer_angle_y, 0, 1, 0);
}

/*****************************************************************************/ /**
 * Funcion que dibuja los objetos
 *
 *
 *
 *****************************************************************************/

void _gl_widget::idle()
{

  switch (F)
  {
  case _fases::F1:
    if (fac_lv4d_1d < 90)
    {
      fac_lv4d_1d++;
      fac_lv4d_2d+=0.1;
      fac_lv3_1d--;
    }
    else
      F = _fases::F2;
    break;

  case _fases::F2:
    if (fac_lv4t_1d >- 90)
    {
      fac_lv4t_1d--;
      fac_lv4d_2d-=0.1;
      fac_lv4d_1d--;
      fac_lv3_1d++;
      fac_lv4t_2d+=0.1;
    }
    else
      F = _fases::F3;

   break;
  case _fases::F3:
    if (fac_lv4d_1d > -60)
    {
      fac_lv4d_1d--;
      fac_lv3_1d--;
      fac_lv4t_1d+=2.5;


    }
    else
      F = _fases::F1;
    break;


/*  case _fases::F4:
    if (fac_lv4d_1d > -90)
    {

      fac_lv4t_1d-=2.5;
      

    }
    else
      F = _fases::F5;
    break;

/*
  case _fases::F5:
    if (delanteras > -45 && traseras > 0)
    {
      delanteras--;
      cuerpo_rot -= 1;

      traseras--;
      cuerpo_rot += 1;
      factor_trasY -= 0.022;
    }
    else
      F = _fases::F1;
    break;*/
  }

  update();
}

void _gl_widget::draw_objects()
{
  Axis.draw_line();

  if (Draw_point)
  {
    glPointSize(5);
    glColor3fv((GLfloat *)&BLACK);
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron.draw_point();
      break;
    case OBJECT_CUBE:
      Cube.draw_point();
      break;
    //
    case OBJECT_CYLINDER:
      Cylinder.draw_point();
      break;
    case OBJECT_CONE:
      Cone.draw_point();
      break;
    case OBJECT_SPHERE:
      Sphere.draw_point();
      break;
    case OBJECT_PLY:
      Ply.draw_point();
      break;
    case OBJECT_PERRO:
      perro.Draw_xxx(0, 0, 0, 0, 0, 0,0,0);
      break;

    default:
      break;
    }
  }

  if (Draw_line)
  {
    glLineWidth(3);
    glColor3fv((GLfloat *)&MAGENTA);
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron.draw_line();
      break;
    case OBJECT_CUBE:
      Cube.draw_line();
      break;
    //
    case OBJECT_CYLINDER:
      Cylinder.draw_line();
      break;
    case OBJECT_CONE:
      Cone.draw_line();
      break;
    case OBJECT_SPHERE:
      Sphere.draw_line();
      break;
    case OBJECT_PLY:
      Ply.draw_line();
      break;
    case OBJECT_PERRO:
      perro.Draw_xxx(0, 0, 0, 0, 0, 0,0,0);
      break;
    default:
      break;
    }
  }

  if (Draw_fill)
  {
    glColor3fv((GLfloat *)&BLUE);
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron.draw_fill();
      break;
    case OBJECT_CUBE:
      Cube.draw_fill();
      break;
    //
    case OBJECT_CYLINDER:
      Cylinder.draw_fill();
      break;
    case OBJECT_CONE:
      Cone.draw_fill();
      break;
    case OBJECT_SPHERE:
      Sphere.draw_fill();
      break;
    case OBJECT_PLY:
      Ply.draw_fill();
      break;
    case OBJECT_PERRO:
      perro.Draw_xxx(0, 0, 0, 0, 0, 0,0,0);
      break;
    default:
      break;
    }
  }

  if (Draw_chess)
  {
    glColor3fv((GLfloat *)&RED);
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron.draw_chess();
      break;
    case OBJECT_CUBE:
      Cube.draw_chess();
      break;
    //
    case OBJECT_CYLINDER:
      Cylinder.draw_chess();
      break;
    case OBJECT_CONE:
      Cone.draw_chess();
      break;
    case OBJECT_SPHERE:
      Sphere.draw_chess();
      break;
    case OBJECT_PLY:
      Ply.draw_chess();
      break;
    case OBJECT_PERRO:
      perro.Draw_xxx(0, 0, 0, 0, 0, 0,0,0);
      break;
    default:
      break;
    }
  }

  if (Draw_model)
  {

    glColor3fv((GLfloat *)&RED);

    switch (motion)
    {

    case _gl_widget_ne::_motion::LEVEL_3:
      switch (opcion)
      {

      case _gl_widget_ne::_opciones::INC_1:
        if (fac_lv3_1d < 0)
          fac_lv3_1d++;
        break;

      case _gl_widget_ne::_opciones::DEC_1:
        if (fac_lv3_1d > -90)
          fac_lv3_1d--;
        break;

      case _gl_widget_ne::_opciones::INC_2:
        fac_lv3_2d++;
        break;
      case _gl_widget_ne::_opciones::DEC_2:
        fac_lv3_2d--;
        break;
      }
      break;

    case _gl_widget_ne::_motion::LEVEL_4:
      switch (opcion)
      {

      case _gl_widget_ne::_opciones::INC_1:
        if (fac_lv4d_1d < 90)
          fac_lv4d_1d++;
        break;

      case _gl_widget_ne::_opciones::DEC_1:
        if (fac_lv4d_1d > -90)
          fac_lv4d_1d--;
        break;

      case _gl_widget_ne::_opciones::INC_2:
        if(fac_lv4d_2d < 45 && ( fac_lv4d_2d - fac_lv4t_2d  )  < 45)
          fac_lv4d_2d++;
        break;
      case _gl_widget_ne::_opciones::DEC_2:
        if(fac_lv4d_2d >-45  && ( fac_lv4d_2d - fac_lv4t_2d  )  >- 45)
          fac_lv4d_2d--;
        break;


//TRASERAS

      case _gl_widget_ne::_opciones::INC_1t:
        if (fac_lv4t_1d < 90)
          fac_lv4t_1d++;
        break;

      case _gl_widget_ne::_opciones::DEC_1t:
        if (fac_lv4t_1d > -90)
          fac_lv4t_1d--;
        break;

      case _gl_widget_ne::_opciones::INC_2t:
        if(fac_lv4t_2d < 45 && ( fac_lv4t_2d - fac_lv4d_2d  )  < 45)
          fac_lv4t_2d++;
        break;
      case _gl_widget_ne::_opciones::DEC_2t:
        if(fac_lv4t_2d >-45  && ( fac_lv4t_2d - fac_lv4d_2d  )  >- 45)
          fac_lv4t_2d--;
        break;
      }
      break;

    case _gl_widget_ne::_motion::LEVEL_5:
      switch (opcion)
      {

      case _gl_widget_ne::_opciones::INC_1:
        fac_lv5_1d++;
        break;

      case _gl_widget_ne::_opciones::DEC_1:
        fac_lv5_1d--;
        break;

      case _gl_widget_ne::_opciones::INC_2:
        fac_lv5_2d++;
        break;
      case _gl_widget_ne::_opciones::DEC_2:
        fac_lv5_2d--;
        break;
      }
      break;

      case _gl_widget_ne::_motion::ANIMACION:

      QTimer *timer = new QTimer(this);
      connect(timer, SIGNAL(timeout()), this, SLOT(idle()));
      timer->start(30);
      motion = _gl_widget_ne::_motion::ESTATICO;
      break;
    }
    opcion = _gl_widget_ne::_opciones::IDLE;
    perro.Draw_xxx(fac_lv3_1d, fac_lv3_2d, fac_lv4d_1d, fac_lv4d_2d,fac_lv4t_1d, fac_lv4t_2d, fac_lv5_1d, fac_lv5_2d);
  }
}

/*****************************************************************************/ /**
 * Evento de dibujado
 *
 *
 *
 *****************************************************************************/

void _gl_widget::paintGL()
{
  clear_window();
  change_projection();
  change_observer();
  draw_objects();
}

/*****************************************************************************/ /**
 * Evento de cambio de tamaño de la ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::resizeGL(int Width1, int Height1)
{
  glViewport(0, 0, Width1, Height1);
}

/*****************************************************************************/ /**
 * Inicialización de OpenGL
 *
 *
 *
 *****************************************************************************/

void _gl_widget::initializeGL()
{
  const GLubyte *strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1')
  {
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
  }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  int Max_texture_size = 0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);

  Observer_angle_x = 0;
  Observer_angle_y = 0;
  Observer_distance = DEFAULT_DISTANCE;

  Draw_point = false;
  Draw_line = false;
  Draw_fill = false;
  Draw_chess = false;

  Draw_model = false;

  fac_lv3_1d = 0;
  fac_lv3_2d = 0;
  fac_lv4d_1d = 0;
  fac_lv4d_2d = 0;
  fac_lv4t_1d = 0;
  fac_lv4t_2d = 0;
  fac_lv5_1d = 0;
  fac_lv5_2d = 0;
}
