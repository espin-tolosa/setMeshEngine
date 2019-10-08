#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "vec3.h"

vec3::vec3()
    : x(0.0), y(0.0), z(0.0) {}

vec3::vec3(const double& x, const double& y, const double& z)
    : x(x), y(y), z(z) {}

void vec3::Add(const vec3& other)
    {
		this->x += other.x;
    	this->y += other.y;
    	this->z += other.z;
    }

void vec3::Add(const float& other)
    {
	x += other;
	y += other;
	z += other;
    }

void vec3::Add(const double& other)
    {
	x += other;
	y += other;
	z += other;
    }

void vec3::Substract(const vec3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

void vec3::Substract(const float& other)
    {
	x -= other;
	y -= other;
	z -= other;
    }

void vec3::Substract(const double& other)
    {
	x -= other;
	y -= other;
	z -= other;
    }

void vec3::Multiply(const vec3& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }

void vec3::Multiply(const float& other)
    {
	x *= other;
	y *= other;
	z *= other;
    }

void vec3::Multiply(const double& other)
    {
	x *= other;
	y *= other;
	z *= other;
    }

void vec3::Divide(const vec3& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }

void vec3::Divide(const float& other)
    {
	x /= other;
	y /= other;
	z /= other;
    }

void vec3::Divide(const double& other)
    {
	x /= other;
	y /= other;
	z /= other;
    }

vec3 vec3::Loc2Glob(const vec3& other, const vec3& glob_ref)
    {return vec3(other.x + glob_ref.x, other.y + glob_ref.y, other.z + glob_ref.z);}

vec3 vec3::Glob2Loc(const vec3& other,const vec3& loc_ref)
    {return vec3(other.x - loc_ref.x, other.y - loc_ref.y, other.z - loc_ref.z);}

double vec3::Dot(const vec3&A, const vec3& B)
    {return (A.x*B.x + A.y*B.y + A.z*B.z);}

///CORREGIDO Un BUG EN LAS COMPONENTES MULTIPLICADAS
vec3 vec3::Cross(const vec3& A, const vec3& B)
    {return vec3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x);}

vec3 vec3::UCross(const vec3& A, const vec3& B)
    {
	vec3 AxB{A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x};
	AxB.Divide(AxB.Norma());
	return AxB;//	return AxB.Divide(sqrtl(AxB.x*AxB.x + AxB.y*AxB.y + AxB.z*AxB.z));
    }

vec3 vec3::Cross(const vec3& origin, const vec3& p2, const vec3& p3)
    {return vec3::Cross(vec3::Glob2Loc(p2,origin),vec3::Glob2Loc(p3,origin));}

double vec3::DotCross(const vec3& A, const vec3& B, const vec3& C)
    {return vec3::Dot(vec3::Cross(A,B),C);}

double vec3::DotCross(const vec3& origin, const vec3& p1, const vec3& p2, const vec3& p3)
    {return vec3::DotCross(vec3::Glob2Loc(p1,origin), vec3::Glob2Loc(p2,origin), vec3::Glob2Loc(p3,origin));}

vec3 vec3::RotX(const vec3& p1, double alpha)
    {return vec3(p1.x, p1.y*cos(alpha) - p1.z*sin(alpha), p1.y*sin(alpha) + p1.z*cos(alpha));}

vec3 vec3::RotY(const vec3& p1, double alpha)
    {return vec3(p1.x*cos(alpha) - p1.z*sin(alpha), p1.y, p1.x*sin(alpha) + p1.z*cos(alpha));}

vec3 vec3::RotZ(const vec3& p1, double alpha) //precision error ~e-7
    {return vec3(p1.x*cos(alpha) - p1.y*sin(alpha), p1.x*sin(alpha) + p1.y*cos(alpha), p1.z);}
