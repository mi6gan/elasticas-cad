#ifndef C2DLIBRARY_H
#define C2DLIBRARY_H

#include <QList>
#include <QString>
#include "C2DItem.h"

class C2DLibrary
{
public:
    enum Type { Items, Export, Composit };

    C2DLibrary( const QString & name, const QString & filename, const Type & type )
        : libname( name ), libfilename( filename ), libtype( type )  {  }
    ~C2DLibrary()  {  }

    inline    const QString & name()   {  return this->libname;   }
    inline             Type   type()   {  return this->libtype;   }
    inline QList< C2DItem * > items()  {  return this->libitems;  }

protected:
    void addItem( C2DItem * item )  {  this->libitems.append( item );  }

private:
    QString libname;
    QString libfilename;
    Type libtype;

    QList< C2DItem * > libitems;
};

extern "C" C2DLibrary * library();

#endif //C2DLIBRARY_H
