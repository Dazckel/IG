/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */

#include "glwidget.h"
#include "window.h"

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

// Skeleton for pick fuction using glDeleteFramebuffers
//
// Domingo Martín Perandrés
// GPL
//
// Window_width and Window_height are the widht and height of the device window
// Selection_position_x and Selection_position_y are the coordinates of the mouse

void _gl_widget::pick()
{
  makeCurrent();

  // Frame Buffer Object to do the off-screen rendering
  GLuint FBO;
  glGenFramebuffers(1, &FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);

  // Texture for drawing
  GLuint Color_texture;
  glGenTextures(1, &Color_texture);
  glBindTexture(GL_TEXTURE_2D, Color_texture);
  // RGBA8
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width(), height());
  // this implies that there is not mip mapping
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // Texure for computing the depth
  GLuint Depth_texture;
  glGenTextures(1, &Depth_texture);
  glBindTexture(GL_TEXTURE_2D, Depth_texture);
  // Float
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, width(), height());

  // Attatchment of the textures to the FBO
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, Color_texture, 0);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, Depth_texture, 0);

  // OpenGL will draw to these buffers (only one in this case)
  static const GLenum Draw_buffers[] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1, Draw_buffers);

  /*************************/
  int id;
  int id_fin;
  int p;
  the_one_ply = -1;
  the_one_object = -1;
  switch (Object)
  {
  case OBJECT_TETRAHEDRON:
    Tetrahedron->draw_selection();
    Tetrahedron->selected = false;
    break;
  case OBJECT_CUBE:
    Cube->draw_selection();
    Cube->selected = false;
    break;
  //
  case OBJECT_CYLINDER:
    Cylinder->draw_selection();
    Cylinder->selected = false;
    break;
  case OBJECT_CONE:
    Cone->draw_selection();
    Cone->selected = false;
    break;
  case OBJECT_SPHERE:
    Sphere->draw_selection();
    Sphere->selected = false;
    break;
  case OBJECT_PLY:
    Ply->draw_selection();
    Ply->selected = false;
    break;
  case OBJECT_TABLERO:
    Tablero.draw_selection();
    Tablero.selected = false;
    break;

  case MULTIPLE_OBJECTS:
    id = 1;
    id_fin = 1;
    for (int i = 0; i < objetos_size; i++)
    {

      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glTranslated(((objetos_size + 2) / objetos_size) * i - objetos_size / 2, 0, 0);
      id_fin = objetos[i]->draw_selection(id);
      objetos[i]->selected = false;
      objetos[i]->id_fin = id_fin;
      objetos[i]->id_ini = id;
      id = id_fin;
      glPopMatrix();
    }
    break;
  case PLYS:
    id = 1;
    id_fin = 1;
    p = 0;
    for (int i = 0; i < size_ply; i++)
      for (int j = 0; j < size_ply; j++, p++)
      {

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated((size_ply + separacion) * i - size_ply * size_ply, -separacion * 2 + j * separacion, 0);
        id_fin = vector_plys[p].draw_selection(id);
        vector_plys[p].selected = false;
        vector_plys[p].id_fin = id_fin;
        vector_plys[p].id_ini = id;
        id = id_fin;
        glPopMatrix();
      }

    break;
  case OBJECT_SPOT:
    id = 1;
    id_fin = 1;
    int sz = model_objects.size();
    for (int i = 0; i < sz; i++)
    {
      int Nt = model_objects[i]->Triangles.size();
      model_objects[i]->id_ini = id;
      model_objects[i]->id_fin = Nt + id;
      model_objects[i]->selected = false;
      model_objects[i]->pick_model = false;
      id = Nt + id;
    }
    dogocopter->Draw_xxx(_draw_modes_model::SELECTION);
    break;
  }
  /*************************/

  // get the pixel
  int Color;
  glReadBuffer(GL_FRONT);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);

  glReadPixels(Selection_position_x, Selection_position_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &Color);

  cout << Color << endl;
  /*************************/

  uint B = uint((Color & 0x00FF0000) >> 16);
  uint G = uint((Color & 0x0000FF00) >> 8);
  uint R = uint((Color & 0x000000FF));

  int Selected_triangle = (R << 16) + (G << 8) + B;
  if (Selected_triangle == 16777215)
    Selected_triangle = -1;

  if (Selected_triangle > 0)
  {
    Selected_triangle--;
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron->selected = true;
      Tetrahedron->n_triangle_selected = Selected_triangle;
      break;
    case OBJECT_CUBE:
      Cube->selected = true;
      Cube->n_triangle_selected = Selected_triangle;
      break;
    //
    case OBJECT_CYLINDER:
      Cylinder->selected = true;
      Cylinder->n_triangle_selected = Selected_triangle;
      break;
    case OBJECT_CONE:
      Cone->selected = true;
      Cone->n_triangle_selected = Selected_triangle;
      break;
    case OBJECT_SPHERE:
      Sphere->selected = true;
      Sphere->n_triangle_selected = Selected_triangle;
      break;
    case OBJECT_PLY:
      Ply->selected = true;
      Ply->n_triangle_selected = Selected_triangle;
      break;
    case OBJECT_TABLERO:
      Tablero.selected = true;
      Tablero.n_triangle_selected = Selected_triangle;
      break;
    case MULTIPLE_OBJECTS:
      Selected_triangle++;
      for (int i = 0; i < objetos_size; i++)
      {
        if ((objetos[i]->id_ini <= Selected_triangle) && (objetos[i]->id_fin > Selected_triangle))
        {
          Selected_triangle -= objetos[i]->id_ini;
          objetos[i]->n_triangle_selected = Selected_triangle;
          objetos[i]->selected = true;
          the_one_object = i;
        }
      }
      break;

    case PLYS:
      Selected_triangle++;
      for (int i = 0; i < size_ply * size_ply; i++)
      {
        if ((vector_plys[i].id_ini <= Selected_triangle) && (vector_plys[i].id_fin > Selected_triangle))
        {
          //Por esto hago "Selected_triangle++" por que si he seleccionado el primer triangulo (0)
          //si le resto el id==1 ( para saber si corresponde a ese objeto) falla.
          Selected_triangle -= vector_plys[i].id_ini;
          vector_plys[i].n_triangle_selected = Selected_triangle;
          vector_plys[i].selected = true;
          the_one_ply = i;
        }
      }
      break;
    case OBJECT_SPOT:
      Selected_triangle++;
      int size = model_objects.size();
      for (int i = 0; i < size; i++)
      {
        if ((model_objects[i]->id_ini <= Selected_triangle) && (model_objects[i]->id_fin > Selected_triangle))
        {

          //Por esto hago "Selected_triangle++" por que si he seleccionado el primer triangulo (0)
          //si le resto el id==1 ( para saber si corresponde a ese objeto) falla.
          int aux = Selected_triangle - model_objects[i]->id_ini;
          model_objects[i]->n_triangle_selected = aux;
          model_objects[i]->selected = true;
          model_objects[i]->pick_model = true;
        }
      }
      break;
    }
  }
  glUseProgram(0);
  glBindVertexArray(0);
  /*************************/

  glDeleteTextures(1, &Color_texture);
  glDeleteTextures(1, &Depth_texture);
  glDeleteFramebuffers(1, &FBO);
  // the normal framebuffer takes the control of drawing
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, defaultFramebufferObject());
}

