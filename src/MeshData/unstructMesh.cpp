#include "MeshDataFunc.h"

//display self-defined data
void polydata_self_defined()
{
	vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
	lut->SetNumberOfColors(10);
	lut->SetHueRange(0.6667, 0.0);
	lut->Build();
	vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
	//reader->SetFileName("D:/vtk_test_project/vtk_ex/materials/Data/honolulu4.vtk");
	reader->SetFileName("D:/vtk_test_project/vtk-top-contour/output/output_info.vtk");
	reader->Update();
	
	vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());
	mapper->SetLookupTable(lut);
	mapper->SetScalarRange(0, 1);

	vtkScalarBarActor* scalarBar = vtkScalarBarActor::New();
	//scalarBar->SetLookupTable(mapper->GetLookupTable());
	scalarBar->SetLookupTable(lut);
	//设置标题
	scalarBar->SetTitle("Displacement(mm)");
	//设置颜色范围的分段数目
	scalarBar->SetNumberOfLabels(10);
	
	
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	//常规
	vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren1);
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	ren1->AddActor2D(scalarBar);//??
	ren1->AddActor(actor);
	ren1->SetBackground(0.1, 0.3, 0.4);
	renWin->SetSize(500, 500);
	vtkSmartPointer<vtkInteractorStyle> style = vtkSmartPointer<vtkInteractorStyle>::New();

	////
	//vtkCamera* aCamera = vtkCamera::New();
	//aCamera->SetViewUp(0, 0, -1);//设视角位置
	////aCamera->SetViewUp(0, 0, -1);//设视角位置
	////aCamera->SetPosition(-2, -2, -2);//设观察对象位
	//aCamera->SetFocalPoint(0.5, 0.5, 0.5);//设焦点
	//aCamera->Zoom(0.2);
	//aCamera->ComputeViewPlaneNormal();//自动
	//ren1->SetActiveCamera(aCamera);

	renWin->Render();//一闪而过，无法交互
	Sleep(2000);
	//iren->Initialize();
	////iren->ProcessEvents();
	//iren->Start();
}

//display demo data
void polydata()
{
	vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
	lut->SetNumberOfColors(256);
	lut->SetHueRange(0.1, 1);
	lut->Build();
	vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
	reader->SetFileName("D:/vtk_test_project/vtk_ex/materials/Data/honolulu.vtk");
	//reader->SetFileName("D:/vtk_test_project/vtk-top-contour/output/output_info.vtk");
	reader->Update();

	vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());
	mapper->SetLookupTable(lut);
	mapper->SetScalarRange(0.1, 1);
	//eval mapper SetScalarRange [[reader GetOutput]GetScalarRange];
	//mapper->SetScalarRange(reader->GetOutput()->GetScalarRange());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	//常规
	vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren1);
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	ren1->AddActor(actor);
	ren1->SetBackground(1, 1, 1);
	renWin->SetSize(500, 500);
	vtkSmartPointer<vtkInteractorStyle> style = vtkSmartPointer<vtkInteractorStyle>::New();
	renWin->Render();//一闪而过，无法交互
	iren->Initialize();
	//iren->ProcessEvents();
	iren->Start();
}