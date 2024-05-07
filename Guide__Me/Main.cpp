#include "QtWidgetsClass.h"
#include <QApplication>
#include "RoadMap.h"

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

    // Create a view to visualize the scene
    w.view = new QGraphicsView(w.scene);
    w.view->show();

    return app.exec();
}
