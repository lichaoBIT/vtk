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

	//����
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
	
	//����
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

	// vtkProperty ���������ɫ��͸���ȵȲ���
	vtkSmartPointer<vtkProperty> property = vtkSmartPointer<vtkProperty>::New();
	property->SetColor(0, 0, 0);

	vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
	outlineActor->SetMapper(outlineMapper);
	outlineActor->SetProperty(property);

	//����
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
	
	// vtkProperty ���������ɫ��͸���ȵȲ���
	vtkSmartPointer<vtkProperty> property = vtkSmartPointer<vtkProperty>::New();
	property->SetColor(0, 0, 0);

	vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
	outlineActor->SetMapper(outlineMapper);
	outlineActor->SetProperty(property);
	
	//����
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

	//����
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
		reader SetFileName ��Data / subset.vtk��
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
//	//������������ı���
//	cylinder->SetResolution(50);
//	vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
//	cone->SetResolution(100);
//	// ������Ⱦ����μ������ݣ�������ת��Ϊ����ͼԪ
//	vtkSmartPointer<vtkPolyDataMapper> coneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//	coneMapper->SetInputData(cylinder->GetOutput());
//	// !!!���ӻ����ߵ�����/����ӿڣ��������ö��
//	coneMapper->AddInputConnection(0, cylinder->GetOutputPort());
//	// Ҳ���Խ���������һ����SetInputConnectionֻ�����һ��������
//	coneMapper->SetInputConnection(cylinder->GetOutputPort());
//	// vtkProperty ���������ɫ��͸���ȵȲ���
//	vtkSmartPointer<vtkProperty> property = vtkSmartPointer<vtkProperty>::New();
//	property->SetColor(0.7, 0.2, 0.3);
//
//	// vtkActor ������ vtkProp ��Ⱦ���������ݵĿ��ӻ����ͨ��vtkProp���ฺ�𣬸���ȷ��λ�ã���С��
//	vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
//	coneActor->SetMapper(coneMapper);
//	coneActor->SetProperty(property);
//
//	//	//��������Ⱦ����
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
//	// RenderWindowInteractor---���𽻻�
//	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor> ::New();
//	iren->SetRenderWindow(renWin);
//	// ��������ʽ
//	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
//	iren->SetInteractorStyle(style);
//	iren->Initialize();
//	//�����¼�ѭ���������ȵ��� Initialize ��׼������
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
//	// ������vtkPolyDataAlgorithm  �����ɵ���������ΪvtkPolyData , ����
//	vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
//	cylinder->SetHeight(10);
//
//	cylinder->SetRadius(15.0);
//	// ������������ı���
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
//	// ���� phi / theta �����ϵĵ��������Ҳ�������Ϊ�ߵ�����
//	sphere->SetPhiResolution(50);
//	sphere->SetThetaResolution(50);
//
//	// ������Ⱦ����μ������ݣ�������ת��Ϊ����ͼԪ
//	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//	// ���ӻ����ߵ�����/����ӿڣ��������ö��
//	//cylinderMapper->AddInputConnection(1, cube->GetOutputPort());
//	//cylinderMapper->AddInputConnection(0, cylinder->GetOutputPort());
//	// Ҳ���Խ���������һ����SetInputConnectionֻ�����һ��������
//	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());
//	// vtkProperty ���������ɫ��͸���ȵȲ���
//	vtkSmartPointer<vtkProperty> property = vtkSmartPointer<vtkProperty>::New();
//	property->SetColor(0.7, 0.2, 0.3);
//
//
//	// vtkActor ������ vtkProp ��Ⱦ���������ݵĿ��ӻ����ͨ��vtkProp���ฺ�𣬸���ȷ��λ�ã���С��
//	vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
//	cylinderActor->SetMapper(cylinderMapper);
//	cylinderActor->SetProperty(property);
//	//��������Ⱦ����
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
//	// ���𽻻�
//	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//
//	iren->SetRenderWindow(window);
//
//	// ��������ʽ
//	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
//
//	iren->SetInteractorStyle(style);
//
//	iren->Initialize();
//	// �����¼�ѭ���������ȵ��� Initialize ��׼������
//	iren->Start();
//
//	return 0;
//
//}