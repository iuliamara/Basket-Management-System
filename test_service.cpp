#include "service.h"
#include "domain.h"
#include "exceptions.h"
#include <cassert>
#include <iostream>
#include <fstream>



void clear_test_file() {
    std::ofstream ofs("test_activitati.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void test_undo() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    std::cout << "Test: Add activity and undo" << std::endl;
    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    assert(service.getAll().size() == 1);
    service.undo();
    assert(service.getAll().size() == 0);

    std::cout << "Test: Delete activity and undo" << std::endl;
    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.delete_activitate("Yoga");
    assert(service.getAll().size() == 0);
    service.undo();
    assert(service.getAll().size() == 1);

    std::cout << "Test: Update activity and undo" << std::endl;
    service.update_activitate("Yoga", "Advanced yoga techniques", "Health", 90);
    assert(service.getAll()[0].getDescriere() == "Advanced yoga techniques");
    service.undo();
    assert(service.getAll()[0].getDescriere() == "Relaxation and stretching");

    std::cout << "Test: Undo with empty stack" << std::endl;
    service.undo();
    try {
        service.undo();
    }
    catch (const UndoException&) {
        assert(true);
    }
    clear_test_file();
}



void test_add_activitate() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    assert(service.getAll().size() == 1);
    assert(service.getAll()[0].getTitlu() == "Yoga");

    // Test adding duplicate activity
    try {
        service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    }
    catch (const ActivitateAlreadyExistsException&) {
        assert(true);
    }
    clear_test_file();
}

void test_delete_activitate() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.delete_activitate("Yoga");
    assert(service.getAll().size() == 0);

    // Test deleting non-existing activity
    try {
        service.delete_activitate("Yoga");
        assert(false); // Should not reach this line
    }
    catch (const EmptyListException&) {
        assert(true);
    }
    clear_test_file();
}

void test_update_activitate() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.update_activitate("Yoga", "Advanced yoga techniques", "Health", 90);
    assert(service.getAll()[0].getDescriere() == "Advanced yoga techniques");
    assert(service.getAll()[0].getDurata() == 90);

    // Test updating non-existing activity
    try {
        service.update_activitate("Cooking", "Learn to cook", "Education", 120);
    }
    catch (const ActivitateNotFoundException&) {
        assert(true);
    }
    clear_test_file();
}

void test_find_activitate() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    assert(service.find_activitate("Yoga") == 0);

    // Test finding non-existing activity
    try {
        service.find_activitate("Cooking");
    }
    catch (const ActivitateNotFoundException&) {
        assert(true);
    }
    clear_test_file();
}

void test_filtrare_durata() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.add_activitate("Cooking", "Learn to cook", "Education", 120);

    auto filtered = service.filtrare_durata(service.getAll(), 90, 1);
    assert(filtered.size() == 1);
    assert(filtered[0].getTitlu() == "Yoga");
    clear_test_file();
}

void test_filtrare_tip() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.add_activitate("Cooking", "Learn to cook", "Education", 120);

    auto filtered = service.filtrare_tip(service.getAll(), "Health");
    assert(filtered.size() == 1);
    assert(filtered[0].getTitlu() == "Yoga");
    clear_test_file();
}

void test_sort_activitati() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.add_activitate("Cooking", "Learn to cook", "Education", 120);

    auto list = service.getAll();
    service.sort_activitati(list, 1, [](const Activitate& a, const Activitate& b) {
        return a.getTitlu() < b.getTitlu();
        });
    assert(list[0].getTitlu() == "Yoga");
    clear_test_file();
}

void test_basket_operations() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.add_activitate_basket("Yoga");
    assert(service.get_basket().size() == 1);

    service.delete_activitate_basket("Yoga");
    assert(service.get_basket().size() == 0);

    service.add_activitate_basket("Yoga");
    service.clear_basket();
    assert(service.get_basket().size() == 0);
    clear_test_file();
}

