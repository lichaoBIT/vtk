#include <vtkAutoInit.h> 
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkExtractEdges.h>

#include <vtkLookupTable.h>
#include <vtkStructuredGridReader.h>
#include <vtkDelaunay2D.h>
#include <vtkObjectBase.h>
#include <vtkDataSetMapper.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkContourFilter.h>
#include <vtkProperty.h>
//stl reader
#include <vtkSTLReader.h>
//write_unstructed_grid
#include <vtkUnstructuredGrid.h>
#include <vector>
#include <windows.h>

#include <vtkPolyDataReader.h>
#include <vtkScalarBarActor.h>

typedef vtkActorCollection* vtkActorCollection_Array;

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
VTK_MODULE_INIT(vtkRenderingFreeType);

#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL2,vtkRenderingOpenGL2)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL2)