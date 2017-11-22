#include "Vector3.h"
#ifndef CAMERA_H
#define CAMERA_H
typedef struct Camera
{
    // float left;
    // float right;
    // float top;
    // float bottom;
    Vector3_t Position;
} Camera_t;

Camera_t CreateCamera(Vector3_t);
#endif