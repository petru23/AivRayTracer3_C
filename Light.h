#include "Vector3.h"
#ifndef LIGHT_H
#define LIGHT_H
typedef struct Light
{
    Vector3_t Position;
} Light_t;

Light_t CreateLight(Vector3_t);
#endif