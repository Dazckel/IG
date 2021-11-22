
/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ug r.es/dmartin
 * 2003-2019
 * GPL 3
 */

#include "object3d.h"

using namespace _colors_ne;

/*****************************************************************************/ /**
 *
 *
 *
 *****************************************************************************/
void _object3D::draw_lighted_flat_smooth()
{

  compute_vertex_normals();

  GLfloat mat_specular[] = {0.2, 0.2, 0.2, 0.2};
  GLfloat light_ambient[] = {0.1, 0.1, 0.1, 0.1};
  GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
  GLfloat lightDifuse[] = {0.7, 0.7, 0.7, 0.7};

  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightDifuse);

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, (GLfloat *)&lightDifuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, (GLfloat *)&mat_specular);
  glLightfv(GL_LIGHT0, GL_AMBIENT, (GLfloat *)&light_ambient);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glShadeModel(GL_SMOOTH);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  glColor3fv((GLfloat *)&RED);
  for (unsigned int i = 0; i < Triangles.size(); i++)
  {

    glNormal3fv((GLfloat *)&NormalsV[Triangles[i]._0]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._0]);
    glNormal3fv((GLfloat *)&NormalsV[Triangles[i]._1]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._1]);
    glNormal3fv((GLfloat *)&NormalsV[Triangles[i]._2]);
    glVertex3fv((GLfloat *)&Vertices[Triangles[i]._2]);
  }
  glEnd();

  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glDisable(GL_COLOR_MATERIAL);

}

void _object3D::compute_triangles_normals()
{
  int tam = Triangles.size();
  NormalsT.resize(tam);

  for (int i = 0; i < tam; i++)
  {
    _vertex3f A = Vertices[Triangles[i]._1] - Vertices[Triangles[i]._0];
    _vertex3f B = Vertices[Triangles[i]._2] - Vertices[Triangles[i]._0];
    _vertex3f Normal;

    Normal._0 = A.y * B.z - A.z * B.y;
    Normal._1 = A.z * B.x - A.x * B.z;
    Normal._2 = A.x * B.y - A.y * B.x;

    double mod = sqrt(pow(Normal.x, 2.0) + pow(Normal.y, 2.0) + pow(Normal.z, 2.0));
    Normal.x /= mod;
    Normal.y /= mod;
    Normal.z /= mod;
    NormalsT[i] = Normal;
  }
}

void _object3D::compute_vertex_normals()
{

  compute_triangles_normals();
  int tam = Vertices.size();
  NormalsV.resize(tam);
  int comp;

  for (int i = 0; i < tam; i++)
  {
    comp = 0;
    for (int j = 0; j < Triangles.size(); j++)
    {
      if (Vertices[Triangles[j]._0] == Vertices[i])
      {
        NormalsV[i] += NormalsT[j];
        comp++;
      }
      else if (Vertices[Triangles[j]._1] == Vertices[i])
      {
        NormalsV[i] += NormalsT[j];
        comp++;
      }
      else if (Vertices[Triangles[j]._2] == Vertices[i])
      {
        NormalsV[i] += NormalsT[j];
        comp++;
      }
    }

    NormalsV[i] /= comp;
  }
}

void _object3D::draw_line()
{

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_TRIANGLES);

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

/*****************************************************************************/ /**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_fill()
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);

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

/*****************************************************************************/ /**
 *
 *
 *
 *****************************************************************************/

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
