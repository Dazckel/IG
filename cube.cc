/*! \file
 * Copyright Jose Heredia Muñoz
 * email: dazckel@correo.ugr.es
 * 2021
 * GPL 3
 */

#include "cube.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cube::_cube(float Size)
{
    Vertices.resize(8);

  Vertices[0]=_vertex3f(-Size/2,-Size/2,Size/2);
  Vertices[1]=_vertex3f(-Size/2,Size/2,Size/2);
  Vertices[2]=_vertex3f(Size/2,Size/2,Size/2);
  Vertices[3]=_vertex3f(Size/2,-Size/2,Size/2);
  Vertices[4]=_vertex3f(-Size/2,-Size/2,-Size/2);
  Vertices[5]=_vertex3f(-Size/2,Size/2,-Size/2);
  Vertices[6]=_vertex3f(Size/2,Size/2,-Size/2);
  Vertices[7]=_vertex3f(Size/2,-Size/2,-Size/2);

/*
    Edges.resize(18);

    for(unsigned int i = 0; i < Vertices.size();i++)
        Edges[i]._0 = i;
    
    for(unsigned int i = 0; i < Vertices.size();i++)
        Edges[i]._1 = i+1;

    Edges[3]._1 = 0;
    Edges[7]._1 = 4;

  Edges[8] = _vertex2i(3,7);
  Edges[9] = _vertex2i(0,4);
  Edges[10] = _vertex2i(2,6);
  Edges[11] = _vertex2i(1,5);

  Edges[12] = _vertex2i(3,1);
  Edges[13] = _vertex2i(0,5);
  Edges[14] = _vertex2i(2,5);
  Edges[15] = _vertex2i(4,6);
  Edges[16] = _vertex2i(0,7);
  Edges[17] = _vertex2i(7,2);
*/
  Triangles.resize(6*2);
  Triangles[0]=_vertex3ui(4,0,5);
  Triangles[1]=_vertex3ui(0,1,5);
  Triangles[2]=_vertex3ui(0,3,1);
  Triangles[3]=_vertex3ui(3,2,1);

  Triangles[4]=_vertex3ui(3,7,2);
  Triangles[5]=_vertex3ui(7,6,2);
  Triangles[6]=_vertex3ui(7,4,6);
  Triangles[7]=_vertex3ui(4,5,6);

  Triangles[8]=_vertex3ui(1,2,5);
  Triangles[9]=_vertex3ui(2,6,5);
  Triangles[10]=_vertex3ui(4,7,0);
  Triangles[11]=_vertex3ui(7,3,0);

}
