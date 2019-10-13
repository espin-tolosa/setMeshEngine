#include <iostream>
#include <math.h>

#include "structuredHexMesh.h"
/**
[INTRO] This is an attempt to create a class for structured mesh which has been created from sweep face
        it should be able to take a C4 elements of a structured mesh and the create a structured mesh from it

        The structured mesh is going to be initialized as void and then if the function sweep is called,
        the structure will be created from an input face

        This structure has dynamic allocated memory, since it is able to perform many sweep operations which,
        will then increase the number of elements. For that reason the Population variables should be private entities
        where the functions that can eventually increase the number of any kind of elements of the mesh updates the value.

[SWEEP] The desing of this operation is based on take the first addess of vec3 and perform all the operations till target is reached,
        then the address pointer increases++ one unit to next vec3 of the stack and the operation is performed recursively until
        the last point of the mesh surface is reached.

    - MEMORY MANAGEMENT:

        When a struturedMesh is instanciated a void C8 mesh is created, then if some operation is performed like sweep face,
        the proper function receive as a parameters a mesh surface and dynamically create the structuredHexMesh of the object.

        So Sweep Faces must call to a function inside its class to instance new memory allocation with the exact size needed by that operation.

    - EXPECTED PARAMETERS:

        Mesh face: pointer to the first vec3 allocated in the stack
        Sweep op : Target of the sweep operation and number of layers

    - RETURNED VALUES:

        Each time a sweep operation over a vertex is done the resulted vertex will be addressed somewhere in the stack were it should be
        according to the map of the structured mesh desinged in the documentation.
        The reason why is not allocated inmediatly is "BY DESING" because of the map created to allocate the strutured vertex of the mesh.


[GET]   This function receives the index of an element and gets the memory address of vertex of the stencil. Provably this function will
        be separated into many functions as center of cell faces, centroid, normals, adjacent centroids, volumes, areas.

[MEMBERS]

        vec3  Mesh
        vec3* Vertex
        vec3* Edges
        vec3* Faces


**/


structuredHexMesh::structuredHexMesh()

/*    :   m_H(0), m_W(0), m_L(0), m_HW(0),
        m_Vertex_Population(0), m_Face_Population(0), m_Volume_Population(0), m_id(0),
        m_Total_Volume(0.0), m_cell_Volume(0.0),
        Mesh(), Cell_Centroids(), Cell_Divided(),
        Face_UNormals(), Face_Centroids(), Boundary_Cell(),
        Vertex(), Edge_i(), Edge_j(), Tris(), Quad(),
		Total_Cell_Divided(0)
*/        {
//            std::cout<<"\n[CONSTRUCTOR]: Structured Mesh\n"<<std::endl;
        }

structuredHexMesh::structuredHexMesh(unsigned UpperLevel_Divided_Cells)

    :   m_H(3), m_W(3), m_L(3), m_HW(3*3),
        m_Vertex_Population(3*3*3*UpperLevel_Divided_Cells),
        m_Volume_Population((3-1)*(3-1)*(3-1)*UpperLevel_Divided_Cells),
        Mesh(m_L*m_H*m_W*UpperLevel_Divided_Cells),
        Cell_Centroids((3-1)*(3-1)*(3-1)*UpperLevel_Divided_Cells),
        Cell_Divided((3-1)*(3-1)*(3-1)*UpperLevel_Divided_Cells, false),
        Face_UNormals((3-1)*(3-1)*(3-1)*UpperLevel_Divided_Cells*6),
        Face_Centroids((3-1)*(3-1)*(3-1)*UpperLevel_Divided_Cells*6),
        Boundary_Cell((3-1)*(3-1)*(3-1)*UpperLevel_Divided_Cells, false)
    {}

