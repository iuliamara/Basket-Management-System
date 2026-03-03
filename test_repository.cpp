#include "repository.h"
#include "domain.h"
#include <cassert>
#include <iostream>

void test_add() {
    Repository repo;
    Activitate a1("Yoga", "Relaxation and stretching", "Health", 60);
    Activitate a2("Cooking", "Learn to cook Italian dishes", "Education", 120);

    // Add activities
    assert(repo.add(a1) == 1);
    assert(repo.add(a2) == 1);

    // Attempt to add duplicate activity
    assert(repo.add(a1) == 0);

    // Verify activities are added
    assert(repo.getAll().size() == 2);
    assert(repo.getAll()[0].getTitlu() == "Yoga");
    assert(repo.getAll()[1].getTitlu() == "Cooking");
}

void test_remove() {
    Repository repo;
    Activitate a1("Yoga", "Relaxation and stretching", "Health", 60);
    Activitate a2("Cooking", "Learn to cook Italian dishes", "Education", 120);

    repo.add(a1);
    repo.add(a2);

    // Remove existing activity
    assert(repo.remove("Yoga") == 1);
    assert(repo.getAll().size() == 1);
    assert(repo.getAll()[0].getTitlu() == "Cooking");

    // Attempt to remove non-existing activity
    assert(repo.remove("Yoga") == 0);
}

void test_update() {
    Repository repo;
    Activitate a1("Yoga", "Relaxation and stretching", "Health", 60);
    Activitate a2("Cooking", "Learn to cook Italian dishes", "Education", 120);
    Activitate a3("Yoga", "Advanced yoga techniques", "Health", 90);

    repo.add(a1);
    repo.add(a2);

    // Update existing activity
    assert(repo.update(a3) == 1);
    assert(repo.getAll()[0].getDescriere() == "Advanced yoga techniques");
    assert(repo.getAll()[0].getDurata() == 90);

    // Attempt to update non-existing activity
    Activitate a4("Painting", "Learn watercolor techniques", "Art", 120);
    assert(repo.update(a4) == 0);
}

void test_cauta() {
    Repository repo;
    Activitate a1("Yoga", "Relaxation and stretching", "Health", 60);
    Activitate a2("Cooking", "Learn to cook Italian dishes", "Education", 120);

    repo.add(a1);
    repo.add(a2);

    // Search for existing activities
    assert(repo.cauta("Yoga") == 0);
    assert(repo.cauta("Cooking") == 1);

    // Search for non-existing activity
    assert(repo.cauta("Painting") == -1);
}

void test_getAll() {
    Repository repo;
    Activitate a1("Yoga", "Relaxation and stretching", "Health", 60);
    Activitate a2("Cooking", "Learn to cook Italian dishes", "Education", 120);

    repo.add(a1);
    repo.add(a2);

    // Verify all activities are retrieved
    const auto& all = repo.getAll();
    assert(all.size() == 2);
    assert(all[0].getTitlu() == "Yoga");
    assert(all[1].getTitlu() == "Cooking");
}

void run_repository_tests() {
    test_add();
    test_remove();
    test_update();
    test_cauta();
    test_getAll();
    std::cout << "All repository tests passed!" << std::endl;
}