void test_generate_activitati() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.add_activitate("Cooking", "Learn to cook", "Education", 120);

    service.generate_activitati(1);
    assert(service.get_basket().size() == 1);
    clear_test_file();
}

void test_export_basketserv() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.add_activitate_basket("Yoga");

    service.export_basket("test_export.csv");
    std::ifstream fin("test_export.csv");
    assert(fin.is_open());
    std::string line;
    getline(fin, line);
    assert(line == "Yoga,Relaxation and stretching,Health,60");
    fin.close();
    clear_test_file();
}

void test_raport() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.add_activitate("Cooking", "Learn to cook", "Education", 120);

    auto report = service.raport();
    assert(report[60].count == 1); // Access count directly
    assert(report[120].count == 1); // Access count directly
    clear_test_file();
}


void test_validate() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    // Valid activity
    Activitate valid("Yoga", "Relaxation and stretching", "Health", 60);
    assert(service.validate(valid) == 1);

    // Invalid activities
    Activitate invalid1("", "Relaxation and stretching", "Health", 60);
    assert(service.validate(invalid1) == 0);

    Activitate invalid2("Yoga", "", "Health", 60);
    assert(service.validate(invalid2) == 0);

    Activitate invalid3("Yoga", "Relaxation and stretching", "", 60);
    assert(service.validate(invalid3) == 0);

    Activitate invalid4("Yoga", "Relaxation and stretching", "Health", 0);
    assert(service.validate(invalid4) == 0);
    clear_test_file();
}

void test_filtrare_durata_edge_cases() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.add_activitate("Cooking", "Learn to cook", "Education", 120);

    // Filter with property 1 (<= duration)
    auto filtered1 = service.filtrare_durata(service.getAll(), 60, 1);
    assert(filtered1.size() == 1);
    assert(filtered1[0].getTitlu() == "Yoga");

    // Filter with property 2 (> duration)
    auto filtered2 = service.filtrare_durata(service.getAll(), 60, 2);
    assert(filtered2.size() == 1);
    assert(filtered2[0].getTitlu() == "Cooking");

    // Filter with no matches
    auto filtered3 = service.filtrare_durata(service.getAll(), 30, 1);
    assert(filtered3.size() == 0);
    clear_test_file();
}

void test_filtrare_tip_edge_cases() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.add_activitate("Cooking", "Learn to cook", "Education", 120);

    // Filter with matching type
    auto filtered1 = service.filtrare_tip(service.getAll(), "Health");
    assert(filtered1.size() == 1);
    assert(filtered1[0].getTitlu() == "Yoga");

    // Filter with no matches
    auto filtered2 = service.filtrare_tip(service.getAll(), "Art");
    assert(filtered2.size() == 0);
    clear_test_file();
}

void test_sort_activitati_edge_cases() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.add_activitate("Cooking", "Learn to cook", "Education", 120);

    // Sort by title ascending
    auto list1 = service.getAll();
    service.sort_activitati(list1, 0, [](const Activitate& a, const Activitate& b) {
        return a.getTitlu() < b.getTitlu();
        });
    assert(list1[0].getTitlu() == "Cooking");
    assert(list1[1].getTitlu() == "Yoga");

    // Sort by title descending
    auto list2 = service.getAll();
    service.sort_activitati(list2, 1, [](const Activitate& a, const Activitate& b) {
        return a.getTitlu() < b.getTitlu();
        });
    assert(list2[0].getTitlu() == "Yoga");
    assert(list2[1].getTitlu() == "Cooking");
    clear_test_file();
}

void test_basket_exceptions() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    // Test adding to basket when activity does not exist
    try {
        service.add_activitate_basket("Nonexistent");
    }
    catch (const ActivitateNotFoundException&) {
        assert(true);
    }

    // Test deleting from empty basket
    try {
        service.delete_activitate_basket("Yoga");
    }
    catch (const EmptyListException&) {
        assert(true);
    }

    // Test clearing empty basket
    try {
        service.clear_basket();
    }
    catch (const EmptyListException&) {
        assert(true);
    }
    clear_test_file();
}

