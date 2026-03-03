#pragma once

#include <QWidget>
#include "observer.h"
#include "basket.h"

class CosReadOnlyGUI : public QWidget, public Observer {
    Q_OBJECT

private:
    Basket& basket;

public:
    CosReadOnlyGUI(Basket& b);
    ~CosReadOnlyGUI() override;

    void paintEvent(QPaintEvent* event) override;
    void update() override;
};
