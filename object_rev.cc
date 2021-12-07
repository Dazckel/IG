#include "object_rev.h"
#include "math.h"

//Constructor de la clase revolución.
_revolution::_revolution()
{
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

    GenerarTriangulos(v, nr, e);
}

void _revolution::GenerarTriangulos(vector<_vertex3f> v, int nr, eje e)
{

    int nt = n_tapas(v, e); /**Número de tapas*/
    int nv_sinrep = 0;      /**Número de vertices de la plantilla que no se repiten*/
    
    if (nt == DOS_TP)
        nv_sinrep = v.size() - 2;
    else if (nt == TP_SUP || nr == TP_INF)
        nv_sinrep = v.size() - 1;

    int nv_tot = nv_sinrep * nr; /**Vértices totales de la figura, sin contar los de las tapas*/
    Triangles.resize(nv_tot * TR_IN_SQ);

    //CREACION DE LOS TRIÁNGULOS DIFERENCIANDO 3 ZONAS.
    glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
    int p = 0;

    //TRIANGULOS CENTRALES//



///FORMA GUAY DE GENERAR LOS TRIANGULOS
    //Creamos los triángulos centrales que no se repiten, y
    // la unión final-principio va  aparte en una zona contigua del vector
    for (int j = 0; j < nv_sinrep - 1; j++)
        for (int i = 0; i < nr; i++, p += TR_IN_SQ)
        {
            Triangles[p] = _vertex3ui((0 + (i * nv_sinrep)) + j, (nv_sinrep + (i * nv_sinrep)) + j, (1 + (i * nv_sinrep)) + j);
            Triangles[p + 1] = _vertex3ui((nv_sinrep + (i * nv_sinrep)) + j, (nv_sinrep + 1 + (i * nv_sinrep)) + j, (1 + (i * nv_sinrep)) + j);
        }

    //TRIANGULOS QUE CIERRAN//

    p = nr * TR_IN_SQ;
    // este bucle recorre la matriz de triangulos de arriba abajo en la última columna
    for (int i = 0; i < nv_sinrep - 1; i++, p += nr * TR_IN_SQ)
    {
        Triangles[p - 2] = _vertex3ui(i + (nr - 1) * nv_sinrep, i, i + nv_tot - (nv_sinrep - 1));
        Triangles[p - 1] = _vertex3ui(i, i + 1, nv_tot - (nv_sinrep - 1) + i);
    }

    //TRIÁNGULOS DE LAS TAPAS//

    int tamanio = nv_sinrep * nr + v.size() - nv_sinrep;
    p = nr * (nv_sinrep - 1) * TR_IN_SQ; /**Nos indica donde empezar a almacenar los triángulos que faltan*/

    if (nt == 3)
        for (int i = 0; i < nr; i++)
        { //Multiplico *2 porque ha de empezar en al 2da rotación
            Triangles[p + nr + i] = _vertex3ui(nv_sinrep - 1 + i * nv_sinrep, ((2 + i) * nv_sinrep - 1) % nv_tot, tamanio - 1);
            Triangles[p + i] = _vertex3ui(i * nv_sinrep, tamanio - 2, (nv_sinrep * (i + 1)) % nv_tot);
        }
    else
        for (int i = 0; i < nr; i++, p++)
            Triangles[p] = _vertex3ui(i * nv_sinrep, nv_tot, tamanio - 1);

    glEnd();
}

