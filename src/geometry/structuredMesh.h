#ifndef STRUCTUREDHEXMESH_H_INCLUDED
#define STRUCTUREDHEXMESH_H_INCLUDED

#include "vectors.h"

class structuredHexMesh
{

    unsigned int m_Vertex_Population;
    unsigned int m_Face_Population;
    unsigned int m_Volume_Population;
    unsigned int m_id;
    float m_Total_Volume;

    float m_cellVolume;

//    unsigned int m_CellID; //Id of element

    public:
    vec3* Mesh;
    vec3* Centroids;

    vec3* Vertex[8];
    vec3* Edge_i[12]; //        int id_vert[] = {0,2, 1,3, 2,5, 1,6, 5,7, 4,6, 7,0, 4,3, 0,5, 4,1, 2,7, 6,3 }
    vec3* Edge_j[12];
    vec3* Tris[3*2*6];
    vec3* Quad[4*6];

     structuredMesh();
     structuredMesh(const int &count_mesh, const int  &count_faces, const int &count_volumes);
    ~structuredMesh();

    void SweepFace(vec3* MeshSurface, int count_MeshSurface, int count_Layers, float sweepConst);



    void setElement(const int &id_e);

    void getCentroid(const int &id);
    void getCentroidC8(const int id);

    void getVertex(const int e_cell, const int &Heigth, const int &Wide);

    float AreaC3(const vec3& p1, const vec3& p2, const vec3& p3);
    float AreaC4(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3);
    vec3 CenterC3(const vec3& p1, const vec3& p2, const vec3& p3);
    vec3 CenterC4(const vec3& p1, const vec3& p2, const vec3& p3, const vec3& p4);
/**    void CentroidF2(const vec3& ci1,
                    const vec3& ci2,
                    const vec3& ci3,
                    const vec3& ci4,
                    const vec3& cj1,
                    const vec3& cj2,
                    const vec3& cj3,
                    const vec3& cj4);
**/
    vec3 CenterT4(const vec3& v0,
                  const vec3& v1,
                  const vec3& v2,
                  const vec3& v3);

    float VolumeT4(const vec3& v0,
                   const vec3& v1,
                   const vec3& v2,
                   const vec3& v3);

    void CenterC8(const vec3& v0,
                  const vec3& v1,
                  const vec3& v2,
                  const vec3& v3,
                  const vec3& v4,
                  const vec3& v5,
                  const vec3& v6,
                  const vec3& v7);

    void Log();


};



#endif // STRUCTUREDHEXMESH_H_INCLUDED
