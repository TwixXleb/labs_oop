#include "../../include/Elf.h"
#include "../../include/classVisitor.h"

Elf::Elf(const std::string &nm, int xx, int yy) : name(nm), x(xx), y(yy), alive(true) {}
std::string Elf::GetType() const { return "Elf"; }
std::string Elf::GetName() const { return name; }
int Elf::GetX() const { return x; }
int Elf::GetY() const { return y; }
void Elf::SetPosition(int xx, int yy) { x = xx; y = yy; }
bool Elf::IsAlive() const { return alive; }
void Elf::Kill() { alive = false; }
void Elf::Accept(classVisitor &visitor) { visitor.Visit(*this); }