void _gl_widget::mousePressEvent(QMouseEvent *Event)
{
  if (Event->buttons() & Qt::LeftButton)
  {
    Change_position = true;
    OldX = Event->x();
    OldY = Event->y();
  }
  else
  {
    if (Event->buttons() & Qt::RightButton)
    {
      Selection_position_x = Event->x();
      Selection_position_y = height() - Event->y();
    }
  }
  update();
}

void _gl_widget ::mouseReleaseEvent(QMouseEvent *Event)
{

  if (Event->button() & Qt::RightButton)
  {
    if (DrawModes[1])
      pick();
  }
  if (Event->button() & Qt::LeftButton)
    Change_position = false;

  update();
}

void _gl_widget::mouseMoveEvent(QMouseEvent *event)
{

  if (Change_position)
  {
    float X = event->x();
    float Y = event->y();

    float XDisplacement = X - OldX;
    float YDisplacement = Y - OldY;

    if (XDisplacement < 0)
    {
      XDisplacement = -.2 * abs(XDisplacement);
    }
    else
    {
      XDisplacement = .2 * abs(XDisplacement);
    }

    if (YDisplacement < 0)
    {
      YDisplacement = -.2 * abs(YDisplacement);
    }
    else
    {
      YDisplacement = .2 * abs(YDisplacement);
    }

    Observer_angle_x += YDisplacement;
    Observer_angle_y += XDisplacement;
    OldX = X;
    OldY = Y;
    update();
  }
}

