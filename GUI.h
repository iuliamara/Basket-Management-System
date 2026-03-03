#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include "service.h"
#include "CosCRUDGUI.h"
#include "CosReadOnlyGUI.h"
#include <QTableView>
#include "ActivitateTableModel.h"

class ActivitateGUI : public QWidget {
    Q_OBJECT
private:
    Service& srv;

    QTableView* tabelActivitati;
    ActivitateTableModel* modelTabel;

    QLineEdit* txtTitlu = nullptr,
        * txtDescriere = nullptr,
        * txtTip = nullptr,
        * txtDurata = nullptr,
        * txtTitluCos = nullptr;

    QSpinBox* spinGenCos = nullptr;

    QPushButton* btnAdd = nullptr,
        * btnDelete = nullptr,
        * btnUpdate = nullptr,
        * btnSort = nullptr,
        * btnFilter = nullptr,
        * btnUndo = nullptr,
        * btnOpenCosCRUD = nullptr,
        * btnOpenCosRO = nullptr,
        * btnAddCos = nullptr,
        * btnGenCos = nullptr,
        * btnRemoveCos = nullptr;

    // ferestre pentru cos 
    CosCRUDGUI* cosCrudWin = nullptr;
    CosReadOnlyGUI* cosROWin = nullptr;

    // helpers
    void initGUI();
    void connectSignalsSlots();
    void loadTable(const std::vector<Activitate>& activitati);
    void clearFields();
    void showError(const std::string& msg);

public:
    explicit ActivitateGUI(Service& srv);
};