/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "object3d.h"

using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_line()
{

  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glBegin(GL_TRIANGLES);

  int Vertex_1,Vertex_2,Vertex_3;

  for(unsigned int i = 0; i < Triangles.size();i++){

    Vertex_1=Triangles[i]._0;
    Vertex_2=Triangles[i]._1;
    Vertex_3=Triangles[i]._2;

    glVertex3fv((GLfloat*) &Vertices[Vertex_1]);
    glVertex3fv((GLfloat*) &Vertices[Vertex_2]);
    glVertex3fv((GLfloat*) &Vertices[Vertex_3]);

  }

  glEnd();
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_fill()
{
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);

  int Vertex_1,Vertex_2,Vertex_3;

  for(unsigned int i = 0; i < Triangles.size();i++){

    Vertex_1=Triangles[i]._0;
    Vertex_2=Triangles[i]._1;
    Vertex_3=Triangles[i]._2;

    glVertex3fv((GLfloat*) &Vertices[Vertex_1]);
    glVertex3fv((GLfloat*) &Vertices[Vertex_2]);
    glVertex3fv((GLfloat*) &Vertices[Vertex_3]);

  }

  glEnd();
  
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_chess()
{
  
  glBegin(GL_TRIANGLES);

  int Vertex_1,Vertex_2,Vertex_3;

  for(unsigned int i = 0; i < Triangles.size();i++){

    Vertex_1=Triangles[i]._0;
    Vertex_2=Triangles[i]._1;
    Vertex_3=Triangles[i]._2;

    if(i%2 == 0)
      glColor3fv((GLfloat *) &RED);
    else 
      glColor3fv((GLfloat *) &GREEN) ;

    glVertex3fv((GLfloat*) &Vertices[Vertex_1]);
    glVertex3fv((GLfloat*) &Vertices[Vertex_2]);
    glVertex3fv((GLfloat*) &Vertices[Vertex_3]);

  }

  glEnd();

}
/*
void _object3D::mover(_vertex3f vt){

  int n_puntos = Vertices.size();

  for(int i = 0; i < n_puntos;i++)
  {
    Vertices[i].x += vt.x;
    Vertices[i].y += vt.y;
    Vertices[i].z += vt.z;
  }
}


void _object3D::ampliar(_vertex3f v)
{

}
*/