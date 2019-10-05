#include "structuredHexMesh.h"
#include "octreeSHM.h"
#include <iostream>

octreeSHM::octreeSHM() {

//	std::cout<<"\n[CONSTRUCTOR]: Octree Mesh"<<std::endl;

	m_H  = 3;
	m_W  = 3;
	m_L  = 3;
	m_HW = m_H*m_W;
}

octreeSHM::~octreeSHM() {

//	std::cout<<"\n[DESTRUCTOR]: Octree Mesh"<<std::endl;
	delete[] vTable;
}




void octreeSHM::loadVertexId(const unsigned &id) {

	if(id<m_Volume_Population) {

		m_id = id; //ESTO TENGO QUE ARREGLARLO: OTRAS FUNCIONES DEPENDEN DE QUE ESTA SEA LLAMADA PRIMERO PARA PODER USAR m_id

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
    		this->Vertex[4] = &Mesh[i+m_HW];		//(0 1 0)
    		this->Vertex[5] = &Mesh[i+1+m_HW];	//(1 1 0)
    		this->Vertex[6] = &Mesh[i+1+m_W+m_HW];	//(1 1 1)
    		this->Vertex[7] = &Mesh[i+m_W+m_HW];	//(0 1 1)
	//OBS: los centroides no estan optimiz y de momento no comparten info asi el indice no hay que procesarlo como para los vertex
	}
    
    else{std::cout<<"[ERROR] ID out of bound in OCTREE"<< std::endl;
    	 std::cout<<"Llamando a la celda: " << m_id << "/" << m_Volume_Population<<std::endl; }
}


//own implementation of loadVertexId for octree level as it maps cell in other way
void octreeSHM::loadVertexId(const unsigned &id, int octreeLevel) {

	if(id<m_Volume_Population) {

		m_id = id; //ESTO TENGO QUE ARREGLARLO: OTRAS FUNCIONES DEPENDEN DE QUE ESTA SEA LLAMADA PRIMERO PARA PODER USAR m_id
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
    		this->Vertex[4] = &Mesh[i+m_HW];		//(0 1 0)
    		this->Vertex[5] = &Mesh[i+1+m_HW];	//(1 1 0)
    		this->Vertex[6] = &Mesh[i+1+m_W+m_HW];	//(1 1 1)
    		this->Vertex[7] = &Mesh[i+m_W+m_HW];	//(0 1 1)
	//OBS: los centroides no estan optimiz y de momento no comparten info asi el indice no hay que procesarlo como para los vertex
	}
    
    else{std::cout<<"[ERROR] ID out of bound in OCTREE: "<< octreeLevel <<std::endl;
    	 std::cout<<"Llamando a la celda: " << m_id << "/" << m_Volume_Population<<std::endl; }
}

void octreeSHM::setHexMeshElement(structuredHexMesh& MeshUP) {

	//if octree is not already created then create one
	if(!Mesh) {

	const int c_Ysweep{2}; //values of octree for one cell

	m_Vertex_Population = (c_Ysweep+1)*m_H*m_W	* MeshUP.Total_Cell_Divided;
	m_Volume_Population = (m_H-1)*(m_W-1)*c_Ysweep	* MeshUP.Total_Cell_Divided;

	Mesh           = new vec3[m_Vertex_Population];
	Cell_Centroids = new vec3[m_Volume_Population];
	Cell_Divided   = new bool[m_Volume_Population]{false};
	Face_UNormals  = new vec3[m_Volume_Population*6]; //each cube has six normals, not using share optimiz.
	Face_Centroids = new vec3[m_Volume_Population*6];
	vTable         = new unsigned[m_Vertex_Population];

	//std::cout<<"[OCTREE] POPULATION: "<<m_Volume_Population<<std::endl;
	int this_cell_is_divided{0}, layer{0};
	for(unsigned j =0; j<MeshUP.Log_Cells_Max(); j++) {

		if(MeshUP.Cell_Divided[j]) {
		
			layer = (this_cell_is_divided++)*9*3;
			MeshUP.loadVertexId(j);

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

	else {std::cout<<"Mesh has been already created"<<std::endl;}
}

void octreeSHM::setHexMeshElement(octreeSHM& MeshUP) {

	//if octree is not already created then create one
	if(!Mesh) {

	const int c_Ysweep{2}; //values of octree for one cell

	m_Vertex_Population = (c_Ysweep+1)*m_H*m_W 		* MeshUP.Total_Cell_Divided;
	m_Volume_Population = (m_H-1)*(m_W-1)*c_Ysweep	* MeshUP.Total_Cell_Divided;

	Mesh           = new vec3[m_Vertex_Population];
	Cell_Centroids = new vec3[m_Volume_Population];
	Cell_Divided   = new bool[m_Volume_Population]{false};
	Face_UNormals  = new vec3[m_Volume_Population*6]; //each cube has six normals, not using share optimiz.
	Face_Centroids = new vec3[m_Volume_Population*6];
	vTable         = new unsigned[m_Vertex_Population];

	//std::cout<<"[OCTREE] POPULATION: "<<m_Volume_Population<<std::endl;
	int this_cell_is_divided{0}, layer{0};
	for(unsigned j =0; j<MeshUP.Log_Cells_Max(); j++) {

		if(MeshUP.Cell_Divided[j]) {
		
			layer = (this_cell_is_divided++)*9*3;
			MeshUP.loadVertexId(j);

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

	else {std::cout<<"Mesh has been already created"<<std::endl;}
}


void octreeSHM::arrayInnerCompareTwo(const int Array[], const int& sizeArray) {

	std::cout<<"ESTOY EN COMPARE"<<std::endl;

	for(int i=0; i<sizeArray; i++) {
		for(int j = i+1; j<(sizeArray-i); j++) {

			std::cout<<"Comparing: Array["<<i<<"] = "<<i<<" with Array["<<j<<"]"<<j<<std::endl;
  		}
 	}
}
