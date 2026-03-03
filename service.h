#pragma once
#include "domain.h"
#include "repository.h"
#include "basket.h"
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <memory>
#include "undo.h"
#include "file_repository.h"

using namespace std;

class Service {
private:
    Repository& repo;
    Basket service_basket;
    std::vector<std::unique_ptr<UndoAction>> undoActions;

public:
    Service(Repository& repo) : repo(repo) {
        this->service_basket = Basket();
    }
    void undo();
    /*
    *
    */

    vector<Activitate>& getAll();
    /*
    * functie care returneaza toate activitatile
    */

    void add_activitate(const string& titlu, const string& descriere, const string& tip, const int& durata);
    /*
    * functie care adauga o activitate
    * titlu: titlul activitatii
    * descriere: descrierea activitatii
    * tip: tipul activitatii
    * durata: durata activitatii
    * arunca exceptie daca activitatea exista deja sau datele sunt invalide
    */

    const int validate(Activitate& a) const;
    /*
    * functie care valideaza o activitate
    * a: activitatea de validat
    * return: 1 daca activitatea este valida, 0 altfel
    */

    void delete_activitate(const string& titlu);
    /*
    * functia care sterge o activitate
    * titlu : titlul activitatii de sters
    * arunca exceptie daca activitatea nu exista sau lista este goala
    */

    void update_activitate(const string& titlu, const string& descriere, const string& tip, const int& durata);
    /*
    * functie care actualizeaza o activitate
    * titlu: titlul activitatii de actualizat
    * descriere: descrierea noua
    * tip: tipul nou
    * durata: durata noua
    * arunca exceptie daca activitatea nu exista sau datele sunt invalide
    */

    int find_activitate(const string& titlu) const;
    /*
    * functia care cauta o activitate dupa titlu
    * titlu: titlul activitatii cautate
    * returneaza pozitia activitatii cautate sau -1 daca nu exista
    */

    vector<Activitate> filtrare_tip(const vector<Activitate>& activitati, const string& tip);
    /*
    * Filtrare dupa tip
    * activitati: lista de activitati
    * tip: tipul dupa care se filtreaza
    * returneaza o lista de activitati filtrate
    */

    vector<Activitate> filtrare_durata(const vector<Activitate>& activitati, const int& durata, const int& property);
    /*
    * Filtrare dupa durata
    * activitati: lista de activitati
    * durata: durata dupa care se filtreaza
    * property: proprietatea de comparare
    * returneaza o lista de activitati filtrate
    */

    void sort_activitati(std::vector<Activitate>& list, int order, function<bool(const Activitate&, const Activitate&)> cmp);
    /*
    * Functia de sortare generala
    * list: lista de activitati
    * cmp: functia de comparare
    * order: ordinea de sortare (1 pentru crescator, -1 pentru descrescator)
    * returneaza lista sortata
    */

    void add_activitate_basket(const string& titlu);
    /*
    * Functia care adauga o activitate in cos
    * titlu: titlul activitatii de adaugat
    * Arunca exceptie daca activitatea nu exista in lista de activitati
    */

    void delete_activitate_basket(const string& titlu);
    /*
    * Functia care sterge o activitate din cos
    * titlu: titlul activitatii de sters
    * Arunca exceptie daca activitatea nu exista in cos sau cosul este gol
    */

    vector<Activitate>& get_basket();
    /*
    * Functia care returneaza cosul
    */

    void clear_basket();
    /*
    * Functia care goleste cosul
    * Arunca exceptie daca cosul este gol
    */

    void generate_activitati(int n);
    /*
    * Functia care genereaza n activitati random
    * n: numarul de activitati de generat
    * Arunca exceptie daca lista de activitati este goala
    */

    void export_basket(const string& filename);
    /*
    * Functia care salveaza cosul in fisierul dat
    * filename: fisierul dat
    * Arunca exceptie daca cosul este gol sau numele fisierului este invalid
    */

    map<int, ActivitateDTO> raport();
    /*
    * Functia care genereaza un raport cu activitatile grupate dupa tip
    * return: un map cu durata si numarul de activitati
    */

    Basket& get_cos();
};

