#pragma once
#include "domain.h"
#include <vector>

using namespace std;
class Repository {
protected:
	vector <Activitate> activitati;

public:
	Repository(); // Constructor implicit
	vector<Activitate>& getAll(); // Returneaza toate activitatile
	virtual int add(const Activitate& a);
	/*
	* Adauga o activitate
	* a: activitatea de adaugat
	* returneaza 1 daca activitatea a fost adaugata cu succes
	*/
	virtual int remove(const std::string& titlu);
	/*
	* Sterge o activitate
	* titlu: titlul activitatii de sters
	* returneaza 1 daca activitatea a fost stearsa cu succes
	*/
	virtual int update(const Activitate& a);
	/*
	* Actualizeaza o activitate
	* a: activitatea actualizata
	* returneaza 1 daca activitatea a fost actualizata cu succes
	*/
	virtual int cauta(const string& titlu) const;
	/*
	* Cauta o activitate
	* titlu: titlul activitatii cautate
	* returneaza pozitia activitatii cautate sau -1 daca nu exista activitatea
	*/
	virtual ~Repository() = default;
};

