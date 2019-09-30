#ifndef GAS_H_INCLUDED
#define GAS_H_INCLUDED

class gas : public eos 
{
    public:
	    double* u;
    	    double* r;
   	    double* T;
    	    double* p;

	    double* e;
    	    double* h;
   	    double* s;

//estas variables: gamma, cp, coeff, se asumen de momento constantes por lo tanto se aplican globales para todo el dominio
	    double gamma, cp, *coeff[5];
	    
	    gas();
	    gas(const double& gm, const double& cp, const double* coeff, const unsigned& Volume_Population);

};

#endif
