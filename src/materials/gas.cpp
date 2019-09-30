#include <math.h>
#include "eos.h"
#include "gas.h"

gas::gas()
    : u(0.0), r(0.0), T(0.0), p(0.0), e(0.0), h(0.0), s(0.0), gamma(0.0), cp(0.0)
    {
        for(int i=0; i<5; i++)
        {
            this->coeff[i] = 0.0;
        }
    }


gas::gas(const double& gamma, const double& cp, const double* coeff, const unsigned& Volume_Population)
        :   gamma(gamma), cp(cp)
        {
		u = new double[Volume_Population]{0.0};
		r = new double[Volume_Population]{0.0};
		T = new double[Volume_Population]{0.0};
		p = new double[Volume_Population]{0.0};

		e = new double[Volume_Population]{0.0};
		h = new double[Volume_Population]{0.0};
		s = new double[Volume_Population]{0.0};

            	for(int i=0; i<5; i++)
            	{
                	this->coeff[i] = coeff[i];
            	}
        }