structuredHexMesh::structuredHexMesh(unsigned nel_TSx, unsigned nel_TSy, unsigned nel_TSz)

    :   m_H(nel_TSz), m_W(nel_TSx), m_L(nel_TSy),
        m_Vertex_Population(nel_TSz*nel_TSx*nel_TSy), m_Face_Population(0), m_Volume_Population((nel_TSz-1)*(nel_TSx-1)*(nel_TSy-1)),
        m_id(0), m_Total_Volume(0.0), m_cell_Volume(0.0),
        Mesh(nel_TSz*nel_TSx*nel_TSy),
        Cell_Centroids((nel_TSz-1)*(nel_TSx-1)*(nel_TSy-1)),
        Cell_Divided((nel_TSz-1)*(nel_TSx-1)*(nel_TSy-1), false),
        Face_UNormals((nel_TSz-1)*(nel_TSx-1)*(nel_TSy-1)*6),
        Face_Centroids((nel_TSz-1)*(nel_TSx-1)*(nel_TSy-1)*6),
        Boundary_Cell((nel_TSz-1)*(nel_TSx-1)*(nel_TSy-1),false),
        Vertex(), Edge_i(), Edge_j(), Tris(), Quad(),
		Total_Cell_Divided(0)
        {
		    m_HW = m_H*m_W;
        }

structuredHexMesh::~structuredHexMesh()
    {
//      std::cout<<"[DESTRUCTOR]: Structured Mesh"<<std::endl;

//	delete[] u;
//	delete[] r;
//	delete[] p;
//	delete[] T;

	}

    void structuredHexMesh::DisplaceMesh(const vec3& offset)
    {
        for(unsigned i = 0; i<m_Vertex_Population; i++) Mesh[i].Add(offset);
    }

    void structuredHexMesh::RotateXMesh(const float &alphax)
    {
        for(unsigned i = 0; i<m_Vertex_Population; i++) Mesh[i]= vec3::RotX(Mesh[i], alphax);
    }

    void structuredHexMesh::RotateYMesh(const float &alphay)
    {
        for(unsigned i = 0; i<m_Vertex_Population; i++) Mesh[i]= vec3::RotY(Mesh[i], alphay);
    }

    void structuredHexMesh::RotateZMesh(const float &alphaz)
    {
        for(unsigned i = 0; i<m_Vertex_Population; i++) Mesh[i]= vec3::RotZ(Mesh[i], alphaz);
    }

    void structuredHexMesh::loadCellEdges()
    {
        int map_v2e_i[] = {0,1,2,3,4,7,6,5,0,1,2,3};
        int map_v2e_j[] = {1,2,3,0,7,6,5,4,4,5,6,7};

        for(int l = 0; l<12; l++)
        {
            this->Edge_i[l] = Vertex[map_v2e_i[l]];
            this->Edge_j[l] = Vertex[map_v2e_j[l]];
        }
    }


    double structuredHexMesh::AreaC3(const vec3& p1, const vec3& p2, const vec3& p3)
    {
        vec3 W = vec3::Cross(p1,p2,p3);
        return 0.5*sqrtl(W.x*W.x + W.y*W.y + W.z*W.z);
    }

