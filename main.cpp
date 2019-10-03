#include "lib/lib.h"

//#include <vtkXMLUnstructuredGrid.h>
//#include <GL/glew.h>

int main()
{

	float VIEW_ROTX = 0;
	float VIEW_ROTZ = 0;

	int NEL = 6;
	int t=0;
	int tfin = 4;

	structuredHexMesh MyCube;
	//Defining the mesh-surface that will be extruded later
	//with SweepFace to create a 3D hexaedral structured-mesh
	{
		vec3 cubeMeshSurface[] {
			vec3(0.0 , 0.0, 0.0),
			vec3(1.0 , 0.0, 0.0),
			vec3(2.0 , 0.0, 0.0),
			vec3(3.0 , 0.0, 0.0),

			vec3(0.0 , 0.0, 1.0),
			vec3(1.0 , 0.0, 1.0),
			vec3(2.0 , 0.0, 1.0),
			vec3(3.0 , 0.0, 1.0),

			vec3(0.0 , 0.0, 2.0),
			vec3(1.0 , 0.0, 2.0),
			vec3(2.0 , 0.0, 2.0),
			vec3(3.0 , 0.0, 2.0),

			vec3(0.0 , 0.0, 3.0),
			vec3(1.0 , 0.0, 3.0),
			vec3(2.0 , 0.0, 3.0),
			vec3(3.0 , 0.0, 3.0)
		};

		for(int i=0; i< sizeof(cubeMeshSurface)/sizeof(vec3); i++) {

			cubeMeshSurface[i].Add(vec3(0.1,0.0,0.0));
		}

		MyCube.SweepFace(cubeMeshSurface, 4, 4, NEL, PI/(float) NEL, vec3(0.0,0.0,0.0));
		MyCube.DisplaceMesh(vec3(0.,-1.5,-1.5));

		//This command compute cell centers of all cells for the mesh
		for(int i=0; i< (int)MyCube.Log_Cells_Max(); i++) {

			MyCube.loadVertexId((unsigned) i);
			MyCube.CenterC8();
		}
	} //end of scope of 2D mesh-surface: cubeMeshSurface 

	//Defining an cloud of points to test the octree algorithm
	vec3 points[] {
		vec3(  0.3 ,  1.8 , 1.1  ),
		vec3( -1.8 , -2.0 , 0.51 ),
		vec3( -1.5 , -2.0 , 0.71 ),
		vec3( -1.2 , -2.0 , 0.5  ),

		vec3( -0.9 , -2.0 , 0.5  ),
		vec3( -0.6 , -2.0 , 0.7  ),
		vec3( -0.3 , -2.0 , 0.5  ),

		vec3(  0.0 , -2.0 , 0.5  ),

		vec3(  0.3 , -2.0 , 0.5  ),
		vec3(  0.6 , -2.0 , 0.7  ),
		vec3(  0.9 , -2.0 , 0.5  ),

		vec3(  1.2 , -2.0 , 0.5  ),
		vec3(  1.5 , -2.0 , 0.7  ),
		vec3(  1.8 , -2.0 , 0.5  ),

		vec3(  0.0 , 0.0 , 0.0   ),
		vec3( -1.8 , 2.0 , 0.5   ),
		vec3( -1.5 , 2.0 , 0.7   ),
		vec3( -1.2 , 2.0 , 0.5   ),

		vec3( -0.9 , 2.0 , 0.5   ),
		vec3( -0.6 , 2.0 , 0.7   ),
		vec3( -0.3 , 2.0 , 0.5   ),

		vec3(  0.0 , 2.0 , 0.5   ),

		vec3(  0.3 , 2.0 , 0.5   ),
		vec3(  0.6 , 2.0 , 0.7   ),
		vec3(  0.9 , 2.0 , 0.5   ),

		vec3(  1.2 , 2.0 , 0.5   ),
		vec3(  1.5 , 2.0 , 0.7   ),
		vec3(  1.8 , 2.0 , 0.5   )

	};

	int number_of_points = sizeof(points)/sizeof(vec3);

	//Main loop to run the algorithm. It takes the cloud of points and compute
	//what cell of the mesh they belong to slit this cell in octree recursively
	while(t++<tfin)
	{

		//[Info] Updating position of points insertion
		int iop = 0; //{iop = 0 (Add); iop = 1 (Substract)} //this line will remove after suit documentation
		points[0].ForEach(points, number_of_points, vec3(0.01, 0.0, 0.0), 0);


		//[Info] Reset to false all entries of subdivions before recompute the insertion points in next step
		if(MyCube.Total_Cell_Divided) {

			MyCube.Total_Cell_Divided = 0;
			for(int i=0; (unsigned) i<MyCube.Log_Cells_Max(); i++) {
	
				*(MyCube.Cell_Divided+i) = false;
			}
		}

		//[Info] Buscando en MyCube los puntos insertados	
		for(int k=0; k<(int)MyCube.Log_Cells_Max(); k++) {

			MyCube.loadVertexId((unsigned) k);
			for(int j=0; j<number_of_points; j++) {
				//if the cell is not yet divided enters in search function to check if a  point is there
				if(!MyCube.Cell_Divided[k]) {
			
					MyCube.vertexSearchCell(points[j]);
				}
			}
		}

		
		//[Info] Craeting Octree level 1
		if(MyCube.Total_Cell_Divided) {
		octreeSHM* Octree_1 = new octreeSHM;
		Octree_1->setHexMeshElement(MyCube);
		//[Info] Buscando en Octree1 los puntos insertados
		for(int k=0; k<(int)Octree_1->Log_Cells_Max(); k++) {
			Octree_1->loadVertexId((unsigned) k);
			Octree_1->CenterC8();
			for(int j=0; j<number_of_points; j++) {
				if(!Octree_1->Cell_Divided[k]) {
				Octree_1->vertexSearchCell(points[j]);
				}
			}
		}

		//[Info] Creating Octree level 2
		if(Octree_1->Total_Cell_Divided) {
		octreeSHM* Octree_2 = new octreeSHM;
		Octree_2->setHexMeshElement(*Octree_1);
		//[Info] Buscando en Octree1 los puntos insertados
		for(int k=0; k<(int)Octree_2->Log_Cells_Max(); k++) {
			Octree_2->loadVertexId((unsigned) k);
			Octree_2->CenterC8();
			for(int j=0; j<number_of_points; j++) {
				if(!Octree_2->Cell_Divided[k]) {
					Octree_2->vertexSearchCell(points[j]);
				}
			}
		}

		//[Info] Creating el Octree level 3
		if(Octree_2->Total_Cell_Divided) {
		octreeSHM* Octree_3 = new octreeSHM;
		Octree_3->setHexMeshElement(*Octree_2);
		//[Info] Buscando en Octree1 los puntos insertados
		for(int k=0; k<(int)Octree_3->Log_Cells_Max(); k++) {
			Octree_3->loadVertexId((unsigned) k);
			Octree_3->CenterC8();
			for(int j=0; j<number_of_points; j++) {
				if(!Octree_3->Cell_Divided[k]) {
					Octree_3->vertexSearchCell(points[j]);
				}
			}
		}

		//[Info] Creating el Octree level 4
		if(Octree_3->Total_Cell_Divided) {
		octreeSHM* Octree_4 = new octreeSHM;
		Octree_4->setHexMeshElement(*Octree_3);
		//[Info] Buscando en Octree1 los puntos insertados
		for(int k=0; k<(int)Octree_4->Log_Cells_Max(); k++) {
			Octree_4->loadVertexId((unsigned) k);
			Octree_4->CenterC8();
			for(int j=0; j<number_of_points; j++) {
				if(!Octree_4->Cell_Divided[k]) {
					Octree_4->vertexSearchCell(points[j]);
				}
			}
		}



		//[Info] Creating el Octree level 5
		if(Octree_4->Total_Cell_Divided) {
		octreeSHM* Octree_5 = new octreeSHM;
		Octree_5->setHexMeshElement(*Octree_4);
		//[Info] Buscando en Octree1 los puntos insertados
		for(int k=0; k<(int)Octree_5->Log_Cells_Max(); k++) {
			Octree_5->loadVertexId((unsigned) k);
			Octree_5->CenterC8();
			for(int j=0; j<number_of_points; j++) {
				if(!Octree_5->Cell_Divided[k]) {
					Octree_5->vertexSearchCell(points[j]);
				}
			}
		}

		//[Info] Creating el Octree level 6
		if(Octree_5->Total_Cell_Divided) {
		octreeSHM* Octree_6 = new octreeSHM;
		Octree_6->setHexMeshElement(*Octree_5);
		//[Info] Buscando en Octree1 los puntos insertados
		for(int k=0; k<(int)Octree_4->Log_Cells_Max(); k++) {
			Octree_6->loadVertexId((unsigned) k);
			Octree_6->CenterC8();
			for(int j=0; j<number_of_points; j++) {
				if(!Octree_6->Cell_Divided[k]) {
					Octree_6->vertexSearchCell(points[j]);
				}
			}
		}

		//[Info] Creating el Octree level 7
		if(Octree_6->Total_Cell_Divided) {
		octreeSHM* Octree_7 = new octreeSHM;
		Octree_7->setHexMeshElement(*Octree_6);
		//[Info] Buscando en Octree1 los puntos insertados
		for(int k=0; k<(int)Octree_7->Log_Cells_Max(); k++) {
			Octree_7->loadVertexId((unsigned) k);
			Octree_7->CenterC8();
			for(int j=0; j<number_of_points; j++) {
				if(!Octree_7->Cell_Divided[k]) {
					Octree_7->vertexSearchCell(points[j]);
				}
			}
		}


		int cells_added = Octree_1 -> Log_Cells_Max() +
				  Octree_2 -> Log_Cells_Max() +
				  Octree_3 -> Log_Cells_Max() +
				  Octree_4 -> Log_Cells_Max() +
				  Octree_5 -> Log_Cells_Max() +
				  Octree_6 -> Log_Cells_Max() +
				  Octree_7 -> Log_Cells_Max() ;

//		std::cout<<"[INFO] Cells Added: " << cells_added << "/" << MyCube.Log_Cells_Max()
//				 <<                  " (" <<100.0*(float)cells_added/(float)MyCube.Log_Cells_Max() << ")%" << std::endl;
	//[Info] Output to GNUPLOT
//	#include "lib/gnuplot.h" //sudo apt-get install gnuplot
//	system("sed -i -e 's/\r$//' temp/gnu.data"); 
//	system("chmod +x temp/gnu.data");
//	system("./temp/gnu.data");

//	std::string nameFile = "meshIO_" + std::integerToString(t);

//	MyCube.WriteMesh(meshFileOF, nameFile);

	std::cout<<"DELETING OCTREES 7: "<< Octree_7->Log_Cells_Max() << std::endl;
//	Octree_7->WriteMesh();
	delete Octree_7;
}

	std::cout<<"DELETING OCTREES 6: "<< Octree_6->Log_Cells_Max() << std::endl;
//	Octree_6->WriteMesh();
	delete Octree_6;
}

	std::cout<<"DELETING OCTREES 5: "<< Octree_5->Log_Cells_Max() << std::endl;
//	Octree_5->WriteMesh();
	delete Octree_5;
}

	std::cout<<"DELETING OCTREES 4: "<< Octree_4->Log_Cells_Max() << std::endl;
//	Octree_4->WriteMesh();
	delete Octree_4;
}

	std::cout<<"DELETING OCTREES 3: "<< Octree_3->Log_Cells_Max() << std::endl;
//	Octree_3->WriteMesh();
	delete Octree_3;
}

	std::cout<<"DELETING OCTREES 2: "<< Octree_2->Log_Cells_Max() << std::endl;
	Octree_2->WriteMesh();
	delete Octree_2;
}
	std::cout<<"DELETING OCTREES 1: "<< Octree_1->Log_Cells_Max() << std::endl;

//	Octree_1->WriteMesh();
	delete Octree_1;
}

//	MyCube.WriteMesh();

	std::cout<<"TIME-STAMP: "<<t<<"/"<<tfin<<std::endl;
//	t++;
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