/*
void vec3::LocRotX(const vec3& p0, double alpha)
    {
		this->x = p0.x + (this->x-p0.x);
		this->y = p0.y + (this->y-p0.y)*cos(alpha) - (this->z-p0.z)*sin(alpha);
		this->z = p0.z + (this->y-p0.y)*sin(alpha) + (this->z-p0.z)*cos(alpha);

		return;
	}
*/
void vec3::LocRotX(double alpha)
    {
		this->x = (this->x);
		this->y = (this->y)*cos(alpha) - (this->z)*sin(alpha);
		this->z = (this->y)*sin(alpha) + (this->z)*cos(alpha);

		return;
	}
/*
void vec3::LocRotY(const vec3& p0, double alpha)
    {
		this->x = p0.x + (this->x-p0.x)*cos(alpha) - (this->z-p0.z)*sin(alpha);
		this->y = p0.y + (this->y-p0.y);
		this->z = p0.z + (this->x-p0.x)*sin(alpha) + (this->z-p0.z)*cos(alpha);

		return;
	}
*/
void vec3::LocRotY(double alpha)
    {
		this->x = (this->x)*cos(alpha) - (this->z)*sin(alpha);
		this->y = (this->y);
		this->z = (this->x)*sin(alpha) + (this->z)*cos(alpha);

		return;
	}
/*
void vec3::LocRotZ(const vec3& p0, double alpha)
    {
		this->x = p0.x + (this->x-p0.x)*cos(alpha) - (this->y-p0.y)*sin(alpha);
		this->y = p0.y + (this->x-p0.x)*sin(alpha) + (this->y-p0.y)*cos(alpha);
		this->z = p0.z + (this->z-p0.z);

		return;
	}
*/
void vec3::LocRotZ(double alpha)
    {
		x = x*cos(alpha) - y*sin(alpha);
		y = x*sin(alpha) + y*cos(alpha);
//		z = z;

		return;
	}
vec3 vec3::AbsoluteVec3(const vec3& p1)
    {
    	double vx = p1.x;
    	double vy = p1.y;
    	double vz = p1.z;

		if(p1.x<0.0) vx=-1.0*p1.x;
        if(p1.y<0.0) vy=-1.0*p1.y;
        if(p1.z<0.0) vz=-1.0*p1.z;

        return vec3(vx,vy,vz);
    }

double vec3::Norma()
    {return sqrtl(x*x + y*y + z*z);}

double vec3::Norma(const vec3& other)
    {return sqrtl((other.x-x)*(other.x-x)+(other.y-y)*(other.y-y)+(other.z-z)*(other.z-z));}

vec3 vec3::Line(const vec3& Xi, const vec3& Xj, double sigma)
    {return vec3(sigma*Xj.x + (1-sigma)*Xi.x, sigma*Xj.y + (1-sigma)*Xi.y, sigma*Xj.z + (1-sigma)*Xi.z);}

//stackoverflow.com/questions/31708302/function-pointer-array-to-a-method-within-a-class
void vec3::ArithmeticForEach(vec3* array, const int& size_array, const vec3& other,  int method_type)
{	
	typedef void (vec3::*method_function)(const vec3&);
	method_function method_pointer[] = 	{&vec3::Add, &vec3::Substract, &vec3::Multiply, &vec3::Divide};
	method_function function = method_pointer[method_type];

	for(int i = 0;  i< size_array; i++)
	{
		((array + i)->*function)(other);
	}
}

//void vec3::LocRotForEach(vec3* array, const int& size_array, const vec3& origin, double alpha, int method_type)
void vec3::LocRotForEach(vec3* array, const int& size_array, double alpha, int method_type)
{
	typedef void (vec3::*method_function)(double);
	method_function method_pointer[] =	{&vec3::LocRotX, &vec3::LocRotY, &vec3::LocRotZ};
	method_function function = method_pointer[method_type];

	for(int i = 0;  i< size_array; i++)
	{
		((array + i)->*function)(alpha);
	}
}

std::ostream& operator<<(std::ostream& stream, const vec3& vector)
    {
        stream  << vector.x << ", " << vector.y << ", " << vector.z ;
        return stream;
    }
