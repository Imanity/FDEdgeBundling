#include "GraphVisualization.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	GraphVisualization w;
	w.show();
	return a.exec();
}
