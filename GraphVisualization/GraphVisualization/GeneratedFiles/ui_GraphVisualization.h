/********************************************************************************
** Form generated from reading UI file 'GraphVisualization.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHVISUALIZATION_H
#define UI_GRAPHVISUALIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphVisualizationClass
{
public:
    QWidget *centralWidget;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *GraphVisualizationClass)
    {
        if (GraphVisualizationClass->objectName().isEmpty())
            GraphVisualizationClass->setObjectName(QStringLiteral("GraphVisualizationClass"));
        GraphVisualizationClass->resize(600, 400);
        centralWidget = new QWidget(GraphVisualizationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GraphVisualizationClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(GraphVisualizationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GraphVisualizationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(GraphVisualizationClass);

        QMetaObject::connectSlotsByName(GraphVisualizationClass);
    } // setupUi

    void retranslateUi(QMainWindow *GraphVisualizationClass)
    {
        GraphVisualizationClass->setWindowTitle(QApplication::translate("GraphVisualizationClass", "GraphVisualization", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphVisualizationClass: public Ui_GraphVisualizationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHVISUALIZATION_H
