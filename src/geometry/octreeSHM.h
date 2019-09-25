#ifndef OCTREESHM_H_INCLUDED
#define OCTREESHM_H_INCLUDED

#include "structuredHexMesh.h"

class octreeSHM : public structuredHexMesh
{
	public:

    	void loadVertexId(const unsigned& id) override;
	void setHexMeshElement(structuredHexMesh& leveli);
	void setHexMeshElement(octreeSHM& leveli);
	//	void setOctreeLevel1(vec3 Qt[], int Divisions);
};



#endif // OCTREESHM_H_INCLUDED
