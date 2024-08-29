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

// Edge.h
//#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <QTextBrowser>
#include <QMessageBox>



class QtWidgetsClass : public QMainWindow
{
    Q_OBJECT

public:
    RoadMap* map = new RoadMap();

    QtWidgetsClass(QWidget* parent = nullptr);
    ~QtWidgetsClass();

    void setCoverPhoto();
    void startButton();
    void GraphRead(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, bool mod = 0);
    void addButton();
    void deleteButton();
    void updateButton();
    void traversButton();
    void returnButton();
    void allPathsButton();
    void visualizeNodes(RoadMap* map,bool mod);
    void visualizeNodes(std::vector<string> cities);
    void visualizeEdges(RoadMap* map, int x1, int y1, int x2, int y2, bool mod);

    Ui::QtWidgetsClassClass ui;
    QGraphicsScene* scene;
    QGraphicsView* view;
    std::unordered_map<std::string, std::pair<int, int>> coordinates;
 

public slots:

    void slotAdd() {
        QString src = ui.comboBox->currentText();
        QString des = ui.comboBox_2->currentText();
        QString method = ui.textEdit_2->toPlainText();
        method.remove(" ");
        QString price = ui.textEdit_4->toPlainText();
        price.remove(" ");
        if ( (src.toStdString() != "" && des.toStdString() != "" && method.toStdString() != "" && price.toStdString() != "") && (src!=des))
        {
            map->addTransportation(src.toStdString(), des.toStdString(), method.toStdString(), price.toDouble());
            GraphRead();
            //ui.textEdit->clear();
            //ui.textEdit_3->clear();
            ui.textEdit_2->clear();
            ui.textEdit_4->clear();
            ui.stackedWidget_2->setCurrentWidget(ui.page_4);
        }
        else
        {
            QMessageBox::information(nullptr, "Alert", "Incomplete information!");
        }
    };

    void slotDelete() {
        QString src = ui.comboBox_5->currentText();
        QString des = ui.comboBox_6->currentText();
        QString method = ui.textEdit_15->toPlainText();
        method.remove(" ");
        map->deleteTransportation(src.toStdString(), des.toStdString(), method.toStdString());
        GraphRead();
        //ui.textEdit_13->clear();
        //ui.textEdit_14->clear();
        ui.textEdit_15->clear();
        ui.stackedWidget_2->setCurrentWidget(ui.page_6);
    };

    void slotUpdate() {
        QString src = ui.comboBox_3->currentText();
        QString des = ui.comboBox_4->currentText();
        QString method = ui.textEdit_11->toPlainText();
        method.remove(" ");
        QString nPrice = ui.textEdit_12->toPlainText();
        nPrice.remove(" ");
        map->updateTransportation(src.toStdString(), des.toStdString(), method.toStdString(), nPrice.toDouble());
        GraphRead();
        //ui.textEdit_9->clear();
        //ui.textEdit_10->clear();
        ui.textEdit_11->clear();
        ui.textEdit_12->clear();
        ui.stackedWidget_2->setCurrentWidget(ui.page_5);

    };

    void slotConnect() {

        map->isConnected();

    };

    void slotComplete() {

        map->isComplete();

    };

    void slotDFS() {

       // ui.textBrowser->clear(); 

        QString src = ui.comboBox_7->currentText();
        QString text = map->dfs(src.toStdString());

        QStringList cityList = text.split("\n");

        // Convert the QStringList to a std::vector<std::string>
        std::vector<std::string> cities;
        for (const QString& city : cityList) {
            cities.push_back(city.toStdString()); // Convert each QString to std::string
        }

        visualizeNodes(cities);

       // ui.textBrowser->append(text); 
    };

    void slotBFS() {

       // ui.textBrowser->clear(); 

        QString src = ui.comboBox_7->currentText();
        QString text = map->bfs(src.toStdString());


        QStringList cityList = text.split("\n");

        // Convert the QStringList to a std::vector<std::string>
        std::vector<std::string> cities;
        for (const QString& city : cityList) {
            cities.push_back(city.toStdString()); // Convert each QString to std::string
        }

        visualizeNodes(cities);


     //   ui.textBrowser->append(text); 

    };

    void slotAllPaths() {

        ui.textBrowser_2->clear(); 

        QString src = ui.comboBox_8->currentText();
        QString des = ui.comboBox_9->currentText();
        QString bud = ui.textEdit_19->toPlainText();
        bud.remove(" ");

        QString text = map->outputofpaths(src.toStdString(), des.toStdString(), bud.toDouble());

        //ui.textEdit_17->clear();
        //ui.textEdit_18->clear();
        ui.textEdit_19->clear();

        ui.textBrowser_2->append(text); 

    };

    /*void slotTransDisplay() {

        ui.textBrowser_3->clear();
        QString src = ui.textEdit_5->toPlainText();
        QString des = ui.textEdit_6->toPlainText();
       
        QString text = map->DisplayEdges(src.toStdString(), des.toStdString());

        ui.textBrowser_3->append(text); 
    }*/





};

class Edge : public QGraphicsLineItem {
public:
    Edge(int x1, int y1, int x2, int y2, const QString& source, const QString& destination, RoadMap* roadMap, QGraphicsItem* parent = nullptr)
        : QGraphicsLineItem(x1, y1, x2, y2, parent), source_(source), destination_(destination), roadMap_(roadMap), textBrowser_(nullptr) {
        setFlag(QGraphicsItem::ItemIsSelectable);
        setAcceptHoverEvents(true); // Optional: for hover events if needed
        setPen(QPen(Qt::red, 5)); // Default color and thickness

        x1_ = x1;
        x2_ = x2;
        y1_ = y1;
        y2_ = y2;

    }

    void setTextBrowser(QTextBrowser* textBrowser) {
        textBrowser_ = textBrowser;
    }
    void setwidget(QtWidgetsClass* widg) {
        wid = widg;
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            // Change edge color to blue when clicked

            wid->GraphRead(x1_, y1_, x2_,y2_,1);
            
            wid->scene->addItem(this);
            QPen pen = this->pen();
            pen.setColor(Qt::blue);
            setPen(pen);

            wid->visualizeNodes(roadMap_, 0);
            
             
             if (textBrowser_) {
                QString edgeData;
                std::string src = source_.toStdString();
                std::string des = destination_.toStdString();
                for (const auto& trans : roadMap_->map[src][des]) {
                    edgeData += QString::fromStdString(trans.vehicle) + " - " + QString::number(trans.price) + "\n";
                }
                textBrowser_->setText(edgeData);
            }
        }
        QGraphicsLineItem::mousePressEvent(event);
    }

    // Override shape and boundingRect if needed to manage the selection box
    QPainterPath shape() const override {
        QPainterPath path;
        path.addPath(QGraphicsLineItem::shape());
        return path;
    }

    QRectF boundingRect() const override {
        return QGraphicsLineItem::boundingRect();
    }


private:

    QtWidgetsClass* wid;
    QString source_;
    QString destination_;
    RoadMap* roadMap_;
    QTextBrowser* textBrowser_;
    int x1_, y1_, x2_, y2_;

};
