#include "octreeSHM.h"

void octreeSHM::loadVertexId(const unsigned &id)
{
    	if(id<m_Volume_Population)
    {
    	m_id = id; //ESTO TENGO QUE ARREGLARLO: OTRAS FUNCIONES DEPENDEN DE QUE ESTA SEA LLAMADA PRIMERO PARA PODER USAR m_id

	int m_W = 3;
	int m_H = 3;
	int m_L = 3;
	int HW = m_H*m_W;                       //Count vertex in a layer
        int count_Cells_layer = (m_H-1)*(m_W-1);//Count elements in a layer

        int count_rows_passed = 0;              //Adds the last vertex of the row |-0-|-1-|-2-|-3-(|) <-this
        int count_layers_passed = 0;            //Adds the top row of vertex-W

	int id_eq = id - (id/8)*8; //esto lleva cualquier id a su equivalente en la primera celda
        count_rows_passed = id_eq/(m_W-1);
        count_layers_passed = id_eq/count_Cells_layer;

	int i = id_eq + count_rows_passed + count_layers_passed * m_W + (id/8)*(m_H*m_W*3);
	//Mapp of local vertex enum		global possition XYZ in a dimensional global frame reference
	//ESTE TAMBIEN HAY QUE ARREGLARLO PORQUE ESTE MAPEADO SOLO SIRVE PARA LA MALLA DE LEVEL0 LOS DEMAS LEVEL TIENEN OTRO MAPEADO
	this->Vertex[0] = &Mesh[i];		//(0 0 0)
        this->Vertex[1] = &Mesh[i+1];		//(1 0 0)
        this->Vertex[2] = &Mesh[i+1+m_W];	//(1 0 1)
        this->Vertex[3] = &Mesh[i+m_W];		//(0 0 1)

        this->Vertex[4] = &Mesh[i+HW];		//(0 1 0)
        this->Vertex[5] = &Mesh[i+1+HW];	//(1 1 0)
        this->Vertex[6] = &Mesh[i+1+m_W+HW];	//(1 1 1)
        this->Vertex[7] = &Mesh[i+m_W+HW];	//(0 1 1)
	//OBS: los centroides no estan optimizados y de momento no comparten info asi el indice no hay que procesarlo como para los vertex
    }
    
    else
    {
	std::cout<<"[ERROR] ID out of bound"<<std::endl;
    }
}

