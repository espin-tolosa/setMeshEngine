#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include "lib/lib.h"
//#include <vtkXMLUnstructuredGrid.h>
//#include <GL/glew.h>

using namespace std;

int main()
{

	float VIEW_ROTX = 90;
	float VIEW_ROTZ = 30;

	int t=0;
	int tfin = 2;

	int NEL = 1E1;

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
		cubeMeshSurface[i].Add(vec3(1.0,0.0,0.0));
	}

	structuredHexMesh MyCube;

	MyCube.SweepFace(cubeMeshSurface, 3, 4, NEL, 3.1415l/10.0, vec3(0.0,0.0,0.0));
	MyCube.setHexMeshElement(cube);


	while(t<tfin)
	{

	for(int k=0; (unsigned) k<MyCube.Log_Cells_Max(); k++)
	{
		MyCube.getCellConnections((unsigned) k);
		MyCube.CenterC8();
	}

	MyCube.Log();
//	#include "lib/gnuplot.h"
	MyCube.RotateYMesh(0.01f);
//	MyCube.RotateXMesh(0.02f);
//	MyCube.DisplaceMesh(vec3(0.l,0.l,0.l));
//	t++;
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
