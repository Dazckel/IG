#include "object_rev.h"
#include "cmath"

//Constructor de la clase revolución.
_revolution::_revolution()
{
}

_revolution::_revolution(vector<_vertex3f> v, float nr, eje e, objeto o)
{
    crear_OR(v,nr,e,o);
}

float roundd(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

//Función que crea un objeto por el método de revolución
void _revolution::crear_OR(vector<_vertex3f> v, float nr, eje e, objeto o)
{

    if (text)
        RotarVertices(v, nr, e, o);
    else
        RotarVerticesOptimizado(v, nr, e, o);

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
            e = eje::EJE_Z;
            break;
        case eje::EJE_Z:
            e = eje::EJE_X;
            break;
        }
        if (text)
            RotarVertices(v, nr, e, o);
        else{
            RotarVerticesOptimizado(v, nr, e, o);
        }
    }
    nv_plantilla = v.size();
    ej = e;
    if (text)
        GenerarTriangulos(v, nr, e);
    else
        GenerarTriangulosOptimizado(v, nr, e);
}



/////////////////////////////////////////////////////////////
//////////  Genera triángulos no optimizado para TEXTURA
/////////////////////////////////////////////////////////////
void _revolution::GenerarTriangulos(vector<_vertex3f> v, float nr, eje e)
{

    int nt = n_tapas(v, e); /**Número de tapas*/
    int nv = v.size();
    //Niveles de triangulos centrales (sin degenerados)
    int lvs = (nv - 1) - num_tapas;
    //
    int nt_centrales = lvs*TR_IN_SQ*nr;
    int nt_tapas_sin_degenerados = num_tapas*nr;
    //Le estamos restando los triangulos degenerados.
    int tamanio = nt_centrales+nt_tapas_sin_degenerados;
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

    int ini = 1;

    //dependiendo de si tiene tapa superior o no el triangulo central inial comenzará en un
    //vértice o en otro
    if(nt==TP_SUP)
       ini = 0;

    for (int j = 0; j < lvs; j++)
        for (int i = 0; i < nr - 1; i++, p += TR_IN_SQ)
        {
            Triangles[p] = _vertex3ui((ini + (i * nv)) + j, ((nv + ini) + (i * nv)) + j, (ini+1 + (i * nv)) + j);
            Triangles[p + 1] = _vertex3ui(((nv + ini) + (i * nv)) + j, ((nv + ini+1) + (i * nv)) + j, (ini+1 + (i * nv)) + j);
        }

    //TRIANGULOS QUE CIERRAN//

    // este bucle recorre la matriz de triangulos de arriba abajo en la última columna
    //Hasta (nv-3) ya que, por ejemplo, con 4 vertices tenemos 3 enlaces de los cuales
    //en este bucle solo aprovechamos 1 ya que los otros 2 son de las tapas
    // y si los generasemos aquí obtendríamos triángulos degenerados.

    for (int i = 0; i < lvs; i++, p += TR_IN_SQ)
    {
        Triangles[p] = _vertex3ui(i + ini + ((nr - 1) * nv), i + ini + (nr * nv), i + 1+ini + ((nr - 1) * nv));
        Triangles[p + 1] = _vertex3ui(i + ini + (nr * nv), i + ini+1 + (nr * nv), i + 1+ini + ((nr - 1) * nv));
    }

    //TRIÁNGULOS DE LAS TAPAS//

    if (nt == DOS_TP)
        for (int i = 0; i < nr; i++, p++)
        { //Multiplico *2 porque ha de empezar en al 2da rotación
            Triangles[p] = _vertex3ui(nv - 2 + i * nv, (nv - 2 + (i + 1) * nv), nv - 1 + i * nv);
            Triangles[p + nr] = _vertex3ui((i + 1) * nv, (i + 1) * nv + 1, (1 + i * nv));
        }
    else if (nt == TP_SUP)
    {
        for (int i = 0; i < nr; i++, p++)
            Triangles[p] = _vertex3ui(nv-2 + nv*i, (i + 1) * nv +nv-2, nv - 1 + i * nv);
    }
    else if (nt == TP_INF)
    {
        for (int i = 0; i < nr; i++, p++)
            Triangles[p] = _vertex3ui(1 + nv*i, (i + 1) * nv , (i + 1) * nv +1 );
    }
    glEnd();
}

