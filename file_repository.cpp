#include "file_repository.h"
#include <fstream>
#include <sstream>

FileRepository::FileRepository(const std::string& file) : filename{ file } {
    loadFromFile();
}

void FileRepository::loadFromFile() {
    std::ifstream in(filename);
    if (!in.is_open()) return;
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string titlu, descriere, tip;
        int durata;
        std::getline(iss, titlu, ',');
        std::getline(iss, descriere, ',');
        std::getline(iss, tip, ',');
        iss >> durata;
        Repository::add(Activitate(titlu, descriere, tip, durata));
    }
    in.close();
}

void FileRepository::writeToFile() {
    std::ofstream out(filename);
    for (const auto& a : getAll()) {
        out << a.getTitlu() << "," << a.getDescriere() << "," << a.getTip() << "," << a.getDurata() << "\n";
    }
    out.close();
}

int FileRepository::add(const Activitate& activ) {
    int rezultat = Repository::add(activ);
    writeToFile();
    return rezultat;
}

int FileRepository::remove(const std::string& titlu) {
    int rezultat = Repository::remove(titlu);
    writeToFile();
    return rezultat;
}

int FileRepository::update(const Activitate& activ) {
    int rezultat = Repository::update(activ);
    writeToFile();
    return rezultat;
}
