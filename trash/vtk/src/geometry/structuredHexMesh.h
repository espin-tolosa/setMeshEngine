#ifndef STRUCTUREDHEXMESH_H_INCLUDED
#define STRUCTUREDHEXMESH_H_INCLUDED

#include "../maths/vectors.h"

class structuredHexMesh : public vec3
{
    unsigned m_H;
    unsigned m_W;
    unsigned m_L;
    unsigned m_id;
    unsigned m_Vertex_Population;
    unsigned m_Face_Population;
    unsigned m_Volume_Population;

    long double m_Total_Volume;
    long double m_cell_Volume;

    public:

    vec3* Mesh;
    vec3* Centroids;

    vec3* Vertex[8];
    vec3* Edge_i[12]; //        int id_vert[] = {0,2, 1,3, 2,5, 1,6, 5,7, 4,6, 7,0, 4,3, 0,5, 4,1, 2,7, 6,3 }
    vec3* Edge_j[12];
    vec3* Tris[3*2*6];
    vec3* Quad[4*6];

     structuredHexMesh();
//     structuredHexMesh(const unsigned H, const unsigned W, const unsigned L, const unsigned count_mesh, const unsigned  count_faces, const unsigned count_volumes);
    ~structuredHexMesh();


    void DisplaceMesh(const vec3& offset);              //Rigid body 3Ddisplace of the mesh
    void RotateXMesh(const float &alphax);              //Rigid body X-rotation of the mesh
    void RotateYMesh(const float &alphay);              //Rigid body Y-rotation of the mesh
    void RotateZMesh(const float &alphaz);              //Rigid body Z-rotation of the mesh
//    void setHexMeshElement(vec3* )


//    void setElement(const unsigned &id_e);

//    void getCentroid(const unsigned &id);
//    void getCentroidC8(const unsigned &id);

    void getCellConnections(const unsigned &id);        //Pass global *Mesh.Vertex -> Vertex & Edge_ij

    long double AreaC3(const vec3& p1, const vec3& p2, const vec3& p3);
//    float AreaC4(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3);
    vec3 CenterC3(const vec3& p1, const vec3& p2, const vec3& p3);
    vec3 CenterC4(const vec3& p1, const vec3& p2, const vec3& p3, const vec3& p4);
//    vec3 CenterC4(const vec3& Quad);
/**    void CentroidF2(const vec3& ci1,
                    const vec3& ci2,
                    const vec3& ci3,
                    const vec3& ci4,
                    const vec3& cj1,
                    const vec3& cj2,
                    const vec3& cj3,
                    const vec3& cj4);
**/

    vec3 CenterT4(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3);

    long double VolumeT4(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3);

    void CenterC8();

    void setHexMeshElement(const vec3* vertex_data_C8); //Create a mesh manually actually conformed by one element
    void SweepFace(vec3* MeshSurface, int c_Xwide, int c_Zheight, int c_Ysweep, long double sweepValue, const vec3 &origin);
    void Log();
    unsigned Log_Cells(unsigned id);
    unsigned Log_Cells_Max();
    unsigned Log_Verts();


};



#endif // STRUCTUREDHEXMESH_H_INCLUDED
