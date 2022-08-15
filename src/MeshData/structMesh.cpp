#include "MeshDataFunc.h"


void colormap_3d()
{
	vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
	lut->SetNumberOfColors(256);
	lut->SetHueRange(0.1, 1);
	lut->Build();

	vtkSmartPointer<vtkStructuredGridReader> reader = vtkSmartPointer<vtkStructuredGridReader>::New();
	//reader->SetFileName("D:/vtk_test_project/vtk_ex/materials/Data/density.vtk");
	reader->SetFileName("D:/vtk_test_project/vtk-top-contour/output/output_info.vtk");
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
	/*std::cout << "aa" << std::endl;
	Sleep(3000); */
	//iren->Initialize();
	//iren->ProcessEvents();

	/*iren->CreateOneShotTimer(3000);*/
	//iren->Start();
	//iren->Start();

	//// can not interaction
	//renWin->Start();
	//Sleep(3000);
	//renWin->Finalize();

	//Sleep(3000);

}

void colormap_scalerangle()
{
	vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
	lut->SetNumberOfColors(256);
	lut->SetHueRange(0, 1);
	//lut->SetHueRange(0.0, 1.0);
	lut->Build();

	vtkSmartPointer<vtkStructuredGridReader> reader = vtkSmartPointer<vtkStructuredGridReader>::New();
	//reader->SetFileName("D:/vtk_test_project/vtk_ex/materials/Data/subset_remove_vec.vtk");
	reader->SetFileName("D:/vtk_test_project/vtk-top-contour/output/output_info.vtk");
	reader->Update();

	vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());
	mapper->SetLookupTable(lut);
	mapper->SetScalarRange(0, 1.0);

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	//常规
	vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren1);
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	ren1->AddActor(actor);
	ren1->SetBackground(0.1, 0.2, 0.4);
	renWin->SetSize(500, 500);

	renWin->Render();
	iren->Initialize();
	iren->Start();
}

void plot_contour_multi()
{
	vtkSmartPointer<vtkStructuredGridReader> reader = vtkSmartPointer<vtkStructuredGridReader>::New();
	reader->SetFileName("D:/vtk_test_project/vtk_ex/materials/Data/subset.vtk");
	reader->Update();

	vtkSmartPointer<vtkContourFilter> contour = vtkSmartPointer<vtkContourFilter>::New();
	contour->SetInputConnection(reader->GetOutputPort());
	//contour->SetValue(0, .26); single
	//contour GenerateValues 10 [[reader GetOutput] GetScalarRange]
	contour->GenerateValues(10, 0, .40);

	vtkSmartPointer<vtkPolyDataMapper> contourMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputConnection(contour->GetOutputPort());
	contourMapper->SetScalarRange(0, 10);//?

	vtkSmartPointer<vtkActor> contourActor = vtkSmartPointer<vtkActor>::New();
	contourActor->SetMapper(contourMapper);

	vtkSmartPointer<vtkStructuredGridOutlineFilter> outline = vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
	outline->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> outlineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	outlineMapper->SetInputConnection(outline->GetOutputPort());

	// vtkProperty 负责控制颜色，透明度等参数
	vtkSmartPointer<vtkProperty> property = vtkSmartPointer<vtkProperty>::New();
	property->SetColor(0, 0, 0);

	vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
	outlineActor->SetMapper(outlineMapper);
	outlineActor->SetProperty(property);

	//常规
	vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren1);
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	ren1->AddActor(outlineActor);
	ren1->AddActor(contourActor);
	ren1->SetBackground(1, 1, 1);
	renWin->SetSize(500, 500);

	renWin->Render();
	iren->Initialize();
	iren->Start();
}

void plot_contour_single()
{
	/*vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
	lut->SetNumberOfColors(256);
	lut->SetHueRange(0.667, 0.0);
	lut->Build();*/

	vtkSmartPointer<vtkStructuredGridReader> reader = vtkSmartPointer<vtkStructuredGridReader>::New();
	reader->SetFileName("D:/vtk_test_project/vtk_ex/materials/Data/subset.vtk");
	reader->Update();

	vtkSmartPointer<vtkContourFilter> contour = vtkSmartPointer<vtkContourFilter>::New();
	contour->SetInputConnection(reader->GetOutputPort());
	contour->SetValue(0, .26);

	vtkSmartPointer<vtkPolyDataMapper> contourMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputConnection(contour->GetOutputPort());
	contourMapper->SetScalarRange(0, 10);//?

	vtkSmartPointer<vtkActor> contourActor = vtkSmartPointer<vtkActor>::New();
	contourActor->SetMapper(contourMapper);

	vtkSmartPointer<vtkStructuredGridOutlineFilter> outline = vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
	outline->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> outlineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	outlineMapper->SetInputConnection(outline->GetOutputPort());

	// vtkProperty 负责控制颜色，透明度等参数
	vtkSmartPointer<vtkProperty> property = vtkSmartPointer<vtkProperty>::New();
	property->SetColor(0, 0, 0);

	vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
	outlineActor->SetMapper(outlineMapper);
	outlineActor->SetProperty(property);

	//常规
	vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren1);
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	ren1->AddActor(outlineActor);
	ren1->AddActor(contourActor);
	ren1->SetBackground(1, 1, 1);
	renWin->SetSize(500, 500);

	renWin->Render();
	iren->Initialize();
	iren->Start();
}

void display_obj()
{

	//vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
	//tableColor = vtkLookupTable.New();
	vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
	lut->SetNumberOfColors(256);
	//lut->SetHueRange(0.0, 0.667);
	lut->SetHueRange(0.667, 0.0);
	lut->Build();

	vtkSmartPointer<vtkStructuredGridReader> reader = vtkSmartPointer<vtkStructuredGridReader>::New();
	//reader->SetFileName("D:/vtk_test_project/vtk_ex/materials/Data/subset.vtk");
	reader->SetFileName("D:/vtk_test_project/vtk-top-contour/output/output_info.vtk");
	reader->Update();
	vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());
	mapper->SetLookupTable(lut);
	mapper->SetScalarRange(0, 10);//?

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkStructuredGridOutlineFilter> outline = vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
	outline->SetInputConnection(reader->GetOutputPort());
	vtkSmartPointer<vtkPolyDataMapper> outlineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	outlineMapper->SetInputConnection(outline->GetOutputPort());
	vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
	outlineActor->SetMapper(outlineMapper);

	//常规
	vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren1);
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	ren1->AddActor(outlineActor);
	ren1->AddActor(actor);
	ren1->SetBackground(0.5, 0.5, 0.5);
	renWin->SetSize(500, 500);

	//iren->AddObserver(UserEvent->deiconify.vtkInteract);
	renWin->Render();
	iren->Initialize();
	iren->Start();

}