#include "C2DCommon.h"

void C2DCommon::writeData( QHash< QString, QVariant > data )
{
    this->changeState( true );

     qDebug() << "C2DCommon: writting data...";

    if ( this->dialog_busy )
    {
        QHashIterator< QString, QVariant > i( data );

        while( i.hasNext() )
        {
            i.next();

            qDebug() << "Writting: " << i.key() << i.value().toString();

            this->commonValue( i.key() ) = i.value();
        }
    }

    this->changeState( false );

    this->commonValuesChanged();


    qDebug() << "C2DCommon: writting done!";

    //Elasticas::Dialog::Accept();
}
