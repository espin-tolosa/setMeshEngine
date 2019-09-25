#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "vec3.h"

vec3::vec3()
    : x(0.0l), y(0.0l), z(0.0l) {}

vec3::vec3(const long double& x, const long double& y, const long double& z)
    : x(x), y(y), z(z) {}

void vec3::Add(const vec3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }

void vec3::Substract(const vec3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

void vec3::Multiply(const vec3& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }

void vec3::Divide(const vec3& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }

vec3 vec3::Loc2Glob(const vec3& other, const vec3& glob_ref)
    {return vec3(other.x + glob_ref.x, other.y + glob_ref.y, other.z + glob_ref.z);}

vec3 vec3::Glob2Loc(const vec3& other,const vec3& loc_ref)
    {return vec3(other.x - loc_ref.x, other.y - loc_ref.y, other.z - loc_ref.z);}

long double vec3::Dot(const vec3&A, const vec3& B)
    {return (A.x*B.x + A.y*B.y + A.z*B.z);}

///CORREGIDO Un BUG EN LAS COMPONENTES MULTIPLICADAS
vec3 vec3::Cross(const vec3& A, const vec3& B)
    {return vec3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x);}

vec3 vec3::Cross(const vec3& origin, const vec3& p2, const vec3& p3)
    {return vec3::Cross(vec3::Glob2Loc(p2,origin),vec3::Glob2Loc(p3,origin));}

long double vec3::DotCross(const vec3& A, const vec3& B, const vec3& C)
    {return vec3::Dot(vec3::Cross(A,B),C);}

long double vec3::DotCross(const vec3& origin, const vec3& p1, const vec3& p2, const vec3& p3)
    {return vec3::DotCross(vec3::Glob2Loc(p1,origin), vec3::Glob2Loc(p2,origin), vec3::Glob2Loc(p3,origin));}

vec3 vec3::RotX(const vec3& p1, long double alpha)
    {return vec3(p1.x, p1.y*cosl(alpha) - p1.z*sinl(alpha), p1.y*sinl(alpha) + p1.z*cosl(alpha));}

vec3 vec3::RotY(const vec3& p1, long double alpha)
    {return vec3(p1.x*cosl(alpha) - p1.z*sinl(alpha), p1.y, p1.x*sinl(alpha) + p1.z*cosl(alpha));}

vec3 vec3::RotZ(const vec3& p1, long double alpha) //precision error ~e-7
    {return vec3(p1.x*cosl(alpha) - p1.y*sinl(alpha), p1.x*sinl(alpha) + p1.y*cosl(alpha), p1.z);}

vec3 vec3::AbsoluteVec3(const vec3& p1)
    {
    long double vx = p1.x;
    long double vy = p1.y;
    long double vz = p1.z;
        if(p1.x<0.0l) vx=-1.0l*p1.x;
        if(p1.y<0.0l) vy=-1.0l*p1.y;
        if(p1.z<0.0l) vz=-1.0l*p1.z;

        return vec3(vx,vy,vz);
    }

long double vec3::Norma()
    {return sqrt(x*x + y*y + z*z);}

long double vec3::Norma(const vec3& other)
    {return sqrt((other.x-x)*(other.x-x)+(other.y-y)*(other.y-y)+(other.z-z)*(other.z-z));}

vec3 vec3::Line(const vec3& Xi, const vec3& Xj, long double sigma)
    {return vec3(sigma*Xj.x + (1-sigma)*Xi.x, sigma*Xj.y + (1-sigma)*Xi.y, sigma*Xj.z + (1-sigma)*Xi.z);}

std::ostream& operator<<(std::ostream& stream, const vec3& vector)
    {
        stream  << vector.x << " " << vector.y << " " << vector.z ;
        return stream;
    }
