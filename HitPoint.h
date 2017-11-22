#ifndef HITPOINT_H
#define HITPOINT_H
typedef struct HitPoint
{
    Vector3_t Position;
    Vector3_t Normal;
    draw_color_t Color;
    float Distance;
} HitPoint_t;
#endif