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
typedef vtkActorCollection* vtkActorCollection_Array;

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
VTK_MODULE_INIT(vtkRenderingFreeType);


#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL2,vtkRenderingOpenGL2)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL2)


void ex01();
void display_obj();
void ex03();
//void ex04_triangle();
void plot_contour_single();
void plot_contour_multi();
void colormap_scalerangle();
void colormap_3d();
void read_stl();
void build_read_plot();
void build_read_plot3D();
int main()
{
	build_read_plot3D();
	return 0;
}

void build_read_plot3D()
{
	std::vector<float> coordinates;
	int nelx = 80; int nely = 40; int nelz = 10;
	double Lx = 40.0;
	int n = nelx * nely * nelz;
	int ncoo = n * 3;
	coordinates.reserve(ncoo);
	int j = 0;
	for (int k = 0; k < nelz; k++)
	{
		for (int i = 0; i < nelx; i++)
		{
			for (j = 0; j < nely; j++)
			{
				coordinates.push_back(i);
				coordinates.push_back(j);
				float temp;
				temp = (float(i) - Lx) * (float(i) - Lx) / 200;
				coordinates.push_back(k + temp);
				//coordinates.push_back(k);
			}
		}
	}
	
	std::vector<float> value;
	value.reserve(n);
	for (int k = 0; k < nelz; k++)
	{
		for (int i = 0; i < nelx; i++)
		{
			for (int j = 0; j < nely; j++)
			{
				float tem = float(i) / float(nelx);
				value.push_back(tem);
			}
		}
	}
	std::string name = "D:/vtk_test_project/vtk-top-contour/output/output_info.vtk";
	std::ofstream ofs(name, std::ios::out);
	ofs << "# vtk DataFile Version 3.0" << std::endl;
	ofs << "vtk output" << std::endl;
	ofs << "ASCII" << std::endl;
	ofs << "DATASET STRUCTURED_GRID" << std::endl;
	//ofs << "DATASET POLYDATA" << std::endl;
	ofs << "DIMENSIONS " << nelx << " " << nely << " " << nelz << std::endl;
	ofs << "POINTS " << n << " float" << std::endl;
	int k = 1;
	for (auto ele : coordinates)
	{
		ofs << ele << " ";
		if (k / 3 == 1)
		{
			ofs << std::endl;
			k = 0;
		}
		k++;
	}
	ofs << std::endl;
	/*ofs << "CELL_DATA 21" << std::endl;
	ofs << "POINT_DATA 32" << std::endl;*/
	ofs << "CELL_DATA " << (nelx - 1) * (nely - 1) * (nelz - 1) << std::endl;
	ofs << "POINT_DATA " << n << std::endl;
	ofs << "SCALARS Density float" << std::endl;
	ofs << "LOOKUP_TABLE default" << std::endl;
	k = 1;
	for (auto ele : value)
	{
		ofs << ele << " " << std::endl;
	}
	colormap_3d();
}


void build_read_plot()
{
	std::vector<float> coordinates;
	int nelx = 80; int nely = 40;
	double Lx = 40.0;
	int n = nelx * nely;
	int ncoo = n * 3;
	coordinates.reserve(ncoo);
	int j = 0;
	for (int i = 0; i < nelx; i++)
	{
		for (j = 0; j < nely; j++)
		{
			coordinates.push_back(i);
			coordinates.push_back(j);
			float temp;
			temp = (float(i) - Lx) * (float(i) - Lx) / 200;
			coordinates.push_back(temp);

		}
	}
	std::vector<float> value;
	value.reserve(n);
	for (int i = 0; i < nelx; i++)
	{
		for (int j = 0; j < nely; j++)
		{
			float tem = float(i) / float(nelx);
			value.push_back(tem);
		}
	}

	std::string name = "D:/vtk_test_project/vtk-top-contour/output/output_info.vtk";
	std::ofstream ofs(name, std::ios::out);
	ofs << "# vtk DataFile Version 3.0" << std::endl;
	ofs << "vtk output" << std::endl;
	ofs << "ASCII" << std::endl;
	ofs << "DATASET STRUCTURED_GRID" << std::endl;
	//ofs << "DATASET POLYDATA" << std::endl;
	ofs << "DIMENSIONS " << nelx << " " << nely << " 1" << std::endl;
	ofs << "POINTS " << n << " float" << std::endl;
	int k = 1;
	for (auto ele : coordinates)
	{
		ofs << ele << " ";
		if (k / 3 == 1)
		{
			ofs << std::endl;
			k = 0;
		}
		k++;
	}
	ofs << std::endl;
	/*ofs << "CELL_DATA 21" << std::endl;
	ofs << "POINT_DATA 32" << std::endl;*/
	ofs << "CELL_DATA " << (nelx - 1) * (nely - 1) << std::endl;
	ofs << "POINT_DATA " << n << std::endl;
	ofs << "SCALARS Density float" << std::endl;
	ofs << "LOOKUP_TABLE default" << std::endl;
	k = 1;
	for (auto ele : value)
	{
		ofs << ele << " " << std::endl;
	}
	//display_obj();
	//colormap_scalerangle();
	colormap_3d();
}