/**
    float structuredHexMesh::AreaC4(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3)
        {
        vec3 W0,W1;
        W0.Cross(v0,v1,v3);
        W1.Cross(v2,v3,v1);

        return 0.5*(sqrt(W0.x*W0.x+W0.y*W0.y+W0.z*W0.z)+sqrt(W1.x*W1.x+W1.y*W1.y+W1.z*W1.z));
        }
**/
    vec3 structuredHexMesh::CenterC3(const vec3& p1, const vec3& p2, const vec3& p3)
        {
            double i = 1./3.; //Multiplications are most efficient than divisions

            float x = (p1.x + p2.x + p3.x) * i;
            float y = (p1.y + p2.y + p3.y) * i;
            float z = (p1.z + p2.z + p3.z) * i;

            return vec3(x,y,z);
        }


    vec3 structuredHexMesh::CenterT4(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3)
    {
            double i = 1./4.; //Multiplications are most efficient than divisions
            double x = (v0.x + v1.x + v2.x + v3.x) * i;
            double y = (v0.y + v1.y + v2.y + v3.y) * i;
            double z = (v0.z + v1.z + v2.z + v3.z) * i;

            return vec3(x,y,z);
    }

    double structuredHexMesh::VolumeT4(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3)
    {
        double v1v2v3 = vec3::DotCross(v0,v1,v2,v3);
        return (sqrtl(v1v2v3*v1v2v3) / 6.);
    }

    vec3 structuredHexMesh::CenterC4(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3)
        {

        ///LA FUNCION AREAC3 está anulada porque produce una pequeña inestabilidad al usarlo en la media ponderada del centro de la cara
            vec3 C1 = structuredHexMesh::CenterC3(v0,v1,v2);
            double ac1 = structuredHexMesh::AreaC3(v0,v1,v2);

            vec3 C2 = structuredHexMesh::CenterC3(v0,v2,v3);
            double ac2 = structuredHexMesh::AreaC3(v0,v2,v3);

            vec3 D1 = structuredHexMesh::CenterC3(v0,v1,v3);
            double ad1 = structuredHexMesh::AreaC3(v0,v1,v3);

            vec3 D2 = structuredHexMesh::CenterC3(v1,v2,v3);
            double ad2 = structuredHexMesh::AreaC3(v1,v2,v3);

            double x1,y1,z1,x2,y2,z2;

            x1 = (C1.x*ac1+C2.x*ac2)/(ac1+ac2);
            y1 = (C1.y*ac1+C2.y*ac2)/(ac1+ac2);
            z1 = (C1.z*ac1+C2.z*ac2)/(ac1+ac2);

            x2 = (D1.x*ad1+D2.x*ad2)/(ad1+ad2);
            y2 = (D1.y*ad1+D2.y*ad2)/(ad1+ad2);
            z2 = (D1.z*ad1+D2.z*ad2)/(ad1+ad2);

            double x = 0.5*(x1+x2);
            double y = 0.5*(y1+y2);
            double z = 0.5*(z1+z2);

            return vec3(x,y,z);
        }

    void structuredHexMesh::CenterC8()
        {
            vec3 v0 = *Vertex[0];
            vec3 v1 = *Vertex[1];
            vec3 v2 = *Vertex[2];
            vec3 v3 = *Vertex[3];
            vec3 v4 = *Vertex[4];
            vec3 v5 = *Vertex[5];
            vec3 v6 = *Vertex[6];
            vec3 v7 = *Vertex[7];


	    //reset any carried value of Total Volume for cases of recursively calling CenterC8
	    m_Total_Volume = 0.;

            vec3 cL = structuredHexMesh::CenterC4(v0,v1,v2,v3);
            vec3 cR = structuredHexMesh::CenterC4(v4,v7,v6,v5);
            vec3 cB = structuredHexMesh::CenterC4(v0,v3,v7,v4);
            vec3 cF = structuredHexMesh::CenterC4(v1,v5,v6,v2);
            vec3 cS = structuredHexMesh::CenterC4(v0,v4,v5,v1);
            vec3 cN = structuredHexMesh::CenterC4(v2,v6,v7,v3);

	    Face_Centroids[m_id*6    ] = cL;
	    Face_Centroids[m_id*6 + 1] = cR;
            Face_Centroids[m_id*6 + 2] = cB;
            Face_Centroids[m_id*6 + 3] = cF;
            Face_Centroids[m_id*6 + 4] = cS;
            Face_Centroids[m_id*6 + 5] = cN;

	    //COMPUTE OUTTER NORMALS USING DIAGONALS OF FACES
	    //LEF
	    vec3 v20 = vec3::Glob2Loc(v2,v0);
	    vec3 v31 = vec3::Glob2Loc(v3,v1);
	    Face_UNormals[m_id*6] = vec3::UCross(v20,v31);
	    //FRONT
	    vec3 v61 = vec3::Glob2Loc(v6,v1);
	    vec3 v25 = vec3::Glob2Loc(v2,v5);
  	    Face_UNormals[m_id*6+3] = vec3::UCross(v61,v25);
	    //RIGHT
	    vec3 v75 = vec3::Glob2Loc(v7,v5);	   
	    vec3 v64 = vec3::Glob2Loc(v6,v4);
    	    Face_UNormals[m_id*6+1] = vec3::UCross(v75,v64);
	    //BACK
	    vec3 v34 = vec3::Glob2Loc(v3,v4);
	    vec3 v70 = vec3::Glob2Loc(v7,v0);
    	    Face_UNormals[m_id*6+2] = vec3::UCross(v34,v70);
	    //NORTH
	    vec3 v72 = vec3::Glob2Loc(v7,v2);
	    vec3 v36 = vec3::Glob2Loc(v3,v6);
    	    Face_UNormals[m_id*6+5] = vec3::UCross(v72,v36);
	    //SOUTH
	    vec3 v50 = vec3::Glob2Loc(v5,v0);
	    vec3 v14 = vec3::Glob2Loc(v1,v4);
   	    Face_UNormals[m_id*6+4] = vec3::UCross(v50,v14);

	    //COMPUTE THE CELL CENTER AND THE SHELL CENTROID
	    //cell_center (volume average)
	    //shell center (surface average) actually obsolete, it was ussed before created cell_center    
	    vec3 Shell_centroid;

            double i = 1./6.;

            Shell_centroid.x = (cL.x + cR.x + cB.x + cF.x + cS.x + cN.x) * i;
            Shell_centroid.y = (cL.y + cR.y + cB.y + cF.y + cS.y + cN.y) * i;
            Shell_centroid.z = (cL.z + cR.z + cB.z + cF.z + cS.z + cN.z) * i;

	    vec3 centerP;
	    vec3    s;
	    double as;
            
	    s = structuredHexMesh::CenterT4(Shell_centroid,v0,v1,v3);
            as = structuredHexMesh::VolumeT4(Shell_centroid,v0,v1,v3);
	    centerP.x += as*s.x;
	    centerP.y += as*s.y;
	    centerP.z += as*s.z;
       	    m_cell_Volume += as;

	    s  = structuredHexMesh::CenterT4(Shell_centroid,v1,v2,v3);
            as = structuredHexMesh::VolumeT4(Shell_centroid,v1,v2,v3);
	    centerP.x += as*s.x;
	    centerP.y += as*s.y;
	    centerP.z += as*s.z;
       	    m_cell_Volume += as;

	     s = structuredHexMesh::CenterT4(Shell_centroid,v1,v5,v6);
            as = structuredHexMesh::VolumeT4(Shell_centroid,v1,v5,v6);
	    centerP.x += as*s.x;
	    centerP.y += as*s.y;
	    centerP.z += as*s.z;
       	    m_cell_Volume += as;

	     s = structuredHexMesh::CenterT4(Shell_centroid,v1,v6,v2);
            as = structuredHexMesh::VolumeT4(Shell_centroid,v1,v6,v2);
	    centerP.x += as*s.x;
	    centerP.y += as*s.y;
	    centerP.z += as*s.z;
       	    m_cell_Volume += as;

	     s = structuredHexMesh::CenterT4(Shell_centroid,v4,v5,v6);
            as = structuredHexMesh::VolumeT4(Shell_centroid,v4,v5,v6);
	    centerP.x += as*s.x;
	    centerP.y += as*s.y;
	    centerP.z += as*s.z;
       	    m_cell_Volume += as;

             s = structuredHexMesh::CenterT4(Shell_centroid,v4,v6,v7);
            as = structuredHexMesh::VolumeT4(Shell_centroid,v4,v5,v7);
	    centerP.x += as*s.x;
	    centerP.y += as*s.y;
	    centerP.z += as*s.z;
       	    m_cell_Volume += as;

             s = structuredHexMesh::CenterT4(Shell_centroid,v0,v3,v4);
            as = structuredHexMesh::VolumeT4(Shell_centroid,v0,v3,v4);
	    centerP.x += as*s.x;
	    centerP.y += as*s.y;
	    centerP.z += as*s.z;
       	    m_cell_Volume += as;

             s = structuredHexMesh::CenterT4(Shell_centroid,v3,v7,v4);
            as = structuredHexMesh::VolumeT4(Shell_centroid,v3,v7,v4);
	    centerP.x += as*s.x;
	    centerP.y += as*s.y;
	    centerP.z += as*s.z;
       	    m_cell_Volume += as;

             s = structuredHexMesh::CenterT4(Shell_centroid,v2,v6,v3);
            as = structuredHexMesh::VolumeT4(Shell_centroid,v2,v6,v3);
	    centerP.x += as*s.x;
	    centerP.y += as*s.y;
	    centerP.z += as*s.z;
       	    m_cell_Volume += as;

             s = structuredHexMesh::CenterT4(Shell_centroid,v3,v6,v7);
            as = structuredHexMesh::VolumeT4(Shell_centroid,v3,v6,v7);
	    centerP.x += as*s.x;
	    centerP.y += as*s.y;
	    centerP.z += as*s.z;
       	    m_cell_Volume += as;

             s = structuredHexMesh::CenterT4(Shell_centroid,v0,v1,v4);
            as = structuredHexMesh::VolumeT4(Shell_centroid,v0,v1,v4);
	    centerP.x += as*s.x;
	    centerP.y += as*s.y;
	    centerP.z += as*s.z;
       	    m_cell_Volume += as;

             s = structuredHexMesh::CenterT4(Shell_centroid,v1,v5,v4);
            as = structuredHexMesh::VolumeT4(Shell_centroid,v1,v5,v4);
	    centerP.x += as*s.x;
	    centerP.y += as*s.y;
	    centerP.z += as*s.z;
       	    m_cell_Volume += as;

            m_Total_Volume += m_cell_Volume;

            vec3 centerS;
            centerS.x /= m_cell_Volume;
            centerS.y /= m_cell_Volume;
            centerS.z /= m_cell_Volume;

	    Cell_Centroids[m_id] = centerS;
}


