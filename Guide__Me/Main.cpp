#include "QtWidgetsClass.h"
#include "RoadMap.h"
#include <qboxlayout.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QtWidgetsClass w;


    // Create a scene
    w.scene = new QGraphicsScene();

    RoadMap* map = new RoadMap();

    // Visualize nodes
    w.visualizeNodes(map);

    // Visualize edges
    w.visualizeEdges(map);

    w.view = new QGraphicsView(w.scene);

    // Set up the layout
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(w.view);
    layout->addWidget(w.ui.pushButton); 

    // add layout on central widget
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    w.setCentralWidget(centralWidget);

    w.show();

    return app.exec();
}
