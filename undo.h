#pragma once
#include "domain.h"
#include "repository.h"

class UndoAction {
public:
    virtual void doUndo() = 0;
    virtual ~UndoAction() = default;
};

class UndoAdauga : public UndoAction {
    Activitate activitate;
    Repository& repo;
public:
    UndoAdauga(Repository& repo, const Activitate& act);
    void doUndo() override;
};

class UndoSterge : public UndoAction {
    Activitate activitate;
    Repository& repo;
public:
    UndoSterge(Repository& repo, const Activitate& act);
    void doUndo() override;
};

class UndoModifica : public UndoAction {
    Activitate activitateVeche;
    Repository& repo;
public:
    UndoModifica(Repository& repo, const Activitate& actVeche);
    void doUndo() override;
};
