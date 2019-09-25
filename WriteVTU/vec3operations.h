#ifndef VEC3OPERATIONS_H_INCLUDED
#define VEC3OPERATIONS_H_INCLUDED

#include "vec3.h"

class vec3operations
{
    public:

    float Dot(const vec3& A, const vec3& B);
    vec3 Cross(const vec3& A, const vec3& B);
    float DotCross(const vec3& A, const vec3& B, const vec3& C);
};

#endif // VEC3OPERATIONS_H_INCLUDED
