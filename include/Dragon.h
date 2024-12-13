#ifndef LAB0_DRAGON_H
#define LAB0_DRAGON_H

#include "NPC.h"

class Dragon : public NPC {
    std::string name;
    int x, y;
    bool alive;
public:
    Dragon(const std::string &nm, int xx, int yy);
    std::string GetType() const override;
    std::string GetName() const override;
    int GetX() const override;
    int GetY() const override;
    void SetPosition(int xx, int yy) override;
    bool IsAlive() const override;
    void Kill() override;
    void Accept(classVisitor &visitor) override;
};

#endif //LAB0_DRAGON_H
