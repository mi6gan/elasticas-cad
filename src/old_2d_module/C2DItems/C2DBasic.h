#ifndef C2DBASIC_H
#define C2DBASIC_H

#include "../C2DModule/Frameworks/Items/include/C2DLibrary.h"

#include "Items/C2DStraightSkirt.h"
#include "Items/C2DFlaredSkirt.h"
#include "Items/C2DTulipSkirt.h"

class C2DBasic : public C2DLibrary
{
public:
    C2DBasic() : C2DLibrary( QString( "Basic library" ),
                             QString( "libc2dbasic.dll" ),
                             C2DLibrary::Items )
    {
        //this->addItem( new C2DStraightSkirt );
        this->addItem( new C2DFlaredSkirt );
        this->addItem( new C2DTulipSkirt );
    }
protected:
private:

};

#endif //C2DBASIC_H
