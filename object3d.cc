
/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */

#include "object3d.h"
#include "QImage"
#include "QImageReader"
#include "QGuiApplication"
#include "QMessageBox"
#include "QDir"
#include "QObject"

using namespace _colors_ne;
_object3D::_object3D(_opciones op)
{
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
    textura += "../texturas/2k_earth_nightmap.jpg";
    break;
  }
  selected = false;
  pick_model = false;
  id_ini = 0;
  id_fin = 0;
  n_triangle_selected = 0;
  nv_plantilla = 0;
  num_rot = 0;
}


////////////////////////////////////////////////
//////////////  PICK
////////////////////////////////////////////////

int _object3D::draw_selection(int id)
{
  //Le asigno a cada triangulo un color que es su identificador.
  int size = Triangles.size();

  glBegin(GL_TRIANGLES);
  glPolygonMode(GL_FRONT, GL_FILL);
  int i;
  for (i = id; i < size + id; i++)
  {
    _vertex3f *Color = new _vertex3f();
    Color->r = (i & 0x00FF0000) >> 16;
    Color->g = (i & 0x0000FF00) >> 8;
    Color->b = i & 0x000000FF;
    (*Color) = (*Color) / 255.0;

    glColor3fv((GLfloat *)Color);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i - id]._0]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i - id]._1]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i - id]._2]);

    delete (Color);
  }
  glEnd();
  return i;
}

/*****************************************************************************/ /**
 *
 *            LUCES
 *
 *****************************************************************************/

////////////////////////////////////////////////
//////////////  SMOOTH
////////////////////////////////////////////////
void _object3D::draw_lighted_smooth(_object obj)
{

  if (obj != _object::OBJECT_SPHERE)
    compute_normals_vertex();
  else
    compute_normals_vertex_sphere();

  //la posición del usuario influye en el calculo de la especularidad
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glPolygonMode(GL_FRONT, GL_FILL);

  glBegin(GL_TRIANGLES);
  int tamT = Triangles.size();

  for (int i = 0; i < tamT; i++)
  {

    glNormal3fv((GLfloat *)&NormalsV[Triangles[i]._0]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._0]);
    glNormal3fv((GLfloat *)&NormalsV[Triangles[i]._1]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._1]);
    glNormal3fv((GLfloat *)&NormalsV[Triangles[i]._2]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._2]);
  }
  glEnd();

  glDisable(GL_NORMALIZE);
  glDisable(GL_LIGHTING);
}

////////////////////////////////////////////////
//////////////  FLAT
////////////////////////////////////////////////
void _object3D::draw_lighted_flat()
{

  compute_normals_triangles();

  //la posición del usuario influye en el calculo de la especularidad

  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBegin(GL_TRIANGLES);

  for (unsigned int i = 0; i < Triangles.size(); i++)
  {
    glNormal3fv((GLfloat *)&NormalsT[i]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._0]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._1]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._2]);
  }
  glEnd();

  glDisable(GL_NORMALIZE);
  glDisable(GL_LIGHTING);
}


void _object3D::compute_normals_vertex()
{
  int tam = Triangles.size();
  int tamV = Vertices.size();

  Veces_visitado.resize(tamV);
  NormalsT.resize(tam);
  NormalsV.resize(tamV);
  for (int i = 0; i < tamV; i++)
  {
    NormalsV[i] = _vertex3f(0, 0, 0);
    Veces_visitado[i] = 0;
  }

  for (int i = 0; i < tam; i++)
  {
    _vertex3f A = Vertices[Triangles[i]._0] - Vertices[Triangles[i]._1];
    _vertex3f B = Vertices[Triangles[i]._2] - Vertices[Triangles[i]._1];
    _vertex3f Normal = B.cross_product(A);

    NormalsT[i] = Normal.normalize();

    NormalsV[Triangles[i]._0] += Normal;
    Veces_visitado[Triangles[i]._0]++;
    NormalsV[Triangles[i]._1] += Normal;
    Veces_visitado[Triangles[i]._1]++;
    NormalsV[Triangles[i]._2] += Normal;
    Veces_visitado[Triangles[i]._2]++;
  }
  for (int i = 0; i < tamV; i++)
    NormalsV[i] /= Veces_visitado[i];
}

