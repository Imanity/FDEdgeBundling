#include "GraphVisualization.h"

GraphVisualization::GraphVisualization(QWidget *parent)	: QMainWindow(parent) {
	ui.setupUi(this);
}

void GraphVisualization::paintEvent(QPaintEvent *ev) {
	QPainter p(this);
	p.setPen(Qt::black);
	p.setBrush(Qt::red);
	p.drawEllipse(16, 16, 8, 8);
}
