// #define SDL_MAIN_HANDLED
// #include <SDL.h>
// #include <stdio.h>
// #include "camera.h"

// Vector3_t *Position = NULL;

// SDL_Window *win = NULL;
#include "camera.h"

Camera_t CreateCamera(Vector3_t pos)
{
    Camera_t vec3;
    vec3.Position.x = pos.x;
    vec3.Position.y = pos.y;
    vec3.Position.z = pos.z;
    return vec3;
}