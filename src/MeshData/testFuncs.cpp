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
	//���Կ���ͼ����27��С�����������һ�����������
	//x[8][3],����ÿһ��С������� 8�����x,y,zֵ
	float x[8][3] = { { 0, 0, 0 }, { 0.3, 0, 0 }, { 0.3, 0.3, 0 }, { 0, 0.3, 0 },
	{ 0, 0, 0.3 }, { 0.3, 0, 0.3 }, { 0.3, 0.3, 0.3 }, { 0, 0.3, 0.3 } };
	//�������VTK�ĵ����ֽ��͵ĸ������Ĳ�һ�����������п������ҿ�����������
	//�ҵ������ �����ģ� һ�������� ���� 6������ɣ����ǳ���Ҳ���Ǵ�������λ��С��CELL ���������Ҫ��������
	//��Ȼ������Ҳ������������������ֻ�ܻ���������ı߿򣬾Ͳ����������õ���PolyData,��Ҫ��vtkLine���������ΪCELL
	//��Ȼѡ���� ��������ɣ��ǾͲ����������棬��һ���� �������涨���8����� 0,1,2,3�ĸ�����ɣ������Դ����ơ�
	//�ر�ע����ǣ������0,1,2,3 �⼸���㣬�����Ƕ�Ӧ�� x[8][3]������ĵ�0,1,2,3����Ϊʲô�����˵��
	vtkIdType pts[6][4] = { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 0, 1, 5, 4 },
	{ 1, 2, 6, 5 }, { 2, 3, 7, 6 }, { 3, 0, 4, 7 } };
	//concrete dataset represents vertices, lines, polygons, and triangle strips��   �����ĵ�����������Ѿ��Ƚ�����ˡ�
	vtkPolyData* cube = vtkPolyData::New();
	//����������棬������˵�� ��֮������˽ṹ����Ϊ����VTK������ �����Ǳ�����ô����һ���������
	vtkCellArray* polys = vtkCellArray::New();
	//����ǹ�����ɫ������ֵ�������ﲻ���ص���ܡ�
	vtkFloatArray* scalars = vtkFloatArray::New();
	//����ͬ���ĵ�����Ϊ���������Լ�����ĵ㣬������VTK����� vtksphere,vtkcone�� source�����Ա���ѵ�ŵ�vtkPoints��
	vtkPoints* points = vtkPoints::New();
	//�����Ƕ���õĵ㣬�ŵ�points������i ����������������������ǵ�ѭ����i=8��ʼ
	//�����ĵ���������Լ�cell�����õģ�������������һ��
	for (i = 0; i < 8; i++)
	{
		points->InsertPoint(i, x[i]);
	}
	//���������˽ṹ��

		//��һ������ ��Ȼ��vtkIdType���͵ģ�����ʵ��Ҳ��һ��int�͵ģ��ĵ���Ľ��͵�һ�������� ��ĸ������ڶ����ǵ�����ݡ�
	for (i = 0; i < 6; i++)
	{
		polys->InsertNextCell(4, pts[i]);
	}
	for (i = 0; i < 8; i++)
	{
		scalars->InsertTuple1(i, i);
	}
	//�������Ϳ�ʼ��VTK��pipeline���̡�
	cube->SetPoints(points);
	cube->SetPolys(polys);
	cube->GetPointData()->SetScalars(scalars);

	//��ǰphotoshop��ʱ��һ�������壬������Χ�ٻ��ϱ߿�������о�������һЩ������
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
	//p,j,k��Ϊ������������Ĳ�ͬλ�á�
	float p = 0.0, j = 0.0, k = 0.0;
	vtkRenderer* renderer = vtkRenderer::New();
	for (p = 0.0; p < 0.9; p = p + 0.3)
	{
		for (j = 0.0; j < 0.9; j = j + 0.3)
		{
			for (k = 0.0; k < 0.9; k = k + 0.3)
			{
				vtkActor* cubeActor = vtkActor::New();
				//����ACTOR�Ĳ�ͬλ�ã�����ʾ���յ�ͼ�Ρ�
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
	//���ȥ�����style��ô��������ʱ�������������һ��ת��
	//������ϣ�����ÿ�������嵥��ת��   
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

