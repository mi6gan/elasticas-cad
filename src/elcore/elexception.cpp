#include "elexception.h"
namespace Elasticas
{
Exception::Exception(const char* c) throw()
{
    this->cwhat=c;
}

Exception::~Exception() throw()
{
}

const char* Exception::what() const throw()
{
    return this->cwhat.c_str();
}
}
//________________________________________________________________________________
