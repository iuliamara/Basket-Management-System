#include "CosReadOnlyGUI.h"
#include <QPainter>
#include <QRandomGenerator>

CosReadOnlyGUI::CosReadOnlyGUI(Basket& b) : basket{ b } {
    basket.addObserver(this);
    setWindowTitle("Cos ReadOnly View");
    resize(400, 300);
}

CosReadOnlyGUI::~CosReadOnlyGUI() {
    basket.removeObserver(this);
}

void CosReadOnlyGUI::update() {
    repaint(); // redeseneaza cand se modifica cosul
}

void CosReadOnlyGUI::paintEvent(QPaintEvent* event) {
    QPainter p{ this };
    QRandomGenerator* gen = QRandomGenerator::global();

    int x = 10, y = 10;

    for (const auto& act : basket.get_basket()) {
        int w = gen->bounded(20, 80);
        int h = gen->bounded(20, 80);
        QColor color = QColor::fromRgb(gen->bounded(256), gen->bounded(256), gen->bounded(256));

        p.setBrush(color);
        p.drawRect(x, y, w, h);

        x += w + 10;
        if (x + 100 > width()) {
            x = 10;
            y += h + 10;
        }
    }
}
