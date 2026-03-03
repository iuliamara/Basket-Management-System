
#include <QApplication>
#include "GUI.h"
#include "service.h"
#include "repository.h"
#include "tests.h"

int main(int argc, char* argv[]) {
    test_add_basket();
    test_delete_basket();
    test_clear_basket();
    test_generate_basket();
    test_export_basket();
    testActivitate();
    run_repository_tests();
    run_service_tests();

    QApplication a(argc, argv);
    FileRepository repo("activitati.txt");
    Service srv{ repo };
    ActivitateGUI gui{ srv };
    gui.show();
    return a.exec();
}
