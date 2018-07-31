#ifndef C2DEXCHANGE_H
#define C2DEXCHANGE_H

#include <QDebug>
#include <QString>
#include <QVariant>

#include "C2DVariable.h"

#include "Unicus/Unicus.h"
//#include "Unicus/cGeometry.h"
class C2DExchange
{
public:

    C2DExchange()  {  }

    QList< C2DVariable * > variableList();
    void updateVariables( QHash< QString, QVariant > values );

    inline void setPrefix( const QString & prefix )  {  this->exchange_prefix = prefix;  }

    inline void addVariable( C2DVariable * variable )
    {  this->exchange_variables.insert( variable->name(), variable );  }

protected:

    inline int      I( const QString & name )  {  return this->Q< int > ( name );            }
    inline bool     B( const QString & name )  {  return this->Q< bool >( name );            }
    inline double   D( const QString & name )  {  return this->V( name ).toDouble();         }
    void   SetD( QString name, double val )    {  exchange_hash[name] = val;                 }
    inline QVariant V( const QString & name )  {  return this->exchange_hash.value( name );  }

    inline bool hashContains( const QString & name )
    {  return this->exchange_hash.contains( name );  }

    QHash< QString, QVariant > variables();


private:

    template < class T > T Q( const QString & name );

    virtual void requiredVariables() = 0;

    inline const QString & prefix()  { return this->exchange_prefix;  }

    QString                         exchange_prefix;
    QHash< QString, QVariant >      exchange_hash;
    QHash< QString, C2DVariable * > exchange_variables;

};

template < class T > T C2DExchange::Q( const QString & name )
{
    if ( ( this->exchange_hash.contains( name ) ) && qVariantCanConvert< T >( name ) )
            return qvariant_cast< T >( this->exchange_hash.value( name ) );
    else
    {
        if ( this->exchange_hash.contains( name ) )
            qWarning() << this->prefix() + " " + name + " not a type of "
                       << QVariant( T( 0.0f ) ).type();
        else
            qWarning() << this->prefix() + " Missed Variable " + name;

        return T( 0.0f );
    }
};

#endif // C2DEXCHANGE_H