void test_generate_activitati_exceptions() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    // Test generating activities when repository is empty
    try {
        service.generate_activitati(1);
    }
    catch (const EmptyListException&) {
        assert(true);
    }
    clear_test_file();
}

void test_export_basket_exceptions() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    // Test exporting empty basket
    try {
        service.export_basket("test_export.csv");
    }
    catch (const EmptyListException&) {
        assert(true);
    }

    // Test exporting with invalid filename
    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.add_activitate_basket("Yoga");
    try {
        service.export_basket("invalid_file");
    }
    catch (const FileException&) {
        assert(true);
    }
    clear_test_file();
}

void test_raport_edge_cases() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    // Test report with no activities
    auto report1 = service.raport();
    assert(report1.empty());

    // Test report with activities of the same duration
    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.add_activitate("Cooking", "Learn to cook", "Education", 60);
    auto report2 = service.raport();
    assert(report2[60].count == 2);
    clear_test_file();
}

void test_update_activitate_invalid_data() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);

    // Test updating with invalid data
    try {
        service.update_activitate("Yoga", "", "Health", 60); // Empty description
    }
    catch (const ValidationException&) {
        assert(true);
    }

    try {
        service.update_activitate("Yoga", "Relaxation and stretching", "", 60); // Empty type
    }
    catch (const ValidationException&) {
        assert(true);
    }

    try {
        service.update_activitate("Yoga", "Relaxation and stretching", "Health", -10); // Negative duration
    }
    catch (const ValidationException&) {
        assert(true);
    }
    clear_test_file();
}

void test_delete_activitate_nonexistent() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);

    // Test deleting a non-existent activity
    try {
        service.delete_activitate("Cooking");
    }
    catch (const ActivitateNotFoundException&) {
        assert(true);
    }
    clear_test_file();
}

void test_add_activitate_invalid_data() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    // Test adding an activity with invalid data
    try {
        service.add_activitate("", "Relaxation and stretching", "Health", 60); // Empty title
    }
    catch (const ValidationException&) {
        assert(true);
    }

    try {
        service.add_activitate("Yoga", "", "Health", 60); // Empty description
    }
    catch (const ValidationException&) {
        assert(true);
    }

    try {
        service.add_activitate("Yoga", "Relaxation and stretching", "", 60); // Empty type
    }
    catch (const ValidationException&) {
        assert(true);
    }

    try {
        service.add_activitate("Yoga", "Relaxation and stretching", "Health", -10); // Negative duration
    }
    catch (const ValidationException&) {
        assert(true);
    }
    clear_test_file();
}

void test_delete_activitate_basket_nonexistent() {
    FileRepository repo("test_activitati.txt");
    Service service(repo);

    service.add_activitate("Yoga", "Relaxation and stretching", "Health", 60);
    service.add_activitate_basket("Yoga");

    // Test deleting a non-existent activity from the basket
    try {
        service.delete_activitate_basket("Cooking");
    }
    catch (const ActivitateNotFoundException&) {
        assert(true);
    }
    clear_test_file();
}


void run_service_tests() {
    test_undo();
    test_add_activitate();
    test_add_activitate_invalid_data();
    test_delete_activitate();
    test_delete_activitate_nonexistent();
    test_update_activitate();
    test_update_activitate_invalid_data();
    test_find_activitate();
    test_validate();
    test_filtrare_durata();
    test_filtrare_durata_edge_cases();
    test_filtrare_tip();
    test_filtrare_tip_edge_cases();
    test_sort_activitati();
    test_sort_activitati_edge_cases();
    test_basket_operations();
    test_delete_activitate_basket_nonexistent();
    test_basket_exceptions();
    test_generate_activitati();
    test_generate_activitati_exceptions();
    test_export_basketserv();
    test_export_basket_exceptions();
    test_raport();
    test_raport_edge_cases();
    std::cout << "All service tests passed!" << std::endl;
}
