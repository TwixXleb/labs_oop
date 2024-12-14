#include "../../../include/NOWAY/CombatVisitor_v2.h"
#include "../../../include/Elf.h"
#include "../../../include/Dragon.h"
#include "../../../include/Druid.h"
#include <cmath>
#include <cstdlib>
#include <random>

CombatVisitor_v2::CombatVisitor_v2(std::vector<NPC*> &allNpcs, float range, Subject_v2 &subj, std::mutex &cmutex)
        : npcs_v2(allNpcs), fightRange_v2(range), subject_v2(subj), attacker_v2(nullptr), cout_mutex_v2(cmutex) {}

void CombatVisitor_v2::Visit(Elf &elf) {
    attacker_v2 = &elf;
    ExecuteFights_v2("Elf");
}

void CombatVisitor_v2::Visit(Dragon &dragon) {
    attacker_v2 = &dragon;
    ExecuteFights_v2("Dragon");
}

void CombatVisitor_v2::Visit(Druid &druid) {
    attacker_v2 = &druid;
    ExecuteFights_v2("Druid");
}

bool CombatVisitor_v2::CanAttack_v2(const std::string &attackerType, const std::string &victimType) {
    if (attackerType == "Dragon" && victimType == "Elf") return true;
    if (attackerType == "Elf" && victimType == "Druid") return true;
    if (attackerType == "Druid" && victimType == "Dragon") return true;
    return false;
}

float CombatVisitor_v2::Distance_v2(NPC *a, NPC *b) {
    float dx = static_cast<float>(a->GetX() - b->GetX());
    float dy = static_cast<float>(a->GetY() - b->GetY());
    return std::sqrt(dx * dx + dy * dy);
}

void CombatVisitor_v2::Fight_v2(NPC *attacker, NPC *victim) {
    if (!attacker->IsAlive() || !victim->IsAlive()) return;

    // Бросаем кубики
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    int attackRoll = dis(gen);
    int defenseRoll = dis(gen);

    {
        std::lock_guard<std::mutex> lg(cout_mutex_v2);
        std::cout << "[V2] " << attacker->GetType() << " " << attacker->GetName()
                  << " атакует " << victim->GetType() << " " << victim->GetName()
                  << " (Атака: " << attackRoll << " vs Защита: " << defenseRoll << ")\n";
    }

    if (attackRoll > defenseRoll) {
        victim->Kill();
        subject_v2.NotifyKill_v2(attacker->GetType(), attacker->GetName(),
                                 victim->GetType(), victim->GetName());
    }
}

void CombatVisitor_v2::ExecuteFights_v2(const std::string &attackerType) {
    if (!attacker_v2 || !attacker_v2->IsAlive()) return;
    for (auto victim : npcs_v2) {
        if (victim == attacker_v2) continue;
        if (!victim->IsAlive()) continue;
        if (Distance_v2(attacker_v2, victim) <= fightRange_v2 && CanAttack_v2(attackerType, victim->GetType())) {
            Fight_v2(attacker_v2, victim);
            if (!attacker_v2->IsAlive()) break;
        }
    }
}
