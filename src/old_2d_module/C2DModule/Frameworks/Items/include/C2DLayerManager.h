#ifndef C2DLAYERMANAGER_H
#define C2DLAYERMANAGER_H

#include <QMap>
#include <QMessageBox>

#include "C2DLayer.h"
#include "C2DManager.h"

class C2DLayerManager: public C2DManager
{
public:
    C2DLayerManager( QObject * parent = NULL );

    void AddDefaultLayer();

    void DeleteLayerByID( int id );

    void SetCurrentID( int );
    inline int GetCurrentID() const   {  return this->currentID;                  }

    inline C2DLayer * CurrentLayer()  {  return this->layers[ this->currentID ];  }
    inline C2DLayer * thick_solid()   {  return this->layers[ 0 ];                }
    inline C2DLayer * thick_dashed()  {  return this->layers[ 1 ];                }
    inline C2DLayer * bold_solid()    {  return this->layers[ 2 ];                }
    inline C2DLayer * thick_red()     {  return this->layers[ 3 ];                }
    inline C2DLayer * thick_yellow()  {  return this->layers[ 4 ];                }
    inline C2DLayer * thick_blue()    {  return this->layers[ 5 ];                }
    inline C2DLayer * thick_green()   {  return this->layers[ 6 ];                }

protected:
private:
    int ID, currentID;

    QMap< int, C2DLayer * > layers;
};

#endif // C2DLAYERMANAGER_H
