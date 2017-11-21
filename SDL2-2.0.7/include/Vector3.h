typedef struct Vector3
{
    float x;
    float y;
    float z;
} Vector3_t;

const Vector3_t Vector3_zero = {0.0, 0.0, 0.0};
const Vector3_t Vector3_up = {0.0, 1.0, 0.0};
const Vector3_t Vector3_down = {0.0, -1.0, 0.0};

Vector3_t newVector3(float, float, float);
Vector3_t Vector3_Add(Vector3_t, Vector3_t);
Vector3_t Vector3_Sub(Vector3_t, Vector3_t);
float Vector3_Length(Vector3_t);
Vector3_t Vector3_Normalized(Vector3_t);
float Vector3_Dot(Vector3_t, Vector3_t);
Vector3_t Vector3_Direction(Vector3_t, Vector3_t);
Vector3_t Vector3_Scaled(Vector3_t,float);
