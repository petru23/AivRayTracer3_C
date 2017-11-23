#include "Ray.h"

// get ray from pixel x y
Ray_t ScreenPointToRay(int x, int y, float fov, int width, int height, Camera_t Camera, draw_context_t *context)
{
    float screen_space_y = tan(180 / 3.1415296 * fov / 2);
    float screen_space_x = screen_space_y * context->aspect_ratio;
    float norm_x = (float)x / width;
    float norm_y = (float)y / height;
    norm_x = (2 * norm_x - 1) * screen_space_x;
    norm_y = (1 - 2 * norm_y) * screen_space_y;
    Vector3_t P = newVector3(norm_x, norm_y, 0); //Testa modificando la z
    Ray_t ray;
    ray.Direction = Vector3_Normalized(Vector3_Sub(P, Camera.Position));
    ray.Origin = Camera.Position;
    return ray;
}

Ray_t RayShadow(HitPoint_t *hitPoint, Light_t light)
{
    Ray_t rayShadow;
    Vector3_t lightDirection = Vector3_Normalized(Vector3_Sub(light.Position, hitPoint->Position));
    rayShadow.Origin = Vector3_Add(hitPoint->Position, Vector3_Scaled(lightDirection, 0.001));
    rayShadow.Direction = lightDirection;
    return rayShadow;
}