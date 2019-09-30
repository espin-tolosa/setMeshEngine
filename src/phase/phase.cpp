#include <iostream>
#include "phase.h"

phase::phase()
    : name("UNKNOWN"), gas() {}

phase::phase(char* name_phase, gas& v)
    : gas(v), name(name_phase) {}

void phase::Log()
{
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"Name:                     "<<name<<std::endl;
    std::cout<<"Density:                  "<<r<<std::endl;
    std::cout<<"Temperature:              "<<T<<std::endl;
    std::cout<<"Pressure:                 "<<p<<std::endl;
    std::cout<<"Adiabatic rate expansion: "<<gamma<<std::endl;
    std::cout<<"Internal Energy:          "<<e<<std::endl;
    std::cout<<"Specific enthalpy:        "<<h<<std::endl;
    std::cout<<"Specific entrophy:        "<<s<<std::endl;
    std::cout<<"Velocity:                 "<<u<<std::endl;
}
