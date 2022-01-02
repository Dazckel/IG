#include "tablero.h"

_tablero::_tablero(){

    
    float dimension = 10.0f;
    int n_casillas = 100 ;
    int nv = n_casillas+1;
    nv_plantilla = nv;
    num_rot = nv-1;
    Vertices.resize(nv*nv);

    int p = 0;
    float fact = dimension/nv;
    for(int i = 0;i<nv;i++)
        for(int j = 0;j < nv;j++,p++)
            Vertices[p] = _vertex3f(i*fact -dimension/2.0f,j*fact-dimension/2.0f,0);

    Triangles.resize(n_casillas*n_casillas*2);

    p=0;
    for(int i = 0; i < n_casillas;i++)
        for(int j = 0; j < n_casillas;j++,p+=2)
        {
            Triangles[p] = _vertex3ui(0 + j*(nv) +i ,(nv)+ j*(nv) +i ,1+j*(nv) +i);
            Triangles[p+1] = _vertex3ui((nv)+ j*(nv) +i,(nv+1) + j*(nv) +i,1+j*(nv) +i);
        }
}
