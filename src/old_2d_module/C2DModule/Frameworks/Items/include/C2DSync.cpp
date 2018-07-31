#include "C2DSync.h"

C2DSync::C2DSync( QHash< QString, QVariant > attr,
                  C2DLayer * l,
                  Border * b )
{
    this->sync_attributes = attr;
    this->sync_layer      = l;
    this->sync_border     = b;

    //qDebug() << "Attributes: " << attr;
}

C2DSync * Sync( QPair< QString, QVariant > pair_name,
                QPair< QString, QVariant > pair_type,
                QPair< QString, QVariant > pair_list,
                C2DLayer * layer,
                QPair< QString, QVariant > pair_first_custom_attribute,
                QPair< QString, QVariant > pair_second_custom_attribute )
{
    QHash< QString, QVariant > hash;

    hash.insert( pair_name.first,   pair_name.second );
    hash.insert( pair_type.first,   pair_type.second );
    hash.insert( pair_list.first,   pair_list.second );

    if ( pair_first_custom_attribute != pair_empty )
        hash.insert( pair_first_custom_attribute.first, pair_first_custom_attribute.second );

    if ( pair_second_custom_attribute != pair_empty )
        hash.insert( pair_second_custom_attribute.first, pair_second_custom_attribute.second );

    //qDebug() << "Type: " << pair_type.second;

    return new C2DSync( hash, layer );
}

Border * MakeBorder( QString next_true,
                     bool first,
                     bool cross,
                     QString next_false )
{
    return new Border( first, cross, next_true, next_false );
}

QStringList MakeList( const QString & s1,
                      const QString & s2,
                      const QString & s3,
                      const QString & s4,
                      const QString & s5,
                      const QString & s6,
                      const QString & s7,
                      const QString & s8 )
{
    QStringList List;
    if ( !s1.isEmpty() ) List.append( s1 );
    if ( !s2.isEmpty() ) List.append( s2 );
    if ( !s3.isEmpty() ) List.append( s3 );
    if ( !s4.isEmpty() ) List.append( s4 );
    if ( !s5.isEmpty() ) List.append( s5 );
    if ( !s6.isEmpty() ) List.append( s6 );
    if ( !s7.isEmpty() ) List.append( s7 );
    if ( !s8.isEmpty() ) List.append( s8 );
    return List;
}
