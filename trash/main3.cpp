#include "lib/lib.h"
//#include <vtkXMLUnstructuredGrid.h>
#include <GL/glew.h>

using namespace std;

int main()
{

	float VIEW_ROTX = 90;
	float VIEW_ROTZ = 0;

	int t=0;
	int tfin = 200;

	int NEL = 5;

	vec3 cube[] =
	{
		vec3(0.0f, 0.0f, 0.0f),
		vec3(1.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, 1.0f),
		vec3(1.0f, 0.0f, 1.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(1.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f)
	};

	vec3 cubeMeshSurface[] =
	{
		vec3(0.0f, 0.0f, 0.0f),
		vec3(1.0f, 0.0f, 0.0f),
		vec3(2.0f, 0.0f, 0.0f),

		vec3(0.0f, 0.0f, 1.0f),
		vec3(1.0f, 0.0f, 1.0f),
		vec3(2.0f, 0.0f, 1.0f),

		vec3(0.0f, 0.0f, 2.0f),
		vec3(1.0f, 0.0f, 2.0f),
		vec3(2.0f, 0.0f, 2.0f),

		vec3(0.0f, 0.0f, 3.0f),
		vec3(1.0f, 0.0f, 3.0f),
		vec3(2.0f, 0.0f, 3.0f)
	};

	for(int i = 0; i<12; i++)
	{
		cubeMeshSurface[i].Add(vec3(0.25,0.0,0.0));
	}

	structuredHexMesh MyCube;
	MyCube.SweepFace(cubeMeshSurface, 3, 4, NEL, 0.3, vec3(0.0,0.0,0.0));
	MyCube.setHexMeshElement(cube);

	for(unsigned id = 0; id<10; id++)
	{
		MyCube.loadVertexId(id);
//		MyCube.Log_Cells();
	}

	int CELDA;
	while(t<tfin)
	{
	CELDA = 100;
	vec3 point{0.5,0.25+0.01*(float)t,0.5+0.01*(float)t};
	structuredHexMesh Octree1;
	for(int k=0; (unsigned) k<MyCube.Log_Cells_Max(); k++)
	{
		MyCube.getCellConnections((unsigned) k);
		MyCube.loadVertexId((unsigned) k);
		MyCube.CenterC8();
		if(MyCube.vertexSearchCell(point))
		{
			CELDA = k;	
		        vec3* Qt;
			Qt = MyCube.setHexMeshElement();
			for(int w=0;w<3;w++)
			{std::cout<<"OCTREE IS: "<<*(Qt+w)<<std::endl;}
			Octree1.setOctreeLevel1(Qt);
//			std::cout<<"POINTER TO NEW CUBE"<<MyCube.setHexMeshElement()<<std::endl;
		}
	}


//	MyCube.Log();
//	#include "lib/gnuplot.h"
//	MyCube.RotateYMesh(0.05f);
//	MyCube.RotateXMesh(0.05f);
//	MyCube.RotateZMesh(0.03f);
//	MyCube.DisplaceMesh(vec3(0.l,0.l,0.l));
//	t++;
//	}

//	if(t<20)
//	{
//		VIEW_ROTZ += t/2;
//	}
	#include "lib/gnuplot.h" //sudo apt-get install gnuplot
	system("sed -i -e 's/\r$//' temp/gnu.data"); 
	system("chmod +x temp/gnu.data");
	system("./temp/gnu.data");
	t++;
	}

	std::cout<<"Converting image..."; //sudo apt-get install imagemagick
	system("convert -delay 0 -loop 0 *.png anim_001.gif");
	system("rm *.png");
	return 0;
}

