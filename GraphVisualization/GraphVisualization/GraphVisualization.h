#pragma once

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimer>

#include <QtWidgets/QMainWindow>
#include "ui_GraphVisualization.h"

#include "Graph.h"

class GraphVisualization : public QMainWindow {
	Q_OBJECT

public:
	GraphVisualization(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

public slots:
	void openGraph();
	void timeoutEvent();
	void switchFDGraphFlag();
	void switchEdgeBundlingFlag();

private:
	Ui::GraphVisualizationClass ui;
	int wnd_width = 800, wnd_height = 600, tbr_height = 34;
	int user_detail_uid = -1;
	int dragging_uid = -1;
	bool fdgraph_flag = true;
	bool edgebundling_flag = false;
	bool isAnimating = false;
	QTimer *timer;
	int animate_frame = 0;
	int max_frame = 15;

	Graph graph, target_graph;
	std::string avatar_path;
};
