#include "vec3operations.h"

float vec3operations::Dot(const vec3& A, const vec3& B)
    {
        return (A.x*B.x + A.y*B.y + A.z*B.z);
    }

vec3 vec3operations::Cross(const vec3& A, const vec3& B)
    {
        return vec3(A.y*B.z - A.z*B.y, A.x*B.z - A.z*B.x, A.x*B.y - A.y*B.x);
    }

float vec3operations::DotCross(const vec3& A, const vec3& B, const vec3& C)
    {
        return vec3operations::Dot(vec3operations::Cross(A,B),C);
    }
