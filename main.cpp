#include "lib/lib.h"

//#include <vtkXMLUnstructuredGrid.h>
//#include <GL/glew.h>

bool Log_Status   = true;
bool Write_Mesh   = false;
bool Write_Octree = false;
bool Write_Vec3   = false;

int main()
{

	float VIEW_ROTX = 0;
	float VIEW_ROTZ = 0;

	int NEL = 100;
	int t=0;
	int tfin = 100;

	structuredHexMesh MyCube;

//Defining the mesh-surface that will be extruded later
//with SweepFace to create a 3D hexaedral structured-mesh
{
    int NEL_X = 20; double DX = 0.25;
    int NEL_Z = 20; double DZ = 0.4;
    vec3 Surface[NEL_X*NEL_Z];

    for (int j=0; j<NEL_Z; j++) {
        for (int i=0; i<NEL_X; i++) {

            Surface[NEL_X*j+i] = vec3(DX*(double)i, 0.0, DZ*(double)j);
        }
    }

	    int vertexNEL = sizeof(Surface)/sizeof(vec3);
	    Surface[0].ArithmeticForEach(Surface, NEL_X*NEL_Z , vec3(0.0, 0.0, 2.0), 1);

		MyCube.SweepFace(Surface, NEL_X, NEL_Z, NEL, 2.0*PI/(float) NEL, vec3(0.0,0.0,0.0));
	
		//This command compute cell centers of all cells for the mesh
		for(int i=0; i< (int)MyCube.Log_Cells_Max(); i++) {

			MyCube.loadVertexId((unsigned) i);
			MyCube.CenterC8();
		}

			MyCube.Log();	
}//end of scope of 2D mesh-surface: Surface 

//Defining an cloud of points to test the octree algorithm
  const double lower{1.0}, upper{1.5};
  double num_random = dRandom(lower, upper);

    vec3 Item[1000];

    for(int i=0; i<1000; i++)
    {
        Item[i] = vec3(dRandom(lower,upper), dRandom(lower,upper), dRandom(lower,upper) );
    }

	int number_of_points = sizeof(Item)/sizeof(vec3);

//Main loop to run the algorithm. It takes the cloud of points and compute
//what cell of the mesh they belong to slit this cell in octree recursively
while(t++<tfin) {

    std::string nameFile = "temp/meshIO_" + std::to_string(t) + ".csv";
    std::ofstream meshFileOF;

    #include "issues/LocRotForEach.h"

	//[Info] Reset to false all entries of subdivions before recompute the insertion points in next step
	if(MyCube.Total_Cell_Divided) {

        MyCube.Total_Cell_Divided = 0;
		for(int i=0; (unsigned) i<MyCube.Log_Cells_Max(); i++) {
	        
            *(MyCube.Cell_Divided+i) = false;
		}
	}

	//[Info] Buscando en MyCube los puntos insertados	
	bool Item_inserted[number_of_points]={false};
	for(unsigned id=0; id < MyCube.Log_Cells_Max(); id++) {

		MyCube.loadVertexId(id);

		for(int j=0; j<number_of_points; j++) {

			if(!Item_inserted[j]) {

				if(!MyCube.Cell_Divided[id]) {

					if(MyCube.vertexSearchCell(Item[j])) {

						Item_inserted[j] = true;
					}
				}
			}
		}
	}

	//[Info] Creating Octree level 1
	if(MyCube.Total_Cell_Divided) {
	octreeSHM* Octree_1 = new octreeSHM;
	Octree_1->setHexMeshElement(MyCube);

	//[Info] Buscando en Octree1 los puntos insertados
	bool Item_inserted[number_of_points]={false};

	for(int k=0; k<(int)Octree_1->Log_Cells_Max(); k++) {

		for(int j=0; j<number_of_points; j++) {

			if(!Item_inserted[j]) {

				if(!Octree_1->Cell_Divided[k]) {

					Octree_1->loadVertexId((unsigned) k, 1);
					Octree_1->CenterC8();

					if(Octree_1->vertexSearchCell(Item[j])) {
						Item_inserted[j] = true;
					}
				}
			}
		}
	}

    //[Info] Creating Octree level 2
	if(Octree_1->Total_Cell_Divided) {
	octreeSHM* Octree_2 = new octreeSHM;
	Octree_2->setHexMeshElement(*Octree_1);

	//[Info] Buscando en Octree1 los puntos insertados
	bool Item_inserted[number_of_points]={false};

	for(int k=0; k<(int)Octree_2->Log_Cells_Max(); k++) {

		for(int j=0; j<number_of_points; j++) {

			if(!Item_inserted[j]) {

				if(!Octree_2->Cell_Divided[k]) {

					Octree_2->loadVertexId((unsigned) k, 1);
					Octree_2->CenterC8();

					if(Octree_2->vertexSearchCell(Item[j])) {
						Item_inserted[j] = true;
					}
				}
			}
		}
	}

	int cells_added =   Octree_1 -> Log_Cells_Max() +
		                Octree_2 -> Log_Cells_Max() ;

    if(Log_Status)	std::cout<<"DELETING OCTREES 2: "<< Octree_2->Log_Cells_Max() << std::endl;
    if(Write_Octree) Octree_2->WriteMesh(&meshFileOF, nameFile, 2);

	delete Octree_2;
}

    if(Log_Status) std::cout<<"DELETING OCTREES 1: "<< Octree_1->Log_Cells_Max() << std::endl;
    if(Write_Octree) Octree_1->WriteMesh(&meshFileOF, nameFile, 1);

	delete Octree_1;
}

    if(Log_Status) std::cout<<"TIME-STAMP: "<<t<<"/"<<tfin<<std::endl;
    if(Write_Mesh) MyCube.WriteMesh(&meshFileOF, nameFile, 0);

    if(Write_Vec3){
        #include "issues/WriteVec3.h"
    }
}

	return 0;
}

