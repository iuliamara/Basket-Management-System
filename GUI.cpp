#include "GUI.h"
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <QFileDialog>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QHeaderView>

ActivitateGUI::ActivitateGUI(Service& srv) : srv{ srv } {
    initGUI();
    connectSignalsSlots();
    loadTable(srv.getAll());
}

void ActivitateGUI::initGUI() {
    auto lyMain = new QHBoxLayout;
    setLayout(lyMain);

    //tabel
    tabelActivitati = new QTableView;
    modelTabel = new ActivitateTableModel;
    tabelActivitati->setModel(modelTabel); tabelActivitati = new QTableView;
    modelTabel = new ActivitateTableModel;
    tabelActivitati->setModel(modelTabel);
    tabelActivitati->horizontalHeader()->setStretchLastSection(true);
    lyMain->addWidget(tabelActivitati);

    //panou dreapta
    auto right = new QVBoxLayout;
    auto form = new QFormLayout;

    txtTitlu = new QLineEdit;
    txtDescriere = new QLineEdit;
    txtTip = new QLineEdit;
    txtDurata = new QLineEdit;

    form->addRow("Titlu", txtTitlu);
    form->addRow("Descriere", txtDescriere);
    form->addRow("Tip", txtTip);
    form->addRow("Durata", txtDurata);
    right->addLayout(form);

    btnAdd = new QPushButton("Add");
    btnDelete = new QPushButton("Delete");
    btnUpdate = new QPushButton("Update");
    btnSort = new QPushButton("Sort");
    btnFilter = new QPushButton("Filter");
    btnUndo = new QPushButton("Undo");
    btnOpenCosCRUD = new QPushButton("Cos CRUD GUI");
    btnOpenCosRO = new QPushButton("Cos ReadOnly GUI");

    txtTitluCos = new QLineEdit;
    spinGenCos = new QSpinBox;
    spinGenCos->setMinimum(1);
    spinGenCos->setMaximum(1000);

    btnAddCos = new QPushButton("Adauga in cos");
    btnGenCos = new QPushButton("Genereaza cos");
    btnRemoveCos = new QPushButton("Sterge din cos");

    right->addWidget(btnAdd);
    right->addWidget(btnDelete);
    right->addWidget(btnUpdate);
    right->addWidget(btnSort);
    right->addWidget(btnFilter);
    right->addWidget(btnUndo);
    right->addSpacing(10);
    right->addWidget(btnOpenCosCRUD);
    right->addWidget(btnOpenCosRO);

    auto cosForm = new QFormLayout;
    cosForm->addRow("Titlu pt cos:", txtTitluCos);
    cosForm->addRow("Nr activitati:", spinGenCos);
    right->addLayout(cosForm);
    right->addWidget(btnAddCos);
    right->addWidget(btnGenCos);
    right->addWidget(btnRemoveCos);

    lyMain->addLayout(right);
}