void octreeSHM::setHexMeshElement(structuredHexMesh& MeshUP)
{

    if(Mesh==0)
    {
        const int m_H      = 3; //valores del octree para una celda at level1
        const int m_W      = 3; //valores del octree para una celda at level1
	const int c_Ysweep = 2; //valores del octree para una celda at level1
        //const int count_MeshSurface = m_H*m_W*Divisions;
	//m_id = (m_H-1)*(m_W-1)*c_Ysweep*Divisions;

        m_Vertex_Population = (c_Ysweep+1)*m_H*m_W;
        m_Volume_Population = (m_H-1)*(m_W-1)*c_Ysweep;
	
	//Actual values for level1 of octree:
	m_Vertex_Population *=MeshUP.Total_Cell_Divided;
	m_Volume_Population *=MeshUP.Total_Cell_Divided;

//	std::cout<<"[OCTREE] POPULATION: "<<m_Volume_Population<<std::endl;
        Mesh           = new vec3[m_Vertex_Population];
        Cell_Centroids = new vec3[m_Volume_Population];
	Cell_Divided   = new bool[m_Volume_Population]{false};
	Face_UNormals  = new vec3[m_Volume_Population*6]; //each cube has six normals, not using face-share optimiz.
	Face_Centroids = new vec3[m_Volume_Population*6];
    }

    else
    {
        std::cout<<"Mesh has been already created"<<std::endl;
    }

	int i = 0;
	for(int j =0; j<MeshUP.Log_Cells_Max(); j++)
       	{if(MeshUP.Cell_Divided[j])
	{
		int layer = i*9*3;
		i++;
		MeshUP.loadVertexId((unsigned) j);
		//NEW LEFT
		//dereference operator gives the actual coordinates in *MeshUP.Vertex[N]	
		Mesh[layer+0]  = *MeshUP.Vertex[0];
		Mesh[layer+1]  = vec3::Line(*MeshUP.Vertex[0],*MeshUP.Vertex[1], 0.5l);
		Mesh[layer+2]  = *MeshUP.Vertex[1];
		Mesh[layer+3]  = vec3::Line(*MeshUP.Vertex[0],*MeshUP.Vertex[3], 0.5l);
		Mesh[layer+5]  = vec3::Line(*MeshUP.Vertex[1],*MeshUP.Vertex[2], 0.5l);
		Mesh[layer+6]  = *MeshUP.Vertex[3];
		Mesh[layer+7]  = vec3::Line(*MeshUP.Vertex[3],*MeshUP.Vertex[2], 0.5l);
		Mesh[layer+8]  = *MeshUP.Vertex[2];
		Mesh[layer+4]  = vec3::Line(Mesh[layer+3],Mesh[layer+5], 0.5l);
		//NEW RIGTH
		Mesh[layer+18] = *MeshUP.Vertex[4];
		Mesh[layer+19] = vec3::Line(*MeshUP.Vertex[4],*MeshUP.Vertex[5], 0.5l);
		Mesh[layer+20] = *MeshUP.Vertex[5];
		Mesh[layer+21] = vec3::Line(*MeshUP.Vertex[4],*MeshUP.Vertex[7], 0.5l);
		Mesh[layer+23] = vec3::Line(*MeshUP.Vertex[5],*MeshUP.Vertex[6], 0.5l);
		Mesh[layer+24] = *MeshUP.Vertex[7];
		Mesh[layer+25] = vec3::Line(*MeshUP.Vertex[7],*MeshUP.Vertex[6], 0.5l);
		Mesh[layer+26] = *MeshUP.Vertex[6];
		Mesh[layer+22] = vec3::Line(Mesh[layer+21],Mesh[layer+23], 0.5l);
	
		//NEW CENTER
		Mesh[layer+9]  = vec3::Line(*MeshUP.Vertex[0],*MeshUP.Vertex[4], 0.5l);
		Mesh[layer+10] = vec3::Line(Mesh[layer+1],Mesh[layer+19], 0.5l);
		Mesh[layer+11] = vec3::Line(*MeshUP.Vertex[1],*MeshUP.Vertex[5], 0.5l);
		Mesh[layer+12] = vec3::Line(Mesh[layer+3],Mesh[layer+21], 0.5l);
		Mesh[layer+13] = vec3::Line(Mesh[layer+4],Mesh[layer+22], 0.5l);
		Mesh[layer+14] = vec3::Line(Mesh[layer+5],Mesh[layer+23], 0.5l);
		Mesh[layer+15] = vec3::Line(*MeshUP.Vertex[3],*MeshUP.Vertex[7], 0.5l);
		Mesh[layer+16] = vec3::Line(Mesh[layer+7],Mesh[layer+25], 0.5l);
		Mesh[layer+17] = vec3::Line(*MeshUP.Vertex[2],*MeshUP.Vertex[6], 0.5l);
	}
	}
}