/////////////////////////////////////////////////////////
//Rotar vértices no optimizado para TEXTURA
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void _revolution::RotarVertices(vector<_vertex3f> v, float nr, eje e, objeto o)
{
    vector<_vertex3f> plantilla; /**Vector sin vertices de las tapas*/
    int nv = v.size();           /**Vértices de la plantilla*/

    plantilla.resize(nv);

    for (int i = 0; i < nv; i++)
        plantilla[i] = v[i];

    float ang = 2;
    int tamanio = nv * (nr + 1);

    //Si es una esfera,rotamos media circunferencia para obtener la plantilla.
    if (o == objeto::SPHERE_P)
    {
        ang = 1;
    }
    else{
        nv_plantilla = nv;
        num_rot = nr;
    }

/*
    // Media esfera para textura
    else     if (o == objeto::SPHERE)
    {
        ang = 1;
        nv_plantilla = nv;
        num_rot = nr;
    }

*/
    //Tamaño total que tendrá el vector de vértices: vertices que rotan + los que no

    int p = 0;
    float alpha;
    Vertices.resize(tamanio);
    //Rotamos en función del eje.
    // (i * fact) / nr)*M_PI ->  hemos simplificado el PI/180 ya que una vez tenemos que girar 360 y 360/180 == 2, y la otra es 180/180 (plantilla esfera) que es 1.
    switch (e)
    {
    case eje::EJE_X:
        for (int i = 0; i <= nr; i++)
        {
            alpha = (i * ang) / nr;
            for (int j = 0; j < nv; j++, p++)
            {
                float a = plantilla[j].y * cos(alpha * M_PI) - plantilla[j].z * sin(alpha * M_PI);
                float b = plantilla[j].y * sin(alpha * M_PI) + plantilla[j].z * cos(alpha * M_PI);
                Vertices[p] = _vertex3f(plantilla[j].x, a, b);
            }
        }
        break;
    case eje::EJE_Y:
        for (int i = 0; i <= nr; i++)
        {
            alpha = (i * ang) / nr;

            for (int j = 0; j < nv; j++, p++)
            {
                float a = plantilla[j].x * cos(alpha * M_PI) + plantilla[j].z * sin(alpha * M_PI);
                float b = -plantilla[j].x * sin(alpha * M_PI) + plantilla[j].z * cos(alpha * M_PI);
                Vertices[p] = _vertex3f(a, plantilla[j].y, b);
            }
        }
        break;
    case eje::EJE_Z:
        for (int i = 0; i <= nr; i++)
        {
            alpha = (i * ang) / nr;

            for (int j = 0; j < nv; j++, p++)
            {
                float a = plantilla[j].x * cos(alpha * M_PI) - plantilla[j].y * sin(alpha * M_PI);
                float b = plantilla[j].x * sin(alpha * M_PI) + plantilla[j].y * cos(alpha * M_PI);
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
        if (roundd(p.y) == 0 && roundd(p.z) == 0)
            dentro = true;
        break;

    case eje::EJE_Y:
        if (roundd(p.x) == 0 && roundd(p.z) == 0)
            dentro = true;
        break;
    case eje::EJE_Z:
        if (roundd(p.x) == 0 && roundd(p.y) == 0)
            dentro = true;
        break;
    }
    return dentro;
}
/////////////////////////////////////////////////////////
/////// PARA TODO MENOS TEXTURA
/////////////////////////////////////////////////////////
void _revolution::GenerarTriangulosOptimizado(vector<_vertex3f> v, float nr, eje e)
{

    int nt = n_tapas(v, e); /**Número de tapas*/
    int nv_sinrep = 0;      /**Número de vertices de la plantilla que no se repiten*/

    if (nt == DOS_TP)
        nv_sinrep = v.size() - 2;
    else if (nt == TP_SUP || nt == TP_INF)
        nv_sinrep = v.size() - 1;
    else
        nv_sinrep = v.size();

    int nv_tot = nv_sinrep * nr; /**Vértices totales de la figura, sin contar los de las tapas*/
    int nt_centrales = (nv_sinrep-1)*TR_IN_SQ*nr;
    int nt_tapas = num_tapas*nr;
    Triangles.resize(nt_centrales+nt_tapas);

    //CREACION DE LOS TRIÁNGULOS DIFERENCIANDO 3 ZONAS.
    glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
    int p = 0;

    //TRIANGULOS CENTRALES//

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
    int mod = (nv_sinrep * nr);
    if (nt == DOS_TP)
        for (int i = 0; i < nr; i++)
        { //Multiplico *2 porque ha de empezar en al 2da rotación
            Triangles[p + nr + i] = _vertex3ui(nv_sinrep - 1 + i * nv_sinrep, ((2 + i) * nv_sinrep - 1) % nv_tot, tamanio - 1);
            Triangles[p + i] = _vertex3ui(i * nv_sinrep, tamanio - 2, (nv_sinrep * (i + 1)) % nv_tot);
        }
    else if (nt == TP_SUP)
    {
        for (int i = 0; i < nr; i++, p++)
            Triangles[p] = _vertex3ui(i * nv_sinrep+1, ((i + 1) * nv_sinrep + 1) % mod, tamanio - 1);
    }
    else if (nt == TP_INF)
    {
        for (int i = 0; i < nr; i++, p++)
            Triangles[p] = _vertex3ui(i * nv_sinrep, (tamanio - 1), ((i + 1) * nv_sinrep) % mod);
    }
    glEnd();
}

/////////////////////////////////////////////////////////
// PARA TODOS LOS MODOS MENOS PARA TEXTURA.
/////////////////////////////////////////////////////////
void _revolution::RotarVerticesOptimizado(vector<_vertex3f> v, float nr, eje e, objeto o)
{
    vector<_vertex3f> plantilla; /**Vector sin vertices de las tapas*/
    int n_vertices = v.size();   /**Vértices de la plantilla*/
    //Indice para el bucle que coge los vértices "centrales"
    int ind_i = 0;
    int nt = n_tapas(v, e);     /**Número de tapas de la figura*/
    int nv_sinrep = n_vertices; /**Vértices que no se repiten,supongo que no tiene tapas*/
    int rot = nr;

    double ang = 2;
    if (o == objeto::SPHERE_P)
    {
        ang = 1;
        //Añadimos una rotación más para poder cerrar la semicircunferencia.
        nr++;
    }

//Semiesfera optimizada.
/*
    if (o == objeto::SPHERE){
        ang=1;
        nr++;
    }
*/


    //El indice inicial ind_i me sirve para dejar fuera los vertices que no rotan
    // se añaden al final.

    if (nt == DOS_TP)
    {
        ind_i++;
        nv_sinrep -= 2;
    }
    else if (nt == TP_SUP)
    {
        nv_sinrep -= 1;
    }
    else if (nt == TP_INF)
    {
        ind_i++;
        nv_sinrep -= 1;
    }

    plantilla.resize(nv_sinrep);
    for (int i = 0; i < nv_sinrep; ind_i++, i++)
        plantilla[i] = v[ind_i];

    //n_vertices - nv_sinrep == vertices de las tapas, que no rotan
    int tamanio = nv_sinrep * nr + n_vertices - nv_sinrep;

    
    //Si es una esfera,rotamos media circunferencia para obtener la plantilla.

    //Tamaño total que tendrá el vector de vértices: vertices que rotan + los que no
    Vertices.resize(tamanio);
    int p = 0;
    float alpha;
    //
    //Rotamos en función del eje.

    switch (e)
    {
    case eje::EJE_X:
        for (int i = 0; i < nr; i++)
        {
            alpha = (i * ang) / rot;
            for (int j = 0; j < nv_sinrep; j++, p++)
            {
                float a = plantilla[j].y * cos(alpha * M_PI) - plantilla[j].z * sin(alpha * M_PI);
                float b = plantilla[j].y * sin(alpha * M_PI) + plantilla[j].z * cos(alpha * M_PI);
                Vertices[p] = _vertex3f(plantilla[j].x, a, b);
            }
        }
        break;
    case eje::EJE_Y:
        for (int i = 0; i < nr; i++)
        {
            alpha = (i * ang) / rot;
            for (int j = 0; j < nv_sinrep; j++, p++)
            {
                float a = plantilla[j].x * cos(alpha * M_PI) + plantilla[j].z * sin(alpha * M_PI);
                float b = -plantilla[j].x * sin(alpha * M_PI) + plantilla[j].z * cos(alpha * M_PI);
                Vertices[p] = _vertex3f(a, plantilla[j].y, b);
            }
        }
        break;
    case eje::EJE_Z:
        for (int i = 0; i < nr; i++)
        {
            alpha = (i * ang) / rot;
            for (int j = 0; j < nv_sinrep; j++, p++)
            {
                float a = plantilla[j].x * cos(alpha * M_PI) - plantilla[j].y * sin(alpha * M_PI);
                float b = plantilla[j].x * sin(alpha * M_PI) + plantilla[j].y * cos(alpha * M_PI);
                Vertices[p] = _vertex3f(a, b, plantilla[j].z);
            }
        }
        break;
    }

    //Ahora el vertice de la tapa y el de la zona baja los podemos encontrar solo en v, y en el vector de vértices no los tenemos
    //Los añadimos ahora

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
