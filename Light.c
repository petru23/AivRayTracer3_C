#include "Light.h"

Light_t CreateLight(Vector3_t position)
{
    Light_t vec3;
    vec3.Position = position;
    return vec3;
}