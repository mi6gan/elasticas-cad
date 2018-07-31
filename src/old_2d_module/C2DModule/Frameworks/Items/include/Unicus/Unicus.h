#ifndef LIBRARY_H
#define LIBRARY_H

//Library Global Definetions

#include <QtGlobal>

#include <math.h>
#include <iostream>

namespace Unicus
{
    //Precision: the number of signs after the decimal point in calculation result;
    const int p = 10;

    //Function to cut off numbers less then the precision number;
    inline qreal e10( qreal number )
    {  return ( fabs( number ) < pow( 10, -p ) ? 0 : number );  }

    inline void console( const char * name, double value )
    {
        #if defined( C2D_DEBUG )
            std::cout << name << " : " << value << " ;\n";
        #endif
    }

    inline void console( const char * name, const char * value )
    {
        #if defined( C2D_DEBUG )
            std::cout << name << " : " << value << " ;\n";
        #endif
    }
}

#endif // LIBRARY_H
