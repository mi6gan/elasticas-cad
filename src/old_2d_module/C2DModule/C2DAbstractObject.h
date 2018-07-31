#ifndef C2DABSTRACTOBJECT_H
#define C2DABSTRACTOBJECT_H

#include <typeinfo>

class AbstractObject
{
    friend class C2DFactory;
public:
    AbstractObject() { RefNum=1; }
private:
    virtual const std::type_info & GetType() = 0 ;

    int RefNum;
    const int & incr() { return ++RefNum; }
    const int & decr() { return --RefNum; }
};

template <class T> class TypedObject : public AbstractObject
{
public:
    const std::type_info & GetType() { return typeid(T); }
};
#endif // C2DABSTRACTOBJECT_H
