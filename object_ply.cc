/*
* Practicas de IG
* Jose Heredia Muñoz© 2021-2022
*
* GPL 3
*/

#include "object_ply.h"

_ply::_ply(_opciones op ){

    //Abrimos el fichero.
    _file_ply obj;
    switch (op)
    {
    case _opciones::OP1:
        fichero.clear();
        fichero += "/home/dazckel/Facultad/IG/ply_models/big_dodge.ply";
        break;

    case _opciones::OP2:
        fichero.clear();
        fichero += "/home/dazckel/Facultad/IG/ply_models/beethoven.ply";
        break;

    case _opciones::OP3:
        fichero.clear();
        fichero += "/home/dazckel/Facultad/IG/ply_models/ant.ply";
        break;
    }
    obj.open(fichero);

    vector<float> coord;
    vector<unsigned int> pos;
    //Obtenemos las coordenadas de los puntos y la posicion que ocupan.
    obj.read(coord,pos);
    obj.close();


    //rellenamos el vector de vértices
    int tam = coord.size();
    Vertices.resize(tam/3);

    int k = 0;
    for(int i = 0 ; i < tam;i+=3,k++)
    {
        Vertices[k].x = coord[i];
        Vertices[k].y = coord[i+1];
        Vertices[k].z = coord[i+2];
    }

    //Creamos los triangulos
    int siz =pos.size();
    Triangles.resize(siz/3);
    k=0;
    for(int i = 0;i < siz;i+=3,k++)
        Triangles[k] = _vertex3ui(pos[i],pos[i+1],pos[i+2]);


}

