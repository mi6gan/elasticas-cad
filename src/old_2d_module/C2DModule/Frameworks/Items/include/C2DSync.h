#ifndef C2DSYNC_H
#define C2DSYNC_H

#include <QPair>
#include <QHash>
#include <QDebug>
#include <QString>
#include <QVariant>

#include "C2DLayer.h"

#define SYNC_NAME        QString( "sync_name"   )
#define SYNC_TYPE        QString( "sync_type"   )
#define SYNC_LIST        QString( "sync_list"   )
#define SYNC_LAYER       QString( "sync_layer"  )
#define SYNC_RADIUS      QString( "sync_radius" )
#define SYNC_SIGN_DUAL   QString( "sync_sign_dual" )
#define SYNC_SIGN_ANGLE  QString( "sync_sign_angle" )
#define SYNC_BADPATH_DUAL   QString( "sync_path_dual" )
#define SYNC_BADPATH_ANGLE  QString( "sync_path_angle" )
#define PATH_QPAINTER    QString( "path_qpainter" )

#define pair_empty        QPair< QString, QVariant >()
#define attr( name, var ) QPair< QString, QVariant >( name, var )

class Border
{
public:
    Border( bool f, bool c, QString n_true, QString n_false )
        : border_first( f ), border_cross( c ),
          border_next_true( n_true ), border_next_false( n_false ) {  }

    inline void setCross( bool c )  {  this->border_cross = c;     }
    inline bool isFirst()           {  return this->border_first;  }

    inline QString whichNext()  {  return ( this->border_cross ) ?
                                   this->border_next_true : this->border_next_false;  }

private:
    bool    border_first;
    bool    border_cross;
    QString border_next_true;
    QString border_next_false;
};

class C2DSync
{
public:
    enum Type { Point, Sign, Line , Circle , Arc , Spline, Dart, BadPath, Ppath, Button };

    C2DSync( QHash< QString, QVariant > attributes, C2DLayer * l, Border * b = NULL );

    inline QString       name()        {  return this->value< QString >( SYNC_NAME );        }
    inline C2DSync::Type type()        {  return ( Type )( this->value< int >( SYNC_TYPE ) );  }
    inline double        radius()      {  return this->value< double >( SYNC_RADIUS );       }
    inline QStringList   list()        {  return this->value< QStringList >( SYNC_LIST );    }
    inline C2DLayer *    layer()       {  return this->sync_layer;                           }

    inline void setProperty( const QString & name, const QVariant & value )
    {
        this->sync_attributes.insert( name, value );
    }

    template < class T > T property( const QString & name )
    {
        //qDebug() << "C2DSync::property() - " << name << " : " << this->value< T >( name );
        return this->value< T >( name );
    }

private:
    template < class T > inline T value( const QString & name )
    {
//        qDebug() << "C2DSync::"
//                 << name
//                 << " : " << this->sync_attributes.value( name )
//                 << this->sync_attributes.value( name ).value< T >();
        return this->sync_attributes.value( name ).value< T >();
    }

    C2DLayer                   * sync_layer;
    Border                     * sync_border;
    QHash< QString, QVariant >   sync_attributes;
};

Q_DECLARE_METATYPE( C2DSync::Type );

C2DSync * Sync( QPair< QString, QVariant > pair_name,
                QPair< QString, QVariant > pair_type,
                QPair< QString, QVariant > pair_list,
                C2DLayer * layer,
                QPair< QString, QVariant > pair_first_custom_attribute = pair_empty,
                QPair< QString, QVariant > pair_second_custom_attribute = pair_empty );

Border * MakeBorder( QString next_true,
                     bool    first = false,
                     bool    cross = true,
                     QString next_false = QString( "" ) );

QStringList MakeList( const QString & s1,
                      const QString & s2 = QString( "" ),
                      const QString & s3 = QString( "" ),
                      const QString & s4 = QString( "" ),
                      const QString & s5 = QString( "" ),
                      const QString & s6 = QString( "" ),
                      const QString & s7 = QString( "" ),
                      const QString & s8 = QString( "" ) );

#endif // C2DSYNC_H