void _gl_widget::wheelEvent(QWheelEvent *event)
{
  float rat = 0.935;
  int numDegrees = event->angleDelta().ry() / 120;
  if (numDegrees > 0)
  {
    Observer_distance /= .9 * abs(numDegrees);
    X_MIN_O *= rat * numDegrees;
    Y_MIN_O *= rat * numDegrees;
    X_MAX_O *= rat * numDegrees;
    Y_MAX_O *= rat * numDegrees;
  }
  else
  {
    Observer_distance *= .9 * abs(numDegrees);
    X_MIN_O /= rat * abs(numDegrees);
    Y_MIN_O /= rat * abs(numDegrees);
    X_MAX_O /= rat * abs(numDegrees);
    Y_MAX_O /= rat * abs(numDegrees);
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

void _gl_widget::draw_objects()
{
  Axis.draw_line();
  if (DrawModes[0])
  {
    glPointSize(5);
    glColor3fv((GLfloat *)&BLACK);
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron->draw_point();
      break;
    case OBJECT_CUBE:
      Cube->draw_point();
      break;
    //
    case OBJECT_CYLINDER:
      Cylinder->draw_point();
      break;
    case OBJECT_CONE:
      Cone->draw_point();
      break;
    case OBJECT_SPHERE:
      Sphere->draw_point();
      break;
    case OBJECT_PLY:
      Ply->draw_point();
      break;
    case OBJECT_TABLERO:
      Tablero.draw_point();
      break;
    case OBJECT_SPOT:
      dogocopter->Draw_xxx(_draw_modes_model::POINTS);
      break;
    case MULTIPLE_OBJECTS:

      for (int i = 0; i < objetos_size; i++)
      {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated(((objetos_size + 2) / objetos_size) * i - objetos_size / 2, 0, 0);
        objetos[i]->draw_point();
        glPopMatrix();
      }

      break;
    case PLYS:
      int p = 0;
      for (int i = 0; i < size_ply; i++)
        for (int j = 0; j < size_ply; j++, p++)
        {
          glMatrixMode(GL_MODELVIEW);
          glPushMatrix();
          glTranslated((size_ply + separacion) * i - size_ply * size_ply, -separacion * 2 + j * separacion, 0);
          vector_plys[p].draw_point();
          glPopMatrix();
        }

      break;
    }
  }

  if (DrawModes[8])
  {
    glLineWidth(3);

    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron->draw_line();
      break;
    case OBJECT_CUBE:
      Cube->draw_line();
      break;
    //
    case OBJECT_CYLINDER:
      Cylinder->draw_line();
      break;
    case OBJECT_CONE:
      Cone->draw_line();
      break;
    case OBJECT_SPHERE:
      Sphere->draw_line();
      break;
    case OBJECT_PLY:
      Ply->draw_line();
      break;
    case OBJECT_SPOT:
      dogocopter->Draw_xxx(_draw_modes_model::LINES);
      break;
    case OBJECT_TABLERO:
      Tablero.draw_line();
      break;
    case MULTIPLE_OBJECTS:

      for (int i = 0; i < objetos_size; i++)
      {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated(((objetos_size + 2) / objetos_size) * i - objetos_size / 2, 0, 0);
        objetos[i]->draw_line();
        glPopMatrix();
      }

      break;
    case PLYS:
      int p = 0;
      for (int i = 0; i < size_ply; i++)
        for (int j = 0; j < size_ply; j++, p++)
        {
          glMatrixMode(GL_MODELVIEW);
          glPushMatrix();
          glTranslated((size_ply + separacion) * i - size_ply * size_ply, -separacion * 2 + j * separacion, 0);
          vector_plys[p].draw_line();
          glPopMatrix();
        }

      break;
    }
  }

  if (DrawModes[1])
  {
    glColor3fv((GLfloat *)&RED);
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron->draw_fill();
      break;
    case OBJECT_CUBE:
      Cube->draw_fill();
      break;
    //
    case OBJECT_CYLINDER:
      Cylinder->draw_fill();
      break;
    case OBJECT_CONE:
      Cone->draw_fill();
      break;
    case OBJECT_SPHERE:
      Sphere->draw_fill();
      break;
    case OBJECT_PLY:
      Ply->draw_fill();
      break;
    case OBJECT_SPOT:
      dogocopter->Draw_xxx(_draw_modes_model::FILL);
      break;
    case OBJECT_TABLERO:
      Tablero.draw_fill();
      break;
    case MULTIPLE_OBJECTS:

      for (int i = 0; i < objetos_size; i++)
      {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated(((objetos_size + 2) / objetos_size) * i - objetos_size / 2, 0, 0);
        if (the_one_object == i)
        {
          glLineWidth(5);
          objetos[the_one_object]->draw_line();
        }
        objetos[i]->draw_fill();
        glPopMatrix();
      }

      break;
    case PLYS:
      int p = 0;
      for (int i = 0; i < size_ply; i++)
        for (int j = 0; j < size_ply; j++, p++)
        {
          glMatrixMode(GL_MODELVIEW);
          glPushMatrix();
          glTranslated((size_ply + separacion) * i - size_ply * size_ply, -separacion * 2 + j * separacion, 0);
          if (p == the_one_ply)
          {
            glLineWidth(5);
            vector_plys[the_one_ply].draw_line();
          }
          vector_plys[p].draw_fill();
          glPopMatrix();
        }

      break;
    }
  }

  if (first_light)
    glEnable(GL_LIGHT0);
  if (second_light)
    glEnable(GL_LIGHT1);

  if (DrawModes[3])
  {
    glShadeModel(GL_FLAT);
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron->draw_lighted_flat();
      break;
    case OBJECT_CUBE:
      Cube->draw_lighted_flat();
      break;
    //
    case OBJECT_CYLINDER:
      Cylinder->draw_lighted_flat();
      break;
    case OBJECT_CONE:
      Cone->draw_lighted_flat();
      break;
    case OBJECT_SPHERE:
      Sphere->draw_lighted_flat();
      break;
    case OBJECT_PLY:
      Ply->draw_lighted_flat();
      break;
    case OBJECT_SPOT:
      dogocopter->Draw_xxx(_draw_modes_model::FLAT);
      break;
    case OBJECT_TABLERO:
      Tablero.draw_lighted_flat();
      break;
    case MULTIPLE_OBJECTS:

      for (int i = 0; i < objetos_size; i++)
      {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated(((objetos_size + 2) / objetos_size) * i - objetos_size / 2, 0, 0);
        objetos[i]->draw_lighted_flat();
        glPopMatrix();
      }

      break;
    case PLYS:
      int p = 0;
      for (int i = 0; i < size_ply; i++)
        for (int j = 0; j < size_ply; j++, p++)
        {
          glMatrixMode(GL_MODELVIEW);
          glPushMatrix();
          glTranslated((size_ply + separacion) * i - size_ply * size_ply, -separacion * 2 + j * separacion, 0);
          vector_plys[p].draw_lighted_flat();
          glPopMatrix();
        }

      break;
    }
  }
  if (DrawModes[6])
  {
    glShadeModel(GL_FLAT);
    glActiveTexture(GL_TEXTURE0);
    switch (Object)
    {
    case OBJECT_CYLINDER:
      Cylinder->draw_texture_flat();
      break;
    case OBJECT_CONE:
      Cone->draw_texture_flat();
      break;
    case OBJECT_SPHERE:
      Sphere->draw_texture_flat();
      break;
    case OBJECT_TABLERO:
      Tablero.draw_texture_flat();
      break;
    }
  }

  if (DrawModes[7])
  {
    glActiveTexture(GL_TEXTURE0);
    glShadeModel(GL_SMOOTH);
    switch (Object)
    {
    case OBJECT_CYLINDER:
      Cylinder->draw_texture_smooth(_object::OBJECT_CYLINDER);
      break;
    case OBJECT_CONE:
      Cone->draw_texture_smooth(_object::OBJECT_CONE);
      break;
    case OBJECT_SPHERE:
      Sphere->draw_texture_smooth(_object::OBJECT_SPHERE);
      break;
    case OBJECT_TABLERO:
      Tablero.draw_texture_smooth(_object::OBJECT_TABLERO);
      break;
    }
  }
  if (DrawModes[4])
  {
    glShadeModel(GL_SMOOTH);

    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron->draw_lighted_smooth(_object::OBJECT_TETRAHEDRON);
      break;
    case OBJECT_CUBE:
      Cube->draw_lighted_smooth(_object::OBJECT_CUBE);
      break;
    //
    case OBJECT_CYLINDER:
      Cylinder->draw_lighted_smooth(_object::OBJECT_CYLINDER);
      break;
    case OBJECT_CONE:
      Cone->draw_lighted_smooth(_object::OBJECT_CONE);
      break;
    case OBJECT_SPHERE:
      Sphere->draw_lighted_smooth(_object::OBJECT_SPHERE);
      break;
    case OBJECT_PLY:
      Ply->draw_lighted_smooth(_object::OBJECT_PLY);
      break;
    case OBJECT_SPOT:
      dogocopter->Draw_xxx(_draw_modes_model::SMOOTH);
      break;
    case OBJECT_TABLERO:
      Tablero.draw_lighted_smooth(_object::OBJECT_TABLERO);
      break;
    case MULTIPLE_OBJECTS:

      for (int i = 0; i < objetos_size; i++)
      {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated(((objetos_size + 2) / objetos_size) * i - objetos_size / 2, 0, 0);
        objetos[i]->draw_lighted_smooth(_object::OBJECT_CONE);
        glPopMatrix();
      }

      break;
    case PLYS:
      int p = 0;
      for (int i = 0; i < size_ply; i++)
        for (int j = 0; j < size_ply; j++, p++)
        {
          glMatrixMode(GL_MODELVIEW);
          glPushMatrix();
          glTranslated((size_ply + separacion) * i - size_ply * size_ply, -separacion * 2 + j * separacion, 0);
          vector_plys[p].draw_lighted_smooth(_object::OBJECT_PLY);
          glPopMatrix();
        }
    }
  }
  if (first_light)
    glDisable(GL_LIGHT0);
  if (second_light)
    glDisable(GL_LIGHT1);

  if (DrawModes[5])
  {
    glActiveTexture(GL_TEXTURE0);
    switch (Object)
    {
    case OBJECT_CYLINDER:
      Cylinder->draw_texture();
      break;
    case OBJECT_CONE:
      Cone->draw_texture();
      break;
    case OBJECT_SPHERE:
      Sphere->draw_texture();
      break;
    case OBJECT_TABLERO:
      Tablero.draw_texture();
      break;
    }
  }

  if (DrawModes[2])
  {
    glColor3fv((GLfloat *)&RED);
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron->draw_chess();
      break;
    case OBJECT_CUBE:
      Cube->draw_chess();
      break;
    //
    case OBJECT_CYLINDER:
      Cylinder->draw_chess();
      break;
    case OBJECT_CONE:
      Cone->draw_chess();
      break;
    case OBJECT_SPHERE:
      Sphere->draw_chess();
      break;
    case OBJECT_PLY:
      Ply->draw_chess();
      break;
    case OBJECT_SPOT:
      dogocopter->Draw_xxx(_draw_modes_model::CHESS);
      break;
    case OBJECT_TABLERO:
      Tablero.draw_chess();
      break;
    case MULTIPLE_OBJECTS:

      for (int i = 0; i < objetos_size; i++)
      {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated(((objetos_size + 2) / objetos_size) * i - objetos_size / 2, 0, 0);
        objetos[i]->draw_chess();
        glPopMatrix();
      }

      break;
    case PLYS:
      int p = 0;
      for (int i = 0; i < size_ply; i++)
        for (int j = 0; j < size_ply; j++, p++)
        {
          glMatrixMode(GL_MODELVIEW);
          glPushMatrix();
          glTranslated((size_ply + separacion) * i - size_ply * size_ply, -separacion * 2 + j * separacion, 0);
          vector_plys[p].draw_chess();
          glPopMatrix();
        }

      break;
    }
  }
}

