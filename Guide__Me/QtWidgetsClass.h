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
    RoadMap* map = new RoadMap();

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

public slots:
    void slotAdd() {
        QString src = ui.textEdit->toPlainText();
        QString des = ui.textEdit_3->toPlainText();
        QString method = ui.textEdit_2->toPlainText();
        QString price = ui.textEdit_4->toPlainText();
        map->addTransportation(src.toStdString(),des.toStdString(),method.toStdString(), price.toDouble());
        GraphRead();
        ui.textEdit->clear();
        ui.textEdit_3->clear();
        ui.textEdit_2->clear();
        ui.textEdit_4->clear();
    };

    void slotDelete() {
        QString src = ui.textEdit_13->toPlainText();
        QString des = ui.textEdit_14->toPlainText();
        QString method = ui.textEdit_15->toPlainText();
        map->deleteTransportation(src.toStdString(), des.toStdString(), method.toStdString());
        GraphRead();
        ui.textEdit_13->clear();
        ui.textEdit_14->clear();
        ui.textEdit_15->clear();
    };
    
    void slotUpdate() {
        QString src = ui.textEdit_9->toPlainText();
        QString des = ui.textEdit_10->toPlainText();
        QString method = ui.textEdit_11->toPlainText();
        QString nPrice = ui.textEdit_12->toPlainText();
        map->updateTransportation(src.toStdString(), des.toStdString(), method.toStdString(), nPrice.toDouble());
        GraphRead();
        ui.textEdit_9->clear();
        ui.textEdit_10->clear();
        ui.textEdit_11->clear();
        ui.textEdit_12->clear();
    };

    void slotConnect() {
        
        map->isComplete();

    };
    
    void slotDFS() {
        
        ui.textBrowser->clear(); // Clear existing contents

        QString src = ui.textEdit_16->toPlainText();
        QString text = map->dfs(src.toStdString());
        ui.textEdit_16->clear();

        ui.textBrowser->append(text); // Add new text
    };
    
    void slotBFS() {
        
        ui.textBrowser->clear(); // Clear existing contents

        QString src = ui.textEdit_16->toPlainText();
        QString text = map->bfs(src.toStdString());
        ui.textEdit_16->clear(); 
        
        ui.textBrowser->append(text); // Add new text

    };
    
    void slotAllPaths() {
        
        ui.textBrowser_2->clear(); // Clear existing contents

        QString src = ui.textEdit_17->toPlainText();
        QString des = ui.textEdit_18->toPlainText();
        QString bud = ui.textEdit_19->toPlainText();

        QString text = map->outputofpaths(src.toStdString(), des.toStdString(), bud.toDouble());

        ui.textEdit_17->clear(); 
        ui.textEdit_18->clear(); 
        ui.textEdit_19->clear(); 
        
        ui.textBrowser_2->append(text); // Add new text

    };


};
