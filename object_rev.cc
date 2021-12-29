#include "object_rev.h"
#include "cmath"

//Constructor de la clase revolución.
_revolution::_revolution()
{
}

float roundd(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

//Función que crea un objeto por el método de revolución
void _revolution::crear_OR(vector<_vertex3f> v, int nr, eje e, objeto o)
{
    RotarVertices(v, nr, e, o);

    //ESFERA
    //El modo en el que genero la esfera es rotando dos veces, en 2 ejes distintos
    if (o == objeto::SPHERE_P)
    {
        v = Vertices;
        o = objeto::SPHERE;

        switch (e)
        {
        case eje::EJE_X:
            e = eje::EJE_Y;
            break;
        case eje::EJE_Y:
            e = eje::EJE_X;
            break;
        case eje::EJE_Z:
            e = eje::EJE_X;
            break;
        }
        RotarVertices(v, nr, e, o);
    }
    nv_plantilla = v.size();
    GenerarTriangulos(v, nr, e);
}

void _revolution::GenerarTriangulos(vector<_vertex3f> v, int nr, eje e)
{

    int nt = n_tapas(v, e); /**Número de tapas*/
    int nv = v.size();

    //Le estamos restando los triangulos degenerados.
    int tamanio = ((nv - 1) * nr - nr) * TR_IN_SQ;
    Triangles.resize(tamanio);

    //CREACION DE LOS TRIÁNGULOS DIFERENCIANDO 3 ZONAS.
    glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
    int p = 0;

    ///No generamos los triángulos degenerados.

    //Creamos los triángulos centrales que no se repiten, y
    // la unión final-principio va  aparte en una zona contigua del vector

    //TRIANGULOS CENTRALES.

    //¿ Qué hace cada índice?
    //  - i -> avanza horizontalmente por el desarroll de la figura.
    //  - j -> avanza verticalmente por el desarrollo de la figura.

    int lvs = (nv - 1) - num_tapas;
    for (int j = 0; j < lvs; j++)
        for (int i = 0; i < nr - 1; i++, p += TR_IN_SQ)
        {
            Triangles[p] = _vertex3ui((1 + (i * nv)) + j, ((nv + 1) + (i * nv)) + j, (2 + (i * nv)) + j);
            Triangles[p + 1] = _vertex3ui(((nv + 1) + (i * nv)) + j, ((nv + 2) + (i * nv)) + j, (2 + (i * nv)) + j);
        }

    //TRIANGULOS QUE CIERRAN//

    // este bucle recorre la matriz de triangulos de arriba abajo en la última columna
    //Hasta (nv-3) ya que, por ejemplo, con 4 vertices tenemos 3 enlaces de los cuales
    //en este bucle solo aprovechamos 1 ya que los otros 2 son de las tapas
    // y si los generasemos aquí obtendríamos triángulos degenerados.

    for (int i = 0; i < lvs; i++, p += TR_IN_SQ)
    {
        Triangles[p] = _vertex3ui(i + 1 + ((nr - 1) * nv), i + 1 + (nr * nv), i + 2 + ((nr - 1) * nv));
        Triangles[p + 1] = _vertex3ui(i + 1 + (nr * nv), i + 2 + (nr * nv), i + 2 + ((nr - 1) * nv));
    }

    //TRIÁNGULOS DE LAS TAPAS//

    if (nt == 3)
        for (int i = 0; i < nr; i++, p++)
        { //Multiplico *2 porque ha de empezar en al 2da rotación
            Triangles[p] = _vertex3ui(nv - 2 + i * nv, (nv - 2 + (i + 1) * nv), nv - 1 + i * nv);
            Triangles[p + nr] = _vertex3ui((i + 1) * nv, (i + 1) * nv + 1, (1 + i * nv));
        }
    else if (nt == 2)
        for (int i = 0; i < nr; i++, p++)
            Triangles[p] = _vertex3ui((i + 1) * nv, (i + 1) * nv + 1, (1 + i * nv));
    else
        for (int i = 0; i < nr; i++, p++)
            Triangles[p] = _vertex3ui(nv - 2 + i * nv, (nv - 2 + (i + 1) * nv), nv - 1 + i * nv);

    glEnd();
}

/////////////////////////////////////////////////////////
void _revolution::RotarVertices(vector<_vertex3f> v, int nr, eje e, objeto o)
{
    vector<_vertex3f> plantilla; /**Vector sin vertices de las tapas*/
    int nv = v.size();           /**Vértices de la plantilla*/

    plantilla.resize(nv);

    for (int i = 0; i < nv; i++)
        plantilla[i] = v[i];

    float fact = 2;
    int tamanio = nv * (nr + 1);

    //Si es una esfera,rotamos media circunferencia para obtener la plantilla.
    if (o == objeto::SPHERE_P)
        fact = 1;
    else
    {
        nv_plantilla = nv;
        num_rot = nr;
    }
    //Tamaño total que tendrá el vector de vértices: vertices que rotan + los que no
    Vertices.resize(tamanio);
    int p = 0;

    //Rotamos en función del eje.
    // (i * fact) / nr)*M_PIl ->  hemos simplificado el PI/180 ya que una vez tenemos que girar 360 y 360/180 == 2, y la otra es 180/180 (plantilla esfera) que es 1.
    switch (e)
    {
    case eje::EJE_X:
        for (int i = 0; i <= nr; i++)
        {
            
            for (int j = 0; j < nv; j++, p++)
            {
                float a = plantilla[j].y * cos(((i * fact) / nr)*M_PIl) - plantilla[j].z * sin(((i * fact) / nr)*M_PIl);
                float b = plantilla[j].y * sin(((i * fact) / nr)*M_PIl) + plantilla[j].z * cos(((i * fact) / nr)*M_PIl);
                Vertices[p] = _vertex3f(plantilla[j].x, a, b);
            }
        }
        break;
    case eje::EJE_Y:
        for (int i = 0; i <= nr; i++)
        {
            
            for (int j = 0; j < nv; j++, p++)
            {
                float a = plantilla[j].x * cos(((i * fact) / nr)*M_PIl) + plantilla[j].z * sin(((i * fact) / nr)*M_PIl);
                float b = -plantilla[j].x * sin(((i * fact) / nr)*M_PIl) + plantilla[j].z * cos(((i * fact) / nr)*M_PIl);
                Vertices[p] = _vertex3f(a, plantilla[j].y, b);
            }
        }
        break;
    case eje::EJE_Z:
        for (int i = 0; i <= nr; i++)
        {
            
            for (int j = 0; j < nv; j++, p++)
            {
                float a = plantilla[j].x * cos((i * fact) / nr*M_PIl) - plantilla[j].y * sin((i * fact) / nr*M_PIl);
                float b = plantilla[j].x * sin((i * fact) / nr*M_PIl) + plantilla[j].y * cos((i * fact) / nr*M_PIl);
                Vertices[p] = _vertex3f(a, b, plantilla[j].z);
            }
        }
        break;
    }
}
/////////////////////////////////////////////////////////
int _revolution::n_tapas(vector<_vertex3f> v, eje e)
{
    int nt = 0;
    if (dentro_eje(v[0], e) && dentro_eje(v[v.size() - 1], e))
    {
        nt = DOS_TP;
        num_tapas = 2;
    }
    else if (dentro_eje(v[0], e))
    {
        nt = TP_INF;
        num_tapas = 1;
    }
    else if (dentro_eje(v[v.size() - 1], e))
    {
        nt = TP_SUP;
        num_tapas = 1;
    }

    return nt;
}
/////////////////////////////////////////////////////////
bool _revolution::dentro_eje(_vertex3f p, eje e)
{
    bool dentro = false;

    switch (e)
    {
    case eje::EJE_X:
        if (round(p.y) == 0 && round(p.z) == 0)
            dentro = true;
        break;

    case eje::EJE_Y:
        if (round(p.x) == 0 && round(p.z) == 0)
            dentro = true;
        break;
    case eje::EJE_Z:
        if (round(p.x) == 0 && round(p.y) == 0)
            dentro = true;
        break;
    }
    return dentro;
}
/////////////////////////////////////////////////////////
float _revolution::Distancia(_vertex3f p1, _vertex3f p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}
