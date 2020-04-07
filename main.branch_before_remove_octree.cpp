#include "lib/lib.h"

//#include <vtkXMLUnstructuredGrid.h>
//#include <GL/glew.h>


bool Log_Status   = true;
bool Write_Mesh   = true;
bool Write_Octree = false;
bool Write_Vec3   = true;

bool old = true;

unsigned octreeSHM::Depth = 1; //reserved level 0 for root mesh

int main()
{

    float VIEW_ROTX = 0;
    float VIEW_ROTZ = 0;
    int MAX_DEPTH = 17;
    unsigned NEL_Y = 1000+1;
    unsigned NEL_X = 10+1; double DX = 1.0;
    unsigned NEL_Z = 10+1; double DZ = 1.0;
    int t=0;
    int tfin = 10;

	structuredHexMesh MyCube(NEL_X, NEL_Y, NEL_Z);

//Defining the mesh-surface that will be extruded later
//with SweepFace to create a 3D hexaedral structured-mesh
{
    vec3 Surface[NEL_X*NEL_Z];

    for (int j=0; j<NEL_Z; j++) {
        for (int i=0; i<NEL_X; i++) {

            Surface[NEL_X*j+i] = vec3(DX*(double)i, 0.0, DZ*(double)j);
        }
    }

	    int vertexNEL = sizeof(Surface)/sizeof(vec3);
	    //Surface[0].ArithmeticForEach(Surface, NEL_X*NEL_Z , vec3(0.0, 0.0, 2.0), 1);

		MyCube.SweepFace(Surface, NEL_X, NEL_Z, NEL_Y-1, 0.016*2.0*PI/(float) (NEL_Y-1), vec3(-100.0,0.0,0.0));
	
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


   octreeSHM* OctreeLevel[MAX_DEPTH+1]{nullptr};
//   OctreeLevel[0] = (octreeSHM)&MyCube;

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

	//[Info] Buscando en MyCube los puntos insertados	
	bool Item_inserted[number_of_points]={false};
	for(unsigned id=0; id < MyCube.Log_Cells_Max(); id++) {

        if(MyCube.Total_Cell_Divided == MyCube.Log_Cells_Max()) break;

            for(int j=0; j<number_of_points; j++) {

                if(!Item_inserted[j]) {

                    if(!MyCube.Cell_Divided[id]) {

                        MyCube.loadVertexId(id);
                        if(MyCube.vertexSearchCell(Item[j])) {
						Item_inserted[j] = true;
					    }
				    }
			    }
            }
	}

    unsigned thisOctLevel;

	//[Info] Creating Octree level 1

    thisOctLevel = octreeSHM::Depth;
	if(MyCube.Total_Cell_Divided) {

	OctreeLevel[thisOctLevel] = new octreeSHM(MyCube.Total_Cell_Divided);

	OctreeLevel[thisOctLevel]->setHexMeshElement(MyCube);

	//[Info] Buscando en Octree1 los puntos insertados
	bool Item_inserted[number_of_points]={false};

	for(int k=0; k<(int)OctreeLevel[thisOctLevel]->Log_Cells_Max(); k++) {
    if(OctreeLevel[thisOctLevel]->Total_Cell_Divided == OctreeLevel[thisOctLevel]->Log_Cells_Max()) break;
		for(int j=0; j<number_of_points; j++) {

			if(!Item_inserted[j]) {

				if(!OctreeLevel[thisOctLevel]->Cell_Divided[k]) {

					OctreeLevel[thisOctLevel]->loadVertexId((unsigned) k, 1);
					OctreeLevel[thisOctLevel]->CenterC8();

//std::cout<<"Buscando el punto: " << j << " en Octree 1"<<"Celda: "<< k <<std::endl;
					if(OctreeLevel[thisOctLevel]->vertexSearchCell(Item[j])) {
						Item_inserted[j] = true;
					}
				}
			}
		}
    }
    }//I want to avoid Nested Invoking Classes

//WHILE LOOP TO CREATE OCTREE MESH
while(octreeSHM::Depth < MAX_DEPTH+1)
{
	//[Info] Creating Octree level 1

    thisOctLevel = octreeSHM::Depth;
    unsigned cells_divided = OctreeLevel[octreeSHM::giveLowerLevelID()]->Total_Cell_Divided;

	if(cells_divided) {
	OctreeLevel[thisOctLevel] = new octreeSHM(cells_divided);

	OctreeLevel[thisOctLevel]->setHexMeshElement(*OctreeLevel[octreeSHM::giveLowerLevelID()]);

	//[Info] Buscando en Octree1 los puntos insertados
	bool Item_inserted[number_of_points]={false};

	for(int k=0; k<(int)OctreeLevel[thisOctLevel]->Log_Cells_Max(); k++) {
    if(OctreeLevel[thisOctLevel]->Total_Cell_Divided == OctreeLevel[thisOctLevel]->Log_Cells_Max()) break;
		for(int j=0; j<number_of_points; j++) {

			if(!Item_inserted[j]) {

				if(!OctreeLevel[thisOctLevel]->Cell_Divided[k]) {

					OctreeLevel[thisOctLevel]->loadVertexId((unsigned) k, 1);
					OctreeLevel[thisOctLevel]->CenterC8();

					if(OctreeLevel[thisOctLevel]->vertexSearchCell(Item[j])) {
						Item_inserted[j] = true;
					}
				}
			}
		}
    }
    }//I want to avoid Nested Invoking Classes
}

	int cells_added{0};
    for (int i = (int)octreeSHM::giveLowerLevelID(); i>0; i--) {

       	cells_added += OctreeLevel[i] -> Log_Cells_Max();

        if(Write_Octree) OctreeLevel[i]->WriteMesh(&meshFileOF, nameFile, 2);

        delete OctreeLevel[i];
        OctreeLevel[i] = nullptr;
    }


    if(Log_Status) std::cout<<"TIME-STAMP: "<<t<<"/"<<tfin<<"\nCells Added: " << cells_added << std::endl;
    if(Write_Mesh) MyCube.WriteMesh(&meshFileOF, nameFile, 0);

    if(Write_Vec3){
    #include "issues/WriteVec3.h"
    }
}

	return 0;
}

