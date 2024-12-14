#include "../../../include/NOWAY/CombatVisitor_v2.h"
#include "../../../include/Elf.h"
#include "../../../include/Dragon.h"
#include "../../../include/Druid.h"
#include <cmath>
#include <cstdlib>
#include <random>

CombatVisitor::CombatVisitor(std::vector<NPC*> &allNpcs, float range, Subject &subj, std::mutex &cmutex)
        : npcs(allNpcs), fightRange(range), subject(subj), attacker(nullptr), cout_mutex(cmutex) {}

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
    float dx = static_cast<float>(a->GetX() - b->GetX());
    float dy = static_cast<float>(a->GetY() - b->GetY());
    return std::sqrt(dx*dx + dy*dy);
}

void CombatVisitor::Fight(NPC *attacker, NPC *victim) {
    if (!attacker->IsAlive() || !victim->IsAlive()) return;

    // Бросаем кубики
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    int attackRoll = dis(gen);
    int defenseRoll = dis(gen);

    {
        std::lock_guard<std::mutex> lg(cout_mutex);
        std::cout << attacker->GetType() << " " << attacker->GetName()
                  << " атакует " << victim->GetType() << " " << victim->GetName()
                  << " (Атака: " << attackRoll << " vs Защита: " << defenseRoll << ")\n";
    }

    if (attackRoll > defenseRoll) {
        victim->Kill();
        subject.NotifyKill(attacker->GetType(), attacker->GetName(),
                           victim->GetType(), victim->GetName());
    }
}

void CombatVisitor::ExecuteFights(const std::string &attackerType) {
    if (!attacker || !attacker->IsAlive()) return;
    for (auto victim : npcs) {
        if (victim == attacker) continue;
        if (!victim->IsAlive()) continue;
        if (Distance(attacker, victim) <= fightRange && CanAttack(attackerType, victim->GetType())) {
            Fight(attacker, victim);
            if (!attacker->IsAlive()) break;
        }
    }
}
