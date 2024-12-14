#ifndef LAB0_COMBATVISITOR_V2_H
#define LAB0_COMBATVISITOR_V2_H

#include "../classVisitor.h"
#include "../NPC.h"
#include "Observer_v2.h"
#include <vector>
#include <mutex>

class CombatVisitor_v2 : public classVisitor {
    std::vector<NPC*> &npcs_v2;
    float fightRange_v2;
    Subject_v2 &subject_v2;
    NPC *attacker_v2;
    std::mutex &cout_mutex_v2;
public:
    CombatVisitor_v2(std::vector<NPC*> &allNpcs, float range, Subject_v2 &subj, std::mutex &cmutex);

    void Visit(Elf &elf) override;
    void Visit(Dragon &dragon) override;
    void Visit(Druid &druid) override;

private:
    bool CanAttack_v2(const std::string &attackerType, const std::string &victimType);
    float Distance_v2(NPC *a, NPC *b);
    void Fight_v2(NPC *attacker, NPC *victim);
    void ExecuteFights_v2(const std::string &attackerType);
};

#endif //LAB0_COMBATVISITOR_V2_H
