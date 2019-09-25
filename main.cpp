#include "lib/lib.h"
#include <new>
//#include <vtkXMLUnstructuredGrid.h>
//#include <GL/glew.h>

using namespace std;

int main()
{

	float VIEW_ROTX = 0;
	float VIEW_ROTZ = 0;

	int t=0;
	int tfin = 100;

	int NEL = 10000;
	vec3 cubeMeshSurface[] =
	{
		vec3(0.0f , 0.0f, 0.0f),
		vec3(0.75f, 0.0f, 0.0f),
		vec3(1.25f, 0.0f, 0.0f),
		vec3(2.0f , 0.0f, 0.0f),

		vec3(0.0f , 0.0f, 1.0f),
		vec3(0.75f, 0.0f, 1.0f),
		vec3(1.25f, 0.0f, 1.0f),
		vec3(2.0f , 0.0f, 1.0f),

		vec3(0.0f , 0.0f, 2.0f),
		vec3(0.75f, 0.0f, 2.0f),
		vec3(1.25f, 0.0f, 2.0f),
		vec3(2.0f , 0.0f, 2.0f),

		vec3(0.0f , 0.0f, 3.0f),
		vec3(0.75f, 0.0f, 3.0f),
		vec3(1.25f, 0.0f, 3.0f),
		vec3(2.0f , 0.0f, 3.0f)
	};

	for(int i = 0; i<4*4; i++)
	{
		cubeMeshSurface[i].Add(vec3(0.25,0.0,0.0));
	}

	structuredHexMesh MyCube;
	MyCube.SweepFace(cubeMeshSurface, 4, 4, NEL, PI/(float) NEL, vec3(0.0,0.0,0.0));
	MyCube.DisplaceMesh(vec3(0.,-1.5,-1.5));

	for(int i=0; i<(int)MyCube.Log_Cells_Max(); i++)
	{
		MyCube.loadVertexId((unsigned) i);
		MyCube.CenterC8();
	}

	while(t<tfin)
	{

	//[Info] Updating position of points insertion
	int number_of_points = 14;
	vec3 point[number_of_points]
	{
		vec3(0.3, 1.8, 1.1),
		vec3( -1.8 , -2.0+0.01*(float)t , 0.5-0.01*(float)t ),
		vec3( -1.5 , -2.0+0.01*(float)t , 0.7-0.01*(float)t ),
		vec3( -1.2 , -2.0+0.01*(float)t , 0.5-0.01*(float)t ),

		vec3( -0.9 , -2.0+0.01*(float)t , 0.5-0.01*(float)t ),
		vec3( -0.6 , -2.0+0.01*(float)t , 0.7-0.01*(float)t ),
		vec3( -0.3 , -2.0+0.01*(float)t , 0.5-0.01*(float)t ),

		vec3(  0.0 , -2.0+0.01*(float)t , 0.5-0.01*(float)t ),

		vec3(  0.3 , -2.0+0.01*(float)t , 0.5-0.01*(float)t ),
		vec3(  0.6 , -2.0+0.01*(float)t , 0.7-0.01*(float)t ),
		vec3(  0.9 , -2.0+0.01*(float)t , 0.5-0.01*(float)t ),

		vec3(  1.2 , -2.0+0.01*(float)t , 0.5-0.01*(float)t ),
		vec3(  1.5 , -2.0+0.01*(float)t , 0.7-0.01*(float)t ),
		vec3(  1.8 , -2.0+0.01*(float)t , 0.5-0.01*(float)t )
	};
	
	//[Info] Reset to false all entries of subdivions before recompute the insertion points in next step
	for(int i=0; (unsigned) i<MyCube.Log_Cells_Max(); i++)
	{
		*(MyCube.Cell_Divided+i) = false;
	}
	MyCube.Total_Cell_Divided = 0;
	//[Info] Buscando en MyCube los puntos insertados	
	for(int k=0; k<(int)MyCube.Log_Cells_Max(); k++)
	{
		MyCube.loadVertexId((unsigned) k);

		for(int j=0; j<number_of_points; j++)
		{
			if(!MyCube.Cell_Divided[k])
			{
			MyCube.vertexSearchCell(point[j]);
			}
		}
	}

if(MyCube.Total_Cell_Divided>0)
{
	//[Info] Creando el Octree del primer nivel
	octreeSHM* Octree1 = new octreeSHM;
	Octree1->setHexMeshElement(MyCube);
	//[Info] Buscando en Octree1 los puntos insertados
	for(int k=0; k<(int)Octree1->Log_Cells_Max(); k++)
	{
		Octree1->loadVertexId((unsigned) k);
		Octree1->CenterC8();
		for(int j=0; j<number_of_points; j++)
		{
			if(!Octree1->Cell_Divided[k])
			{
			Octree1->vertexSearchCell(point[j]);
			}
		}
	}

if(Octree1->Total_Cell_Divided>0)
{
	//[Info] Creando el Octree del segundo nivel
	octreeSHM* Octree2 = new octreeSHM;
	Octree2->setHexMeshElement(*Octree1);
	//[Info] Buscando en Octree1 los puntos insertados
	for(int k=0; k<(int)Octree2->Log_Cells_Max(); k++)
	{
		Octree2->loadVertexId((unsigned) k);
		Octree2->CenterC8();
		for(int j=0; j<number_of_points; j++)
		{
			if(!Octree2->Cell_Divided[k])
			{
			Octree2->vertexSearchCell(point[j]);
			}
		}
	}

if(Octree2->Total_Cell_Divided>0)
{
	//[Info] Creando el Octree del tercer nivel
	octreeSHM* Octree3 = new octreeSHM;
	Octree3->setHexMeshElement(*Octree2);
	//[Info] Buscando en Octree3 los puntos insertados
	for(int k=0; k<(int)Octree3->Log_Cells_Max(); k++)
	{
		Octree3->loadVertexId((unsigned) k);
		Octree3->CenterC8();
		for(int j=0; j<number_of_points; j++)
		{
			if(!Octree3->Cell_Divided[k])
			{
			Octree3->vertexSearchCell(point[j]);
			}
		}
	}

if(Octree3->Total_Cell_Divided>0)
{
	//[Info] Creando el Octree del cuarto nivel
	octreeSHM* Octree4 = new octreeSHM;
	Octree4->setHexMeshElement(*Octree3);
	//[Info] Buscando en Octree3 los puntos insertados
	for(int k=0; k<(int)Octree4->Log_Cells_Max(); k++)
	{
		Octree4->loadVertexId((unsigned) k);
		Octree4->CenterC8();
		for(int j=0; j<number_of_points; j++)
		{
			if(!Octree4->Cell_Divided[k])
			{
			Octree4->vertexSearchCell(point[j]);
			}
		}
	}
	//[Info] Output to GNUPLOT
//	#include "lib/gnuplot.h" //sudo apt-get install gnuplot
//	system("sed -i -e 's/\r$//' temp/gnu.data"); 
//	system("chmod +x temp/gnu.data");
//	system("./temp/gnu.data");

//	std::cout<<"DELETING OCTREES 4"<<std::endl;
	delete Octree4;
}

//	std::cout<<"DELETING OCTREES 3"<<std::endl;
	delete Octree3;
}

//	std::cout<<"DELETING OCTREES 2"<<std::endl;
	delete Octree2;
}

//	std::cout<<"DELETING OCTREES 1"<<std::endl;
	delete Octree1;
}

	std::cout<<"TIME-STAMP: "<<t<<std::endl;
t++;
//	VIEW_ROTZ += 1;

//	MyCube.RotateYMesh(0.02f);
//	MyCube.RotateXMesh(0.02f);
//	MyCube.RotateZMesh(0.02f);
//	MyCube.DisplaceMesh(vec3(0.l,0.l,0.l));
	
	}

//	std::cout<<"Converting image..."; //sudo apt-get install imagemagick
//	system("convert -delay 100 -loop 0 *.png anim_001.gif");
//	system("rm *.png");
	return 0;
}