void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  // Front_plane>0  Back_plane>PlanoDelantero)
  if (!projection)
    glFrustum(X_MIN * this->width() / this->height(), X_MAX * this->width() / this->height(), Y_MIN, Y_MAX, FRONT_PLANE_PERSPECTIVE, BACK_PLANE_PERSPECTIVE);
  else
    glOrtho(X_MIN_O * this->width() / this->height(), X_MAX_O * this->width() / this->height(), Y_MIN_O, Y_MAX_O, FRONT_PLANE_PERSPECTIVE, BACK_PLANE_PERSPECTIVE);
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
  resizeGL(this->width(), this->height());
  change_projection();
  change_observer();
  if ((second_light || first_light) && (DrawModes[4] || DrawModes[3] || DrawModes[7] || DrawModes[6]))
    lights_options();
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
  //La razón - ratio: cuando empezamos es 1:1
  //Al cambiar la ventana, cambia la razón
  //Para no deformar debemos cambiar la ventana en la cámara.

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

  glewExperimental = GL_TRUE;

  int err = glewInit();
  if (GLEW_OK != err)
  {
    // Problem: glewInit failed, something is seriously wrong.
    QMessageBox MsgBox(this);
    MsgBox.setText("Error: There is not OpenGL drivers\n\nPlease, look for the information of your GPU (AMD, INTEL or NVIDIA) and install the drivers");
    MsgBox.exec();
    Window->close();
  }
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

  //Vector de modos
  DrawModes.resize(N_drawmodes);
  for (int i = 0; i < N_drawmodes; i++)
    DrawModes[i] = false;

  first_light = false;
  second_light = false;
  animacion = false;
  Change_position = false;
  projection = false;

  material = 0;

  flx = 1;
  fly = 1;
  flz = 1;
  gr1 = 1;
  gr2 = 1;
  gr3 = 1;
  gr4 = 1;
  gr5 = 1;
  gr6 = 1;

  Sphere = new _sphere;
  Cylinder = new _cylinder;
  Cone = new _cone;
  Tetrahedron = new _tetrahedron;
  Cube = new _cube;

  _sphere* aSphere = new _sphere;
  _cylinder* aCylinder = new _cylinder;
  _cone* aCone = new _cone;
  _tetrahedron* aTetrahedron = new _tetrahedron;
  _cube* aCube = new _cube;

  objetos = {aSphere, aCylinder, aCone, aTetrahedron, aCube};
  the_one_object = -1;
  the_one_ply = -1;
  //Inicialización del vector de Plys.
  vector_plys.resize(size_ply * size_ply);
  for (int i = 0; i < size_ply * size_ply; i++)
  {
    _ply aux;
    vector_plys[i] = aux;
  }
  F = _fases::F1;

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(idle()));

  //Objetos del modelo
  dogocopter = new _dogocopter;

  for (int i = 0; i < 4; i++)
  {
    model_objects.push_back(dogocopter->dog->legs[i]->femur);
    model_objects.push_back(dogocopter->dog->legs[i]->shoulder);
    model_objects.push_back(dogocopter->dog->legs[i]->forearm->forearm);
    model_objects.push_back(dogocopter->dog->legs[i]->forearm->knee);
  }
  model_objects.push_back(dogocopter->dog->body);

  model_objects.push_back(dogocopter->gorrocopter->helixs[0]->helix);
  model_objects.push_back(dogocopter->gorrocopter->helixs[1]->helix);
  model_objects.push_back(dogocopter->gorrocopter->base);

  Ply = new _ply;
}

