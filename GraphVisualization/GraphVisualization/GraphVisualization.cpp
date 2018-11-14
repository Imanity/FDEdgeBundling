#include "GraphVisualization.h"

#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <opencv2/opencv.hpp>

GraphVisualization::GraphVisualization(QWidget *parent)	: QMainWindow(parent) {
	ui.setupUi(this);

	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(timeoutEvent()));
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openGraph()));
	connect(ui.actionFDGraph, SIGNAL(triggered()), this, SLOT(switchFDGraphFlag()));
	connect(ui.actionEdgeBundling, SIGNAL(triggered()), this, SLOT(switchEdgeBundlingFlag()));
}

void GraphVisualization::paintEvent(QPaintEvent *e) {
	QPainter p(this);
	p.setPen(QColor("#4169E1"));
	p.setBrush(QColor("#9400D3"));

	if (edgebundling_flag) {
		for (int i = 0; i < graph.edges.size(); ++i) {
			if (graph.subdivision_points.size() <= i || graph.subdivision_points[i].size() <= 1)
				break;
			for (int j = 0; j < graph.subdivision_points[i].size() - 1; ++j) {
				p.drawLine(graph.subdivision_points[i][j].x, tbr_height + graph.subdivision_points[i][j].y,
					graph.subdivision_points[i][j + 1].x, tbr_height + graph.subdivision_points[i][j + 1].y);
			}
		}
	} else {
		for (int i = 0; i < graph.edges.size(); ++i) {
			p.drawLine(graph.nodes[graph.edges[i].id1].pos.x, tbr_height + graph.nodes[graph.edges[i].id1].pos.y,
				graph.nodes[graph.edges[i].id2].pos.x, tbr_height + graph.nodes[graph.edges[i].id2].pos.y);
		}
	}

	for (int i = 0; i < graph.nodes.size(); ++i) {
		p.drawEllipse(graph.nodes[i].pos.x - 4, tbr_height + graph.nodes[i].pos.y - 4, 8, 8);
	}

	p.setPen(QColor("#1A1A1A"));
	p.setBrush(QColor("#F5F5F5"));
	if (user_detail_uid >= 0) {
		int x = graph.nodes[user_detail_uid].pos.x + 20;
		int y = graph.nodes[user_detail_uid].pos.y - 10;
		std::string username = graph.nodes[user_detail_uid].username;
		long long uid = graph.nodes[user_detail_uid].uid;

		int dlg_width = 80, dlg_height = 100;
		x = x < 0 ? 0 : x;
		x = x > (wnd_width - dlg_width) ? (wnd_width - dlg_width) : x;
		y = y < 0 ? 0 : y;
		y = y > (wnd_height - dlg_height) ? (wnd_height - dlg_height) : y;
		p.drawRect(x, y + tbr_height, dlg_width, dlg_height);

		QImage qimg;
		cv::Mat img, tmpImg;
		img = cv::imread(avatar_path + QString::number(uid).toStdString() + ".png");
		if (img.channels() == 3) {
			cvtColor(img, tmpImg, CV_BGR2RGB);
			qimg = QImage((const unsigned char *)(tmpImg.data), tmpImg.cols, tmpImg.rows, tmpImg.cols*tmpImg.channels(), QImage::Format_RGB888);
		}
		else if (img.channels() == 1) {
			qimg = QImage((const unsigned char *)(img.data), img.cols, img.rows, img.cols*img.channels(), QImage::Format_ARGB32);
		}
		else {
			qimg = QImage((const unsigned char *)(img.data), img.cols, img.rows, img.cols*img.channels(), QImage::Format_RGB888);
		}
		p.drawPixmap(x + 3, y + tbr_height + 8, dlg_width - 6, dlg_width - 6, QPixmap::fromImage(qimg));

		p.drawText(x + 10, y + tbr_height + dlg_width + 15, QString::fromStdString(username));
	}
}

void GraphVisualization::timeoutEvent() {
	for (int i = 0; i < graph.nodes.size(); ++i) {
		graph.nodes[i].pos += (target_graph.nodes[i].pos - graph.nodes[i].pos) / 3;
	}
	animate_frame++;
	if (animate_frame >= max_frame) {
		graph = target_graph;
		isAnimating = false;
		timer->stop();
	}
	update();
}

void GraphVisualization::mouseMoveEvent(QMouseEvent *e) {
	int x = e->x(), y = e->y() - tbr_height;
	user_detail_uid = -1;
	for (int i = 0; i < graph.nodes.size(); ++i) {
		if (abs(graph.nodes[i].pos.x - x) < 6 && abs(graph.nodes[i].pos.y - y) < 6) {
			user_detail_uid = i;
			break;
		}
	}
	update();
	if (isAnimating || edgebundling_flag)
		return;
	if (dragging_uid >= 0) {
		graph.nodes[dragging_uid].pos.x = e->x();
		graph.nodes[dragging_uid].pos.y = e->y() - tbr_height;
		update();
		return;
	}
}

void GraphVisualization::mousePressEvent(QMouseEvent *e) {
	if (isAnimating || edgebundling_flag)
		return;
	int x = e->x(), y = e->y() - tbr_height;
	dragging_uid = -1;
	for (int i = 0; i < graph.nodes.size(); ++i) {
		if (abs(graph.nodes[i].pos.x - x) < 6 && abs(graph.nodes[i].pos.y - y) < 6) {
			dragging_uid = i;
			break;
		}
	}
}

void GraphVisualization::mouseReleaseEvent(QMouseEvent *e) {
	if (isAnimating || edgebundling_flag)
		return;
	if (dragging_uid >= 0) {
		dragging_uid = -1;
		if (fdgraph_flag) {
			target_graph = graph;
			target_graph.forceDirectedLayout(wnd_width, wnd_height, 100);
			isAnimating = true;
			animate_frame = 0;
			timer->start(40);
		}
	}
}

void GraphVisualization::openGraph() {
	QString file = QFileDialog::getExistingDirectory(this, "Open Graph", "Data");
	if (!file.size())
		return;
	graph.readFromFile(file.toStdString());
	avatar_path = file.toStdString() + "/Avatars/";
	graph.randomLayout(wnd_width, wnd_height);
	update();
	if (fdgraph_flag) {
		target_graph = graph;
		target_graph.forceDirectedLayout(wnd_width, wnd_height, 100);
		isAnimating = true;
		animate_frame = 0;
		timer->start(40);
	}
}

void GraphVisualization::switchFDGraphFlag() {
	fdgraph_flag = !fdgraph_flag;
	if (fdgraph_flag) {
		target_graph = graph;
		target_graph.forceDirectedLayout(wnd_width, wnd_height, 100);
		isAnimating = true;
		animate_frame = 0;
		timer->start(40);
	}
}

void GraphVisualization::switchEdgeBundlingFlag() {
	edgebundling_flag = !edgebundling_flag;
	if (edgebundling_flag) {
		graph.edgeBundling();
	}
	update();
}
