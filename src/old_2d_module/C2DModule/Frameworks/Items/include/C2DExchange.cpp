#include "C2DExchange.h"

QList< C2DVariable * > C2DExchange::variableList()
{
    QList< C2DVariable * > list;

    foreach ( C2DVariable * v, this->exchange_variables )
        list.append( v );

    return list;
}

void C2DExchange::updateVariables( QHash< QString, QVariant > values )
{
    Unicus::console( "Variable warnings", "start" );

    QHashIterator< QString, C2DVariable * > i( this->exchange_variables );
    C2DVariable * v = NULL;

    while ( i.hasNext() )
    {
        i.next();

        v = i.value();

        //qDebug() << i.key()
        //         << " : ("
        //         << v->common_name()
        //         << " ; "
        //         << v->default_value()
        //         << " )\n";

        if ( values.contains( v->common_name() ) )
        {
            if ( v->modifier() != 1.0f )
                this->exchange_hash.insert( i.key(), values.value( v->common_name() )
                                                    .toDouble() * v->modifier() );
            else
                this->exchange_hash.insert( i.key(), values.value( v->common_name() ) );

            qDebug() << i.key() + ": " << exchange_hash.value( i.key() );
        }
        else
        {
            this->exchange_hash.insert( i.key(), v->default_value() );

            qWarning() << this->prefix() + " "
                       << "Variable "
                       << i.key()
                       << " have no value and set to the default!";
       }
    }

    Unicus::console( "Variable warnings", "end" );
}
