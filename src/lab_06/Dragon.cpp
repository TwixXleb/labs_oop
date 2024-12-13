#include "../../include/Dragon.h"
#include "../../include/classVisitor.h"

Dragon::Dragon(const std::string &nm, int xx, int yy) : name(nm), x(xx), y(yy), alive(true) {}
std::string Dragon::GetType() const { return "Dragon"; }
std::string Dragon::GetName() const { return name; }
int Dragon::GetX() const { return x; }
int Dragon::GetY() const { return y; }
void Dragon::SetPosition(int xx, int yy) { x = xx; y = yy; }
bool Dragon::IsAlive() const { return alive; }
void Dragon::Kill() { alive = false; }
void Dragon::Accept(classVisitor &visitor) { visitor.Visit(*this); }