#include "../../include/Druid.h"
#include "../../include/classVisitor.h"

Druid::Druid(const std::string &nm, int xx, int yy) : name(nm), x(xx), y(yy), alive(true) {}
std::string Druid::GetType() const { return "Druid"; }
std::string Druid::GetName() const { return name; }
int Druid::GetX() const { return x; }
int Druid::GetY() const { return y; }
void Druid::SetPosition(int xx, int yy) { x = xx; y = yy; }
bool Druid::IsAlive() const { return alive; }
void Druid::Kill() { alive = false; }
void Druid::Accept(classVisitor &visitor) { visitor.Visit(*this); }