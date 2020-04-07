#include "lib/lib.h"

//#include <vtkXMLUnstructuredGrid.h>
//#include <GL/glew.h>


bool Log_Status   = true;
bool Write_Mesh   = true;
bool Write_Octree = false;
bool Write_Vec3   = true;

bool old = true;

unsigned octreeSHM::Depth = 0;

int main()
{

	float VIEW_ROTX = 0;
	float VIEW_ROTZ = 0;

	int NEL = 10;
	int t=0;
	int tfin = 10;

	structuredHexMesh MyCube;

//Defining the mesh-surface that will be extruded later
//with SweepFace to create a 3D hexaedral structured-mesh
{
    int NEL_X = 11; double DX = 1.0;
    int NEL_Z = 11; double DZ = 1.0;
    vec3 Surface[NEL_X*NEL_Z];

    for (int j=0; j<NEL_Z; j++) {
        for (int i=0; i<NEL_X; i++) {

            Surface[NEL_X*j+i] = vec3(DX*(double)i, 0.0, DZ*(double)j);
        }
    }

	    int vertexNEL = sizeof(Surface)/sizeof(vec3);
	    //Surface[0].ArithmeticForEach(Surface, NEL_X*NEL_Z , vec3(0.0, 0.0, 2.0), 1);

		MyCube.SweepFace(Surface, NEL_X, NEL_Z, NEL, 0.016*2.0*PI/(float) NEL, vec3(-100.0,0.0,0.0));
	
		//This command compute cell centers of all cells for the mesh
		for(int i=0; i< (int)MyCube.Log_Cells_Max(); i++) {

			MyCube.loadVertexId((unsigned) i);
			MyCube.CenterC8();
            MyCube.Log_Cell();
		}

			MyCube.Log();	
}//end of scope of 2D mesh-surface: Surface 

//Defining an cloud of points to test the octree algorithm
  const double lowerX{0.0}, upperX{1.0};
  const double lowerY{0.0}, upperY{1.0};
  const double lowerZ{0.0}, upperZ{1.0};
//  double num_randomX = dRandom(lowerX, upperX);
//  double num_randomY = dRandom(lowerY, upperY);
//  double num_randomZ = dRandom(lowerZ, upperZ);

    vec3 Item[100];

    for(int i=0; i<100; i++)
    {
        Item[i] = vec3(dRandom(lowerX,upperX), dRandom(lowerY,upperY), dRandom(lowerZ,upperZ) );
    }

	int number_of_points = sizeof(Item)/sizeof(vec3);

//Main loop to run the algorithm. It takes the cloud of points and compute
//what cell of the mesh they belong to slit this cell in octree recursively
while(t++<tfin) {

    std::string nameFile = "temp/meshIO_" + std::to_string(t) + ".csv";
    std::ofstream meshFileOF;
//    Item[0].ArithmeticForEach(Item, number_of_points, vec3(0.01, 0.0, 0.0), 0);
//    #include "issues/LocRotForEach.h"
    

	//[Info] Reset to false all entries of subdivions before recompute the insertion points in next step
	if(MyCube.Total_Cell_Divided) {

        MyCube.Total_Cell_Divided = 0;
		for(int i=0; (unsigned) i<MyCube.Log_Cells_Max(); i++) {
	        
            *(MyCube.Cell_Divided+i) = false;
		}
	}
/*
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

    //[Info] Creating Octree level 3
	if(Octree_2->Total_Cell_Divided) {
	octreeSHM* Octree_3 = new octreeSHM;
	Octree_3->setHexMeshElement(*Octree_2);

	//[Info] Buscando en Octree1 los puntos insertados
	bool Item_inserted[number_of_points]={false};

	for(int k=0; k<(int)Octree_3->Log_Cells_Max(); k++) {

		for(int j=0; j<number_of_points; j++) {

			if(!Item_inserted[j]) {

				if(!Octree_3->Cell_Divided[k]) {

					Octree_3->loadVertexId((unsigned) k, 1);
					Octree_3->CenterC8();

					if(Octree_3->vertexSearchCell(Item[j])) {
						Item_inserted[j] = true;
					}
				}
			}
		}
	}
*/

	//[Info] Buscando en MyCube los puntos insertados	
	bool Item_inserted[number_of_points]={false};
	for(unsigned id=0; id < MyCube.Log_Cells_Max(); id++) {
    if(MyCube.Total_Cell_Divided == MyCube.Log_Cells_Max()) break;

		for(int j=0; j<number_of_points; j++) {

			if(!Item_inserted[j]) {

				if(!MyCube.Cell_Divided[id]) {

//std::cout<<"Buscando el punto: " << j << " en el Cubo"<<"Celda: "<< id << std::endl;
		            MyCube.loadVertexId(id);
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
    if(Octree_1->Total_Cell_Divided == Octree_1->Log_Cells_Max()) break;
		for(int j=0; j<number_of_points; j++) {

			if(!Item_inserted[j]) {

				if(!Octree_1->Cell_Divided[k]) {

					Octree_1->loadVertexId((unsigned) k, 1);
					Octree_1->CenterC8();

//std::cout<<"Buscando el punto: " << j << " en Octree 1"<<"Celda: "<< k <<std::endl;
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
    if(Octree_2->Total_Cell_Divided == Octree_2->Log_Cells_Max()) break;
		for(int j=0; j<number_of_points; j++) {

			if(!Item_inserted[j]) {

				if(!Octree_2->Cell_Divided[k]) {

					Octree_2->loadVertexId((unsigned) k, 1);
					Octree_2->CenterC8();

//std::cout<<"Buscando el punto: " << j << " en Octree 2"<<"Celda: "<< k <<std::endl;
					if(Octree_2->vertexSearchCell(Item[j])) {
						Item_inserted[j] = true;
					}
				}
			}
		}
	}

    //[Info] Creating Octree level 3
	if(Octree_2->Total_Cell_Divided) {
	octreeSHM* Octree_3 = new octreeSHM;
	Octree_3->setHexMeshElement(*Octree_2);

	//[Info] Buscando en Octree1 los puntos insertados
	bool Item_inserted[number_of_points]={false};

	for(int k=0; k<(int)Octree_3->Log_Cells_Max(); k++) {
    if(Octree_3->Total_Cell_Divided == Octree_3->Log_Cells_Max()) break;
		for(int j=0; j<number_of_points; j++) {

			if(!Item_inserted[j]) {

				if(!Octree_3->Cell_Divided[k]) {

					Octree_3->loadVertexId((unsigned) k, 1);
					Octree_3->CenterC8();

//std::cout<<"Buscando el punto: " << j << " en Octree 3"<<"Celda: "<< k <<std::endl;
					if(Octree_3->vertexSearchCell(Item[j])) {
						Item_inserted[j] = true;
					}
				}
			}
		}
	}

	int cells_added =   Octree_1 -> Log_Cells_Max() +
		                Octree_2 -> Log_Cells_Max() +
		                Octree_3 -> Log_Cells_Max() ;


    if(Log_Status)	std::cout<<"DELETING OCTREES 3: "<< Octree_3->Log_Cells_Max() << std::endl;
    if(Write_Octree) Octree_3->WriteMesh(&meshFileOF, nameFile, 3);

	delete Octree_3;
}
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

