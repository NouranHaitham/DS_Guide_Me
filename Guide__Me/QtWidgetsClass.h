#pragma once

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include "RoadMap.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QWidget>
#include <unordered_map>
#include <ui_QtWidgetsClass.h>

class QtWidgetsClass : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsClass(QWidget* parent = nullptr);
    ~QtWidgetsClass();

    void GraphRead();
    void addButton();
    void deleteButton();
    void updateButton();
    void traversButton();
    void returnButton();
    void allPathsButton();
    void visualizeNodes(RoadMap* map);
    void visualizeEdges(RoadMap* map);
    void onPushButtonClicked();

    Ui::QtWidgetsClassClass ui;
    QGraphicsScene* scene;
    QGraphicsView* view;
    std::unordered_map<std::string, std::pair<int, int>> coordinates;
private:


};
