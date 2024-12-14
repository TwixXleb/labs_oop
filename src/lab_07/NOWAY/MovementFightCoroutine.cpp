#include "../../../include/NOWAY/MovementFightCoroutine.h"
#include "../../../include/NOWAY/CombatVisitor_v2.h"
#include <vector>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <chrono>
#include <atomic>
#include <random>
#include <iostream>

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;

Generator MovementFightCoroutine::run() {
    while (!stop) {
        co_await TimerAwaiter{std::chrono::milliseconds(100)};

        {
            std::unique_lock<std::shared_mutex> lock(npcMutex);

            for (auto npc : npcs) {
                if (!npc || !npc->IsAlive()) continue;

                int dx = rand() % 3 - 1;
                int dy = rand() % 3 - 1;
                int newX = npc->GetX() + dx;
                int newY = npc->GetY() + dy;

                newX = std::max(0, std::min(newX, MAP_WIDTH - 1));
                newY = std::max(0, std::min(newY, MAP_HEIGHT - 1));

                npc->SetPosition(newX, newY);
            }

            for (auto attacker : npcs) {
                if (!attacker || !attacker->IsAlive()) continue;

                for (auto victim : npcs) {
                    if (!victim || victim == attacker || !victim->IsAlive()) continue;

                    float dx = static_cast<float>(attacker->GetX() - victim->GetX());
                    float dy = static_cast<float>(attacker->GetY() - victim->GetY());
                    float distance = std::sqrt(dx * dx + dy * dy);

                    if (distance <= 3.0f) {
                        bool canAttack = false;
                        std::string aType = attacker->GetType();
                        std::string vType = victim->GetType();

                        if ((aType == "Dragon" && vType == "Elf") ||
                            (aType == "Elf" && vType == "Druid") ||
                            (aType == "Druid" && vType == "Dragon")) {
                            canAttack = true;
                        }

                        if (canAttack) {
                            CombatVisitor_v2 visitor(npcs, 3.0f, subject, cout_mutex);
                            attacker->Accept(visitor);
                        }
                    }
                }
            }
        }
    }
}
