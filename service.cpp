#include "service.h"
#include "domain.h"
#include "exceptions.h"
#include "basket.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include "undo.h"

using namespace std;

vector<Activitate>& Service::getAll() {
	return this->repo.getAll();
}

void Service::add_activitate(const string& titlu, const string& descriere, const string& tip, const int& durata) {
	Activitate a = Activitate(titlu, descriere, tip, durata);
	int v = validate(a);
	if (v == 0) {
		throw ValidationException("Datele introduse sunt invalide");
	}
	v = this->repo.add(a);
	if (v == 0)
		throw ActivitateAlreadyExistsException("Activitatea exista deja");
	else
		this->undoActions.push_back(std::make_unique<UndoAdauga>(this->repo, a));
}

void Service::delete_activitate(const string& titlu) {
	if (this->repo.getAll().size() == 0)
		throw EmptyListException("Lista este goala");

	int index = this->repo.cauta(titlu);
	if (index == -1) // Verifica daca activitatea nu exista
		throw ActivitateNotFoundException("Activitatea nu exista");

	Activitate act = this->repo.getAll()[index];
	int v = this->repo.remove(titlu);
	if (v == 0)
		throw ActivitateNotFoundException("Activitatea nu exista");
	else
		this->undoActions.push_back(std::make_unique<UndoSterge>(this->repo, act));
}


void Service::update_activitate(const string& titlu, const string& descriere, const string& tip, const int& durata) {
	Activitate a = Activitate(titlu, descriere, tip, durata);
	int v = validate(a);
	if (v == 0) {
		throw ValidationException("Datele introduse sunt invalide");
	}
	int index = this->repo.cauta(titlu);
	if (index == -1) // Verifica daca activitatea nu exista
		throw ActivitateNotFoundException("Activitatea nu exista");
	Activitate actVeche = this->repo.getAll()[this->repo.cauta(titlu)];
	v = this->repo.update(a);
	if (v == 0)
		throw ActivitateNotFoundException("Activitatea nu exista");
	else
		this->undoActions.push_back(std::make_unique<UndoModifica>(this->repo, actVeche));
}

int Service::find_activitate(const string& titlu) const {
	int v = this->repo.cauta(titlu);
	if (v == -1)
		throw ActivitateNotFoundException("Activitatea nu exista");
	return v;
}

const int Service::validate(Activitate& a) const {
	if (a.getTitlu() == "" || a.getDescriere() == "" || a.getTip() == "" || a.getDurata() <= 0)
		return 0;
	return 1;
}

vector<Activitate> Service::filtrare_durata(const vector<Activitate>& activitati, const int& durata, const int& property) {
	vector<Activitate> filter;
	filter.reserve(50); // Reserve space for efficiency
	for (const auto& a : activitati) {
		if (property == 1 && a.getDurata() <= durata) {
			filter.push_back(a);
		}
		else if (property == 2 && a.getDurata() > durata) {
			filter.push_back(a);
		}
	}
	return filter;
}

vector<Activitate> Service::filtrare_tip(const vector<Activitate>& activitati, const string& tip) {
	vector<Activitate> filter;
	filter.reserve(50); // Reserve space for efficiency
	for (const auto& a : activitati) {
		if (a.getTip() == tip) {
			filter.push_back(a);
		}
	}
	return filter;
}

void Service::sort_activitati(std::vector<Activitate>& list, int order, function<bool(const Activitate&, const Activitate&)> cmp) {
	if (order == 1) {
		sort(list.begin(), list.end(), [cmp](const Activitate& a, const Activitate& b) {
			return !cmp(a, b);
			});
	}
	else {
		sort(list.begin(), list.end(), cmp);
	}
}

void Service::add_activitate_basket(const string& titlu) {
	int v = this->repo.cauta(titlu);
	if (v == -1)
		throw ActivitateNotFoundException("Activitatea nu exista");
	this->service_basket.add_to_basket(this->repo.getAll()[v]);
}

vector <Activitate>& Service::get_basket() {
	return this->service_basket.get_basket();
}

Basket& Service::get_cos() {
	return this->service_basket;
}


void Service::delete_activitate_basket(const string& titlu) {
	vector<Activitate>& basket = this->service_basket.get_basket();
	if (basket.size() == 0)
		throw EmptyListException("Cosul este gol");
	auto it = find_if(basket.begin(), basket.end(), [&](const auto& activitate) { return activitate.getTitlu() == titlu; });
	if (it != basket.end()) {
		basket.erase(it);
	}
	else {
		throw ActivitateNotFoundException("Activitatea nu exista in cos");
	}
}

void Service::clear_basket() {
	if (this->service_basket.get_basket().size() == 0)
		throw EmptyListException("Cosul este gol");
	this->service_basket.clear_basket();
}

void Service::generate_activitati(int n) {
	if (this->repo.getAll().size() == 0)
		throw EmptyListException("Lista este goala");
	this->service_basket.generate_basket(n, this->repo.getAll());
}

void Service::export_basket(const string& filename) {
	if (this->service_basket.get_basket().size() == 0)
		throw EmptyListException("Cosul este gol");
	if (filename.length() < 4 || (filename.substr(filename.length() - 4) != ".csv" && filename.substr(filename.length() - 5) != ".html"))
		throw FileException("Numele fisierului este invalid");
	int v = this->service_basket.export_basket(filename);
	if (v == 0)
		throw FileException("Fisierul nu s-a putut deschide");
}

map<int, ActivitateDTO> Service::raport() {
	map<int, ActivitateDTO> m;
	vector<Activitate>& activitati = this->repo.getAll();
	for (const auto& a : activitati) {
		if (m.find(a.getDurata()) == m.end()) {
			m[a.getDurata()] = ActivitateDTO(a.getDurata(), 1);
		}
		else {
			m[a.getDurata()].increment_count();
		}
	}
	return m;
}


void Service::undo() {
	if (undoActions.size() == 0) {
		throw UndoException("Nu mai exista operatii de undo!");
	}
	std::cout << "Undo :" << undoActions.size() << std::endl;
	undoActions.back()->doUndo();
	undoActions.pop_back();
	std::cout << "Undo after : " << undoActions.size() << std::endl;
}
