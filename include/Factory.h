#ifndef LAB0_FACTORY_H
#define LAB0_FACTORY_H

#include "NPC.h"
#include <string>

class NPCFactory {
public:
    static NPC* CreateNPC(const std::string &type, const std::string &name, int x, int y);
};

#endif //LAB0_FACTORY_H
