#include "QtWidgetsClass.h"
#include "RoadMap.h"
#include <qboxlayout.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QtWidgetsClass w;
    QObject::connect(w.ui.pushButton, &QPushButton::clicked, &w, &QtWidgetsClass::GraphRead);
    QObject::connect(w.ui.pushButton_3, &QPushButton::clicked, &w, &QtWidgetsClass::addButton);
    QObject::connect(w.ui.pushButton_2, &QPushButton::clicked, &w, &QtWidgetsClass::updateButton);
    QObject::connect(w.ui.pushButton_4, &QPushButton::clicked, &w, &QtWidgetsClass::deleteButton);
    QObject::connect(w.ui.pushButton_5, &QPushButton::clicked, &w, &QtWidgetsClass::traversButton);
    QObject::connect(w.ui.pushButton_15, &QPushButton::clicked, &w, &QtWidgetsClass::allPathsButton);

    QObject::connect(w.ui.pushButton_6, &QPushButton::clicked, &w, &QtWidgetsClass::returnButton);
    QObject::connect(w.ui.pushButton_7, &QPushButton::clicked, &w, &QtWidgetsClass::returnButton);
    QObject::connect(w.ui.pushButton_8, &QPushButton::clicked, &w, &QtWidgetsClass::returnButton);
    QObject::connect(w.ui.pushButton_9, &QPushButton::clicked, &w, &QtWidgetsClass::returnButton);
    QObject::connect(w.ui.pushButton_17, &QPushButton::clicked, &w, &QtWidgetsClass::returnButton);

    w.show();

    return app.exec();
}
//