#include "QtWidgetsClass.h"

QtWidgetsClass::QtWidgetsClass(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

QtWidgetsClass::~QtWidgetsClass()
{
    map->~RoadMap();

}
void QtWidgetsClass::GraphRead() {

    scene = new QGraphicsScene();
    ui.graphicsView->setScene(scene);

    // Visualize graph
    visualizeNodes(map);
    visualizeEdges(map);

    //go to 2nd page (2nd page name is from the scene builder)
    ui.stackedWidget->setCurrentWidget(ui.page_2);
    ui.stackedWidget_2->setCurrentWidget(ui.page_3);
}

void QtWidgetsClass::addButton()
{
    ui.stackedWidget_2->setCurrentWidget(ui.page_4);
}

void QtWidgetsClass::updateButton()
{
    ui.stackedWidget_2->setCurrentWidget(ui.page_5);
}

void QtWidgetsClass::deleteButton()
{
    ui.stackedWidget_2->setCurrentWidget(ui.page_6);
}


void QtWidgetsClass::traversButton()
{
    ui.stackedWidget_2->setCurrentWidget(ui.page_7);
}

void QtWidgetsClass::returnButton()
{

    ui.stackedWidget->setCurrentWidget(ui.page_2);
    ui.stackedWidget_2->setCurrentWidget(ui.page_3);
}
void QtWidgetsClass::allPathsButton()
{
    ui.stackedWidget->setCurrentWidget(ui.page_8);
}


void QtWidgetsClass::visualizeNodes(RoadMap* map) {

    int x = 0, y = 500;
    int i = 0;
    int spaceX=-10, spaceY=45;

    for (const auto& pair : map->map) {
        QGraphicsEllipseItem* node = scene->addEllipse(x, y, 40, 40);
        node->setBrush(Qt::red);
        QGraphicsTextItem* text = scene->addText(QString::fromStdString(pair.first));
        text->setPos(x+spaceX, y+spaceY);
        QFont font = text->font();
        font.setPointSize(18); // Set text size to 12
        text->setFont(font);

        // Retrieve the bounding rectangle of the text item
        QRectF textRect = text->boundingRect();

        // Get the width and height of the text
        qreal textWidth = textRect.width();

        coordinates.insert({ pair.first, { x,y + 20 } });

        i++;

        if (i % 2 == 0) {
            x += 200;
            spaceX = 45;
            spaceY = 0;
        }
        else 
        {
            x = 0;
            y -= 100;
            x -= 100;

            spaceX = - 30 - textWidth;
            spaceY = 0;
        }
    }
}

void QtWidgetsClass::visualizeEdges(RoadMap* map) {
    for (const auto& pair : map->map) {
        int x1 = coordinates[pair.first].first;
        int y1 = coordinates[pair.first].second;

        for (const auto& transport : pair.second) {
            if (!transport.second.empty()) {
                int x2 = coordinates[transport.first].first;
                int y2 = coordinates[transport.first].second;

                // Create an Edge object and add it to the scene
                Edge* edge = new Edge(x1 + 20, y1, x2 + 20, y2, QString::fromStdString(pair.first), QString::fromStdString(transport.first), map);
                edge->setTextBrowser(ui.textBrowser_3);  // textBrowser_3 is a member variable of QtWidgetsClass
                scene->addItem(edge);

                // Setting initial pen properties
                QPen pen = edge->pen();
                pen.setColor(Qt::red);
                pen.setWidth(5); // Set line thickness 
                edge->setPen(pen);
            }
        }
    }
}