#ifndef PHASE_H_INCLUDED
#define PHASE_H_INCLUDED

#include <string>

#include "eos.h"

class phase : public eos
{
    std::string name;

    public:

    phase();
    phase(char* name, gas&);

    void Log();
};

#endif // PHASE_H_INCLUDED