void ex03()
{

		int i;
		//可以看到图中有27个小正方体组成了一个大的正方体
		//x[8][3],就是每一个小正方体的 8个点的x,y,z值
		float x[8][3] = { { 0, 0, 0 }, { 0.3, 0, 0 }, { 0.3, 0.3, 0 }, { 0, 0.3, 0 },
		{ 0, 0, 0.3 }, { 0.3, 0, 0.3 }, { 0.3, 0.3, 0.3 }, { 0, 0.3, 0.3 } };
		//这个查阅VTK文档发现解释的跟我理解的不一样。。。很有可能是我看不懂。。。
		//我的理解是 这样的， 一个正方体 是由 6个面组成，我们程序也正是打算以面位最小的CELL 来组成我们要的正方体
		//当然，我们也可以用线来画，那样只能画出正方体的边框，就不能用下面用到的PolyData,而要用vtkLine这个对象作为CELL
		//既然选定了 由面来组成，那就产生了六个面，第一个面 是由上面定义的8个点的 0,1,2,3四个点组成，以下以此类推。
		//特别注意的是，这里的0,1,2,3 这几个点，并不是对应的 x[8][3]，这里的第0,1,2,3具体为什么下面会说。
		vtkIdType pts[6][4] = { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 0, 1, 5, 4 },
		{ 1, 2, 6, 5 }, { 2, 3, 7, 6 }, { 3, 0, 4, 7 } };
		//concrete dataset represents vertices, lines, polygons, and triangle strips，   这是文档里的描述，已经比较清楚了。
		vtkPolyData* cube = vtkPolyData::New();
		//这个用来保存，我们所说的 点之间的拓扑结构，因为根据VTK的流程 ，我们必须这么做，一步步打包。
		vtkCellArray* polys = vtkCellArray::New();
		//这个是关于颜色的属性值，在这里不做重点介绍。
		vtkFloatArray* scalars = vtkFloatArray::New();
		//还是同样的道理，因为我们是用自己定义的点，不是用VTK里面的 vtksphere,vtkcone等 source，所以必须把点放到vtkPoints里
		vtkPoints* points = vtkPoints::New();
		//把我们定义好的点，放到points里，这里的i 才是真正的索引，如果我们的循环从i=8开始
		//真正的点的索引，以及cell中引用的，将会跟这个索引一致
		for (i = 0; i < 8; i++)
		{
			points->InsertPoint(i, x[i]);
		}
		//插入点的拓扑结构，

			//第一个参数 虽然是vtkIdType类型的，但事实上也是一个int型的，文档里的解释第一个参数是 点的个数，第二个是点的内容。
		for (i = 0; i < 6; i++)
		{
			polys->InsertNextCell(4, pts[i]);
		}
		for (i = 0; i < 8; i++)
		{
			scalars->InsertTuple1(i, i);
		}
		//接下来就开始了VTK的pipeline流程。
		cube->SetPoints(points);
		cube->SetPolys(polys);
		cube->GetPointData()->SetScalars(scalars);

		//以前photoshop的时候画一个立方体，会在周围再画上边框，这样会感觉更饱满一些。。。
		vtkExtractEdges* extract = vtkExtractEdges::New();
		extract->SetInputData(cube);
		vtkPolyDataMapper* mapEdges = vtkPolyDataMapper::New();
		mapEdges->SetInputConnection(extract->GetOutputPort());
		mapEdges->SetScalarVisibility(0);
		vtkActor* edgeActor = vtkActor::New();
		edgeActor->SetMapper(mapEdges);
		edgeActor->VisibilityOn();


		vtkPolyDataMapper* cubeMapper = vtkPolyDataMapper::New();
		cubeMapper->SetInputData(cube);
		cubeMapper->SetScalarRange(0, 7);
		int No = 0;
		//p,j,k是为了设置立方体的不同位置。
		float p = 0.0, j = 0.0, k = 0.0;
		vtkRenderer* renderer = vtkRenderer::New();
		for (p = 0.0; p < 0.9; p = p + 0.3)
		{
			for (j = 0.0; j < 0.9; j = j + 0.3)
			{
				for (k = 0.0; k < 0.9; k = k + 0.3)
				{
					vtkActor* cubeActor = vtkActor::New();
					//设置ACTOR的不同位置，来显示最终的图形。
					cubeActor->SetPosition(p, j, k);
					vtkActor* tempactor = vtkActor::New();
					cubeActor->SetMapper(cubeMapper);
					renderer->AddActor(cubeActor);
				}
			}
		}

		vtkCamera* camera = vtkCamera::New();
		camera->SetPosition(1, 1, 1);
		camera->SetFocalPoint(0, 0, 0);


		vtkRenderWindow* reWin = vtkRenderWindow::New();
		reWin->AddRenderer(renderer);

		vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();
		iren->SetRenderWindow(reWin);
		//如果去掉这个style那么，交互的时候，整个立方体会一起转动
		//如果加上，则是每个立方体单独转动   
		//vtkInteractorStyleTrackballActor *style = vtkInteractorStyleTrackballActor::New();
		//iren->SetInteractorStyle(style);

		renderer->SetActiveCamera(camera);
		renderer->ResetCamera();
		renderer->SetBackground(0, 1, 1);

		reWin->SetSize(300, 300);

		reWin->Render();
		iren->Initialize();
		iren->Start();

		points->Delete();
		cube->Delete();
		cubeMapper->Delete();
		renderer->Delete();
		reWin->Delete();
		iren->Delete();
		polys->Delete();
		scalars->Delete();
}