void _object3D::compute_normals_vertex_sphere()
{
  int tamV = Vertices.size();
  NormalsV.resize(tamV);

  for (int i = 0; i < tamV; i++)
  {
    _vertex3f NormalV = Vertices[i];
    NormalsV[i] = NormalV.normalize();
  }
}

void _object3D::compute_normals_triangles()
{
  int tam = Triangles.size();
  NormalsT.resize(tam);

  for (int i = 0; i < tam; i++)
  {
    _vertex3f A = Vertices[Triangles[i]._0] - Vertices[Triangles[i]._1];
    _vertex3f B = Vertices[Triangles[i]._2] - Vertices[Triangles[i]._1];
    _vertex3f Normal;

    Normal = B.cross_product(A);
    NormalsT[i] = Normal.normalize();
  }
}


/*****************************************************************************/ /**
 *
 *      BÁSICOS
 *
 *****************************************************************************/

void _object3D::draw_line()
{

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_TRIANGLES);
  glColor3fv((GLfloat *)&RED);
  int Vertex_1, Vertex_2, Vertex_3;

  for (unsigned int i = 0; i < Triangles.size(); i++)
  {

    Vertex_1 = Triangles[i]._0;
    Vertex_2 = Triangles[i]._1;
    Vertex_3 = Triangles[i]._2;

    glVertex3fv((GLfloat *)&Vertices[Vertex_1]);
    glVertex3fv((GLfloat *)&Vertices[Vertex_2]);
    glVertex3fv((GLfloat *)&Vertices[Vertex_3]);
  }

  glEnd();
}



void _object3D::draw_fill()
{
  int size = Triangles.size();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);

  if (selected)
  {

    for (int i = 0; i < n_triangle_selected; i++)
    {
      glColor3fv((GLfloat *)&BLUE);

      glVertex3fv((GLfloat *)&Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *)&Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *)&Vertices[Triangles[i]._2]);
    }
    glColor4f(1.0f, 1.0f, 0.0f, 0.0f);

    glVertex3fv((GLfloat *)&Vertices[Triangles[n_triangle_selected]._0]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[n_triangle_selected]._1]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[n_triangle_selected]._2]);

    for (int i = n_triangle_selected + 1; i < size; i++)
    {
      glColor3fv((GLfloat *)&BLUE);

      glVertex3fv((GLfloat *)&Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *)&Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *)&Vertices[Triangles[i]._2]);
    }
  }
  else
  {
    for (int i = 0; i < size; i++)
    {
      glColor3fv((GLfloat *)&BLUE);

      glVertex3fv((GLfloat *)&Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *)&Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *)&Vertices[Triangles[i]._2]);
    }
  }

  glEnd();
}


void _object3D::draw_chess()
{

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);

  int Vertex_1, Vertex_2, Vertex_3;

  for (unsigned int i = 0; i < Triangles.size(); i++)
  {

    Vertex_1 = Triangles[i]._0;
    Vertex_2 = Triangles[i]._1;
    Vertex_3 = Triangles[i]._2;

    if (i % 2 == 0)
      glColor3fv((GLfloat *)&RED);
    else
      glColor3fv((GLfloat *)&GREEN);

    glVertex3fv((GLfloat *)&Vertices[Vertex_1]);
    glVertex3fv((GLfloat *)&Vertices[Vertex_2]);
    glVertex3fv((GLfloat *)&Vertices[Vertex_3]);
  }

  glEnd();
}


/*****************************************************************************/ /**
 *
 *          TEXTURAS
 *
 *****************************************************************************/

void _object3D::draw_texture_flat()
{

  compute_normals_triangles();

  // Code for reading an image
  QString File_name(textura.c_str());
  QImage Image;
  QImageReader Reader(File_name);
  Reader.setAutoTransform(true);
  Image = Reader.read();

  Image = Image.mirrored();
  Image = Image.convertToFormat(QImage::Format_RGB888);

  // Code to control the application of the texture
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  // Code to pass the image to OpenGL to form a texture 2D
  glTexImage2D(GL_TEXTURE_2D, 0, 3, Image.width(), Image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, Image.bits());

  //Ahora tenemos una imagen en 2D, solo falta asignar las coordenadas de textura.

  texture_coordinate.resize(Vertices.size());
  int p = 0;
  float fact_y = 1.0f / nv_plantilla;
  float fact_x = 1.0f / num_rot;

  for (int i = 0; i <= num_rot; i++)
    for (int j = 0; j < nv_plantilla; j++, p++)
      texture_coordinate[p] = _vertex2f(i * fact_x, j * fact_y);

  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLES);

  for (unsigned int i = 0; i < Triangles.size(); i++)
  {
    glNormal3fv((GLfloat *)&NormalsT[i]);
    glTexCoord2fv((GLfloat *)&texture_coordinate[Triangles[i]._0]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._0]);
    glTexCoord2fv((GLfloat *)&texture_coordinate[Triangles[i]._1]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._1]);
    glTexCoord2fv((GLfloat *)&texture_coordinate[Triangles[i]._2]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._2]);
  }
  
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_NORMALIZE);
  glDisable(GL_LIGHTING);
}

