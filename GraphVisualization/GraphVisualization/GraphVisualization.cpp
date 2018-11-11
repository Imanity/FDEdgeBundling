#include "GraphVisualization.h"

#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <opencv2/opencv.hpp>

GraphVisualization::GraphVisualization(QWidget *parent)	: QMainWindow(parent) {
	ui.setupUi(this);
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openGraph()));
}

void GraphVisualization::paintEvent(QPaintEvent *e) {
	QPainter p(this);
	p.setPen(Qt::black);
	p.setBrush(Qt::red);

	for (int i = 0; i < graph.edges.size(); ++i) {
		p.drawLine(graph.nodes[graph.edges[i].uid1].x, tbr_height + graph.nodes[graph.edges[i].uid1].y,
			graph.nodes[graph.edges[i].uid2].x, tbr_height + graph.nodes[graph.edges[i].uid2].y);
	}

	for (int i = 0; i < graph.nodes.size(); ++i) {
		p.drawEllipse(graph.nodes[i].x - 4, tbr_height + graph.nodes[i].y - 4, 8, 8);
	}

	p.setBrush(Qt::white);
	if (user_detail_uid >= 0) {
		int x = graph.nodes[user_detail_uid].x + 20;
		int y = graph.nodes[user_detail_uid].y - 10;
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

void GraphVisualization::mouseMoveEvent(QMouseEvent *e) {
	int x = e->x(), y = e->y() - tbr_height;
	user_detail_uid = -1;
	for (int i = 0; i < graph.nodes.size(); ++i) {
		if (abs(graph.nodes[i].x - x) < 6 && abs(graph.nodes[i].y - y) < 6) {
			user_detail_uid = i;
			break;
		}
	}
	update();
}

void GraphVisualization::openGraph() {
	QString file = QFileDialog::getExistingDirectory(this, "Open Graph", "../../Data");
	if (!file.size())
		return;
	graph.readFromFile(file.toStdString());
	avatar_path = file.toStdString() + "/Avatars/";
	update();
}
