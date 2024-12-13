#ifndef LAB0_CLASSVISITOR_H
#define LAB0_CLASSVISITOR_H

class Elf;
class Dragon;
class Druid;

class classVisitor {
public:
    virtual ~classVisitor() {}
    virtual void Visit(Elf &elf) = 0;
    virtual void Visit(Dragon &dragon) = 0;
    virtual void Visit(Druid &druid) = 0;
};

#endif //LAB0_CLASSVISITOR_H
