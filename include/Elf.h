#ifndef LAB0_ELF_H
#define LAB0_ELF_H

#include "NPC.h"

class Elf : public NPC {
    std::string name;
    int x, y;
    bool alive;
public:
    Elf(const std::string &nm, int xx, int yy);
    std::string GetType() const override;
    std::string GetName() const override;
    int GetX() const override;
    int GetY() const override;
    void SetPosition(int xx, int yy) override;
    bool IsAlive() const override;
    void Kill() override;
    void Accept(classVisitor &visitor) override;
};

#endif //LAB0_ELF_H
