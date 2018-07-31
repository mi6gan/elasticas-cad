#ifndef ELEXCEPTION_H
#define ELEXCEPTION_H
#include <exception>
#include <string>
#include <QtGlobal>
#ifdef WIN32
#ifdef BUILD_DLL
#define DLL_DECLSPEC __declspec(dllexport) 
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif
#else
#define DLL_DECLSPEC
#endif

namespace Elasticas
{

class DLL_DECLSPEC Exception: public std::exception
{
        std::string cwhat;
    public:
        Exception(const char* c="undefined Elasticas exception") throw();
        virtual ~Exception() throw();
        virtual const char* what() const throw();
};
}
#endif // ELEXCEPTION_H