/*---------------------------------------------------------
 * proc SweepFace
 * ---------------------
 *
 * Create a mesh struding the Surface[] around axis-Z
 * and center of revolve: Origin_Sweep
 * an angle equals to nel_Sweep * delta_Sweep
 *
 * Tis proc is candidate to be generalized by using
 * pointer function in the extruding operation. By now,
 * the compiled operation is RotZ as far as I don't need
 * more by now.
 *
 * To check:
 *
 * passing Surface Array by const pointer is OK by now
 *
 * evaluate performance of copy: Mesh[i] = *(Surface++);
 *
 * performance of: if(Mesh==0) is it passing everthing
 * or filtering vod mesh properly?
 *
 * add ForEach procedure to simplify the Loop sintaxis
 * ------------------------------------------------------*/
void structuredHexMesh::SweepFace(const vec3* Surface, const int& nel_TSx, const int& nel_TSz, const int& nel_Sweep, const double& delta_Sweep, const vec3& Origin_Sweep)
{
//    if(Mesh==0)
//    {
		for(int i=0; i<m_H*m_W; i++) {

			Mesh[i] = *(Surface++);
            std::cout << "Mesh element" << Mesh[i] << std::endl;
			for (int j = 0; j < nel_Sweep; j++) {
	
				Mesh[i+(j+1)*m_H*m_W] = vec3::Loc2Glob(vec3::RotZ(vec3::Glob2Loc(Mesh[i],Origin_Sweep),(j+1)*delta_Sweep), Origin_Sweep);
       		}
		}
    
		std::cout<<"[SWEEP] POPULATION: "<<m_Volume_Population<<std::endl;
   	}

