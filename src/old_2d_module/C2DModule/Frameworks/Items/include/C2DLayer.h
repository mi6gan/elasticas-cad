#ifndef C2DLAYER_H
#define C2DLAYER_H

#include <QPen>
#include <QFont>
#include <QHash>
#include <QDebug>
#include <QBrush>
#include <QString>
#include <QVariant>
#include <QMetaType>

#define LAYER_NAME         QString( "layer_name" )
#define LAYER_DESCRIPTION  QString( "layer_description" )
#define LAYER_PEN          QString( "layer_pen" )
#define LAYER_BRUSH        QString( "layer_brush" )
#define LAYER_LOCK         QString( "layer_lock" )
#define LAYER_VISIBLE      QString( "layer_visible" )

class C2DLayer
{
public:
    C2DLayer()
    {
        this->attributes.insert( LAYER_NAME, QString( "Default layer" ) );
        this->attributes.insert( LAYER_DESCRIPTION, QString( "Default description" ) );
        this->attributes.insert( LAYER_PEN, QPen() );
        this->attributes.insert( LAYER_BRUSH, QBrush() );
        this->attributes.insert( LAYER_LOCK, false );
        this->attributes.insert( LAYER_VISIBLE, true );
    }

    C2DLayer( const QString & name,
              const QString & description,
              const QPen    & pen,
              const QBrush  & brush,
                    bool      lock,
                    bool      visible )
    {
        this->attributes.insert( LAYER_NAME, name );
        this->attributes.insert( LAYER_DESCRIPTION, description );
        this->attributes.insert( LAYER_PEN, pen );
        this->attributes.insert( LAYER_BRUSH, brush );
        this->attributes.insert( LAYER_LOCK, lock );
        this->attributes.insert( LAYER_VISIBLE, visible );
    }

    C2DLayer( const C2DLayer & layer )
    {
        C2DLayer l = layer;
        this->attributes.insert( LAYER_NAME, l.name() );
        this->attributes.insert( LAYER_DESCRIPTION, l.description() );
        this->attributes.insert( LAYER_PEN, l.pen() );
        this->attributes.insert( LAYER_BRUSH, l.brush() );
        this->attributes.insert( LAYER_LOCK, l.lock() );
        this->attributes.insert( LAYER_VISIBLE, l.visible() );
    }

    ~C2DLayer()  {  }

    inline void setPen( const QPen & pen )        { this->attributes.insert( LAYER_PEN, pen );     }
    inline void setBrush( const QBrush & brush )  { this->attributes.insert( LAYER_BRUSH, brush ); }

    inline void setLock( bool lock )        {  this->attributes.insert( LAYER_LOCK, lock );        }
    inline void setVisible( bool visible )  {  this->attributes.insert( LAYER_VISIBLE, visible );  }

    inline QString name()         { return this->value< QString >( LAYER_NAME );        }
    inline QString description()  { return this->value< QString >( LAYER_DESCRIPTION ); }

    inline QPen   pen()    {  return this->value< QPen >( LAYER_PEN );                  }
    inline QBrush brush()  {  return this->value< QBrush >( LAYER_BRUSH );              }

    inline bool lock()     {  return this->value< bool >( LAYER_LOCK );                 }
    inline bool visible()  {  return this->value< bool >( LAYER_VISIBLE );              }

private:
    template < class T > T value( const QString & n )
    {
        return this->attributes.value( n ).value< T >();
    }

    QHash< QString, QVariant > attributes;
};

Q_DECLARE_METATYPE( C2DLayer );

#endif // C2DLAYER_H
