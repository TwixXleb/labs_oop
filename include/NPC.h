#ifndef LAB0_NPC_H
#define LAB0_NPC_H

#include <string>

class classVisitor;

class NPC {
public:
    virtual ~NPC() {}
    virtual std::string GetType() const = 0;
    virtual std::string GetName() const = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
    virtual void SetPosition(int x, int y) = 0;
    virtual bool IsAlive() const = 0;
    virtual void Kill() = 0;
    virtual void Accept(classVisitor &visitor) = 0;
};

#endif //LAB0_NPC_H
