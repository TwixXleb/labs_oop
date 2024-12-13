#include "../../include/Utils.h"
#include "../../include/Factory.h"
#include <iostream>
#include <fstream>

void SaveToFile(const std::string &filename, const std::vector<NPC*> &npcs) {
    std::ofstream ofs(filename);
    for (auto npc : npcs) {
        ofs << npc->GetType() << " " << npc->GetName() << " " << npc->GetX() << " " << npc->GetY() << "\n";
    }
}

void LoadFromFile(const std::string &filename, std::vector<NPC*> &npcs) {
    std::ifstream ifs(filename);
    std::string type, name;
    int x, y;
    while (ifs >> type >> name >> x >> y) {
        NPC *obj = NPCFactory::CreateNPC(type, name, x, y);
        if (obj) npcs.push_back(obj);
    }
}

void PrintNPCs(const std::vector<NPC*> &npcs) {
    for (auto npc : npcs) {
        std::cout << npc->GetType() << " " << npc->GetName()
                  << " [" << npc->GetX() << "," << npc->GetY() << "] "
                  << (npc->IsAlive() ? "Alive" : "Dead") << "\n";
    }
}
