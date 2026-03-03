#include "basket.h"
#include "domain.h"
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <algorithm>

using namespace std;

Basket::Basket() {
	basket = vector<Activitate>{};
	basket.reserve(50); // Reserve space for efficiency
}

void Basket::add_to_basket(const Activitate& a) {
	basket.push_back(a);
	notifyObservers();
}

vector<Activitate>& Basket::get_basket() {
	return basket;
}

void Basket::clear_basket() {
	basket.clear();
	notifyObservers();
}

void Basket::remove_from_basket(const string& titlu) {
	auto it = find_if(basket.begin(), basket.end(), [&](const auto& activitate) {
		return activitate.getTitlu() == titlu;
		});
	if (it != basket.end()) {
		basket.erase(it);
		notifyObservers(); 
	}
}

void Basket::generate_basket(int n, vector<Activitate>& lista) {
	this->clear_basket(); // Goleste cosul inainte de generare

	if (lista.empty()) {
		throw std::runtime_error("Lista de activitati este goala!"); // Arunca exceptie daca lista este goala
	}

	std::random_device rd;
	std::mt19937 g(rd());

	for (int i = 0; i < n; i++) {
		// Selecteaza o activitate aleatorie din lista
		const auto& activitate = lista[g() % lista.size()];
		this->add_to_basket(activitate); // Adauga activitatea in cos
	}
}


int Basket::export_basket(const string& filename) {
	ofstream fout(filename);
	if (!fout.is_open())
		return 0; // Failed to open file
	for (const auto& activitate : basket) {
		fout << activitate.getTitlu() << "," << activitate.getDescriere() << "," << activitate.getTip() << "," << activitate.getDurata() << "\n";
	}
	fout.close();
	return 1; // Successfully exported
}

void Basket::addObserver(Observer* obs) {
	observers.push_back(obs);
}

void Basket::removeObserver(Observer* obs) {
	observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void Basket::notifyObservers() {
	for (auto obs : observers) {
		obs->update();
	}
}