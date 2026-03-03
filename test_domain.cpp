#include "domain.h"
#include "tests.h"
#include <iostream>
#include <assert.h>

using namespace std;

void testActivitate() {
    cout << "Running Activitate tests..." << endl;
    // Test default constructor
    Activitate a1;
    assert(a1.getTitlu() == "");
    assert(a1.getDescriere() == "");
    assert(a1.getTip() == "");
    assert(a1.getDurata() == 0);

    // Test parameterized constructor
    Activitate a2("titlu", "descriere", "tip", 10);
    assert(a2.getTitlu() == "titlu");
    assert(a2.getDescriere() == "descriere");
    assert(a2.getTip() == "tip");
    assert(a2.getDurata() == 10);

    // Test copy constructor
    Activitate a3(a2);
    assert(a3.getTitlu() == "titlu");
    assert(a3.getDescriere() == "descriere");
    assert(a3.getTip() == "tip");
    assert(a3.getDurata() == 10);

    // Test setters
    a3.setTitlu("titlu2");
    assert(a3.getTitlu() == "titlu2");

    a3.setDescriere("descriere2");
    assert(a3.getDescriere() == "descriere2");

    a3.setTip("tip2");
    assert(a3.getTip() == "tip2");

    a3.setDurata(20);
    assert(a3.getDurata() == 20);

    // Test assignment operator
    Activitate a4;
    a4 = a3;
    assert(a4.getTitlu() == "titlu2");
    assert(a4.getDescriere() == "descriere2");
    assert(a4.getTip() == "tip2");
    assert(a4.getDurata() == 20);

    // Test self-assignment
    a4 = a4;
    assert(a4.getTitlu() == "titlu2");
    assert(a4.getDescriere() == "descriere2");
    assert(a4.getTip() == "tip2");
    assert(a4.getDurata() == 20);

    // Test equality and inequality operators
    assert(a4 == a3);

}
