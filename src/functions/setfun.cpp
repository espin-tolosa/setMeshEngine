#include <iostream>
#include <random>
/**SOME DAY THIS FUNCTION WILL WORK PROPERLY BUT NOT NOW
//issues:   definicion de funciones en diferentes scopes: tengo que definir la funcion toLoweCase dentro la funcion porque no la encuentra
//          el retorno de una variable tipo new no sé cómo se hace ahora mismo de forma óptima, porque quería pasar su dirección pero tambien tendría que pasar su tamaño
//          me he liado en la conversion entre int, char y string, quiero llamar a una funcion que recibe int pero le estoy pasando un char*

void toLowerCaseString (char* chain)
{
char toLowerCase (int c);

    int i=0;
    while(chain[i] != 0)
    {
        chain[i]=toLowerCase(chain[i]);
        std::cout<<toLowerCase(chain[i]);
        i++;
    }
}
**/

char toLowerCase (int c)
{
   if((char)c <= 'Z' && (char)c >= 'A')
   {
        c |= ('a'-'A');
        return (char)c;
   }
        return (char)c;

}

char toUpperCase (int c)
{
    if ( (char)c <= 'z' && (char)c >= 'a' )
    {
        c &= ~('a'-'A');
        return (char)c;
    }
        return (char)c;
}

bool getBool(const bool &byte, int bit_position)
{
    return (byte >> bit_position) & 0x1;
}

bool getBit(unsigned char byte, int position)
{
    return (byte >> position) & 0x1;
}

bool getBit(int byte, int position)
{
    return (byte >> position) & 0x1;
}

void dec2bin(unsigned char byte)
{
    for(unsigned int j=0;j<8*sizeof(byte);j++)
    {
        std::cout<<getBit(byte,j);
    }
}

void dec2bin(int byte)
{
    for(unsigned int j=0;j<8*sizeof(byte);j++)
    {
        std::cout<<getBit(byte,j);
    }
}

bool sign_of_int(const int &signed_var)
{
    if(getBit(signed_var,7))
    {
//        std::cout<<"negative\n";
        return true;
    }

    else
    {
//        std::cout<<"positive\n";
        return false;
    }
}

void size_of_types(void)
{
    std::cout<<"SIZE\t\t|\tBytes"<<std::endl;
    std::cout<<"----------------|---------------------"<<std::endl;
    std::cout<<"BOOL\t\t|\t"<<sizeof(bool)<<"\t2^"<<8*sizeof(bool)<<std::endl;
    std::cout<<"CHAR\t\t|\t"<<sizeof(char)<<"\t2^"<<8*sizeof(char)<<std::endl;
    std::cout<<"SHORT\t\t|\t"<<sizeof(short)<<"\t2^"<<8*sizeof(short)<<std::endl;
    std::cout<<"INT\t\t|\t"<<sizeof(int)<<"\t2^"<<8*sizeof(int)<<std::endl;
    std::cout<<"FLOAT\t\t|\t"<<sizeof(float)<<"\t2^"<<8*sizeof(float)<<std::endl;
    std::cout<<"DOUBLE\t\t|\t"<<sizeof(double)<<"\t2^"<<8*sizeof(double)<<std::endl;
    std::cout<<"LONG\t\t|\t"<<sizeof(long)<<"\t2^"<<8*sizeof(long)<<std::endl;
    std::cout<<"LONGx2\t\t|\t"<<sizeof(long long)<<"\t2^"<<8*sizeof(long long)<<std::endl;
    std::cout<<"LONG DOUBLE\t|\t"<<sizeof(long double)<<"\t2^"<<8*sizeof(long double)<<std::endl;
}

void type_is_(const bool &var){std::cout<<"Variable: "<<var<<", is a BOOL"<<std::endl;}
void type_is_(const char &var){std::cout<<"Variable: "<<var<<", is a CHAR"<<std::endl;}
void type_is_(const short &var){std::cout<<"Variable: "<<var<<", is a SHORT"<<std::endl;}
void type_is_(const int &var){std::cout<<"Variable: "<<var<<", is a INT"<<std::endl;}
void type_is_(const float &var){std::cout<<"Variable: "<<var<<", is a FLOAT"<<std::endl;}
void type_is_(const double &var){std::cout<<"Variable: "<<var<<", is a DOUBLE"<<std::endl;}
void type_is_(const long &var){std::cout<<"Variable: "<<var<<", is a LONG"<<std::endl;}
void type_is_(const long double &var){std::cout<<"Variable: "<<var<<", is a LONG DOUBLE"<<std::endl;}

void int2char(int ascii_code)
{

    std::cout<<"\n\n\n\n-------------------------------------\nunsigned char 0-255: ";
    std::cout<<"\nASCII codification of "<< ascii_code<<" -> '"<<(unsigned char) ascii_code<<"'";
    std::cout<<"\n-------------------------------------\n";
}

double dRandom(const double& lower, const double& upper)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(lower, upper);

    return dis(gen);
}



















