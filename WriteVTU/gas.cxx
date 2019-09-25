#include <math.h>
#include "gas.h"

gas::gas()
    : rho(0.0f), T(0.0f), p(0.0f), gamma(0.0f), cp(0.0f), e(0.0f), h(0.0f), s(0.0f), u(0.0f)
    {
        for(int i=0; i<5; i++)
        {
            this->coeff[i] = 0.0f;
        }
    }


gas::gas(const float& temperature, const float& pressure, const float& gamma, const float& cp, const float& velocity, const float* coeff)
        :   rho(0.0f), T(temperature), p(pressure), gamma(gamma), cp(cp), e(0.0f), h(0.0f), s(0.0f), u(velocity)
        {
            for(int i=0; i<5; i++)
            {
                this->coeff[i] = coeff[i];
            }
        }
