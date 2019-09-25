#include <vtkXMLUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
using vtkPointsP                    = vtkSmartPointer<vtkPoints>;
using vtkUnstructuredGridP          = vtkSmartPointer<vtkUnstructuredGrid>;
using vtkHexahedronP                = vtkSmartPointer<vtkHexahedron>;
using vtkXMLUnstructuredGridWriterP = vtkSmartPointer<vtkXMLUnstructuredGridWriter>;
using Node    = std::vector<double>;
using Element = std::vector<int>;                           
void
OutputVTK::writeGrid(double time,
                     const BoxArray& grid,
                     std::ostringstream& fileName)
{
  // Create a writer
  auto writer = vtkXMLUnstructuredGridWriterP::New();
  // Append the default extension to the file name
  fileName << "." << writer->GetDefaultFileExtension();
  writer->SetFileName((fileName.str()).c_str());
  // Create a pointer to a VTK Unstructured Grid data set
  auto dataSet = vtkUnstructuredGridP::New();
  // Set up pointer to point data
  auto pts = vtkPointsP::New();
  // Count the total number of points to be saved
	int num_pts = 8;
  	//  int num_pts = grid.getNumberOfPoints(); // Implementation is user-dependent
  pts->SetNumberOfPoints(num_pts);
  // Add the time
  addTimeToVTKDataSet(time, dataSet);
  // Get the nodes and elements that are used to describe the grid
	std::vector<Node> nodes {1, 2, 3, 4, 5, 6, 7, 8}
	std::vector<Element> elements {1}
      	//std::vector<Node>    nodes = grid.getNodes();       // Implementation is user-dependent
  	//std::vector<Element> elements = grid.getElements(); // Implementation is user-dependent
  // Add the processor boundaries to the unstructured grid cell data
  addElementsToVTKDataSet(nodes, elements, pts, dataSet);
  // Set the points
  dataSet->SetPoints(pts);
  // Remove unused memory
  dataSet->Squeeze();
  // Write the data
  writer->SetInput(dataSet);
  writer->SetDataModeToAscii();
  writer->Write();
}

void
OutputVTK::addTimeToVTKDataSet(double time,
                               vtkUnstructuredGridP& dataSet)
{
  auto array = vtkDoubleArrayP::New();
  array->SetName("TIME");
  array->SetNumberOfTuples(1);
  array->SetTuple1(0, time);
  dataSet->GetFieldData()->AddArray(array);
}

void
OutputVTK::addElementsToVTKDataSet(const std::vector<Node>& nodes,
                                   const std::vector<Element>& elements,
                                   vtkPointsP& pts,
                                   vtkUnstructuredGridP& dataSet)
{
  // Set the coordinates of the nodes
  int id = 0;
  for (const auto& node : nodes) {
    pts->SetPoint(id, node[0], node[1], node[2]);
    ++id;
  }
  // Set the element connectivities
  auto hex = vtkHexahedronP::New();  // Assuming hex elements
  for (const auto& element : elements) {
    // Get node ids and assign them to a hex element (ids start from 1)
    int nodeNum = 0;
    for (const auto& id : element) {
      hex->GetPointIds()->SetId(nodeNum, id - 1);
      ++nodeNum;
    }
    dataSet->InsertNextCell(hex->GetCellType(), hex->GetPointIds());
  }
}
