#include "MeshDataFunc.h"


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

