

#include "basket.h"
#include "domain.h"
#include "tests.h"
#include <assert.h>
#include <vector>
#include <fstream>

void test_add_basket() {
    Basket b;
    Activitate a1("Yoga", "Relaxation and stretching", "Health", 60);
    Activitate a2("Cooking", "Learn to cook Italian dishes", "Education", 120);
    b.add_to_basket(a1);
    b.add_to_basket(a2);
    assert(b.get_basket().size() == 2);
    assert(b.get_basket()[0].getTitlu() == "Yoga");
    assert(b.get_basket()[1].getTitlu() == "Cooking");
}

void test_delete_basket() {
    Basket b;
    Activitate a1("Yoga", "Relaxation and stretching", "Health", 60);
    Activitate a2("Cooking", "Learn to cook Italian dishes", "Education", 120);
    b.add_to_basket(a1);
    b.add_to_basket(a2);
    std::string titlu = a1.getTitlu();
    b.remove_from_basket(titlu);
    assert(b.get_basket().size() == 1);
    assert(b.get_basket()[0].getTitlu() == "Cooking");
}

void test_clear_basket() {
    Basket b;
    Activitate a1("Yoga", "Relaxation and stretching", "Health", 60);
    Activitate a2("Cooking", "Learn to cook Italian dishes", "Education", 120);
    b.add_to_basket(a1);
    b.add_to_basket(a2);
    b.clear_basket();
    assert(b.get_basket().size() == 0);
}

void test_generate_basket() {
    Basket b;
    std::vector<Activitate> lista;
    lista.push_back(Activitate("Yoga", "Relaxation and stretching", "Health", 60));
    lista.push_back(Activitate("Cooking", "Learn to cook Italian dishes", "Education", 120));
    lista.push_back(Activitate("Painting", "Learn watercolor techniques", "Art", 90));
    b.generate_basket(2, lista);
    assert(b.get_basket().size() == 2);
}

void test_export_basket() {
    Basket b;
    Activitate a1("Yoga", "Relaxation and stretching", "Health", 60);
    Activitate a2("Cooking", "Learn to cook Italian dishes", "Education", 120);
    b.add_to_basket(a1);
    b.add_to_basket(a2);
    int result = b.export_basket("test_export.csv");
    assert(result == 1);
    std::ifstream fin("test_export.csv");
    assert(fin.is_open());
    std::string line;
    getline(fin, line);
    assert(line == "Yoga,Relaxation and stretching,Health,60");
    getline(fin, line);
    assert(line == "Cooking,Learn to cook Italian dishes,Education,120");
    fin.close();
}
