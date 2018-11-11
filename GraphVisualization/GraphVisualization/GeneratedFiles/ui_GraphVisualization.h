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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphVisualizationClass
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *GraphVisualizationClass)
    {
        if (GraphVisualizationClass->objectName().isEmpty())
            GraphVisualizationClass->setObjectName(QStringLiteral("GraphVisualizationClass"));
        GraphVisualizationClass->resize(800, 634);
        GraphVisualizationClass->setMouseTracking(true);
        actionOpen = new QAction(GraphVisualizationClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        centralWidget = new QWidget(GraphVisualizationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMouseTracking(true);
        GraphVisualizationClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(GraphVisualizationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GraphVisualizationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        mainToolBar->addAction(actionOpen);

        retranslateUi(GraphVisualizationClass);

        QMetaObject::connectSlotsByName(GraphVisualizationClass);
    } // setupUi

    void retranslateUi(QMainWindow *GraphVisualizationClass)
    {
        GraphVisualizationClass->setWindowTitle(QApplication::translate("GraphVisualizationClass", "GraphVisualization", nullptr));
        actionOpen->setText(QApplication::translate("GraphVisualizationClass", "\346\211\223\345\274\200", nullptr));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("GraphVisualizationClass", "\346\211\223\345\274\200\345\233\276", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("GraphVisualizationClass", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class GraphVisualizationClass: public Ui_GraphVisualizationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHVISUALIZATION_H
