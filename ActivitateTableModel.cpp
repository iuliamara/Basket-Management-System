#include "ActivitateTableModel.h"

ActivitateTableModel::ActivitateTableModel(QObject* parent)
    : QAbstractTableModel(parent) {
}



void ActivitateTableModel::setActivitati(const std::vector<Activitate>& act) {
    activitati = act;
    beginResetModel();
    endResetModel();
}

//returneaza numarul de randuri din tabel, adica cate activitati sunt
int ActivitateTableModel::rowCount(const QModelIndex& /*parent*/) const {
    return static_cast<int>(activitati.size());
}

int ActivitateTableModel::columnCount(const QModelIndex& /*parent*/) const {
    return 4; // Titlu, Descriere, Tip, Durata
}


//se acceseaza obiectul Activitate corespunzator randului si se extrage valoarea corespunzatoare coloanei
QVariant ActivitateTableModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        const auto& act = activitati.at(index.row());
        switch (index.column()) {
        case 0: return QString::fromStdString(act.getTitlu());
        case 1: return QString::fromStdString(act.getDescriere());
        case 2: return QString::fromStdString(act.getTip());
        case 3: return QString::number(act.getDurata());
        }
    }
    return {};
}

//furnizeaza numele coloanelor, vizibile pe randul de antet
QVariant ActivitateTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Titlu";
        case 1: return "Descriere";
        case 2: return "Tip";
        case 3: return "Durata";
        }
    }
    return {};
}
