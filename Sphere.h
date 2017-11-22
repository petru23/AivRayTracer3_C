#include "Vector3.h"
#include "Draw.h"

typedef struct Sphere
{
    Vector3_t Center;
    float Radius;
    draw_color_t Color;
} Sphere_t;

Sphere_t CreateSphere(Vector3_t, float, draw_color_t);
