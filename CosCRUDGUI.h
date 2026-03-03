#pragma once

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "observer.h"
#include "basket.h"

class CosCRUDGUI : public QWidget, public Observer {
    Q_OBJECT

private:
    Basket& basket;
    QListWidget* lst = new QListWidget;
    QPushButton* btnEmpty = new QPushButton{ "Goleste cosul" };
    QPushButton* btnExport = new QPushButton{ "Exporta cosul" };

    void initGUI();
    void connectSignals();

public:
    CosCRUDGUI(Basket& b);
    ~CosCRUDGUI() override;

    void update() override;
};
