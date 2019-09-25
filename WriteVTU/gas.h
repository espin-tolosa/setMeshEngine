class gas
{
    public:

        float rho, T, p, gamma, cp, e, h, s, u, coeff[5];

        gas();
        gas(const float& temperature, const float& pressure, const float& gamma, const float& cp, const float& velocity, const float* coeff);

};
