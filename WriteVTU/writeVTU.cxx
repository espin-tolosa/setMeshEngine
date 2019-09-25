//VTK LIBRARIES
#include "writeVTU.h"

void writeVTU(const structuredHexMesh& inputMesh)
{

  std::string filename = "vtu/out.vtu";

//        for(int i=0;i<MyCube.Log_Verts();i++)
//        {
//            outFile_ofstream<<MyCube.Mesh[i]<<std::endl;
//        }

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

for(int i=0; i<inputMesh.Log_Cells_Max(); i++)
{
inputMesh.loadVertexId((unsigned) i);

  points->InsertNextPoint(Vertex[0].x, Vertex[0].y, Vertex[0].z);
  points->InsertNextPoint(Vertex[1].x, Vertex[1].y, Vertex[1].z);
  points->InsertNextPoint(Vertex[2].x, Vertex[2].y, Vertex[2].z);
  points->InsertNextPoint(Vertex[3].x, Vertex[3].y, Vertex[3].z);

  points->InsertNextPoint(Vertex[4].x, Vertex[4].y, Vertex[4].z);
  points->InsertNextPoint(Vertex[5].x, Vertex[5].y, Vertex[5].z);
  points->InsertNextPoint(Vertex[6].x, Vertex[6].y, Vertex[6].z);
  points->InsertNextPoint(Vertex[7].x, Vertex[7].y, Vertex[6].z);

//  points->InsertNextPoint(0, 0, 0);
//  points->InsertNextPoint(1, 0, 0);
//  points->InsertNextPoint(1, 1, 0);
//  points->InsertNextPoint(0, 1, 1);

//  points->InsertNextPoint(0, 0, 0);
//  points->InsertNextPoint(1, 0, 0);
//  points->InsertNextPoint(1, 1, 0);
//  points->InsertNextPoint(0, 1, 1);
}
   vtkSmartPointer<vtkCube> cube =
    vtkSmartPointer<vtkCube>::New();

  cube->GetPointIds()->SetId(0, 0);
  cube->GetPointIds()->SetId(1, 1);
  cube->GetPointIds()->SetId(2, 2);
  cube->GetPointIds()->SetId(3, 3);
  cube->GetPointIds()->SetId(4, 4);
  cube->GetPointIds()->SetId(5, 5);
  cube->GetPointIds()->SetId(6, 6);
  cube->GetPointIds()->SetId(7, 7);

  vtkSmartPointer<vtkCellArray> cellArray =
    vtkSmartPointer<vtkCellArray>::New();
  cellArray->InsertNextCell(cube);

  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  unstructuredGrid->SetPoints(points);
  unstructuredGrid->SetCells(VTK_CUBE, cellArray);

  // Write file
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName(filename.c_str());
  writer->SetInputData(unstructuredGrid);
  writer->Write();
}
