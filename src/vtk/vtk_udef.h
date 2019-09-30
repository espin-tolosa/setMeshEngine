#ifndef VTK_UDEF_H_INCLUDED
#define VTK_UDEF_H_INCLUDED

#include "../geometry/structuredHexMesh.h"

class vtk_udef : public structuredHexMesh
{
	public:

	void writeVTU(structuredHexMesh& inputMesh);
};



#endif // VTK_UDEF_H_INCLUDED

