//VTK LIBRARIES
#include "vtk_udef.h"

#include <iostream>
#include <vtkSmartPointer.h>
#include <vtkAppendFilter.h>
//#include <vtkTetra.h>
#include <vtkHexahedron.h>
#include <vtkPoints.h>
#include <vtkDataSet.h>
#include <vtkCellArray.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkDataSetMapper.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPointData.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkAbstractArray.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkFieldData.h>
#include <vtkMappedDataArray.h>
#include <vtkInformationVector.h>
//RENDERING HEADERS
//#include <vtkActor.h>
//#include <vtkRenderer.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderWindowInteractor.h>

void vtk_udef::writeVTU(structuredHexMesh& inputMesh)
{

  using Node 	= std::vector<double>;
  using Element	= std::vector<int>;

  std::string filename = "out.vtu";

  vtkSmartPointer<vtkPoints> 		points 			= vtkSmartPointer<vtkPoints>		::New();
  vtkSmartPointer<vtkHexahedron> 	hexaMesh		= vtkSmartPointer<vtkHexahedron>	::New();
  vtkSmartPointer<vtkCellArray> 	cellArray 		= vtkSmartPointer<vtkCellArray>		::New();
  vtkSmartPointer<vtkUnstructuredGrid> 	unstructuredGrid 	= vtkSmartPointer<vtkUnstructuredGrid>	::New();
  vtkSmartPointer<vtkPolyData> 		polydata 		= vtkSmartPointer<vtkPolyData>		::New();
  vtkSmartPointer<vtkDoubleArray> 	myField 		= vtkSmartPointer<vtkDoubleArray>	::New();
  vtkSmartPointer<vtkAppendFilter> 	appendFilter		= vtkSmartPointer<vtkAppendFilter>	::New();
  double myFieldValue[3] = {1.1,2.2,3.3}; 

 myField->SetNumberOfComponents(3);
 myField->SetName("Position");
 myField->SetNumberOfTuples((int) inputMesh.Log_Cells_Max());
// myField->SetNumberOfValues((int) inputMesh.Log_Cells_Max());

  for(int i=0; i<(int) inputMesh.Log_Verts(); i++)
  {
  	//Insert points in the order of my mesh
  	points->InsertNextPoint((inputMesh.Mesh[i].x),(inputMesh.Mesh[i].y), (inputMesh.Mesh[i].z));
  }	
	
      	//Translating to the order of VTK
  for(int j=0; j<(int) inputMesh.Log_Cells_Max(); j++)
  {
	int H = 4;
	int W = 4;
	int HW = H*W;

        int count_Cells_layer = (H-1)*(W-1);//Count elements in a layer

        int count_rows_passed = 0;              //Adds the last vertex of the row |-0-|-1-|-2-|-3-(|) <-this
        int count_layers_passed = 0;            //Adds the top row of vertex-W

        count_rows_passed = j/(W-1);
        count_layers_passed = j/count_Cells_layer;

	int i = j + count_rows_passed + count_layers_passed * W ;
	hexaMesh->GetPointIds()->SetId( 0, i);
  	hexaMesh->GetPointIds()->SetId( 1, i+1);
  	hexaMesh->GetPointIds()->SetId( 2, i+1+HW);
  	hexaMesh->GetPointIds()->SetId( 3, i+HW);
  	hexaMesh->GetPointIds()->SetId( 4, i+W);
  	hexaMesh->GetPointIds()->SetId( 5, i+1+W);
  	hexaMesh->GetPointIds()->SetId( 6, i+1+W+HW);
  	hexaMesh->GetPointIds()->SetId( 7, i+W+HW);

  	myFieldValue[0] += myFieldValue[0];
  	myFieldValue[1] += myFieldValue[1];
  	myFieldValue[2] += myFieldValue[2];
	cellArray	->InsertNextCell(hexaMesh);
	std::cout<<"insert next tuple"<<std::endl;
//	myField		->InsertNextTuple(myFieldValue);
 	myField->InsertTuple(j,myFieldValue);
  }

  //Adding the points to the grid
  unstructuredGrid->SetPoints(points);
  unstructuredGrid->SetCells(VTK_HEXAHEDRON, cellArray);
  polydata->GetFieldData()->AddArray(myField);
//  appendFilter->AddInputData(polydata->GetFieldData()->GetAbstractArray("Position"));
//  unstructuredGrid->ShallowCopy(myField->GetTuple());
		  //appendFilter->GetOutput());

  //unstructuredGrid->GetFieldData()->AddArray(myField);	
  //UunstructuredGrid->SetCells(VTK_HEXAHEDRON, myField);

  //addElementsToVTKDataSet(hexaMesh,cellArray,points,myField);
  //polydata->SetPoints(points);
  //polydata->SetCells(VTK_HEXAHEDRON, cellArray);
  //Adding polydata to array

  // Write file
  std::cout<<"Writing out.vtu"<<std::endl;
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName(filename.c_str());
  writer->SetInputData(unstructuredGrid);
  writer->SetDataModeToAscii();
  writer->Write();
}

/*AQUI TENGO ESTO SACADO DE THE PARRESIANZ PERO TODAVIA ME FALTA SABER COMPO SE IMPLEMENTAN DOS FUNCIONES
OutputVTK::writeGrid(double time, const structuredHexMesh& inputMesh, std::ostringstream& fileName)
{
	// Create a writer
	auto writer = vtkXMLUnstructuredGridWriterP::Nex();

	// Append the default extension to the file name
	fileName << "." <<writer->GetDefaultFileExtension();
	writer->SetFileName((fileNAme.str()).c_str());

	// Create a pointer to a unstructured grid data set
	auto dataSet = vtkUnstructuredGridP::New();

	//Set up pointer to point data
	auto pts = vtkSmartPointer<vtkPoins>::New();

	//Count the total number of points to be saved
	int num_pts = (int) inputMesh.Log_Cells_Max(); //user implementation
	pts->SetNumberOfPoints(num_pts);

	//Add the time
	addTimeToVTKDataSet(time, dataSet);

	//Get the nodes and elements that are used to describe the grid
	std::vector<Node>	nodes = inputMesh.getNodes(); //Implementation is user-dependent
	std::vector<Element>	elements = grid.getElements(); //Implementation is user-dependent

	//Add the processor boundaries to the unstructured grid cell data
	addElementsToVTKDataSet(nodes, elements, pts, dataSet);

	//Set the points
	dataSet->SetPoints(pts);

	//Remove unused memory
	dataSet->Squeeze();

	//Write the data
	writer->SetInput(dataSet);
	writer->SetDataModeToAscii();
	writer->Write();
}
**********************FIN*/
