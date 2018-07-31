#ifndef C2DBLOUSE_H
#define C2DBLOUSE_H

#include "C2DBlouseDialog.h"
#include "../../C2DModule/Frameworks/Items/include/C2DItem.h"

class C2DBlouse : public C2DItem
{
public:
    C2DBlouse();

   void Update();
protected:
    void requiredVariables();
    void setVariables();
    void UpdatePoints();
    void DrawOnWidget();

};

#endif // C2DBlouse_H

