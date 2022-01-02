#ifndef DOGOCOPTER_H
#define DOGOCOPTER_H

#include "gorrocopter.h"
#include "dog.h"

class _dogocopter
{
public:
    _dogocopter();
    void Draw_xxx(_draw_modes_model dm);

    _dog *dog;
    _gorrocopter *gorrocopter;
    void setD1(float v);
    void setD2(float v);



private:
    float tr; //Movemos el modelo cuando vuele
    float rot;
};

#endif //DOGOCOPTER_H