void _object3D::draw_texture()
{
  // Code for reading an image
  QString File_name(textura.c_str());
  QImage Image;
  QImageReader Reader(File_name);
  Reader.setAutoTransform(true);
  Image = Reader.read();
  //compute_texture_coordinates();
  if (Image.isNull())
  {
    //QMessageBox::information(this, QGuiApplication::applicationDisplayName(),QObject::tr("Cannot load %1.").arg(QDir::toNativeSeparators(File_name)));
    exit(-1);
  }
  Image = Image.mirrored();
  Image = Image.convertToFormat(QImage::Format_RGB888);

  // Code to control the application of the texture
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  // Code to pass the image to OpenGL to form a texture 2D
  glTexImage2D(GL_TEXTURE_2D, 0, 3, Image.width(), Image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, Image.bits());

  //Ahora tenemos una imagen en 2D, solo falta asignar las coordenadas de textura.

  texture_coordinate.resize(Vertices.size());
  int p = 0;
  float fact_y = 1.0f / nv_plantilla;
  float fact_x = 1.0f / num_rot;
  for (int i = 0; i <= num_rot; i++)
    for (int j = 0; j < nv_plantilla; j++, p++)
      texture_coordinate[p] = _vertex2f(i * fact_x, j * fact_y);

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLES);

  for (unsigned int i = 0; i < Triangles.size(); i++)
  {

    glTexCoord2fv((GLfloat *)&texture_coordinate[Triangles[i]._0]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._0]);
    glTexCoord2fv((GLfloat *)&texture_coordinate[Triangles[i]._1]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._1]);
    glTexCoord2fv((GLfloat *)&texture_coordinate[Triangles[i]._2]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._2]);
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void _object3D::draw_texture_smooth(_object obj)
{

  if (obj != _object::OBJECT_SPHERE)
    compute_normals_vertex();
  else
    compute_normals_vertex_sphere();

  // Code for reading an image
  QString File_name(textura.c_str());
  QImage Image;
  QImageReader Reader(File_name);
  Reader.setAutoTransform(true);
  Image = Reader.read();

  Image = Image.mirrored();
  Image = Image.convertToFormat(QImage::Format_RGB888);

  // Code to control the application of the texture
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  // Code to pass the image to OpenGL to form a texture 2D
  glTexImage2D(GL_TEXTURE_2D, 0, 3, Image.width(), Image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, Image.bits());

  //Ahora tenemos una imagen en 2D, solo falta asignar las coordenadas de textura.

  texture_coordinate.resize(Vertices.size());
  int p = 0;
  float fact_y = 1.0f / nv_plantilla;
  float fact_x = 1.0f / num_rot;
  for (int i = 0; i <= num_rot; i++)
    for (int j = 0; j < nv_plantilla; j++, p++)
      texture_coordinate[p] = _vertex2f(i * fact_x, j * fact_y);

  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLES);

  for (unsigned int i = 0; i < Triangles.size(); i++)
  {
    glNormal3fv((GLfloat *)&NormalsV[Triangles[i]._0]);
    glTexCoord2fv((GLfloat *)&texture_coordinate[Triangles[i]._0]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._0]);
    glNormal3fv((GLfloat *)&NormalsV[Triangles[i]._1]);
    glTexCoord2fv((GLfloat *)&texture_coordinate[Triangles[i]._1]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._1]);
    glNormal3fv((GLfloat *)&NormalsV[Triangles[i]._2]);
    glTexCoord2fv((GLfloat *)&texture_coordinate[Triangles[i]._2]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._2]);
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_NORMALIZE);
  glDisable(GL_LIGHTING);
}