//    else
//    {
//        std::cout<<"Mesh has been already created"<<std::endl;
//    }
//}

/*---------------------------------------------------------
 * proc vectexSearchCell
 * ---------------------
 *
 *  this proc takes the private vars: m_id
 *  actually is not necessary to call loadVertexId
 *
 *  I could simply add in first line m_id = id;
 *  the reason for hat is other private vars: Face_*[]
 *  are stored in memory as a linear array without any
 *  cell structure taking in advantage.
 *
 *  So, it is better do not change this because...
 *  I will implement some data structure to share common
 *  faces, vertex,... then I'll really need loadVertexID
 *
 * ------------------------------------------------------*/
bool structuredHexMesh::vertexSearchCell(const vec3& point)
{
	for (int i=0; i<6 ;i++) //It will placed here ForEach
	{
		if(vec3::Dot(vec3::Glob2Loc(point, Face_Centroids[m_id*6 + i]), Face_UNormals[m_id*6 + i]) > 0.0000000001)
		{
			return false;
		}
	}

	this->Cell_Divided[m_id] = true;
	this->Total_Cell_Divided++;
//	std::cout<<"Dividiendo Celda: "<<Total_Cell_Divided<<std::endl;
	return true;
}

//	HW________________Count vertex in a layer
//	(H-1)(W-1)________Count elements in a layer
//	id/(W-1)__________Adds the last vertex of the row |-0-|-1-|-2-|-3-(|) <-this 
//	id/(H-1)(W-1)_____Adds the top row of vertex-W

