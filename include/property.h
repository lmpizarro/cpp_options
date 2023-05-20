// property.h
//
// Base class for Properties. This is a concrete class.
//
//
#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

using namespace std;

template <typename Name=string, typename Type=double>
class Property
{
private:
    Name nam;
    Type con;

public:
    Property(const Name n, const Type c);
    Property();
    Property(const Property<Name, Type> &source);
    virtual Type operator()() const;
    virtual void operator()(const Type &t);
    virtual Name name() const;
    bool operator==(const Property<Name, Type> &prop2);
    virtual void name(const Name &new_name);
};

#endif