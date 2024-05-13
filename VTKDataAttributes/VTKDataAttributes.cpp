#include "VTKDataAttributes.h"

#include <vtkPlaneSource.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkPolyData.h>
#include <vtkUnsignedCharArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>


VTKDataAttributes::VTKDataAttributes(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	_pVTKWidget = new QVTKOpenGLNativeWidget();
	this->setCentralWidget(_pVTKWidget);

	vtkNew<vtkRenderer> renderer;
	this->_pVTKWidget->renderWindow()->AddRenderer(renderer);
	this->_pVTKWidget->renderWindow()->Render();

	vtkNew<vtkPlaneSource> plane;
	int resolutionX = 5, resolutionY = 3;
	plane->SetXResolution(resolutionX);
	plane->SetYResolution(resolutionY);
	plane->Update();

	vtkPolyData* cellPoly = plane->GetOutput();
	// poly->Print(std::cout);
	vtkNew<vtkUnsignedCharArray> cellData;
	cellData->SetNumberOfComponents(3);
	cellData->SetNumberOfTuples(cellPoly->GetNumberOfCells());
	double rgb[][3] = { {255, 0, 0}, {0, 255, 0}, {0, 0, 255} }; // ºì¡¢ÂÌ¡¢À¶
	for (size_t i = 0; i < cellPoly->GetNumberOfCells(); i++)
		cellData->InsertTuple(i, rgb[i % 3]);
	cellPoly->GetCellData()->SetScalars(cellData);

	vtkNew<vtkPolyData> pointPoly;
	pointPoly->DeepCopy(cellPoly);
	vtkNew<vtkUnsignedCharArray> pointData;
	pointData->SetNumberOfComponents(3);
	pointData->SetNumberOfTuples(pointPoly->GetNumberOfPoints());
	for (size_t i = 0; i < pointPoly->GetNumberOfPoints(); i++)
		pointData->InsertTuple(i, rgb[i % 3]);
	pointPoly->GetPointData()->SetScalars(pointData);

	vtkNew<vtkPolyDataMapper> cellMapper;
	cellMapper->SetInputData(cellPoly);
	vtkNew<vtkPolyDataMapper> pointMapper;
	pointMapper->SetInputData(pointPoly);

	vtkNew<vtkActor> cellActor;
	cellActor->SetMapper(cellMapper);
	vtkNew<vtkActor> pointActor;
	pointActor->SetMapper(pointMapper);
	pointActor->SetPosition(2, 0, 0);

	renderer->AddActor(cellActor);
	renderer->AddActor(pointActor);
}

VTKDataAttributes::~VTKDataAttributes()
{}
