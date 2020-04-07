#ifndef OCTREESHM_H_INCLUDED
#define OCTREESHM_H_INCLUDED


class octreeSHM : public structuredHexMesh
{
	private:
	std::vector<unsigned> vTable;

	public:

    std::vector<unsigned> Root_Cell;
    static unsigned Depth;

	octreeSHM();
    octreeSHM(unsigned UpperLevel_Divided_Cells);
	~octreeSHM();

   	void loadVertexId(const unsigned& id) override;
   	void loadVertexId(const unsigned& id, int octreeLevel);
	void setHexMeshElement(structuredHexMesh& leveli);
	void setHexMeshElement(octreeSHM& leveli);
	void arrayInnerCompareTwo(const int Array[], const int& sizeArray);
	//	void setOctreeLevel1(vec3 Qt[], int Divisions);
    static unsigned giveLowerLevelID();
};



#endif // OCTREESHM_H_INCLUDED
