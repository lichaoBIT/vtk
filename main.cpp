#include "MeshDataFunc.h"


int main()
{
	//build_read_plot3D();
	//build_read_plot3D_poly();
	polydata();
	return 0;
}

void build_read_01()
{

}

void polydata_self_defined()
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

void polydata()
{
	vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
	lut->SetNumberOfColors(256);
	lut->SetHueRange(0.1, 1);
	lut->Build();
	vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
	reader->SetFileName("D:/vtk_test_project/vtk_ex/materials/Data/honolulu3.vtk");
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

void build_read_plot3D_poly()
{
	std::vector<float> coordinates;
	int nelx = 80; int nely = 40; int nelz = 10;
	double Lx = 40.0;
	int n = nelx * nely * nelz;
	int ncoo = n * 3;
	coordinates.reserve(ncoo);
	int j = 0;
	int nele = n;
	for (int k = 0; k < nelz; k++)
	{
		for (int i = 0; i < nelx; i++)
		{
			for (j = 0; j < nely; j++)
			{
				if (i < nelx / 2 || j < nely / 2)
				{
				coordinates.push_back(i);
				coordinates.push_back(j);
				float temp;
				temp = (float(i) - Lx) * (float(i) - Lx) / 200;
				coordinates.push_back(k + temp);
				//coordinates.push_back(k);
				nele++;
			}
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
				if (i < nelx / 2 || j < nely / 2)
				{
				float tem = float(i) / float(nelx);
				value.push_back(tem);
				}
			}
		}
	}
	std::string name = "D:/vtk_test_project/vtk-top-contour/output/output_info.vtk";
	std::ofstream ofs(name, std::ios::out);
	ofs << "# vtk DataFile Version 3.0" << std::endl;
	ofs << "vtk output" << std::endl;
	ofs << "ASCII" << std::endl;
	ofs << "DATASET POLYDATA" << std::endl;
	//ofs << "DATASET POLYDATA" << std::endl;
	//ofs << "DIMENSIONS " << nelx << " " << nely << " " << nelz << std::endl;
	ofs << "POINTS " << nele << " float" << std::endl;
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
	//ofs << "CELL_DATA " << (nelx - 1) * (nely - 1) * (nelz - 1) << std::endl;
	ofs << "POINT_DATA " << nele << std::endl;
	ofs << "SCALARS Density float" << std::endl;
	ofs << "LOOKUP_TABLE default" << std::endl;
	k = 1;
	for (auto ele : value)
	{
		ofs << ele << " " << std::endl;
	}
	polydata_self_defined();
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
	int nele = n;
	for (int k = 0; k < nelz; k++)
	{
		for (int i = 0; i < nelx; i++)
		{
			for (j = 0; j < nely; j++)
			{
				/*if (i < nelx / 2 || j < nely / 2)
				{*/
					coordinates.push_back(i);
					coordinates.push_back(j);
					float temp;
					temp = (float(i) - Lx) * (float(i) - Lx) / 200;
					coordinates.push_back(k + temp);
					//coordinates.push_back(k);
					/*nele++;
				}*/
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
				/*if (i < nelx / 2 || j < nely / 2)
				{*/
					float tem = float(i) / float(nelx);
					value.push_back(tem);
				//}
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
	ofs << "POINTS " << nele << " float" << std::endl;
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
	//ofs << "CELL_DATA " << (nelx - 1) * (nely - 1) * (nelz - 1) << std::endl;
	ofs << "POINT_DATA " << nele << std::endl;
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
