#include "property.h"



template <typename Name, typename Type>
Type Property<Name, Type>::
operator()() const
{
    return con;
}

template <typename Name, typename Type>
void Property<Name, Type>::
operator()(const Type &t)
{
    con = t;
}


template <typename Name, typename Type>
Name Property<Name, Type>::
    name() const
{
    return nam;
}

template <typename Name, typename Type>
Property<Name, Type>::
    Property(){};

template <typename Name, typename Type>
Property<Name, Type>::
    Property(const Name n, const Type c)
{
    nam = n;
    con = c;
};

template <typename Name, typename Type>
Property<Name, Type>::
    Property(const Property<Name, Type> &source)
{
    nam = source.nam;
    con = source.con;
};

template <typename Name, typename Type>
bool Property<Name, Type>::
operator==(const Property<Name, Type> &prop2)
{
    if (prop2.con == con & prop2.nam == nam)
    {
        return true;
    }
    return false;
}

template <typename Name, typename Type>
void Property<Name, Type>::
    name(const Name &new_name)
{
    nam = new_name;
}


template class Property<string, float>;
template class Property<string, double>;