void octreeSHM::setHexMeshElement(octreeSHM& MeshUP)
{

    if(Mesh==0)
    {
        const int m_H      = 3; //valores del octree para una celda at level1
        const int m_W      = 3; //valores del octree para una celda at level1
	const int c_Ysweep = 2; //valores del octree para una celda at level1
        //const int count_MeshSurface = m_H*m_W*Divisions;
	//m_id = (m_H-1)*(m_W-1)*c_Ysweep*Divisions;

        m_Vertex_Population = (c_Ysweep+1)*m_H*m_W;
        m_Volume_Population = (m_H-1)*(m_W-1)*c_Ysweep;
	
	//Actual values for level1 of octree:
	m_Vertex_Population *=MeshUP.Total_Cell_Divided;
	m_Volume_Population *=MeshUP.Total_Cell_Divided;

        Mesh           = new vec3[m_Vertex_Population];
        Cell_Centroids = new vec3[m_Volume_Population];
	Cell_Divided   = new bool[m_Volume_Population]{false};
	Face_UNormals  = new vec3[m_Volume_Population*6]; //each cube has six normals, not using face-share optimiz.
	Face_Centroids = new vec3[m_Volume_Population*6];
    }

    else
    {
        std::cout<<"Mesh has been already created"<<std::endl;
    }

	int i = 0;
	for(int j =0; j<MeshUP.Log_Cells_Max(); j++)
       	{if(MeshUP.Cell_Divided[j])
	{
		int layer = i*9*3;
		i++;
		MeshUP.loadVertexId((unsigned) j);
		//NEW LEFT
		//dereference operator gives the actual coordinates in *MeshUP.Vertex[N]	
		Mesh[layer+0]  = *MeshUP.Vertex[0];
		Mesh[layer+1]  = vec3::Line(*MeshUP.Vertex[0],*MeshUP.Vertex[1], 0.5l);
		Mesh[layer+2]  = *MeshUP.Vertex[1];
		Mesh[layer+3]  = vec3::Line(*MeshUP.Vertex[0],*MeshUP.Vertex[3], 0.5l);
		Mesh[layer+5]  = vec3::Line(*MeshUP.Vertex[1],*MeshUP.Vertex[2], 0.5l);
		Mesh[layer+6]  = *MeshUP.Vertex[3];
		Mesh[layer+7]  = vec3::Line(*MeshUP.Vertex[3],*MeshUP.Vertex[2], 0.5l);
		Mesh[layer+8]  = *MeshUP.Vertex[2];
		Mesh[layer+4]  = vec3::Line(Mesh[layer+3],Mesh[layer+5], 0.5l);
		//NEW RIGTH
		Mesh[layer+18] = *MeshUP.Vertex[4];
		Mesh[layer+19] = vec3::Line(*MeshUP.Vertex[4],*MeshUP.Vertex[5], 0.5l);
		Mesh[layer+20] = *MeshUP.Vertex[5];
		Mesh[layer+21] = vec3::Line(*MeshUP.Vertex[4],*MeshUP.Vertex[7], 0.5l);
		Mesh[layer+23] = vec3::Line(*MeshUP.Vertex[5],*MeshUP.Vertex[6], 0.5l);
		Mesh[layer+24] = *MeshUP.Vertex[7];
		Mesh[layer+25] = vec3::Line(*MeshUP.Vertex[7],*MeshUP.Vertex[6], 0.5l);
		Mesh[layer+26] = *MeshUP.Vertex[6];
		Mesh[layer+22] = vec3::Line(Mesh[layer+21],Mesh[layer+23], 0.5l);
	
		//NEW CENTER
		Mesh[layer+9]  = vec3::Line(*MeshUP.Vertex[0],*MeshUP.Vertex[4], 0.5l);
		Mesh[layer+10] = vec3::Line(Mesh[layer+1],Mesh[layer+19], 0.5l);
		Mesh[layer+11] = vec3::Line(*MeshUP.Vertex[1],*MeshUP.Vertex[5], 0.5l);
		Mesh[layer+12] = vec3::Line(Mesh[layer+3],Mesh[layer+21], 0.5l);
		Mesh[layer+13] = vec3::Line(Mesh[layer+4],Mesh[layer+22], 0.5l);
		Mesh[layer+14] = vec3::Line(Mesh[layer+5],Mesh[layer+23], 0.5l);
		Mesh[layer+15] = vec3::Line(*MeshUP.Vertex[3],*MeshUP.Vertex[7], 0.5l);
		Mesh[layer+16] = vec3::Line(Mesh[layer+7],Mesh[layer+25], 0.5l);
		Mesh[layer+17] = vec3::Line(*MeshUP.Vertex[2],*MeshUP.Vertex[6], 0.5l);
	}
	}

//        std::cout<<"[OCTREE] POPULATION: "<<m_Volume_Population<<std::endl;
}
