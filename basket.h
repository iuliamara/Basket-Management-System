#pragma once
#include "domain.h"
#include <vector>
#include "observer.h"

class Basket {
private:
	std::vector<Activitate> basket;
	std::vector<Observer*> observers; // Lista de observatori

public:
	Basket(); // Constructor implicit

	void add_to_basket(const Activitate& a);
	/*
	* functia care adauga o activitate in cos
	* a: activitatea de adaugat
	*/

	std::vector<Activitate>& get_basket();

	void clear_basket();
	/*
	* functia care goleste cosul
	*/

	void remove_from_basket(const std::string& titlu);
	/*
	* functia care sterge o activitate din cos
	* titlu: titlul activitatii de sters
	*/

	void generate_basket(int n, std::vector<Activitate>& lista);
	/*
	* functia care genereaza n activitati random
	* n: numarul de activitati de generat
	* lista: lista de activitati din care se genereaza
	*/

	int export_basket(const std::string& filename);
	/*
	* functia care salveaza cosul in fisier
	* filename: numele fisierului in care se salveaza
	*/


	// Metode pentru Observer
	void addObserver(Observer* obs);
	void removeObserver(Observer* obs);
	void notifyObservers();
};