//////////////////////////////////////////////////////////////////////////////
////////// OPCIONES PARA LA LUZ
//////////////////////////////////////////////////////////////////////////////
void _gl_widget::lights_options()
{
  GLfloat mat_specular[] = {0.633, 0.727811, 0.633, 1};
  GLfloat mat_shininess[] = {60.0f};
  GLfloat mat_difuse[] = {1, 1, 1, 1};
  GLfloat mat_ambient[] = {0.0215, 0.1745, 0.0215, 1};

  GLfloat mat_specular1[] = {0.727811, 0.626959, 0.626959, 1};
  GLfloat mat_shininess1[] = {15.0f};
  GLfloat mat_difuse1[] = {0.61424, 0.04136, 0.04136, 1};
  GLfloat mat_ambient1[] = {0.1745, 0.1745, 0.01175, 1};

  GLfloat mat_specular2[] = {0.296648, 0.296648, 0.296648, 1};
  GLfloat mat_shininess2[] = {100.0f};
  GLfloat mat_difuse2[] = {1, 0.829, 0.829, 1};
  GLfloat mat_ambient2[] = {0.25, 0.20725, 0.20725, 1};

  switch (material)
  {
  case 0:

    glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *)&mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *)&mat_difuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *)&mat_ambient);
    break;

  case 1:

    glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *)&mat_specular1);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *)&mat_difuse1);
    glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *)&mat_ambient1);
    break;

  case 2:

    glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *)&mat_specular2);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *)&mat_difuse2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *)&mat_ambient2);
    break;
  }

  // PARÁMETROS LUZ
  //0
  if (first_light)
  {

    GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1};
    GLfloat light_specular[] = {0.3, 0.3, 0.3, 0.3};
    GLfloat light_position0[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat lightDifuse[] = {0.6, 0.6, 0.6, 6};
    //CONFIGURACIÓN LUZ

    //0
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);            //POSICIÓN
    glLightfv(GL_LIGHT0, GL_DIFFUSE, (GLfloat *)&lightDifuse);     //COMPONENTE DIFUSA
    glLightfv(GL_LIGHT0, GL_SPECULAR, (GLfloat *)&light_specular); //COMPONENTE ESPECULAR
    glLightfv(GL_LIGHT0, GL_AMBIENT, (GLfloat *)&light_ambient);   //COMONENTE AMBIENTAL
  }

  if (second_light)
  {

    GLfloat light_ambient1[] = {0.1, 0.0, 0.1, 1};
    GLfloat light_specular1[] = {0.4, 0.0, 0.4, 0.4};
    GLfloat light_position1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightDifuse1[] = {0.5, 0.0, 0.5, 1};
    //CONFIGURACIÓN LUZ
    //0
    glLightfv(GL_LIGHT1, GL_DIFFUSE, (GLfloat *)&lightDifuse1);     //COMPONENTE DIFUSA
    glLightfv(GL_LIGHT1, GL_SPECULAR, (GLfloat *)&light_specular1); //COMPONENTE ESPECULAR
    glLightfv(GL_LIGHT1, GL_AMBIENT, (GLfloat *)&light_ambient1);   //COMONENTE AMBIENTAL

    glPushMatrix();
    glRotatef(flx, 1, 0, 0);
    glRotatef(fly, 0, 1, 0);
    glRotatef(flz, 0, 0, 1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glPopMatrix();
  }
}

////////////////////////////////////
////////////////////////////////////

void _gl_widget::Modes(_draw_modes dm)
{
  for (int i = 0; i < N_drawmodes; i++)
    DrawModes[i] = false;
  switch (dm)
  {
  case _draw_modes::POINT:
    if (Cone->text)
    {
      e = Cone->ej;
      delete Sphere;
      delete Cone;
      delete Cylinder;

      Sphere = new _sphere(e, false);
      Cylinder = new _cylinder(e, false);
      Cone = new _cone(e, false);
    }
    DrawModes[0] = !DrawModes[0];
    break;
  case _draw_modes::FILL:
    if (Cone->text)
    {
      e = Cone->ej;
      delete Sphere;
      delete Cone;
      delete Cylinder;

      Sphere = new _sphere(e, false);
      Cylinder = new _cylinder(e, false);
      Cone = new _cone(e, false);
    }
    DrawModes[1] = !DrawModes[1];
    break;
  case _draw_modes::CHESS:
    if (Cone->text)
    {
      e = Cone->ej;
      delete Sphere;
      delete Cone;
      delete Cylinder;

      Sphere = new _sphere(e, false);
      Cylinder = new _cylinder(e, false);
      Cone = new _cone(e, false);
    }
    DrawModes[2] = !DrawModes[2];
    break;
  case _draw_modes::LINES:
    if (Cone->text)
    {
      e = Cone->ej;
      delete Sphere;
      delete Cone;
      delete Cylinder;

      Sphere = new _sphere(e, false);
      Cylinder = new _cylinder(e, false);
      Cone = new _cone(e, false);
    }
    DrawModes[8] = !DrawModes[8];
    break;
  case _draw_modes::SMOOTH:
    if (Cone->text)
    {
      e = Cone->ej;
      delete Sphere;
      delete Cone;
      delete Cylinder;

      Sphere = new _sphere(e, false);
      Cylinder = new _cylinder(e, false);
      Cone = new _cone(e, false);
    }
    DrawModes[4] = !DrawModes[4];

    break;
  case _draw_modes::FLAT:
    if (Cone->text)
    {
      e = Cone->ej;
      delete Sphere;
      delete Cone;
      delete Cylinder;

      Sphere = new _sphere(e, false);
      Cylinder = new _cylinder(e, false);
      Cone = new _cone(e, false);
    }
    DrawModes[3] = !DrawModes[3];
    break;
  case _draw_modes::TEXTURE:
    if (!Cone->text)
    {
      e = Cone->ej;
      delete Sphere;
      delete Cone;
      delete Cylinder;

      Sphere = new _sphere(e, true);
      Cylinder = new _cylinder(e, true);
      Cone = new _cone(e, true);
    }
    DrawModes[5] = !DrawModes[5];
    break;
  case _draw_modes::TEXTURE_FLAT:
    if (!Cone->text)
    {
      e = Cone->ej;
      delete Sphere;
      delete Cone;
      delete Cylinder;

      Sphere = new _sphere(e, true);
      Cylinder = new _cylinder(e, true);
      Cone = new _cone(e, true);
    }
    DrawModes[6] = !DrawModes[6];
    break;

  case _draw_modes::TEXTURE_SMOOTH:
    if (!Cone->text)
    {
      e = Cone->ej;

      delete Sphere;
      delete Cone;
      delete Cylinder;

      Sphere = new _sphere(e, true);
      Cylinder = new _cylinder(e, true);
      Cone = new _cone(e, true);
    }
    DrawModes[7] = !DrawModes[7];
    break;
  }
  update();
}

