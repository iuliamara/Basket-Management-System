#include "undo.h"

UndoAdauga::UndoAdauga(Repository& repo, const Activitate& act)
    : repo{ repo }, activitate{ act } {
}

void UndoAdauga::doUndo() {
    repo.remove(activitate.getTitlu());
}

UndoSterge::UndoSterge(Repository& repo, const Activitate& act)
    : repo{ repo }, activitate{ act } {
}

void UndoSterge::doUndo() {
    repo.add(activitate);
}

UndoModifica::UndoModifica(Repository& repo, const Activitate& actVeche)
    : repo{ repo }, activitateVeche{ actVeche } {
}

void UndoModifica::doUndo() {
    repo.update(activitateVeche);
}
