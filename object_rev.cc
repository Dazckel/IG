#include "object_rev.h"
#include "math.h"


//Constructor de la clase revolución.
_revolution::_revolution()
{


}


//Función que crea un objeto por el método de revolución
void _revolution::crear_OR(vector<_vertex3f> v, int nr,eje e,objeto o)
{
  RotarVertices(v,nr,e,o);


    //ESFERA
  if(o == objeto::SPHERE_P){
        v = Vertices;
        o = objeto::SPHERE;

        switch (e)
        {
        case eje::EJE_X:
            v[v.size()-1].z = 0;
            e = eje::EJE_Y;
            break;
        case eje::EJE_Y:
            v[v.size()-1].z = 0;
            e = eje::EJE_X;
            break;
        case eje::EJE_Z:
            e = eje::EJE_X;
            break;
        }
        RotarVertices(v,nr,e,o);
  }
  
  GenerarTriangulos(v,nr,e);
}

void _revolution::GenerarTriangulos(vector<_vertex3f> v,int nr,eje e)
{
    int nv_sinrep = 0;


    //Cojemos aquellos vértices que no se encuentren en la tapa.
    for(unsigned int i = 0; i < v.size();i++)
        if(!dentro_eje(v[i],e))
            nv_sinrep++;

    //Núemro de vértices que vamos a rotar.
    int nv_rot = nv_sinrep*nr;

    //Creamos los triángulos
    int size = nv_rot*2;
    Triangles.resize(size);

    int p = 0;

    glPolygonMode(GL_FRONT_AND_BACK,GL_TRIANGLES);

////////////////////////////////////////////////////////////////////////////////////////////////
        //TRIANGULOS CENTRALES
////////////////////////////////////////////////////////////////////////////////////////////////       
        //Creamos los triángulos centrales que no se repiten, y
        // la unión final-principio va  aparte en una zona contigua del vector
        for(int j = 0; j < nv_sinrep-1;j++)
            for(int i = 0; i < nr;i++,p+=2){
                Triangles[p]   = _vertex3ui((0+(i*nv_sinrep))+j ,(nv_sinrep+(i*nv_sinrep))+j,(1+(i*nv_sinrep))+j);
                Triangles[p+1] = _vertex3ui((nv_sinrep+(i*nv_sinrep))+j,(nv_sinrep+1+(i*nv_sinrep))+j,(1+(i*nv_sinrep))+j);
            }


////////////////////////////////////////////////////////////////////////////////////////////////
        //TRIANGULOS QUE CIERRAN.
////////////////////////////////////////////////////////////////////////////////////////////////
        //Triangulos del final: tf
        int tf= nr*2;
        p=tf;
        // este bucle recorre la matriz de triangulos de arriba abajo, osea, la ultima columna
        //que son aquellos triangulos que cierran la figura.
        for(int i =0; i < nv_sinrep-1;i++,p+=tf)
        {
                Triangles[p-2]   = _vertex3ui(i+(nr-1)*nv_sinrep,i,i+nv_rot-(nv_sinrep-1));
                Triangles[p-1]   = _vertex3ui(i,i+1,nv_rot-(nv_sinrep-1)+i);
        }

////////////////////////////////////////////////////////////////////////////////////////////////
        //TAPAS
////////////////////////////////////////////////////////////////////////////////////////////////

    int tamanio = nv_sinrep*nr+ v.size()-nv_sinrep;

    //Establecemos el indice donde corresponda.
    //Restamos 1 porque con 1v no se crea nada, con 2v se crea una fila de triangulos, con 3v dos filas...
    //Multiplicamos*2 porque en cada iteración del bucle de los triangulos centrales, creabamos 2 triangulos
    // el par y el impar.
    p=nr*(nv_sinrep-1)*2;
    

    //Se hace en 3 partes, porque según tengra 1 o 2 tapas, el vertice que cierra ocupa posicione fiderentes del vector.
    
    int nt = n_tapas(v,e);
    if(nt==3)
        for(int i = 0; i < nr;i++){                           //Multiplico *2 porque ha de empezar en al 2da rotación
            Triangles[p+nr+i]   = _vertex3ui(nv_sinrep-1 + i*nv_sinrep,((2+i)*nv_sinrep-1)%nv_rot ,tamanio-1);
            Triangles[p+i]   = _vertex3ui(i*nv_sinrep,tamanio-2,(nv_sinrep*(i+1))%nv_rot);
        }
    else
        for(int i = 0; i < nr;i++,p++)
            Triangles[p] = _vertex3ui(i*nv_sinrep,nv_rot,tamanio-1);
    glEnd();
}

//Nos dice que  vertice/punto se encuentra dentro del eje Y
bool _revolution::dentro_eje(_vertex3f p,eje e)
{
    bool dentro = false;
    
    switch (e)
    {
    case eje::EJE_X:
        if(p.y==0  && p.z==0)
        dentro = true;
        
        break;
          

    case eje::EJE_Y:
        if(p.x==0  && p.z==0)
            dentro = true;
        break;
      
    
    case eje::EJE_Z:
        if(p.x==0  && p.y==0)
            dentro = true;
        break;
      
    }
    return dentro;
}


