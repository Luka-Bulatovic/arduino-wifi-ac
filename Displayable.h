// Displayable.h
#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

class Displayable {
  public:
    virtual ~Displayable() {} // Virtual destructor for polymorphism

    virtual String getDisplayData() = 0;
};

#endif