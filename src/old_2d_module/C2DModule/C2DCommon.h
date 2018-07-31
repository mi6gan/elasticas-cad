#ifndef C2DCOMMON_H
#define C2DCOMMON_H

#include <QHashIterator>

#include "elcore/elbasicdialogs.h"

class C2DCommon : public Elasticas::Dialog
{

    Q_OBJECT

public:

    C2DCommon() : Elasticas::Dialog( QString( "Common dialog" ) ), dialog_busy( false )  {  }

    ~C2DCommon()  {  }

signals:
    bool state( bool busy );

public slots:

    void writeData( QHash< QString, QVariant > data );

    inline void accept()  {  }
    inline void apply()   {  }
    inline void reject()  {  }
    inline void reset()   {  }
    inline void cancel()  {  }
    inline void exec()  {  }

private:

    bool changeState( bool state )  { this->dialog_busy = state; this->state( state );  }

    bool dialog_busy;

};

#endif // C2DCOMMON_H