void _revolution::RotarVertices(vector<_vertex3f> v,int nr,eje e,objeto o)
{
    //Vector/plantilla que no contiene los vértices de la tapa, es decir, los que se repiten
    //Usaremos este vector para efectuar las rotaciones, ya que los vértices que si podemos rotar si son
    //vertices diferentes en el espacio.
    vector<_vertex3f> plantilla_sin_rep;

    //Rellenamos nuestra plantilla sin repetidos.
    for(unsigned int i = 0; i < v.size();i++)
        if(!dentro_eje(v[i],e))
            plantilla_sin_rep.push_back(v[i]);
    
    //Calculamos el angulo con el que efetuaremos las rotaciones

    
    double ang = 2*M_PI/nr;
    int nv_sinrep =  plantilla_sin_rep.size();
    int tamanio = nv_sinrep*nr+ v.size()-nv_sinrep;



    //Si es una esfera,rotamos media circunferencia para obtener la plantilla.
    if((o == objeto::SPHERE_P)){
        ang = M_PI/nr;
        nr++;
        tamanio++;
    }

    //nvertices que no se repiten


    //Tamaño total que tendrá el vector de vértices: vertices que rotan + los que no 


    Vertices.resize(tamanio);
    
    int p = 0;

//
    //Rotamos en función del eje.



            switch (e)
            {
            case eje::EJE_X:
                for(int i = 0; i < nr;i++)
                    for(int j = 0;j<nv_sinrep;j++,p++){
                double R = Distancia(plantilla_sin_rep[j],_vertex3f(plantilla_sin_rep[j].x,0,0));
                double a = R*cos(ang*i);
                double b = R*sin(ang*i);
                Vertices[p] = _vertex3f(plantilla_sin_rep[j].x,a,b);
                    }
            break;
            case eje::EJE_Y:
                for(int i = 0; i < nr;i++)
                    for(int j = 0;j<nv_sinrep;j++,p++){
                double R = Distancia(plantilla_sin_rep[j],_vertex3f(0,plantilla_sin_rep[j].y,0));
                double a = R*cos(ang*i);
                double b = R*sin(ang*i);
                Vertices[p] = _vertex3f(a,plantilla_sin_rep[j].y,b);
                    }
            break;
            case eje::EJE_Z:
                for(int i = 0; i < nr;i++)
                    for(int j = 0;j<nv_sinrep;j++,p++){
                        double R = Distancia(plantilla_sin_rep[j],_vertex3f(0,0,plantilla_sin_rep[j].z));
                        double a = R*cos(ang*i);
                        double b = R*sin(ang*i);
                Vertices[p] = _vertex3f(a,b,plantilla_sin_rep[j].z);
                    }
            break;

        }
    

    //Ahora el vertice de la tapa y el de la zona baja los podemos encontrar solo en v, y en el vector de vértices no los tenemos
    //Los añadimos ahora


    //Número de vértices de la plantilla
    int n_vertices = v.size();

    int nt = n_tapas(v,e);

    if(nt==3){
        Vertices[p] = v[0];
        Vertices[p+1] = v[n_vertices-1];
    }else if(nt == 2)
        Vertices[p] = v[0];
    else if(nt==1)
        Vertices[p] = v[n_vertices-1];

}



//Nos dice cuantas tapas tiene nuestro perfil.
//Devuelve un entero que indica:
//  -3 -> tiene tapa superior e inferior.
//  -2 -> Tiene tapa inferior
//  -1 -> Tiene tapa superior

int _revolution::n_tapas(vector<_vertex3f> v,eje e)
{   
    int nt=0;

    switch (e)
    {
    case eje::EJE_X:


      if(v[0].z==0 && v[v.size()-1].z==0 && v[0].y==0 && v[v.size()-1].y==0)
        nt=3;
    else if(v[0].z==0  && v[0].y==0)
        nt=2;
    else if(v[v.size()-1].y==0 && v[v.size()-1].z==0)
        nt = 1;
    break;
        

    case eje::EJE_Y:

    if(v[0].z==0 && v[v.size()-1].z==0 && v[0].x==0 && v[v.size()-1].x==0)
        nt=3;
    else if(v[0].z==0  && v[0].x==0)
        nt=2;
    else if(v[v.size()-1].x==0 && v[v.size()-1].z==0)
        nt = 1;
    break;

    case eje::EJE_Z:

    if(v[0].y==0 && v[v.size()-1].y==0 && v[0].x==0 && v[v.size()-1].x==0)
        nt=3;
    else if(v[0].y==0  && v[0].x==0)
        nt=2;
    else if(v[v.size()-1].x==0 && v[v.size()-1].y==0)
        nt = 1;

    break;
    }

    return nt;
}



float _revolution::Distancia(_vertex3f p1, _vertex3f p2)
{
    return sqrt(pow(p1.x -p2.x,2)+pow(p1.y -p2.y,2)+pow(p1.z -p2.z,2));
}

