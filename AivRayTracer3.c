#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <Vector3.h>
#include <math.h>
#include <float.h>

typedef struct Light
{
    Vector3_t Position;
} Light_t;

typedef struct Sphere
{
    Vector3_t Center;
    float Radius;
    Vector3_t Color;
} Sphere_t;

typedef struct Ray
{
    Vector3_t Origin;
    Vector3_t Direction;
} Ray_t;

typedef struct HitPoint
{
    Vector3_t Position;
    Vector3_t Normal;
    Vector3_t Color;
    float Distance;
} HitPoint_t;

typedef struct Camera
{
    float left;
    float right;
    float top;
    float bottom;
    Vector3_t Position;
} Camera_t;

Camera_t CreateCamera(float x, float y, float z)
{
    Camera_t vec3;
    vec3.Position.x = x;
    vec3.Position.y = y;
    vec3.Position.z = z;
    return vec3;
}

Sphere_t CreateSphere(Vector3_t position, Vector3_t _color, float radius)
{
    Sphere_t vec3;
    vec3.Center = position;
    vec3.Color = _color;
    vec3.Radius = radius;
    return vec3;
}

Light_t CreateLight(Vector3_t position)
{
    Light_t vec3;
    vec3.Position = position;
    return vec3;
}

#pragma region //Vector3
Vector3_t newVector3(float x, float y, float z)
{
    Vector3_t vec3;
    vec3.x = x;
    vec3.y = y;
    vec3.z = z;
    return vec3;
}

Vector3_t Vector3_Add(Vector3_t v1, Vector3_t v2)
{
    return newVector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3_t Vector3_Sub(Vector3_t v1, Vector3_t v2)
{
    return newVector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

float Vector3_Length(Vector3_t vec3)
{
    float vx = vec3.x * vec3.x;
    float vy = vec3.y * vec3.y;
    float vz = vec3.z * vec3.z;
    return (float)sqrt(vx + vy + vz);
}

Vector3_t Vector3_Normalized(Vector3_t vec3)
{
    Vector3_t vn;
    vn.x = vec3.x / Vector3_Length(vec3);
    vn.y = vec3.y / Vector3_Length(vec3);
    vn.z = vec3.z / Vector3_Length(vec3);
    return vn;
}

float Vector3_Dot(Vector3_t v1, Vector3_t v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3_t Vector3_Direction(Vector3_t v1, Vector3_t v2)
{
    return Vector3_Normalized(Vector3_Sub(v1, v2));
}

Vector3_t Vector3_Scaled(Vector3_t v1, float scale)
{
    return newVector3(v1.x * scale, v1.y * scale, v1.z * scale);
}
#pragma endregion

void PutPixel(SDL_Renderer *rend, int x, int y, Vector3_t color)
{
    if (color.x > 1)
        color.x = 1;

    if (color.y > 1)
        color.y = 1;

    if (color.z > 1)
        color.z = 1;

    SDL_SetRenderDrawColor(rend, color.x * 255, color.y * 255, color.z * 255, 255);
    SDL_RenderDrawPoint(rend, x, y);
}

// returns true if hit, set hitPoint to wathever the ray hit
int HitByRay(Ray_t ray, HitPoint_t *hitPoint, Sphere_t sphere, Light_t light)
{
    hitPoint->Color = Vector3_zero;
    hitPoint->Distance = FLT_MAX;
    hitPoint->Normal = Vector3_zero;
    hitPoint->Position = Vector3_zero;

    Vector3_t l = Vector3_Sub(sphere.Center, ray.Origin);
    float tca = Vector3_Dot(l, ray.Direction);
    if (tca < 0)
        return 0;

    float d = (float)sqrt((Vector3_Length(l) * Vector3_Length(l)) - (tca * tca));
    if (d > sphere.Radius)
        return 0;

    float thc = (float)sqrt((sphere.Radius * sphere.Radius) - (d * d));
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
    Vector3_Scaled(hitPoint->Color, lambert);

    return 1;
}

// get ray from pixel x y
Ray_t ScreenPointToRay(int x, int y, float fov, int width, int height, Camera_t Camera)
{
    float aspect_ratio = (float)width / height;
    float screen_space_y = tan(180 / 3.1415296 * fov / 2);
    float screen_space_x = screen_space_y * aspect_ratio;
    float norm_x = (float)x / width;
    float norm_y = (float)y / height;
    norm_x = (2 * norm_x - 1) * screen_space_x;
    norm_y = (1 - 2 * norm_y) * screen_space_y;
    Vector3_t P = newVector3(norm_x, norm_y, 1);
    Ray_t ray;
    ray.Direction = Vector3_Normalized(Vector3_Sub(P, Camera.Position));
    ray.Origin = Camera.Position;
    return ray;
}

int main(int argc, char *argv[])
{
    Camera_t camera = CreateCamera(0, 0, 0);
    Sphere_t sphere = CreateSphere(newVector3(0, 0, 5), newVector3(0.5, 1, 0), 1);
    Light_t light = CreateLight(newVector3(100, 100, 50));

    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *bitmapTex = NULL;
    SDL_Surface *bitmapSurface = NULL;
    int posX = 100, posY = 100, width = 800, height = 800;
    int i;
    int k;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("AivRayTracer3", posX, posY, width, height, 0);
    if (!win)
    {
        fprintf(stderr, "ERROR: %s\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(renderer);
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (i = 0; i < height; ++i)
    {
        for (k = 0; k < width; ++k)
        {
            Ray_t ray = ScreenPointToRay(k, i, 60, width, height, camera);
            HitPoint_t hit;
            HitByRay(ray, &hit, sphere, light);
            //it draws what color the ray hitted
            PutPixel(renderer, k, i, hit.Color);
        }
    }

    SDL_RenderPresent(renderer);
    while (1)
    {
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
        }
    }
    if (!renderer)
        SDL_DestroyWindow(win);

    SDL_DestroyRenderer(renderer);

    SDL_Quit();

    return 0;
}