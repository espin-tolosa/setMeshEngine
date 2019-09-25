#ifndef WRITEVTK_H_INCLUDED
#define WRITEVTK_H_INCLUDED

#include<iostream>

#include"octreeSHM.h"

#include <vtkSmartPointer.h>
#include <vtkTetra.h>
#include <vtkCellArray.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkDataSetMapper.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPointData.h>
#include <vtkVertexGlyphFilter.h>

//RENDERING HEADERS
//#include <vtkActor.h>
//#include <vtkRenderer.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderWindowInteractor.h>

void writeVTU(const structuredHexMesh&);

#endif // WRITEVTK_H_INCLUDED

