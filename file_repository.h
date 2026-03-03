#pragma once
#include "repository.h"
#include <string>

class FileRepository : public Repository {
private:
    std::string filename;

    void loadFromFile();
    void writeToFile();

public:
    FileRepository(const std::string& file);

    int add(const Activitate& activ) override;
    int remove(const std::string& titlu) override;
    int update(const Activitate& activ) override;
};