void read_stl()
{
	std::string inputFilename = "D:/vtk_test_project/vtk_ex/3D_bracket_DES.STL";

	vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName(inputFilename.c_str());
	reader->Update();

	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderer->AddActor(actor);
	renderer->SetBackground(.3, .6, .3);
	renderWindow->SetSize(640, 480);

	renderWindow->Render();
	renderWindowInteractor->Start();
}

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

	renWin->Render();
	/*iren->Initialize();
	iren->Start();*/

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

	/*vtkLookupTable lut
		lut SetNumberofColors 16
		lut SetHueRange 0.0 0.667
		lut Build

		vtkStructuredGridReader reader
		reader SetFileName “Data / subset.vtk”
		reader Update

		vtkDataSetMapper mapper
		mapper SetInputConnection[reader GetOutputPort]
		mapper SetLookupTable lut
		eval mapper SetScalarRange [[reader GetOutput]GetScalarRange]

		vtkActor actors
		actor SetMapper mapper*/

}

void ex01()
{
//	// vtkActor -- 3D object
//	vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
//	cylinder->SetHeight(10);
//	cylinder->SetRadius(15.0);
//	//设置柱体横截面的边数
//	cylinder->SetResolution(50);
//	vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
//	cone->SetResolution(100);
//	// 用于渲染多边形几何数据，将数据转化为几何图元
//	vtkSmartPointer<vtkPolyDataMapper> coneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//	coneMapper->SetInputData(cylinder->GetOutput());
//	// !!!可视化管线的输入/输出接口，可以设置多个
//	coneMapper->AddInputConnection(0, cylinder->GetOutputPort());
//	// 也可以仅设置设置一个，SetInputConnection只有最后一个起作用
//	coneMapper->SetInputConnection(cylinder->GetOutputPort());
//	// vtkProperty 负责控制颜色，透明度等参数
//	vtkSmartPointer<vtkProperty> property = vtkSmartPointer<vtkProperty>::New();
//	property->SetColor(0.7, 0.2, 0.3);
//
//	// vtkActor 派生自 vtkProp 渲染场景中数据的可视化表达通过vtkProp子类负责，负责确定位置，大小等
//	vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
//	coneActor->SetMapper(coneMapper);
//	coneActor->SetProperty(property);
//
//	//	//管理场景渲染过程
////	vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
//	vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
//	//ren1->AddActor(actor);
//	ren1->SetBackground(0.1, 0.2, 0.4);
//	ren1->AddActor(coneActor);
//	// Window
//	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
//	renWin->AddRenderer(ren1);
//	renWin->SetSize(500, 500);
//
//	// RenderWindowInteractor---负责交互
//	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor> ::New();
//	iren->SetRenderWindow(renWin);
//	// 交互器样式
//	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
//	iren->SetInteractorStyle(style);
//	iren->Initialize();
//	//进入事件循环，必须先调用 Initialize 做准备工作
//	iren->Start();
//	//wm withdraw
}


