#ifndef PHASE_H_INCLUDED
#define PHASE_H_INCLUDED

#include <string>

#include "../materials/gas.h"

class phase : public gas
{
    std::string name;

    public:

    phase();
    phase(char* name, gas&);

    void Log();
};
#endif // PHASE_H_INCLUDED