void ActivitateGUI::connectSignalsSlots() {
    // --- Add ---
    connect(btnAdd, &QPushButton::clicked, this, [&]() {
        try {
            srv.add_activitate(txtTitlu->text().toStdString(),
                txtDescriere->text().toStdString(),
                txtTip->text().toStdString(),
                txtDurata->text().toInt());
            loadTable(srv.getAll());
            clearFields();
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    // --- Delete ---
    connect(btnDelete, &QPushButton::clicked, this, [&]() {
        try {
            srv.delete_activitate(txtTitlu->text().toStdString());
            loadTable(srv.getAll());
            clearFields();
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    // --- Update ---
    connect(btnUpdate, &QPushButton::clicked, this, [&]() {
        try {
            srv.update_activitate(txtTitlu->text().toStdString(),
                txtDescriere->text().toStdString(),
                txtTip->text().toStdString(),
                txtDurata->text().toInt());
            loadTable(srv.getAll());
            clearFields();
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    // --- Sort (dupa titlu / tip, asc/desc) ---
    connect(btnSort, &QPushButton::clicked, this, [&]() {
        QDialog dlg(this);
        dlg.setWindowTitle("Sort options");
        auto vlay = new QVBoxLayout(&dlg);
        auto btnTitlu = new QPushButton("Titlu");
        auto btnTip = new QPushButton("Tip");
        vlay->addWidget(btnTitlu);
        vlay->addWidget(btnTip);

        connect(btnTitlu, &QPushButton::clicked, [&]() {
            auto list = srv.getAll();
            srv.sort_activitati(list, 0, [](const Activitate& a, const Activitate& b) {
                return a.getTitlu() < b.getTitlu();
                });
            loadTable(list);
            dlg.close();
            });
        connect(btnTip, &QPushButton::clicked, [&]() {
            auto list = srv.getAll();
            srv.sort_activitati(list, 0, [](const Activitate& a, const Activitate& b) {
                return a.getTip() < b.getTip();
                });
            loadTable(list);
            dlg.close();
            });
        dlg.exec();
        });

    // --- Filter (dupa tip / durata) ---
    connect(btnFilter, &QPushButton::clicked, this, [&]() {
        QDialog dlg(this);
        dlg.setWindowTitle("Filter options");
        auto lay = new QVBoxLayout(&dlg);
        auto btnTip = new QPushButton("Tip");
        auto btnDur = new QPushButton("Durata < X");
        lay->addWidget(btnTip);
        lay->addWidget(btnDur);

        connect(btnTip, &QPushButton::clicked, [&]() {
            QString tip = QInputDialog::getText(this, "Filtru tip", "Tip:");
            if (!tip.isEmpty()) {
                auto list = srv.getAll();
                auto rez = srv.filtrare_tip(list, tip.toStdString());
                loadTable(rez);
            }
            dlg.close();
            });
        connect(btnDur, &QPushButton::clicked, [&]() {
            bool ok{ false };
            int val = QInputDialog::getInt(this, "Filtru durata", "Mai mica decat:", 0, 0, 10000, 1, &ok);
            if (ok) {
                auto list = srv.getAll();
                auto rez = srv.filtrare_durata(list, val, 1);
                loadTable(rez);
            }
            dlg.close();
            });
        dlg.exec();
        });

    // --- Undo ---
    connect(btnUndo, &QPushButton::clicked, this, [&]() {
        try {
            srv.undo();
            loadTable(srv.getAll());
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    // --- Cos CRUD GUI ---
    /*connect(btnOpenCosCRUD, &QPushButton::clicked, this, [&]() {
        if (!cosCrudWin) cosCrudWin = new CosCRUDGUI(srv.get_cos());
        cosCrudWin->show();
        });*/

    // --- Cos ReadOnly GUI ---
   /* connect(btnOpenCosRO, &QPushButton::clicked, this, [&]() {
        if (!cosROWin) cosROWin = new CosReadOnlyGUI(srv.get_cos());
        cosROWin->show();
        });*/

    // --- Adauga in cos ---
    connect(btnAddCos, &QPushButton::clicked, this, [&]() {
        QString activityName = txtTitluCos->text(); 
        if (activityName.isEmpty()) {
            QMessageBox::warning(this, "Eroare", "Introdu un nume de activitate."); 
            return;
        }

        auto all = srv.getAll();
        auto it = std::find_if(all.begin(), all.end(), [&](const Activitate& a) {
            return a.getTitlu() == activityName.toStdString();
            });

        if (it != all.end()) {
            srv.get_cos().add_to_basket(*it);
           // loadTable(srv.get_basket());
            txtTitluCos->clear();
        }
        else {
            QMessageBox::warning(this, "Eroare", "Activitatea nu exista.");
        }
        });

    connect(btnRemoveCos, &QPushButton::clicked, this, [&]() {
        QString titlu = txtTitluCos->text();
        if (titlu.isEmpty()) {
            QMessageBox::warning(this, "Eroare", "Introdu un titlu pentru a sterge din cos.");
            return;
        }
        auto all = srv.get_basket();
        auto it = std::find_if(all.begin(), all.end(), [&](const Activitate& a) {
            return a.getTitlu() == titlu.toStdString();
            });

        if (it != all.end()) {
            srv.get_cos().remove_from_basket(titlu.toStdString());
            // loadTable(srv.get_basket());
            txtTitluCos->clear();
        }
        else {
            QMessageBox::warning(this, "Eroare", "Activitatea nu exista.");
        }
        });

	// --- Genereaza cos ---
	connect(btnGenCos, &QPushButton::clicked, this, [&]() {
		int n = spinGenCos->value();
		if (n <= 0) {
			QMessageBox::warning(this, "Eroare", "Numarul de activitati trebuie sa fie pozitiv.");
			return;
		}
		try {
			srv.get_cos().generate_basket(n, srv.getAll());
			QMessageBox::information(this, "Info", "Cosul a fost generat cu succes.");
		}
		catch (const std::exception& ex) {
			showError(ex.what());
		}
		});

    // --- Deschide CosCRUDGUI ---
    connect(btnOpenCosCRUD, &QPushButton::clicked, this, [&]() {
        if (!cosCrudWin) {
            cosCrudWin = new CosCRUDGUI{ srv.get_cos()};
        }
        cosCrudWin->show();
        cosCrudWin->raise();
        cosCrudWin->activateWindow();
        });

    // --- Deschide CosReadOnlyGUI ---
    connect(btnOpenCosRO, &QPushButton::clicked, this, [&]() {
        if (!cosROWin) {
            cosROWin = new CosReadOnlyGUI{ srv.get_cos()};
        }
        cosROWin->show();
        cosROWin->raise();
        cosROWin->activateWindow();
        });

}

void ActivitateGUI::loadTable(const std::vector<Activitate>& activitati) {
    modelTabel->setActivitati(activitati);
}

void ActivitateGUI::clearFields() {
    txtTitlu->clear();
    txtDescriere->clear();
    txtTip->clear();
    txtDurata->clear();
    txtTitluCos->clear();
}

void ActivitateGUI::showError(const std::string& msg) {
    QMessageBox::warning(this, "Eroare", QString::fromStdString(msg));
}