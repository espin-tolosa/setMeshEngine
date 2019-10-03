#ifndef OCTREESHM_H_INCLUDED
#define OCTREESHM_H_INCLUDED


class octreeSHM : public structuredHexMesh
{
	private:
	unsigned* vTable;

	public:

	octreeSHM();
	~octreeSHM();

   	void loadVertexId(const unsigned& id) override;
   	void loadVertexId(const unsigned& id, int octreeLevel);
	void setHexMeshElement(structuredHexMesh& leveli);
	void setHexMeshElement(octreeSHM& leveli);
	void arrayInnerCompareTwo(const int Array[], const int& sizeArray);
	//	void setOctreeLevel1(vec3 Qt[], int Divisions);
};



#endif // OCTREESHM_H_INCLUDED
