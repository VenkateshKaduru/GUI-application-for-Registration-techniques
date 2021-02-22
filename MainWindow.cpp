#include "MainWindow.h"
#include "ui_MainWindow.h"
#include<qmenubar.h>
#include<qpushbutton.h>
#include<qaction.h>
#include<qmessagebox.h>
#include<qlineedit.h>
#include<qlabel.h>
#include<iostream>
#include<string>

//vtk includes
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
	
	//Declare actions
	//open file action
	QAction * open = new QAction("Open File");
	connect(open, &QAction::triggered, [=]() {
		
		vtkSmartPointer<vtkPolyDataReader> Target =
			vtkSmartPointer<vtkPolyDataReader>::New();

		vtkSmartPointer<vtkPolyDataReader> Reference =
			vtkSmartPointer<vtkPolyDataReader>::New();

		Target->SetFileName("D:/Transformation/Target_Mesh.vtk");
		Target->Update();
		Reference->SetFileName("D:/Transformation/mean.vtk");
		Reference->Update();

		vtkSmartPointer<vtkPolyData> polydata1 =
			Target->GetOutput();
		vtkSmartPointer<vtkPolyData> polydata2 =
			Reference->GetOutput();

		/*int count = 1;
		count = polydata1->GetNumberOfPoints();
		count = polydata2->GetNumberOfPoints();
		std::string val = std::to_string(count);

		ui->Start->setText(QString(val.c_str()));*/

		vtkSmartPointer<vtkTransform> transform =
			vtkSmartPointer<vtkTransform>::New();
		transform->Scale(1, 1, 1);

		/*vtkSmartPointer<vtkTransformFilter> transformFilter =
			vtkSmartPointer<vtkTransformFilter>::New();
		transformFilter->SetInputConnection(Target);
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

	});
	//save action
	QAction * save = new QAction("Save");
	connect(save, &QAction::triggered, [=]() {

	});
	//Quit action
	QAction * quitaction = new QAction("Exit");
	connect(quitaction, &QAction::triggered, [=]() {
		QMessageBox message;
		message.setMinimumSize(600,400);
		message.setWindowTitle("Message Ttile");
		message.setText("Do you want to close this application?");
		message.setIcon(QMessageBox::Question);
		message.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

		int ret = message.exec();
		if (ret == QMessageBox::Ok){
			QApplication::quit();
		} 
	});
	//Rigid action
	QAction * rigid = new QAction("Rigid Transformation");
	connect(rigid, &QAction::triggered, [=]() {
		//Rigid code
	});
	//Non-Rigid action
	QAction * nRigid = new QAction("Non-Rigid Transformation");
	connect(nRigid, &QAction::triggered, [=]() {
		//Non-Rigid code
		
	});
	//Translation
	QAction * translation = new QAction("Translation");
	connect(translation, &QAction::trigger, [=]() {
		
	});
	//Rotation
	QAction * roation = new QAction("Rotation");
	connect(roation, &QAction::trigger, [=]() {
	
	});
	//Scaling
	QAction * scaling = new QAction("Scaling");
	connect(scaling, &QAction::trigger, [=]() {

	});

	//Add menu
	//file submenu options
	QMenu * fileSubmenu = menuBar()->addMenu("File");
	fileSubmenu->addAction(open);
	fileSubmenu->addAction(save);
	fileSubmenu->addAction(quitaction);
	//Edit submenu option
	menuBar()->addMenu("Edit");
    
	//View submenu options
	menuBar()->addMenu("View");
	
	//Method submenu options
	QMenu * methodSubmenu = menuBar()->addMenu("Methods");
	methodSubmenu->addAction(translation);
	methodSubmenu->addAction(roation);
	methodSubmenu->addAction(scaling);
	methodSubmenu->addAction(rigid);
	methodSubmenu->addAction(nRigid);
	
	//Help submenu option
	menuBar()->addMenu("Help");

	//Set up renderer
	mRenderwindow->AddRenderer(mRenderer);
	mRenderwindow->SetInteractor(mInteractor);
	mInteractor->SetRenderWindow(mRenderwindow);
	ui->openGLWidget->SetRenderWindow(mRenderwindow);
	

	//UI connections
	//QObject::connect(ui->OpenFile, &QPushButton::clicked,
	//	this, &MainWindow::onReaderClick);

	/*QObject::connect(ui->Start, &QPushButton::clicked,
		this, &MainWindow::emptyWidget);*/

	/*QLabel * xAxis = new QLabel("X-axis:", this);
	xAxis->setMinimumSize(70, 50);
	xAxis->move(10, 10);

	QLineEdit * xAxislineEdit = new QLineEdit(this);
	xAxislineEdit->setMinimumSize(40, 20);
	xAxislineEdit->move(50, 10);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReaderClick() {


}
 