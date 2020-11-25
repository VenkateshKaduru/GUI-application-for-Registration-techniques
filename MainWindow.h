#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<vtkGenericOpenGLRenderWindow.h>
#include<vtkRenderer.h>
#include<QVTKInteractor.h>

#include<vtkInteractorStyle.h>
#include <vtkRenderWindowInteractor.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
private:
	Ui::MainWindow *ui;
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderwindow;
	vtkSmartPointer<vtkRenderer> mRenderer;
	vtkSmartPointer<QVTKInteractor> mInteractor;
	vtkSmartPointer<vtkInteractorStyle> mInteractorStyle;

public slots:
	void onReaderClick();
	void emptyWidget();
	//vtkSmartPointer<vtkPolyData> loadVTKPolyData(const std::string& filename);
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


};

#endif // MAINWINDOW_H
