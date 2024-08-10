#include "QtWidgetsClass.h"
#include "RoadMap.h"
#include <qboxlayout.h>

int main(int argc, char* argv[])
{
    //
    QApplication app(argc, argv);
    QtWidgetsClass w;
    QObject::connect(w.ui.pushButton, &QPushButton::clicked, &w, &QtWidgetsClass::startButton);
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

    QObject::connect(w.ui.pushButton_12, &QPushButton::clicked, &w, &QtWidgetsClass::slotAdd);
    QObject::connect(w.ui.pushButton_10, &QPushButton::clicked, &w, &QtWidgetsClass::slotDelete);
    QObject::connect(w.ui.pushButton_11, &QPushButton::clicked, &w, &QtWidgetsClass::slotUpdate);
    QObject::connect(w.ui.pushButton_18, &QPushButton::clicked, &w, &QtWidgetsClass::slotConnect);

    QObject::connect(w.ui.pushButton_20, &QPushButton::clicked, &w, &QtWidgetsClass::slotComplete);

    QObject::connect(w.ui.pushButton_13, &QPushButton::clicked, &w, &QtWidgetsClass::slotDFS);
    QObject::connect(w.ui.pushButton_14, &QPushButton::clicked, &w, &QtWidgetsClass::slotBFS);

    QObject::connect(w.ui.pushButton_16, &QPushButton::clicked, &w, &QtWidgetsClass::slotAllPaths);


    //QObject::connect(w.ui.pushButton_19, &QPushButton::clicked, &w, &QtWidgetsClass::slotTransDisplay);
    
    w.show();

    return app.exec();
}