void _gl_widget::ObjectType(_object ot)
{
  switch (ot)
  {
  case _object::OBJECT_TETRAHEDRON:
    Object = _object::OBJECT_TETRAHEDRON;
    break;
  case _object::OBJECT_CUBE:
    Object = _object::OBJECT_CUBE;
    break;
  case _object::OBJECT_CONE:
    Object = _object::OBJECT_CONE;
    break;
  case _object::OBJECT_CYLINDER:
    Object = _object::OBJECT_CYLINDER;
    break;
  case _object::OBJECT_SPHERE:
    Object = _object::OBJECT_SPHERE;

    break;
  case _object::OBJECT_PLY:
    Object = _object::OBJECT_PLY;
    break;
  case _object::OBJECT_SPOT:
    Object = _object::OBJECT_SPOT;
    break;
  case _object::OBJECT_TABLERO:
    Object = _object::OBJECT_TABLERO;
    break;

  case _object::MULTIPLE_OBJECTS:
    Object = _object::MULTIPLE_OBJECTS;
    break;

  case _object::PLYS:
    Object = _object::PLYS;
    break;
  }
  update();
}

//////////////////////////////////////////////////////////////////////////////
////////// MOVER MODELO
//////////////////////////////////////////////////////////////////////////////

void _gl_widget::Forearm(_opciones opcion)
{
  int size = dogocopter->dog->legs.size();
  for (int i = 0; i < size; i++)
    switch (opcion)
    {
    case _opciones::OP1:
      if (dogocopter->dog->legs[i]->forearm->getD1() < 0)
        dogocopter->dog->legs[i]->forearm->setD1(gr1);
      break;

    case _opciones::OP2:
      if (dogocopter->dog->legs[i]->forearm->getD1() > -90)
        dogocopter->dog->legs[i]->forearm->setD1(-gr1);
      break;

    case _opciones::OP3:
      dogocopter->dog->legs[i]->forearm->setD2(gr2);
      break;
    case _opciones::OP4:
      if (dogocopter->dog->legs[i]->forearm->getD2() > 0)
        dogocopter->dog->legs[i]->forearm->setD2(-gr2);
      break;
    }

  update();
}

void _gl_widget::ArmBody(_opciones opcion)
{
  switch (opcion)
  {
    //Modificación patas delanteras.
  case _opciones::OP1:
    if (dogocopter->dog->legs[0]->getD1() < 90)
    {
      dogocopter->dog->legs[0]->setD1(gr3);
      dogocopter->dog->legs[1]->setD1(gr3);
    }
    break;
  case _opciones::OP2:
    if (dogocopter->dog->legs[0]->getD1() > -90)
    {
      dogocopter->dog->legs[0]->setD1(-gr3);
      dogocopter->dog->legs[1]->setD1(-gr3);
    }
    break;

  case _opciones::OP3:
    if (dogocopter->dog->legs[0]->getD2() < 45 && (dogocopter->dog->legs[0]->getD2() - dogocopter->dog->legs[2]->getD2()) < 45)
    {
      dogocopter->dog->legs[0]->setD2(gr4);
      dogocopter->dog->legs[1]->setD2(gr4);
    }
    break;
  case _opciones::OP4:
    if (dogocopter->dog->legs[0]->getD2() > -45 && (dogocopter->dog->legs[0]->getD2() - dogocopter->dog->legs[2]->getD2()) > -45)
    {
      dogocopter->dog->legs[0]->setD2(-gr4);
      dogocopter->dog->legs[1]->setD2(-gr4);
    }
    break;

    //Modificación patas Traseras.
  case _opciones::OP5:
    if (dogocopter->dog->legs[2]->getD1() < 90)
    {
      dogocopter->dog->legs[2]->setD1(gr3);
      dogocopter->dog->legs[3]->setD1(gr3);
    }
    break;
  case _opciones::OP6:
    if (dogocopter->dog->legs[2]->getD1() > -90)
    {
      dogocopter->dog->legs[2]->setD1(-gr3);
      dogocopter->dog->legs[3]->setD1(-gr3);
    }
    break;

  case _opciones::OP7:
    if (dogocopter->dog->legs[2]->getD2() < 45 && (dogocopter->dog->legs[2]->getD2() - dogocopter->dog->legs[0]->getD2()) < 45)
    {
      dogocopter->dog->legs[2]->setD2(gr4);
      dogocopter->dog->legs[3]->setD2(gr4);
    }
    break;
  case _opciones::OP8:
    if (dogocopter->dog->legs[2]->getD2() > -45 && (dogocopter->dog->legs[2]->getD2() - dogocopter->dog->legs[0]->getD2()) > -45)
    {
      dogocopter->dog->legs[2]->setD2(-gr4);
      dogocopter->dog->legs[3]->setD2(-gr4);
    }
    break;
  }

  dogocopter->dog->setD1(dogocopter->dog->legs[0]->getD2());
  dogocopter->dog->setD2(dogocopter->dog->legs[2]->getD2());

  dogocopter->setD2(dogocopter->dog->legs[0]->getD2() - dogocopter->dog->legs[2]->getD2());

  update();
}

