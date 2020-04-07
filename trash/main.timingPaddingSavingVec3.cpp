#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

//Aqui tengo un peque codigo que define vec3 y vec3_pack, en teoria ambos son iguales en tanto que la esctructura de datos encaja perfectamente sin hacer padding
//igualmente defino una clase tipo pack para asegurar. El caso es no hay diferencia de tiempo entre definir dos estructuras, copiar los datos de una a otra salvar, leer y recopia
//a hacerlo directamente. Lo cual no entiendo pero asi es.

using namespace std;

struct Timer
{
	std::chrono::high_resolution_clock::time_point start, end;
//	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		float ms = duration.count() * 1000.0f;
		std::cout<<"Time took " <<ms<<" ms"<<std::endl;
	}
};

class vec3{
	public:
	double x,y,z;

	vec3()            : x(0.), y(0.), z(0.){}
	vec3(double x, double y, double z): x(x), y(y), z(z){}
};

#pragma pack(push,1)
class vec3_pack{
	public:
	double x,y,z;

	vec3_pack() : x(0.), y(0.), z(0.){}
	vec3_pack(double x, double y, double z): x(x), y(y), z(z){}
};
#pragma pack (pop)

int main() {
Timer time;
	for(int i = 0; i<1000; i++){
	//This is the code where there is a variable that I would lie to save
	vec3 some = {3.3,4.4,5.5};

	//Define a name file
	string fileName = "test.bin";

//WRITE A BINARY
	//Instanciate the output file class
	ofstream outputFile;
	outputFile.open(fileName, ios::binary);

	//Check if file is succesfully created
	if(outputFile.is_open()){

		vec3_pack someone = {some.x,some.y,some.z};

		//Passing a pointer
		outputFile.write(reinterpret_cast<char *>(&someone),sizeof(vec3_pack));
		outputFile.close();
	}
	else {
		cout<<"Could not create file " + fileName<<endl;
	}

	//Read binary
	
	ifstream inputFile;

	inputFile.open(fileName, ios::binary);

	if(inputFile.is_open()){
		//Defining storage variable
		vec3_pack someoneElse = {};
		//Passing a pointer
		inputFile.read(reinterpret_cast<char *>(&someoneElse),sizeof(vec3_pack));
		inputFile.close();
		//Passing to the output variable non packed
		vec3 someoneElsemore = {someoneElse.x,someoneElse.y,someoneElse.z};
	}
	else {
		cout<<"Could not read file " + fileName<<endl;
	}
}
	return 0;
}
