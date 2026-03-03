#include "repository.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

Repository::Repository() {
    activitati = vector<Activitate>{};
    activitati.reserve(50); // Reserve space for efficiency
}

vector<Activitate>& Repository::getAll() {
    return activitati;
}

int Repository::add(const Activitate& a) {
    if (cauta(a.getTitlu()) != -1) {
        return 0; // Activity already exists
    }
    activitati.push_back(a);
    return 1; // Successfully added
}

int Repository::remove(const string& titlu) {
    auto it = find_if(activitati.begin(), activitati.end(), [&](const auto& activitate) {
        return activitate.getTitlu() == titlu;
        });
    if (it != activitati.end()) {
        activitati.erase(it);
        return 1; // Successfully removed
    }
    return 0; // Activity not found
}

int Repository::update(const Activitate& a) {
    int poz = cauta(a.getTitlu());
    if (poz == -1) {
        return 0; // Activity not found
    }
    activitati[poz] = Activitate(a);
    return 1; // Successfully updated
}

int Repository::cauta(const string& titlu) const {
    auto it = find_if(activitati.begin(), activitati.end(), [&](const auto& activitate) {
        return activitate.getTitlu() == titlu;
        });
    if (it != activitati.end()) {
        return static_cast<int>(it - activitati.begin());
    }
    return -1; // Activity not found
}