void _gl_widget::Fly(_opciones opcion)
{

  switch (opcion)
  {

  case _opciones::OP1:
    dogocopter->gorrocopter->setD1(gr5);
    break;

  case _opciones::OP2:
    dogocopter->gorrocopter->setD1(-gr5);
    break;

  case _opciones::OP3:
    dogocopter->gorrocopter->setD2(gr6);
    break;
  case _opciones::OP4:
    if (dogocopter->gorrocopter->getD2() > 0)
      dogocopter->gorrocopter->setD2(-gr6);
    break;
  }

  dogocopter->setD1(dogocopter->gorrocopter->getD1());
  update();
}

//////////////////////////////////////////////////////////////////////////////
////////// MODIFCIAR RATIOS DE LOS GRADOS DE LIBERTAD DEL MODELO
//////////////////////////////////////////////////////////////////////////////

void _gl_widget::Ratios(_opciones opcion)
{
  switch (opcion)
  {

  case _opciones::OP1:
    gr1++;
    break;

  case _opciones::OP2:
    if (gr1 > 1)
      gr1--;
    break;

  case _opciones::OP3:
    gr2++;
    break;
  case _opciones::OP4:
    if (gr2 > 1)
      gr2--;
    break;

  case _opciones::OP5:
    gr3++;
    break;

  case _opciones::OP6:
    if (gr3 > 1)
      gr3--;
    break;
  case _opciones::OP7:
    gr4++;
    break;

  case _opciones::OP8:
    if (gr4 > 1)
      gr4--;
    break;

  case _opciones::OP9:
    gr5++;
    break;

  case _opciones::OP10:
    if (gr5 > 1)
      gr5--;
    break;
  case _opciones::OP11:
    gr6++;
    break;

  case _opciones::OP12:
    if (gr6 > 1)
      gr6--;
    break;
  }
  update();
}

//////////////////////////////////////////////////////////////////////////////
////////// COMENZAR Y PARAR ANIMACIÓN
//////////////////////////////////////////////////////////////////////////////
void _gl_widget::Animacion()
{

  animacion = !animacion;
  if (animacion)
    timer->start(20);
  else
    timer->stop();
  update();
}

//////////////////////////////////////////////////////////////////////////////
////////// MODIFICAR LUCES Y MATERIALES
//////////////////////////////////////////////////////////////////////////////
void _gl_widget::Luces_Materiales(_opciones opcion)
{
  switch (opcion)
  {

  case _opciones::OP1:
    first_light = !first_light;
    break;

  case _opciones::OP2:
    second_light = !second_light;
    break;

  case _opciones::OP3:
    material = (material + 1) % 3;
    break;
  case _opciones::OP4:
    flx = (flx + 4);
    break;

  case _opciones::OP5:
    fly = (fly + 4);
    break;

  case _opciones::OP6:
    flz = (flz + 4);

    break;
  case _opciones::OP7:
    flx = (flx - 4);
    break;
  case _opciones::OP8:
    fly = (fly - 4);
    break;
  case _opciones::OP9:
    flz = (flz - 4);
    break;
  }
  update();
}

//////////////////////////////////////////////////////////////////////////////
////////// CAMBIAR PERSPECTIVA
//////////////////////////////////////////////////////////////////////////////
void _gl_widget::Perspectiva(_opciones opcion)
{
  switch (opcion)
  {
  case _opciones::OP1:
    projection = false;
    break;

  case _opciones::OP2:

    projection = true;
    break;
  }

  update();
}

//////////////////////////////////////////////////////////////////////////////
////////// CAMBIAR GENERATRIZ ESFERA
//////////////////////////////////////////////////////////////////////////////
void _gl_widget::Ejes(_opciones opcion)
{

  switch (opcion)
  {
  case _opciones::OP1:
    e = eje::EJE_X;
    break;

  case _opciones::OP2:
    e = eje::EJE_Y;
    break;

  case _opciones::OP3:
    e = eje::EJE_Z;
    break;
  }

  bool aux = Sphere->text;
  delete Sphere;
  delete Cone;
  delete Cylinder;

  Sphere = new _sphere(e, aux);
  Cylinder = new _cylinder(e, aux);
  Cone = new _cone(e, aux);
  update();
}

