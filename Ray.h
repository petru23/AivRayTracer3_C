#include "Vector3.h"
#include "camera.h"
#include "Draw.h"
#include "HitPoint.h"
#include "Light.h"

typedef struct Ray
{
    Vector3_t Origin;
    Vector3_t Direction;
} Ray_t;

Ray_t ScreenPointToRay(int, int, float, int, int, Camera_t, draw_context_t *);
Ray_t RayShadow(HitPoint_t *, Light_t);