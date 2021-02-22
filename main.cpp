#include<QtWidgets/QApplication>
#include<MainWindow.h>

int main(int argv, char* argc[]) {
	QApplication app(argv, argc);

	MainWindow mainWindow;
	mainWindow.setWindowTitle("3D Transformation");
	
	mainWindow.show();
	return app.exec();
} 