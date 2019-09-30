#ifndef EOS_H_INCLUDED
#define EOS_H_INCLUDED

class eos
{
    public:

    eos();
//    eos(const float& temperature, const float& pressure, const float& gamma, const float& cp, const float& velocity);
    eos(gas& v);
    void ideal();
    void isentropic(gas &ref);
};

#endif // EOS_H_INCLUDED
