#ifndef LAB0_UTILS_H
#define LAB0_UTILS_H

#include "NPC.h"
#include <vector>
#include <string>

void SaveToFile(const std::string &filename, const std::vector<NPC*> &npcs);
void LoadFromFile(const std::string &filename, std::vector<NPC*> &npcs);
void PrintNPCs(const std::vector<NPC*> &npcs);

#endif //LAB0_UTILS_H