void structuredHexMesh::loadVertexId(const unsigned &id) {

//	std::cout << "Pointer to m_ID: " << &m_id << std::endl;
//	std::cout << "EL valor de m_id antes de ejecutra la funcion: " << m_id << std::endl;
	if(id<m_Volume_Population)
    {
    	m_id = id;
//	std::cin.get();

		int i = m_id + (m_id/(m_W-1)) + (m_id/((m_W-1)*(m_H-1)))*m_W;

		//ESTE TAMBIEN HAY QUE ARREGLARLO PORQUE ESTE MAPEADO SOLO SIRVE PARA LA MALLA DE LEVEL0 LOS DEMAS LEVEL TIENEN OTRO MAPEADO
		this->Vertex[0] = &Mesh[i];				//(0 0 0)
 		this->Vertex[1] = &Mesh[i+1];			//(1 0 0)
		this->Vertex[2] = &Mesh[i+1+m_W];		//(1 0 1)
		this->Vertex[3] = &Mesh[i+m_W];			//(0 0 1)
		this->Vertex[4] = &Mesh[i+m_HW];			//(0 1 0)
		this->Vertex[5] = &Mesh[i+1+m_HW];		//(1 1 0)
		this->Vertex[6] = &Mesh[i+1+m_W+m_HW];	//(1 1 1)
		this->Vertex[7] = &Mesh[i+m_W+m_HW];		//(0 1 1)
		//OBS: los centroides no estan optimiz y de momento no comparten info asi el indice no hay que procesarlo como para los vertex
    }
    
    else{std::cout<<"[ERROR] ID out of bound in MESH"<<std::endl;}

}

void structuredHexMesh::Log() const
{
    std::cout<<"\n----------------------------------[LOG MESH]"<<std::endl;
    std::cout<<"\tVertex\tFaces\tVolumes\tVolume"<<std::endl;
    std::cout<<"Size:\t"<<m_Vertex_Population<<"\t"<<m_Face_Population<<"\t"<<m_Volume_Population<<"\t"<<m_Total_Volume<<std::endl;
    std::cout<<"\nm_ID:\t"<<m_id<<std::endl;

    std::cout<<"Vertex\tID \tX Y Z Coordinates\n";
    for(unsigned i = 0; i<8; i++)
    {
    	std::cout<<"\tID "<<i<<"\t"<<*Vertex[i]<<std::endl;
    }
}

void structuredHexMesh::Log_Cell()
{
//assuming we want to load cell id
    unsigned IDX{0};
    unsigned IDY{0};
    unsigned IDZ{0};

//    std::cout << "Array Coordinates (ID-XZY) of Cell ID: " << m_id << std::endl;
//    std::cout << "--------------------------------------------" << std::endl;

    IDX = m_id % (m_H-1);
    IDZ = (m_id / (m_H-1)) % (m_W-1); 
    IDY = (m_id / ((m_H-1)*(m_W-1))) % (m_L-1);

    if(IDX == 0)        {Boundary_Cell[(int)m_id] = true;}// "Wall at B-Face"
    if(IDZ == 0)        {Boundary_Cell[(int)m_id] = true;}// "Wall at S-Face"
    if(IDY == 0)        {Boundary_Cell[(int)m_id] = true;}// "Wall at L-Face"
    if(IDX == (m_H-2))  {Boundary_Cell[(int)m_id] = true;}// "Wall at F-Face"
    if(IDZ == (m_W-2))  {Boundary_Cell[(int)m_id] = true;}// "Wall at N-Face"
    if(IDY == (m_L-2))  {Boundary_Cell[(int)m_id] = true;}// "Wall at R-Face"

//    std::cout<<"Check Bool: " << m_id <<" " << Boundary_Cell[m_id] << std::endl;
//    if(Boundary_Cell[m_id]) std::cout<< "Element is Wall Boundary Cell" << std::endl;


    //here comes:
    //Input: Item.(x,y,z) -> Cell_ID.(X, Y, Z)
    //Based on geometric global parameters

    //Cartesian
    // IDX <- x/W
    // IDY <- y/L
    // IDZ <- z/H

    //Cilindrical
    // IDA <- atan(y/x)/alpha
    // IDR <- sqrt(x*x + y*y)/W
    // IDZ <- z/H

}

