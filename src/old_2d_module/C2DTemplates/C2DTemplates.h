#ifndef C2DTEMPLATES_H
#define C2DTEMPLATES_H
#include <QGridLayout>
#include "../C2DModule/Frameworks/Items/include/C2DLibrary.h"

#include "Items/C2DPants.h"
//#include "Items/C2DSleeve.h"
#include "Items/C2DDress.h"
#include "Items/C2DBlouse.h"
#include "Items/C2DJacket.h"
#include "Items/C2DMensjacket.h"

class C2DTemplates : public C2DLibrary
{
public:
    C2DTemplates() : C2DLibrary( QString( "Templates library" ),
                             QString( "libc2dtemplates.dll" ),
                             C2DLibrary::Items )
    {
        this->addItem( new C2DPants );
        //this->addItem( new C2DSleeve );
        this->addItem( new C2DDress );
        this->addItem( new C2DBlouse );
        this->addItem( new C2DJacket );
        this->addItem( new C2DMensjacket );
    }
protected:
private:

};

#endif //C2DTEMPLATES_H