//int main(int argc, char* argv[])
//{
//	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
//	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
//	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
//	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//
//	double rangeX[2] = { -1.0, 1.0 };
//	double rangeY[2] = { -1.0, 1.0 };
//	double intervalX = 0.02, intervalY = 0.05;
//
//	// Y lines
//	for (double gridX = rangeX[0]; gridX < rangeX[1] + (intervalX / 2.0); gridX += intervalX)
//	{
//		double lineStart[3] = { gridX, rangeY[0], 0.0 };
//		double lineEnd[3] = { gridX, rangeY[1], 0.0 };
//
//		vtkIdType pointIdStart = points->InsertNextPoint(lineStart);
//		vtkIdType pointIdEnd = points->InsertNextPoint(lineEnd);
//
//		vtkIdType singleLineCell[2] = { pointIdStart, pointIdEnd };
//		cells->InsertNextCell(2, singleLineCell);
//	}
//
//	// x lines
//	for (double gridY = rangeY[0]; gridY < rangeY[1] + (intervalY / 2.0); gridY += intervalY)
//	{
//		double lineStart[3] = { rangeX[0], gridY, 0.0 };
//		double lineEnd[3] = { rangeX[1], gridY, 0.0 };
//
//		vtkIdType pointIdStart = points->InsertNextPoint(lineStart);
//		vtkIdType pointIdEnd = points->InsertNextPoint(lineEnd);
//
//		vtkIdType singleLineCell[2] = { pointIdStart, pointIdEnd };
//		cells->InsertNextCell(2, singleLineCell);
//	}
//
//	polydata->SetLines(cells);
//	polydata->SetPoints(points);
//	mapper->SetInputData(polydata);
//
//	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//	actor->SetMapper(mapper);
//
//	// Renderer
//	vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
//	ren1->AddActor(actor);
//	ren1->SetBackground(0.1, 0.2, 0.4);
//
//	// RenderWindow
//	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
//	renWin->AddRenderer(ren1);
//	renWin->SetSize(300, 300);
//
//	// RenderWindowInteractor
//	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor> ::New();
//	iren->SetRenderWindow(renWin);
//	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
//	iren->SetInteractorStyle(style);
//
//	renWin->SetSize(600, 600);
//	renWin->Render();
//	iren->Start();
//
//	return 0;
//}

//int main()
//{
//	// 派生自vtkPolyDataAlgorithm  其生成的数据类型为vtkPolyData , 柱体
//	vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
//	cylinder->SetHeight(10);
//
//	cylinder->SetRadius(15.0);
//	// 设置柱体横截面的边数
//	cylinder->SetResolution(50);
//	// cube
//	vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
//	cube->SetCenter(10, 10, 10);
//	cube->SetXLength(15);
//	cube->SetYLength(15);
//	cube->SetZLength(15);
//	// sphere 
//	vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
//	sphere->SetCenter(100, 200, 300);
//	sphere->SetRadius(15);
//	// 设置 phi / theta 方向上的点的数量，也可以理解为边的数量
//	sphere->SetPhiResolution(50);
//	sphere->SetThetaResolution(50);
//
//	// 用于渲染多边形几何数据，将数据转化为几何图元
//	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//	// 可视化管线的输入/输出接口，可以设置多个
//	//cylinderMapper->AddInputConnection(1, cube->GetOutputPort());
//	//cylinderMapper->AddInputConnection(0, cylinder->GetOutputPort());
//	// 也可以仅设置设置一个，SetInputConnection只有最后一个起作用
//	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());
//	// vtkProperty 负责控制颜色，透明度等参数
//	vtkSmartPointer<vtkProperty> property = vtkSmartPointer<vtkProperty>::New();
//	property->SetColor(0.7, 0.2, 0.3);
//
//
//	// vtkActor 派生自 vtkProp 渲染场景中数据的可视化表达通过vtkProp子类负责，负责确定位置，大小等
//	vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
//	cylinderActor->SetMapper(cylinderMapper);
//	cylinderActor->SetProperty(property);
//	//管理场景渲染过程
//	vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
//
//	render->AddActor(cylinderActor);
//	render->SetBackground(0.1, 0.2, 0.4);
//
//
//
//
//	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
//	window->AddRenderer(render);
//	window->SetSize(400, 600);
//	// 负责交互
//	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//
//	iren->SetRenderWindow(window);
//
//	// 交互器样式
//	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
//
//	iren->SetInteractorStyle(style);
//
//	iren->Initialize();
//	// 进入事件循环，必须先调用 Initialize 做准备工作
//	iren->Start();
//
//	return 0;
//
//}