/////////////////////////////////////////////////////////
void _revolution::RotarVertices(vector<_vertex3f> v, int nr, eje e, objeto o)
{
    vector<_vertex3f> plantilla_sin_rep; /**Vector sin vertices de las tapas*/
    int n_vertices = v.size();           /**Vértices de la plantilla*/
    //Indice para el bucle que coge los vértices "centrales"
    int ind_i = 0;
    int nt = n_tapas(v, e);     /**Número de tapas de la figura*/
    int nv_sinrep = n_vertices; /**Vértices que no se repiten,supongo que no tiene tapas*/

    if (nt == DOS_TP)
    {
        ind_i++;
        nv_sinrep -= 2;
    }
    else if (nt == TP_SUP)
        nv_sinrep -= 1;
    else if (nt == TP_INF)
    {
        ind_i++;
        nv_sinrep -= 1;
    }

    plantilla_sin_rep.resize(nv_sinrep);
    for (int i = 0; i < nv_sinrep; ind_i++, i++)
        plantilla_sin_rep[i] = v[ind_i];

    double ang = 2 * M_PI / nr;
    int tamanio = nv_sinrep * nr + n_vertices - nv_sinrep;

    //Si es una esfera,rotamos media circunferencia para obtener la plantilla.
    if (o == objeto::SPHERE_P)
        ang = M_PI / nr;

    //Tamaño total que tendrá el vector de vértices: vertices que rotan + los que no
    Vertices.resize(tamanio);
    int p = 0;

    //
    //Rotamos en función del eje.

    switch (e)
    {
    case eje::EJE_X:
        for (int i = 0; i < nr; i++)
            for (int j = 0; j < nv_sinrep; j++, p++)
            {
                double R = Distancia(plantilla_sin_rep[j], _vertex3f(plantilla_sin_rep[j].x, 0, 0));
                double a = R * cos(ang * i);
                double b = R * sin(ang * i);
                Vertices[p] = _vertex3f(plantilla_sin_rep[j].x, a, b);
            }
        break;
    case eje::EJE_Y:
        for (int i = 0; i < nr; i++)
            for (int j = 0; j < nv_sinrep; j++, p++)
            {
                double R = Distancia(plantilla_sin_rep[j], _vertex3f(0, plantilla_sin_rep[j].y, 0));
                double a = R * cos(ang * i);
                double b = R * sin(ang * i);
                Vertices[p] = _vertex3f(a, plantilla_sin_rep[j].y, b);
            }
        break;
    case eje::EJE_Z:
        for (int i = 0; i < nr; i++)
            for (int j = 0; j < nv_sinrep; j++, p++)
            {
                double R = Distancia(plantilla_sin_rep[j], _vertex3f(0, 0, plantilla_sin_rep[j].z));
                double a = R * cos(ang * i);
                double b = R * sin(ang * i);
                Vertices[p] = _vertex3f(a, b, plantilla_sin_rep[j].z);
            }
        break;
    }

    //Ahora el vertice de la tapa y el de la zona baja los podemos encontrar solo en v, y en el vector de vértices no los tenemos
    //Los añadimos ahora

    //Si es una esfera, cierro la plantilla, haciendo que tenga 2 tapas ( dos vértices en el eje).
    if (o == objeto::SPHERE_P)
        Vertices.push_back(v[0] * -1);

    if (nt == DOS_TP)
    {
        Vertices[p] = v[0];
        Vertices[p + 1] = v[n_vertices - 1];
    }
    else if (nt == TP_INF)
        Vertices[p] = v[0];
    else if (nt == TP_SUP)
        Vertices[p] = v[n_vertices - 1];
}
/////////////////////////////////////////////////////////
int _revolution::n_tapas(vector<_vertex3f> v, eje e)
{
    int nt = 0;
    if (dentro_eje(v[0], e) && dentro_eje(v[v.size() - 1], e))
        nt = DOS_TP;
    else if (dentro_eje(v[0], e))
        nt = TP_INF;
    else if (dentro_eje(v[v.size() - 1], e))
        nt = TP_SUP;

    return nt;
}
/////////////////////////////////////////////////////////
bool _revolution::dentro_eje(_vertex3f p, eje e)
{
    bool dentro = false;

    switch (e)
    {
    case eje::EJE_X:
        if (p.y == 0 && p.z == 0)
            dentro = true;
        break;

    case eje::EJE_Y:
        if (p.x == 0 && p.z == 0)
            dentro = true;
        break;
    case eje::EJE_Z:
        if (p.x == 0 && p.y == 0)
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
