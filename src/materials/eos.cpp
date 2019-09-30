#include<iostream>
#include <math.h>
#include "gas.h"
#include "eos.h"

//ESto deberia de estar al reves, que la clase gas, herede de la clase eos
eos::eos()
//eos::eos(const float& temperature, const float& pressure, const float& gamma, const float& cp, const float& velocity)
eos::eos(gas& v)
    : gas(v.gamma, v.cp, coeff){eos::ideal();}

void eos::ideal()
{
    this->r[0]   = 1.4*(1.4-1.0)*100000.0/300.15/1005.2;
    this->e[0]   = 300.15*1005.2/1.4;
    this->h[0]   = 300.15*1005.2/1.4/1.4;
    this->s[0]   = (1005.2/1.4)*(log(300.15/300.0) + (1.4-1.0)*log(10.0/100000.0));
    this->u[0]   = 0.0;

//    this->r = (gamma)/(gamma-1.0)*(*p[0])/(*T[0])/1005.2;
//    this->e   = T*cp/gamma;
//    this->h   = e*gamma;
//    this->s   = (cp/gamma)*(log(T/300.f) + (gamma-1.f)*log(10.f/p));
//    this->u   = 0.0f;
}

void eos::isentropic(gas &ref)
{
//    rho = ref.rho*pow(p/ref.p, 1./gamma);
//    T   = T;
//    p   = p;
//    e   = e;
//    h   = h;
//    s   = s;
//    u   = u;
}