void structuredHexMesh::Log_Cells() const
{
//	std::cout<<"Vertex Coordinates of Node: "<< m_id << std::endl;
	std::cout<<*Vertex[0]<<std::endl;
	std::cout<<*Vertex[1]<<std::endl;
	std::cout<<*Vertex[2]<<std::endl;
	std::cout<<*Vertex[3]<<std::endl;
	std::cout<<*Vertex[4]<<std::endl;
	std::cout<<*Vertex[5]<<std::endl;
	std::cout<<*Vertex[6]<<std::endl;
	std::cout<<*Vertex[7]<<std::endl;
}

unsigned structuredHexMesh::Log_Cells_Max() const
{
    return m_Volume_Population;
}

unsigned structuredHexMesh::Log_Verts() const
{
    return m_Vertex_Population;
}


//void structuredHexMesh::WriteMesh(std::string nameFile)
void structuredHexMesh::WriteMesh(std::ofstream *meshFileOF, std::string nameFile, int level)
{

//	std::ofstream meshFileOF;
//	std::string nameFile = "temp/meshIO.csv";
	meshFileOF->open(nameFile.c_str(), std::ios::app);

	if(meshFileOF->is_open())
	{
		for(int i = 0; i<this->Log_Verts(); i++)
		{
            if(Boundary_Cell[i]) {
			*meshFileOF << this->Mesh[i]<<", "<<level<<std::endl;
            }
		}


	/*	for(unsigned k=0; k < this->Log_Cells_Max(); k++) {
			this->loadVertexId(k);
			meshFileOF		<< *Vertex[0]<<"\n"
						<< *Vertex[1]<<"\n"
						<< *Vertex[2]<<"\n"
						<< *Vertex[3]<<"\n"
						<< *Vertex[4]<<"\n"
						<< *Vertex[5]<<"\n"
						<< *Vertex[6]<<"\n"
						<< *Vertex[7]<<"\n";
		}
	*/
		meshFileOF->close();
	}

}

//////////////////////////////////////////////////////////////////////////////
/*/Other projects

******************************************************************************
  A new posibly constructor por predefined meshes of type vec3[]
  **************************************************************

  structuredHexMesh::structuredHexMesh(const int h, const int w, const int l, const int count_mesh, const int  count_faces, const int count_volumes)

        :   m_H(h), m_W(w), m_L(l),
            m_Vertex_Population(count_mesh), m_Face_Population(count_faces), m_Volume_Population(count_volumes), m_id(0),
            m_Total_Volume(0.0), m_cell_Volume(0.0),
            Mesh(new vec3[count_mesh]),
            Cell_Centroids(new vec3[count_volumes]),
            Vertex(), Edge_i(), Edge_j(), Tris(), Quad()

        {
            std::cout<<"[CONSTRUCTOR]: Structured Mesh"<<std::endl;
            std::cout<<"m_Vertex_Population: "<<m_Vertex_Population<<std::endl;
            std::cout<<"MESH               : "<<&Mesh<<std::endl;
            std::cout<<"Centroids          : "<<&Cell_Centroids<<std::endl;
            std::cout<<"Vertex             : "<<Vertex<<std::endl;
            std::cout<<"Edge_i             : "<<Edge_i<<std::endl;
            std::cout<<"Edge_j             : "<<Edge_j<<std::endl;
	}
*/