//////////////////////////////////////////////////////////////////////////////
////////// ANIMACIÓN
//////////////////////////////////////////////////////////////////////////////
void _gl_widget::idle()
{
  float fa = (9.0 / 60.0);

  switch (F)
  {

  case _fases::F1:
    if (dogocopter->dog->legs[0]->getD1() < 90)
    {
      //Patas delanteras rot
      for (int i = 0; i < 2; i++)
        dogocopter->dog->legs[i]->setD1(gr3 * 1);

      //Patas delanteras tr
      if (dogocopter->dog->legs[0]->getD2() < 9)
      {
        for (int i = 0; i < 2; i++)
          dogocopter->dog->legs[i]->setD2(0.1 * gr4);
        dogocopter->setD2(dogocopter->dog->legs[0]->getD2() - dogocopter->dog->legs[2]->getD2());
        dogocopter->dog->setD1(dogocopter->dog->legs[0]->getD2());
        dogocopter->dog->setD2(dogocopter->dog->legs[2]->getD2());
      }

      //Antebrazos
      if (dogocopter->dog->legs[0]->forearm->getD1() > -90)
        for (int i = 0; i < 4; i++)
          dogocopter->dog->legs[i]->forearm->setD1(-1 * gr1);
    }
    else
      F = _fases::F2;
    break;

  case _fases::F2:
    if (dogocopter->dog->legs[2]->getD1() > -90)
    {
      //Patas traseras.
      for (int i = 2; i < 4; i++)
        dogocopter->dog->legs[i]->setD1(-1 * gr3);
      dogocopter->setD2(dogocopter->dog->legs[0]->getD2() - dogocopter->dog->legs[2]->getD2());
      dogocopter->dog->setD1(dogocopter->dog->legs[0]->getD2());
      dogocopter->dog->setD2(dogocopter->dog->legs[2]->getD2());

      //
      if (dogocopter->dog->legs[0]->getD2() > 0)
        for (int i = 0; i < 2; i++)
          dogocopter->dog->legs[i]->setD2(-0.1 * gr4);

      //
      if (dogocopter->dog->legs[0]->getD1() > 0)
        for (int i = 0; i < 2; i++)
          dogocopter->dog->legs[i]->setD1(-1 * gr3);
      //
      if (dogocopter->dog->legs[0]->forearm->getD1() < 0)
        for (int i = 0; i < 4; i++)
          dogocopter->dog->legs[i]->forearm->setD1(1 * gr1);

      //
      if (dogocopter->dog->legs[2]->getD2() < 9)
        for (int i = 2; i < 4; i++)
          dogocopter->dog->legs[i]->setD2(0.1 * gr4);
      //
      if (dogocopter->dog->legs[0]->forearm->getD2() < 4.5)
        for (int i = 0; i < 4; i++)
          dogocopter->dog->legs[i]->forearm->setD2(0.05 * gr2);
    }
    else
      F = _fases::F3;

    break;
  case _fases::F3:
    if (dogocopter->dog->legs[0]->getD1() > -60)
    {
      for (int i = 0; i < 2; i++)
        dogocopter->dog->legs[i]->setD1(-1 * gr3);
      dogocopter->setD2(dogocopter->dog->legs[0]->getD2() - dogocopter->dog->legs[2]->getD2());
      dogocopter->dog->setD1(dogocopter->dog->legs[0]->getD2());
      dogocopter->dog->setD2(dogocopter->dog->legs[2]->getD2());

      if (dogocopter->gorrocopter->getD1() < 90)
      {
        dogocopter->gorrocopter->setD1(1.5 * gr5);
        dogocopter->setD1(dogocopter->gorrocopter->getD1());
      }

      if (dogocopter->dog->legs[0]->forearm->getD1() > -60)
        for (int i = 0; i < 4; i++)
          dogocopter->dog->legs[i]->forearm->setD1(-1 * gr1);

      if (dogocopter->dog->legs[2]->getD1() < 60)
        for (int i = 2; i < 4; i++)
          dogocopter->dog->legs[i]->setD1(2.5 * gr3);

      if (dogocopter->dog->legs[0]->forearm->getD2() > 0)
        for (int i = 0; i < 4; i++)
          dogocopter->dog->legs[i]->forearm->setD2(-0.075 * gr2);

      if (dogocopter->gorrocopter->getD2() < 4.5)
        dogocopter->gorrocopter->setD2(0.075 * gr6);

      dogocopter->setD1(dogocopter->gorrocopter->getD1());
    }
    else
      F = _fases::F4;
    break;

  case _fases::F4:
    if (dogocopter->dog->legs[2]->getD1() > 0)
    {
      for (int i = 2; i < 4; i++)
        dogocopter->dog->legs[i]->setD1(-1 * gr3);
      dogocopter->setD2(dogocopter->dog->legs[0]->getD2() - dogocopter->dog->legs[2]->getD2());
      dogocopter->dog->setD1(dogocopter->dog->legs[0]->getD2());
      dogocopter->dog->setD2(dogocopter->dog->legs[2]->getD2());

      if (dogocopter->dog->legs[0]->forearm->getD1() > -90)
        for (int i = 0; i < 4; i++)
          dogocopter->dog->legs[i]->forearm->setD1(-0.5 * gr1);

      if (dogocopter->dog->legs[0]->getD1() < 90)
        for (int i = 0; i < 2; i++)
          dogocopter->dog->legs[i]->setD1(2.5 * gr3);

      if (dogocopter->dog->legs[2]->getD2() > 0)
        for (int i = 2; i < 4; i++)
          dogocopter->dog->legs[i]->setD2(-fa * gr4);

      if (dogocopter->dog->legs[0]->getD2() < 9)
        for (int i = 0; i < 2; i++)
          dogocopter->dog->legs[i]->setD2(fa * gr4);

      if (dogocopter->gorrocopter->getD1() > 0)
      {
        dogocopter->gorrocopter->setD1(-1.5 * gr5);
        dogocopter->setD1(dogocopter->gorrocopter->getD1());
      }

      if (dogocopter->gorrocopter->getD2() > 0)
        dogocopter->gorrocopter->setD2(-0.075 * gr6);
    }
    else
      F = _fases::F2;
    break;
  }

  update();
}

void _gl_widget::choose_ply(_opciones op)
{
  vector_plys.clear();
  vector_plys.resize(size_ply * size_ply);
  for (int i = 0; i < size_ply * size_ply; i++)
  {
    _ply aux(op);
    vector_plys[i] = aux;
  }

  Ply = new _ply(op);
  update();
}

void _gl_widget::choose_texture(_opciones op)
{
  string textura;
  textura.clear();

  switch (op)
  {
  case _opciones::OP1:
    textura += "../texturas/2k_mars.jpg";
    break;

  case _opciones::OP2:
    textura += "../texturas/2k_stars.jpg";
    break;

  case _opciones::OP3:
    textura += "../texturas/2k_sun.jpg";
    break;

  case _opciones::OP4:
    textura += "../texturas/2k_venus_surface.jpg";
    break;

  case _opciones::OP5:
    textura += "../texturas/mercury.jpg";
    break;

  case _opciones::OP6:
    textura += "../texturas/2k_earth_daymap.jpg";
    break;
  }

  Sphere->textura = textura;
  Cylinder->textura = textura;
  Cone->textura = textura;
  Tablero.textura = textura;
  update();
}
