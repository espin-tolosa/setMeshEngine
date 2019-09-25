#ifndef VEC3_H_INCLUDED
#define VEC3_H_INCLUDED

struct vec3
{
    long double x,y,z;

    vec3();
    vec3(const long double& x, const long double& y, const long double& z);

    void Add(const vec3& other);
    void Substract(const vec3& other);
    void Multiply(const vec3& other);
    void Divide(const vec3& other);

    vec3 Loc2Glob(const vec3& other,const vec3& glob_ref);
    vec3 Glob2Loc(const vec3& other,const vec3& loc_ref);

    long double Dot  (const vec3& other);
    long double Dot  (const vec3& A, const vec3& B);
    vec3  Cross(const vec3& A, const vec3& B);                          //return normal vertex in GLOBAL REFERENCE
    vec3  Cross(const vec3& origin, const vec3& p2, const vec3& p3);    //return normal vertex in LOCAL REFERENCE

    long double DotCross(const vec3& A, const vec3& B, const vec3& C);
    long double DotCross(const vec3& origin, const vec3& p1, const vec3& p2, const vec3& p3);

    vec3 RotX(const vec3& p1, long double alpha);
    vec3 RotY(const vec3& p1, long double alpha);
    vec3 RotZ(const vec3& p1, long double alpha);

    vec3 AbsoluteVec3(const vec3& p1);

    long double Norma();
    long double Norma(const vec3& other);

    //Create a vertex between 3Dline Xi-Xj as: X(sigma(0:1))->|Xi:Xj|
    vec3 Line(const vec3& Xi, const vec3& Xj, long double sigma);

    friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
};

#endif // VEC3_H_INCLUDED
