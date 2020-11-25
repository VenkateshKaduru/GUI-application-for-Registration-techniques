#include "MainWindow.h"
#include "ui_MainWindow.h"
#include<iostream>
#include<string>

//#include <vtkSphereSource.h>
#include<vtkConeSource.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include<vtkPolyDataReader.h>
#include<vtkPolyData.h>
#include<vtkPointData.h>
#include <vtkGenericDataObjectReader.h>
#include<vtkSTLReader.h>
#include <vtkStructuredPointsReader.h>
#include <vtkRenderWindowInteractor.h>
#include<vtkCamera.h>
#include<vtkProp.h>
#include<vtkTransform.h>
#include<vtkTransformFilter.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	mRenderwindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
	mRenderer(vtkSmartPointer<vtkRenderer>::New()),
	mInteractor(vtkSmartPointer<QVTKInteractor>::New()),
	mInteractorStyle(vtkSmartPointer<vtkInteractorStyle>::New())

{
    ui->setupUi(this);

	//Set up renderer
	mRenderwindow->AddRenderer(mRenderer);
	mRenderwindow->SetInteractor(mInteractor);
	mInteractor->SetRenderWindow(mRenderwindow);
	ui->openGLWidget->SetRenderWindow(mRenderwindow);
	//mInteractor->SetInteractorStyle(mInteractorStyle);
	//mInteractor->Initialize();

	// set backgroud
	//mRenderer->SetBackground(0.5,0.5,0.5);

	//UI connections
	QObject::connect(ui->OpenFile, &QPushButton::clicked,
		this, &MainWindow::onReaderClick);

	QObject::connect(ui->Start, &QPushButton::clicked,
		this, &MainWindow::emptyWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReaderClick() {
	
	/*vtkSmartPointer<vtkGenericDataObjectReader> reader1 =
		vtkSmartPointer<vtkGenericDataObjectReader>::New();*/
	vtkSmartPointer<vtkGenericDataObjectReader> Target =
		vtkSmartPointer<vtkGenericDataObjectReader>::New(); 

	vtkSmartPointer<vtkGenericDataObjectReader> Reference =
		vtkSmartPointer<vtkGenericDataObjectReader>::New();

	Target->SetFileName("D:/Transformation/Target_Mesh.vtk");
	Target->Update();
	Reference->SetFileName("D:/Transformation/mean.vtk");
	Reference->Update();
	vtkSmartPointer<vtkPolyData> polydata1 = 
		Target->GetPolyDataOutput();
	vtkSmartPointer<vtkPolyData> polydata2 =
		Reference->GetPolyDataOutput();

	int count = 1;
	count = polydata1->GetNumberOfPoints();
	count = polydata2->GetNumberOfPoints();
	std::string val = std::to_string(count);

	ui->Start->setText(QString(val.c_str()));

	vtkSmartPointer<vtkTransform> transform =
		vtkSmartPointer<vtkTransform>::New();
	transform->Scale(1, 1, 1);

	/*vtkSmartPointer<vtkTransformFilter> transformFilter =
		vtkSmartPointer<vtkTransformFilter>::New();
	transformFilter->SetInputData(Target);
	transformFilter->SetTransform(transform);
	transformFilter->Update();
*/

	vtkSmartPointer<vtkPolyDataMapper> mapper1 =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper1->SetInputData(polydata1);
	
	vtkSmartPointer<vtkPolyDataMapper> mapper2 =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper2->SetInputData(polydata2);

	vtkSmartPointer<vtkActor> actor1 =
		vtkSmartPointer<vtkActor>::New();
	actor1->SetMapper(mapper1);

	vtkSmartPointer<vtkActor> actor2 =
		vtkSmartPointer<vtkActor>::New();
	actor2->SetMapper(mapper2);

	vtkSmartPointer<vtkCamera> camera =
		vtkSmartPointer<vtkCamera>::New();
	//camera->SetPosition(0, 0, 1);
	//camera->SetFocalPoint(0, 0, 0);

	mRenderer->AddActor(actor1);
	mRenderer->AddActor(actor2);
	mRenderer->SetActiveCamera(camera);
	//mRenderer->ResetCamera();
	mRenderer->GetRenderWindow()->Render();

	
}
void MainWindow::emptyWidget() {
	
}