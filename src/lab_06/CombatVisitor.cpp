#include "../../include/CombatVisitor.h"
#include "../../include/Elf.h"
#include "../../include/Dragon.h"
#include "../../include/Druid.h"
#include <cmath>

CombatVisitor::CombatVisitor(std::vector<NPC*> &allNpcs, float range, Subject &subj)
        : npcs(allNpcs), fightRange(range), subject(subj), attacker(nullptr) {}

void CombatVisitor::Visit(Elf &elf) {
    attacker = &elf;
    ExecuteFights("Elf");
}

void CombatVisitor::Visit(Dragon &dragon) {
    attacker = &dragon;
    ExecuteFights("Dragon");
}

void CombatVisitor::Visit(Druid &druid) {
    attacker = &druid;
    ExecuteFights("Druid");
}

bool CombatVisitor::CanAttack(const std::string &attackerType, const std::string &victimType) {
    if (attackerType == "Dragon" && victimType == "Elf") return true;
    if (attackerType == "Elf" && victimType == "Druid") return true;
    if (attackerType == "Druid" && victimType == "Dragon") return true;
    return false;
}

float CombatVisitor::Distance(NPC *a, NPC *b) {
    float dx = (float)(a->GetX() - b->GetX());
    float dy = (float)(a->GetY() - b->GetY());
    return std::sqrt(dx*dx + dy*dy);
}

void CombatVisitor::Fight(NPC *attacker, NPC *victim) {
    if (!attacker->IsAlive() || !victim->IsAlive()) return;
    victim->Kill();
    subject.NotifyKill(attacker->GetType(), attacker->GetName(),
                       victim->GetType(), victim->GetName());

    attacker->Kill();
    subject.NotifyKill(victim->GetType(), victim->GetName(),
                       attacker->GetType(), attacker->GetName());
}

void CombatVisitor::ExecuteFights(const std::string &attackerType) {
    if (!attacker || !attacker->IsAlive()) return;
    for (auto victim : npcs) {
        if (victim == attacker) continue;
        if (!victim->IsAlive()) continue;
        if (Distance(attacker, victim) <= fightRange &&
            CanAttack(attackerType, victim->GetType())) {
            Fight(attacker, victim);
            if (!attacker->IsAlive()) break;
        }
    }
}