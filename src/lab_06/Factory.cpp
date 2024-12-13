#include "../../include/Factory.h"
#include "../../include/Elf.h"
#include "../../include/Dragon.h"
#include "../../include/Druid.h"

NPC* NPCFactory::CreateNPC(const std::string &type, const std::string &name, int x, int y) {
    if (type == "Elf") return new Elf(name, x, y);
    if (type == "Dragon") return new Dragon(name, x, y);
    if (type == "Druid") return new Druid(name, x, y);
    return nullptr;
}