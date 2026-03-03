#pragma once
#include <string>
#include <iostream>

class ActivitateDTO {
public:
    int durata, count;
    ActivitateDTO(int d, int c) : durata(d), count(c) {}
    /*
    * defineste un film cu atribute
    */
    ActivitateDTO() : count(0) {}
    void increment_count() {
        count++;
    }
};

class Activitate {
private:
    std::string titlu;
    std::string descriere;
    std::string tip;
    int durata;

public:
    static int ccount;
    Activitate(); // constructor implicit
    Activitate(const std::string& titlu, const std::string& descriere, const std::string& tip, const int& durata); // constructor cu parametri
    Activitate(const Activitate& a); // constructor de copiere
    ~Activitate(); // destructor
    std::string getTitlu() const; // getter pentru titlu
    std::string getDescriere() const; // getter pentru descriere
    std::string getTip() const; // getter pentru tip
    int getDurata() const; // getter pentru durata
    void setTitlu(const std::string& titlu1) {
        titlu = titlu1;
    } // setter pentru titlu
    void setDescriere(const std::string& descriere1) {
        descriere = descriere1;
    } // setter pentru descriere
    void setTip(const std::string& tip1) {
        tip = tip1;
    } // setter pentru tip
    void setDurata(const int& durata1) {
        durata = durata1;
    } // setter pentru durata

    Activitate& operator=(const Activitate& other);

    bool operator ==(const Activitate& other) const;
    /*
    * defineste operatorul de egalitate
    * return: true daca cele doua activitati sunt egale, false altfel
    */

    Activitate(Activitate&& other) noexcept;
    /*
    * constructorul de mutare
    * other: Activitatea de mutat
    */

    Activitate& operator=(Activitate&& other) noexcept;
    /*
    * defineste operatorul de asignare
    * other: activitatea de mutat
    * return: activitatea mutat
    */

};
