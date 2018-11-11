#pragma once

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

#include <QtWidgets/QMainWindow>
#include "ui_GraphVisualization.h"

#include "Graph.h"

class GraphVisualization : public QMainWindow {
	Q_OBJECT

public:
	GraphVisualization(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *e);
	void mouseMoveEvent(QMouseEvent *e);

public slots:
	void openGraph();

private:
	Ui::GraphVisualizationClass ui;
	int wnd_width = 800, wnd_height = 600, tbr_height = 34;
	int user_detail_uid = -1;

	Graph graph;
	std::string avatar_path;
};
