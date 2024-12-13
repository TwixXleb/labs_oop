#ifndef LAB0_DRUID_H
#define LAB0_DRUID_H

#include "NPC.h"

class Druid : public NPC {
    std::string name;
    int x, y;
    bool alive;
public:
    Druid(const std::string &nm, int xx, int yy);
    std::string GetType() const override;
    std::string GetName() const override;
    int GetX() const override;
    int GetY() const override;
    void SetPosition(int xx, int yy) override;
    bool IsAlive() const override;
    void Kill() override;
    void Accept(classVisitor &visitor) override;
};

#endif //LAB0_DRUID_H
