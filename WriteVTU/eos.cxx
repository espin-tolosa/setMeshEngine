#include<iostream>
#include <math.h>
#include "eos.h"


eos::eos() : gas(){}
//eos::eos(const float& temperature, const float& pressure, const float& gamma, const float& cp, const float& velocity)
eos::eos(gas& )
    : gas(T, p, gamma, cp, u, coeff){eos::ideal();}

void eos::ideal()
{
    this->rho = (gamma)/(gamma-1.0f)*p/T/1005.2f;
    this->e   = T*cp/gamma;
    this->h   = e*gamma;
    this->s   = (cp/gamma)*(log(T/300.f) + (gamma-1.f)*log(10.f/p));
    this->u   = 0.0f;
}

void eos::isentropic(gas &ref)
{
    rho = ref.rho*pow(p/ref.p, 1/gamma);
    T   = T;
    p   = p;
    e   = e;
    h   = h;
    s   = s;
    u   = u;
}
