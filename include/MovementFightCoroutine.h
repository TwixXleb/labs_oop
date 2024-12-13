#ifndef LAB0_MOVEMENTFIGHTCOROUTINE_H
#define LAB0_MOVEMENTFIGHTCOROUTINE_H

#include "NPC.h"
#include "Observer_v2.h"
#include "CombatVisitor_v2.h"
#include "CoroutineHelpers.h"
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <coroutine>

class MovementFightCoroutine {
public:
    MovementFightCoroutine(std::vector<NPC*> &npcs, Subject &subject, std::mutex &cout_mtx, std::shared_mutex &npc_mtx)
            : npcs(npcs), subject(subject), cout_mutex(cout_mtx), npcMutex(npc_mtx) {}

    Generator run();

    void stopCoroutine() {
        stop = true;
    }

private:
    std::vector<NPC*> &npcs;
    Subject &subject;
    std::mutex &cout_mutex;
    std::shared_mutex &npcMutex;
    std::atomic<bool> stop{false};
    static const int MAP_WIDTH = 100;
    static const int MAP_HEIGHT = 100;
};

#endif //LAB0_MOVEMENTFIGHTCOROUTINE_H
