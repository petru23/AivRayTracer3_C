#include "Vector3.h"
#include <math.h>

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