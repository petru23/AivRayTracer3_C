#define SDL_MAIN_HANDLED
#include "Vector3.h"
#include <math.h>
#include <float.h>
#include "Sphere.h"
#include "Light.h"
#include "camera.h"
#include "Ray.h"
#include "HitPoint.h"
#include "Draw.h"

#define BLACK {0, 0, 0, 255}
#define RED {255, 0, 0, 255}
#define YELLOW {255, 255, 0, 255}
#define GREEN {0, 255, 0, 255}
#define BLUE {0, 0, 255, 255}

#define SPHERE0 { {0, 0, 100}, 3, YELLOW }
#define SPHERE1 { {2, 2, 150}, 5, RED }
#define SPHERE2 { {-3, -1, 200}, 6, BLUE }

draw_color_t black = BLACK;
draw_color_t red = RED;
draw_color_t yellow = YELLOW;
draw_color_t green = GREEN;
draw_color_t blue = BLUE;

Sphere_t spheres[] = {SPHERE0, SPHERE1, SPHERE2};

// returns true if hit, set hitPoint to wathever the ray hit
int HitByRay(Ray_t ray, HitPoint_t *hitPoint, Light_t light)
{
    hitPoint->Color = black;
    hitPoint->Distance = FLT_MAX;
    hitPoint->Normal = newVector3(0, 0, 0);
    hitPoint->Position = newVector3(0, 0, 0);

    for (int i = 0; i < sizeof(spheres); i++)
    {
        Sphere_t sphere = spheres[i];
        Vector3_t l = Vector3_Sub(sphere.Center, ray.Origin);
        float tca = Vector3_Dot(l, ray.Direction);
        if (tca <= 0)
            continue;

        float d = sqrt((Vector3_Length(l) * Vector3_Length(l)) - (tca * tca));
        if (d > sphere.Radius)
            continue;

        float thc = sqrt((sphere.Radius * sphere.Radius) - (d * d));
        float t0 = tca - thc;
        float t1 = tca + thc;

        if (t1 < t0)
            hitPoint->Distance = t1;
        else
            hitPoint->Distance = t0;

        hitPoint->Position = Vector3_Add(ray.Origin, Vector3_Scaled(ray.Direction, hitPoint->Distance));
        hitPoint->Color = sphere.Color;
        hitPoint->Normal = Vector3_Normalized(Vector3_Sub(hitPoint->Position, sphere.Center));

        float lambert = 0;
        Vector3_t lightDirection = Vector3_Normalized(Vector3_Sub(light.Position, hitPoint->Position));
        lambert += Vector3_Dot(lightDirection, hitPoint->Normal);
        hitPoint->Color = draw_scaled(hitPoint->Color, lambert);
        return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    Camera_t camera = CreateCamera(newVector3(0, 0, -5));
    Light_t light = CreateLight(newVector3(1, 1, -10));
    draw_context_t *context = draw_context_new("AivRayTracer3", 600, 600);

    while (1)
    {
        draw_context_clear(context, black);
        for (int y = 0; y < context->height; y++)
        {
            for (int x = 0; x < context->width; x++)
            {
                Ray_t ray = ScreenPointToRay(x, y, 60, context->width, context->height, camera, context);
                HitPoint_t hit;

                if (!HitByRay(ray, &hit, light))
                {
                    Ray_t rayShadow = RayShadow(&hit, light);
                    HitByRay(rayShadow, &hit, light);
                    // it draws what color the ray hitted
                    draw_context_put_pixel(context, x, y, hit.Color);
                }
            }
        }
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
        }
        draw_context_blit(context);
    }
    draw_context_destroy(context); //vedere cosa succede con la &

    return 0;
}