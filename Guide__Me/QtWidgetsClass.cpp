#include "QtWidgetsClass.h"

QtWidgetsClass::QtWidgetsClass(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

QtWidgetsClass::~QtWidgetsClass()
{

}

void QtWidgetsClass::visualizeNodes(RoadMap* map) {
    int x = 0, y = 500;
    int i = 0;
    for (const auto& pair : map->map) {
        QGraphicsEllipseItem* node = scene->addEllipse(x, y, 20, 20);
        QGraphicsTextItem* text = scene->addText(QString::fromStdString(pair.first));
        text->setPos(x - 5, y + 25);

        coordinates.insert({ pair.first, { x,y + 10 } });

        i++;
        if (i % 2 == 0) {
            x += 100;
        }
        else {
            x = 0;
            y -= 50;
            x -= 50;
        }
    }
}

void QtWidgetsClass::visualizeEdges(RoadMap* map) {
    for (const auto& pair : map->map) {
        int x1 = coordinates[pair.first].first;
        int y1 = coordinates[pair.first].second;

        for (const auto& transport : pair.second) {
            int x2 = coordinates[transport.first].first;
            int y2 = coordinates[transport.first].second;
            QGraphicsLineItem* edge = scene->addLine(x1 + 10, y1, x2 + 10, y2);
        }
    }
}
