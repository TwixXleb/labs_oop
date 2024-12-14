#ifndef LAB0_COMBATVISITOR_V2_H
#define LAB0_COMBATVISITOR_V2_H

#include "../classVisitor.h"
#include "../NPC.h"
#include "Observer_v2.h"
#include <vector>
#include <mutex>

class CombatVisitor : public classVisitor {
    std::vector<NPC*> &npcs;
    float fightRange;
    Subject &subject;
    NPC *attacker;
    std::mutex &cout_mutex;
public:
    CombatVisitor(std::vector<NPC*> &allNpcs, float range, Subject &subj, std::mutex &cmutex);

    void Visit(Elf &elf) override;
    void Visit(Dragon &dragon) override;
    void Visit(Druid &druid) override;

private:
    bool CanAttack(const std::string &attackerType, const std::string &victimType);
    float Distance(NPC *a, NPC *b);
    void Fight(NPC *attacker, NPC *victim);
    void ExecuteFights(const std::string &attackerType);
};

#endif //LAB0_COMBATVISITOR_V2_H
