#include "QtWidgetsClass.h"
#include <QTimer>

QtWidgetsClass::QtWidgetsClass(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

QtWidgetsClass::~QtWidgetsClass()
{
    map->~RoadMap();

}
void QtWidgetsClass::startButton()
{
    GraphRead();
    vector<QComboBox*> comboBoxes = { ui.comboBox, ui.comboBox_2, ui.comboBox_3, ui.comboBox_4, ui.comboBox_5, ui.comboBox_6, ui.comboBox_7, ui.comboBox_8, ui.comboBox_9 };
    for (QComboBox* comboBox : comboBoxes) {
        for ( auto pair : map->map) {
            comboBox->addItem(QString::fromStdString(pair.first));
        }
    }
}
void QtWidgetsClass::GraphRead(int x1, int y1, int x2, int y2,bool mod)
{

    scene = new QGraphicsScene();
    ui.graphicsView->setScene(scene);

    // Visualize graph
    visualizeNodes(map,1);
    visualizeEdges(map,x1,y1,x2,y2,mod);
    visualizeNodes(map, 0);

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
    vector<QComboBox*> comboBoxes = { ui.comboBox, ui.comboBox_2, ui.comboBox_3, ui.comboBox_4, ui.comboBox_5, ui.comboBox_6, ui.comboBox_7, ui.comboBox_8, ui.comboBox_9 };

    for (QComboBox* comboBox : comboBoxes) {
        if (comboBox->count() > 0) { // Check if there are items in the combo box
            comboBox->setCurrentIndex(0); // Set the current index to the first item
        }
    }

    vector<QTextEdit*> textEdits = { ui.textEdit_2, ui.textEdit_4, ui.textEdit_11, ui.textEdit_12, ui.textEdit_15, ui.textEdit_19};
    for (QTextEdit* textEdit : textEdits) {
        textEdit->clear();
    }
    ui.stackedWidget->setCurrentWidget(ui.page_2);
    ui.stackedWidget_2->setCurrentWidget(ui.page_3);
}
void QtWidgetsClass::allPathsButton()
{
    ui.stackedWidget->setCurrentWidget(ui.page_8);
}


void QtWidgetsClass::visualizeNodes(RoadMap* map,bool mod) {

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

        if(mod)
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

void QtWidgetsClass::visualizeNodes(std::vector<string> cities)
{
  
    //QTimer* timer = new QTimer();
   

    //for (int i = 0; i < cities.size(); i++) {
    //    QGraphicsEllipseItem* node = scene->addEllipse(coordinates[cities[i]].first, coordinates[cities[i]].second, 40, 40);
    //    node->setBrush(Qt::red);
    //    timer->start(500);

    //}

    QTimer* timer = new QTimer(this); // Make sure the timer is tied to the parent to manage its lifecycle

    // Create a lambda function that will be called each time the timer fires
    int i = 0; // Start index
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (i < cities.size()-1) {
            QGraphicsEllipseItem* node = scene->addEllipse(coordinates[cities[i]].first, coordinates[cities[i]].second-20, 40, 40);
            node->setBrush(Qt::blue);
            i++; // Move to the next city
        }
        else {
            timer->stop(); // Stop the timer when all cities have been processed
            visualizeNodes(map, 0);
        }
        });

    timer->start(1000); // Start the timer with a 500 ms interval
 
}


void QtWidgetsClass::visualizeEdges(RoadMap* map, int x1_, int y1_, int x2_, int y2_, bool mod) {


    for (const auto& pair : map->map) {
        int x1 = coordinates[pair.first].first;
        int y1 = coordinates[pair.first].second;

        for (const auto& transport : pair.second) {
            if (!transport.second.empty()) {
                int x2 = coordinates[transport.first].first;
                int y2 = coordinates[transport.first].second;

                // Create an Edge object and add it to the scene

                if (mod && (x1_ == x1 + 20 && y1_ == y1 && x2_ == x2 + 20 && y2_ == y2))
                    continue;

                Edge* edge = new Edge(x1 + 20, y1, x2 + 20, y2, QString::fromStdString(pair.first), QString::fromStdString(transport.first), map);
                edge->setwidget(this);
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