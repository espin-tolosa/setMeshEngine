#ifndef SETFUN_H_INCLUDED
#define SETFUN_H_INCLUDED

///void toLowerCaseString (char* chain);
char toLowerCase (int c);
char toUpperCase (int c);

bool getBool(const bool &byte, int bit_position);
bool getBit(unsigned char byte, int position);
bool getBit(int byte, int position);

void dec2bin(unsigned char byte);
void dec2bin(int byte);

bool sign_of_int(const int &signed_var);

void size_of_types(void);

///FLOAT        number is defined as a number followed by char 'f'
///DOUBLE       number doesn't need any special character
///LONG DOUBLE  number is defined as a number followed by char 'l'
void type_is_(const bool &var);
void type_is_(const char &var);
void type_is_(const short &var);
void type_is_(const int &var);
void type_is_(const float &var);
void type_is_(const double &var);
void type_is_(const long &var);
void type_is_(const long double &var);

void int2char(int ascii_code);

double dRandom(const double& lower, const double& upper);
#endif // SETFUN_H_INCLUDED

