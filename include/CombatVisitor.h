#ifndef LAB0_COMBATVISITOR_H
#define LAB0_COMBATVISITOR_H

#include "classVisitor.h"
#include "NPC.h"
#include "Observer.h"
#include <vector>

class CombatVisitor : public classVisitor {
    std::vector<NPC*> &npcs;
    float fightRange;
    Subject &subject;
    NPC *attacker;
public:
    CombatVisitor(std::vector<NPC*> &allNpcs, float range, Subject &subj);

    void Visit(Elf &elf) override;
    void Visit(Dragon &dragon) override;
    void Visit(Druid &druid) override;

private:
    bool CanAttack(const std::string &attackerType, const std::string &victimType);
    float Distance(NPC *a, NPC *b);
    void Fight(NPC *attacker, NPC *victim);
    void ExecuteFights(const std::string &attackerType);
};

#endif //LAB0_COMBATVISITOR_H
