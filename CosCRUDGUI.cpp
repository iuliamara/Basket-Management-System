#include "CosCRUDGUI.h"
#include <QMessageBox>
#include <QFileDialog>

CosCRUDGUI::CosCRUDGUI(Basket& b) : basket{ b } {
    initGUI();
    connectSignals();
    basket.addObserver(this);
    update(); // initializare lista
}

CosCRUDGUI::~CosCRUDGUI() {
    basket.removeObserver(this);
}

void CosCRUDGUI::initGUI() {
    auto layout = new QVBoxLayout;
    layout->addWidget(lst);
    layout->addWidget(btnEmpty);
    layout->addWidget(btnExport);
    setLayout(layout);
}

void CosCRUDGUI::connectSignals() {
    QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
        basket.clear_basket();
        });

    QObject::connect(btnExport, &QPushButton::clicked, [&]() {
        QString fileName = QFileDialog::getSaveFileName(this, "Salveaza cosul", "", "CSV (*.csv)");
        if (!fileName.isEmpty()) {
            basket.export_basket(fileName.toStdString());
            QMessageBox::information(this, "Export", "Cosul a fost salvat cu succes!");
        }
        });
}

void CosCRUDGUI::update() {
    lst->clear();
    for (const auto& act : basket.get_basket()) {
        QString item = QString::fromStdString(act.getTitlu() + " | " + act.getTip() + " | " + std::to_string(act.getDurata()));
        lst->addItem(item);
    }
}
