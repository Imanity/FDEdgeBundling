#pragma once

#include <QPainter>
#include <QPaintEvent>

#include <QtWidgets/QMainWindow>
#include "ui_GraphVisualization.h"

class GraphVisualization : public QMainWindow {
	Q_OBJECT

public:
	GraphVisualization(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *ev);

private:
	Ui::GraphVisualizationClass ui;
};
