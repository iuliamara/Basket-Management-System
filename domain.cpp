#include "domain.h"
#include <stdexcept> 
#include <iostream>

using namespace std;

int Activitate::ccount = 0;

Activitate::Activitate() : titlu(""), descriere(""), tip(""), durata(0) {
    ccount++;
}

Activitate::Activitate(const std::string& titlu, const std::string& descriere, const std::string& tip, const int& durata)
    : titlu(titlu), descriere(descriere), tip(tip), durata(durata) {
}

Activitate::Activitate(const Activitate& a) : titlu(a.titlu), descriere(a.descriere), tip(a.tip), durata(a.durata) {
    cout << "S-a facut copiere!" << endl;
}

Activitate::~Activitate() {}

std::string Activitate::getTitlu() const {
    return titlu;
}

std::string Activitate::getDescriere() const {
    return descriere;
}

std::string Activitate::getTip() const {
    return tip;
}

int Activitate::getDurata() const {
    return durata;
}



bool Activitate::operator==(const Activitate& other) const {
    return (this->titlu == other.titlu &&
        this->descriere == other.descriere &&
        this->tip == other.tip &&
        this->durata == other.durata);
}

Activitate::Activitate(Activitate&& other) noexcept
    : titlu(std::move(other.titlu)),
    descriere(std::move(other.descriere)),
    tip(std::move(other.tip)),
    durata(other.durata) {
}

Activitate& Activitate::operator=(const Activitate& other) {
    if (this == &other) {
        return *this; // Handle self-assignment
    }
    titlu = other.titlu;
    descriere = other.descriere;
    tip = other.tip;
    durata = other.durata;
    return *this;
}


Activitate& Activitate::operator=(Activitate&& other) noexcept {
    if (this == &other) return *this;

    titlu = std::move(other.titlu);
    descriere = std::move(other.descriere);
    tip = std::move(other.tip);
    durata = other.durata;

    return *this;
}
